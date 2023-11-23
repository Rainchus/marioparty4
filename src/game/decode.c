#include "common.h"
#include "dolphin/os.h"

struct decode_data
{
    u8 *src;
    u8 *dst;
    u32 size;
};

static u8 TextBuffer[1024];

static void HuDecodeNone(struct decode_data *decode)
{
    while(decode->size) {
        *decode->dst++ = *decode->src++;
        decode->size--;
    }
}

static void HuDecodeLz(struct decode_data *decode)
{
    u16 flag, pos;
    int i, j, copy_len;
    flag = 0;
    pos = 958;
    
    
    for(i=0; i<1024; i++) {
        TextBuffer[i] = 0;
    }
    while(decode->size) {
        flag >>= 1;
        if(!(flag & 0x100)) {
            flag = (*decode->src++)|0xFF00;
        }
        if(flag & 0x1) {
            TextBuffer[pos++] = *decode->dst++ = *decode->src++;
            pos = pos & 0x3FF;
            decode->size--;
        } else {
            i = *decode->src++;
            copy_len = *decode->src++;
            i |= ((copy_len & ~0x3F) << 2);
            copy_len = (copy_len & 0x3F)+3;
            for(j=0; j<copy_len; j++) {
                TextBuffer[pos++] = *decode->dst++ = TextBuffer[(i+j) & 0x3FF];
                pos &= 0x3FF;
            }
            decode->size -= j;
        }
    }
}

static inline void SlideReadHeader(struct decode_data *decode)
{
    int size;
    size = (*decode->src++) << 24;
    size += (*decode->src++) << 16;
    size += (*decode->src++) << 8;
    size += *decode->src++;
}

static void HuDecodeSlide(struct decode_data *decode)
{
    u8 *base_dst;
    u32 num_bits, flag;
    SlideReadHeader(decode);
    num_bits = 0;
    flag = 0;
    base_dst = decode->dst;
    while(decode->size) {
        if(num_bits == 0) {
            flag = (*decode->src++) << 24;
            flag += (*decode->src++) << 16;
            flag += (*decode->src++) << 8;
            flag += *decode->src++;
            num_bits = 32;
        }
        if(flag >> 31) {
            *decode->dst++ = (int)*decode->src++;
            decode->size--;
        } else {
            u8 *src;
            u32 dist, len;
            dist = *decode->src++ << 8;
            dist += *decode->src++;
            len = (dist >> 12) & 0xF;
            dist &= 0xFFF;
            src = decode->dst-dist;
            if(len == 0) {
                len = (*decode->src++)+18;
            } else {
                len += 2;
            }
            decode->size -= len;
            while(len) {
                if(src-1 < base_dst) {
                    *decode->dst++ = 0;
                } else {
                    *decode->dst++ = src[-1];
                }
                len--;
                src++;
            }
        }
        
        flag <<= 1;
        num_bits--;
    }
}

static void HuDecodeFslide(struct decode_data *decode)
{
    u32 num_bits, flag;
    SlideReadHeader(decode);
    num_bits = 0;
    flag = 0;
    while(decode->size) {
        if(num_bits == 0) {
            flag = (*decode->src++) << 24;
            flag += (*decode->src++) << 16;
            flag += (*decode->src++) << 8;
            flag += *decode->src++;
            num_bits = 32;
        }
        if(flag >> 31) {
            *decode->dst++ = (int)*decode->src++;
            decode->size--;
        } else {
            u8 *src;
            u32 dist, len;
            dist = *decode->src++ << 8;
            dist += *decode->src++;
            len = (dist >> 12) & 0xF;
            dist &= 0xFFF;
            src = decode->dst-dist;
            if(len == 0) {
                len = (*decode->src++)+18;
            } else {
                len += 2;
            }
            decode->size -= len;
            while(len) {
                *decode->dst++ = src[-1];
                len--;
                src++;
            }
        }
        
        flag <<= 1;
        num_bits--;
    }
}

static void HuDecodeRle(struct decode_data *decode)
{
    int i;
    while(decode->size) {
        int size = *decode->src++;
        if(size < 128) {
            int fill = *decode->src++;
            for(i=0; i<size; i++) {
                *decode->dst++ = fill;
            }
        } else {
            size -= 128;
            for(i=0; i<size; i++) {
                *decode->dst++ = *decode->src++;
            }
        }
        decode->size -= size;
    }
}

void HuDecodeData(void *src, void *dst, u32 size, int decode_type)
{
    struct decode_data decode;
    struct decode_data *decode_ptr = &decode;
    decode_ptr->src = src;
    decode_ptr->dst = dst;
    decode_ptr->size = size;
    switch(decode_type) {
        case 0:
            HuDecodeNone(decode_ptr);
            break;
            
        case 1:
            HuDecodeLz(decode_ptr);
            break;
            
        case 2:
            HuDecodeSlide(decode_ptr);
            break;
            
        case 3:
            HuDecodeFslide(decode_ptr);
            break;
            
        case 4:
            HuDecodeFslide(decode_ptr);
            break;
            
        case 5:
            HuDecodeRle(decode_ptr);
            break;
            
        default:
            OSReport("decode tyep unknown.(%x)\n", decode_type);
            break;
    }
    DCFlushRange(dst, size);
}