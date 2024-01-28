#include "game/objsub.h"
#include "game/gamework_data.h"
#include "game/object.h"

MgInfo mgInfoTbl[] = {
    {
        9, // ovl
        0, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x170001, // name_mess
        0x200000, // data_dir
        0x160000, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160000, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210000, // rules_mess
        0x210001, // control_mess[0]
        0, // control_mess[1]
        0x210003, // advice_mess
    },
    {
        10, // ovl
        0, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x170002, // name_mess
        0x210000, // data_dir
        0x160001, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160001, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210004, // rules_mess
        0x210005, // control_mess[0]
        0, // control_mess[1]
        0x210007, // advice_mess
    },
    {
        11, // ovl
        0, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x170003, // name_mess
        0x220000, // data_dir
        0x160002, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160002, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210008, // rules_mess
        0x210009, // control_mess[0]
        0, // control_mess[1]
        0x21000B, // advice_mess
    },
    {
        12, // ovl
        4, // type
        2, // flag
        65280, // unk_4
        0, // unk_6
        0x170004, // name_mess
        0x230000, // data_dir
        0x160003, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160003, // mg_pic
        0, // unk_20
        0, // unk_24
        0x21000C, // rules_mess
        0x21000D, // control_mess[0]
        0, // control_mess[1]
        0x21000F, // advice_mess
    },
    {
        13, // ovl
        0, // type
        2, // flag
        0, // unk_4
        0, // unk_6
        0x170005, // name_mess
        0x240000, // data_dir
        0x160004, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160004, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210010, // rules_mess
        0x210011, // control_mess[0]
        0, // control_mess[1]
        0x210013, // advice_mess
    },
    {
        14, // ovl
        0, // type
        2, // flag
        65280, // unk_4
        0, // unk_6
        0x170006, // name_mess
        0x250000, // data_dir
        0x160005, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160005, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210014, // rules_mess
        0x210015, // control_mess[0]
        0, // control_mess[1]
        0x210017, // advice_mess
    },
    {
        15, // ovl
        0, // type
        3, // flag
        256, // unk_4
        0, // unk_6
        0x170007, // name_mess
        0x260000, // data_dir
        0x160006, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160006, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210018, // rules_mess
        0x210019, // control_mess[0]
        0, // control_mess[1]
        0x21001B, // advice_mess
    },
    {
        16, // ovl
        0, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x170008, // name_mess
        0x270000, // data_dir
        0x160007, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160007, // mg_pic
        0, // unk_20
        0, // unk_24
        0x21001C, // rules_mess
        0x21001D, // control_mess[0]
        0, // control_mess[1]
        0x21001F, // advice_mess
    },
    {
        17, // ovl
        0, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x170009, // name_mess
        0x280000, // data_dir
        0x160008, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160008, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210020, // rules_mess
        0x210021, // control_mess[0]
        0, // control_mess[1]
        0x210023, // advice_mess
    },
    {
        18, // ovl
        0, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x17000A, // name_mess
        0x290000, // data_dir
        0x160009, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160009, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210024, // rules_mess
        0x210025, // control_mess[0]
        0, // control_mess[1]
        0x210027, // advice_mess
    },
    {
        19, // ovl
        0, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x17000B, // name_mess
        0x2A0000, // data_dir
        0x16000A, // inst_pic
        0x16000B, // unk_14
        0x16000C, // unk_18
        0x16003E, // mg_pic
        0x16000B, // unk_20
        0x16000C, // unk_24
        0x210028, // rules_mess
        0x210029, // control_mess[0]
        0, // control_mess[1]
        0x21002B, // advice_mess
    },
    {
        20, // ovl
        0, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x17000C, // name_mess
        0x2B0000, // data_dir
        0x16000D, // inst_pic
        0, // unk_14
        0, // unk_18
        0x16000D, // mg_pic
        0, // unk_20
        0, // unk_24
        0x21002C, // rules_mess
        0x21002D, // control_mess[0]
        0, // control_mess[1]
        0x21002F, // advice_mess
    },
    {
        21, // ovl
        0, // type
        2, // flag
        65280, // unk_4
        0, // unk_6
        0x17000D, // name_mess
        0x2C0000, // data_dir
        0x16000E, // inst_pic
        0, // unk_14
        0, // unk_18
        0x16003F, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210030, // rules_mess
        0x210031, // control_mess[0]
        0, // control_mess[1]
        0x210033, // advice_mess
    },
    {
        22, // ovl
        0, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x17000E, // name_mess
        0x2D0000, // data_dir
        0x16000F, // inst_pic
        0, // unk_14
        0, // unk_18
        0x16000F, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210034, // rules_mess
        0x210035, // control_mess[0]
        0, // control_mess[1]
        0x210037, // advice_mess
    },
    {
        23, // ovl
        0, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x17000F, // name_mess
        0x2E0000, // data_dir
        0x160010, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160010, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210038, // rules_mess
        0x210039, // control_mess[0]
        0, // control_mess[1]
        0x21003B, // advice_mess
    },
    {
        24, // ovl
        1, // type
        1, // flag
        65280, // unk_4
        0, // unk_6
        0x170010, // name_mess
        0x2F0000, // data_dir
        0x160011, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160011, // mg_pic
        0, // unk_20
        0, // unk_24
        0x21003C, // rules_mess
        0x21003D, // control_mess[0]
        0x21003E, // control_mess[1]
        0x21003F, // advice_mess
    },
    {
        25, // ovl
        1, // type
        1, // flag
        65280, // unk_4
        0, // unk_6
        0x170011, // name_mess
        0x300000, // data_dir
        0x160012, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160012, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210040, // rules_mess
        0x210041, // control_mess[0]
        0x210042, // control_mess[1]
        0x210043, // advice_mess
    },
    {
        26, // ovl
        1, // type
        1, // flag
        65280, // unk_4
        0, // unk_6
        0x170012, // name_mess
        0x310000, // data_dir
        0x160013, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160013, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210044, // rules_mess
        0x210045, // control_mess[0]
        0x210046, // control_mess[1]
        0x210047, // advice_mess
    },
    {
        27, // ovl
        1, // type
        1, // flag
        65280, // unk_4
        0, // unk_6
        0x170013, // name_mess
        0x320000, // data_dir
        0x160014, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160014, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210048, // rules_mess
        0x210049, // control_mess[0]
        0x21004A, // control_mess[1]
        0x21004B, // advice_mess
    },
    {
        28, // ovl
        1, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170014, // name_mess
        0x330000, // data_dir
        0x160015, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160015, // mg_pic
        0, // unk_20
        0, // unk_24
        0x21004C, // rules_mess
        0x21004D, // control_mess[0]
        0x21004E, // control_mess[1]
        0x21004F, // advice_mess
    },
    {
        29, // ovl
        1, // type
        1, // flag
        65280, // unk_4
        0, // unk_6
        0x170015, // name_mess
        0x340000, // data_dir
        0x160016, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160016, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210050, // rules_mess
        0x210051, // control_mess[0]
        0x210052, // control_mess[1]
        0x210053, // advice_mess
    },
    {
        30, // ovl
        1, // type
        1, // flag
        65280, // unk_4
        0, // unk_6
        0x170016, // name_mess
        0x350000, // data_dir
        0x160017, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160017, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210054, // rules_mess
        0x210055, // control_mess[0]
        0x210056, // control_mess[1]
        0x210057, // advice_mess
    },
    {
        31, // ovl
        1, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170017, // name_mess
        0x360000, // data_dir
        0x160018, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160018, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210058, // rules_mess
        0x210059, // control_mess[0]
        0x21005A, // control_mess[1]
        0x21005B, // advice_mess
    },
    {
        32, // ovl
        1, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170018, // name_mess
        0x370000, // data_dir
        0x160019, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160019, // mg_pic
        0, // unk_20
        0, // unk_24
        0x21005C, // rules_mess
        0x21005D, // control_mess[0]
        0x21005E, // control_mess[1]
        0x21005F, // advice_mess
    },
    {
        33, // ovl
        2, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x170019, // name_mess
        0x380000, // data_dir
        0x16001A, // inst_pic
        0, // unk_14
        0, // unk_18
        0x16001A, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210060, // rules_mess
        0x210061, // control_mess[0]
        0, // control_mess[1]
        0x210063, // advice_mess
    },
    {
        34, // ovl
        2, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x17001A, // name_mess
        0x390000, // data_dir
        0x16001B, // inst_pic
        0, // unk_14
        0, // unk_18
        0x16001B, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210064, // rules_mess
        0x210065, // control_mess[0]
        0, // control_mess[1]
        0x210067, // advice_mess
    },
    {
        35, // ovl
        2, // type
        2, // flag
        512, // unk_4
        0, // unk_6
        0x17001B, // name_mess
        0x3A0000, // data_dir
        0x16001C, // inst_pic
        0, // unk_14
        0, // unk_18
        0x16001C, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210068, // rules_mess
        0x210069, // control_mess[0]
        0, // control_mess[1]
        0x21006B, // advice_mess
    },
    {
        36, // ovl
        2, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x17001C, // name_mess
        0x3B0000, // data_dir
        0x16001D, // inst_pic
        0, // unk_14
        0, // unk_18
        0x16001D, // mg_pic
        0, // unk_20
        0, // unk_24
        0x21006C, // rules_mess
        0x21006D, // control_mess[0]
        0, // control_mess[1]
        0x21006F, // advice_mess
    },
    {
        37, // ovl
        2, // type
        2, // flag
        65280, // unk_4
        0, // unk_6
        0x17001D, // name_mess
        0x3C0000, // data_dir
        0x16001E, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160040, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210070, // rules_mess
        0x210071, // control_mess[0]
        0, // control_mess[1]
        0x210073, // advice_mess
    },
    {
        38, // ovl
        2, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x17001E, // name_mess
        0x3D0000, // data_dir
        0x16001F, // inst_pic
        0, // unk_14
        0, // unk_18
        0x16001F, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210074, // rules_mess
        0x210075, // control_mess[0]
        0x210076, // control_mess[1]
        0x210077, // advice_mess
    },
    {
        39, // ovl
        2, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x17001F, // name_mess
        0x3E0000, // data_dir
        0x160020, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160020, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210078, // rules_mess
        0x210079, // control_mess[0]
        0, // control_mess[1]
        0x21007B, // advice_mess
    },
    {
        40, // ovl
        2, // type
        3, // flag
        768, // unk_4
        0, // unk_6
        0x170020, // name_mess
        0x3F0000, // data_dir
        0x160021, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160021, // mg_pic
        0, // unk_20
        0, // unk_24
        0x21007C, // rules_mess
        0x21007D, // control_mess[0]
        0x21007E, // control_mess[1]
        0x21007F, // advice_mess
    },
    {
        41, // ovl
        7, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x170021, // name_mess
        0x400000, // data_dir
        0x160022, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160022, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210080, // rules_mess
        0x37001F, // control_mess[0]
        0, // control_mess[1]
        0x210083, // advice_mess
    },
    {
        42, // ovl
        2, // type
        2, // flag
        65280, // unk_4
        0, // unk_6
        0x170022, // name_mess
        0x410000, // data_dir
        0x160023, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160023, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210084, // rules_mess
        0x210085, // control_mess[0]
        0, // control_mess[1]
        0x210087, // advice_mess
    },
    {
        43, // ovl
        3, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x170023, // name_mess
        0x420000, // data_dir
        0x160024, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160024, // mg_pic
        0, // unk_20
        0, // unk_24
        0, // rules_mess
        0x210089, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        44, // ovl
        3, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x170024, // name_mess
        0x430000, // data_dir
        0x160025, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160025, // mg_pic
        0, // unk_20
        0, // unk_24
        0, // rules_mess
        0x21008D, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        45, // ovl
        3, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x170025, // name_mess
        0x440000, // data_dir
        0x160026, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160026, // mg_pic
        0, // unk_20
        0, // unk_24
        0, // rules_mess
        0x210091, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        46, // ovl
        4, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x170026, // name_mess
        0x450000, // data_dir
        0x160027, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160027, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210094, // rules_mess
        0x210095, // control_mess[0]
        0, // control_mess[1]
        0x210097, // advice_mess
    },
    {
        47, // ovl
        4, // type
        2, // flag
        65280, // unk_4
        0, // unk_6
        0x170027, // name_mess
        0x460000, // data_dir
        0x160028, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160028, // mg_pic
        0, // unk_20
        0, // unk_24
        0x210098, // rules_mess
        0x210099, // control_mess[0]
        0, // control_mess[1]
        0x21009B, // advice_mess
    },
    {
        48, // ovl
        4, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x170028, // name_mess
        0x470000, // data_dir
        0x160029, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160029, // mg_pic
        0, // unk_20
        0, // unk_24
        0x21009C, // rules_mess
        0x21009D, // control_mess[0]
        0, // control_mess[1]
        0x21009F, // advice_mess
    },
    {
        49, // ovl
        4, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x170029, // name_mess
        0x480000, // data_dir
        0x16002A, // inst_pic
        0, // unk_14
        0, // unk_18
        0x16002A, // mg_pic
        0, // unk_20
        0, // unk_24
        0x2100A0, // rules_mess
        0x2100A1, // control_mess[0]
        0, // control_mess[1]
        0x2100A3, // advice_mess
    },
    {
        50, // ovl
        7, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x17002A, // name_mess
        0x490000, // data_dir
        0x16002B, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160041, // mg_pic
        0, // unk_20
        0, // unk_24
        0x2100A4, // rules_mess
        0x370010, // control_mess[0]
        0, // control_mess[1]
        0x2100A7, // advice_mess
    },
    {
        51, // ovl
        0, // type
        2, // flag
        1280, // unk_4
        0, // unk_6
        0x17002B, // name_mess
        0x4A0000, // data_dir
        0x16002C, // inst_pic
        0, // unk_14
        0, // unk_18
        0x16002C, // mg_pic
        0, // unk_20
        0, // unk_24
        0x2100A8, // rules_mess
        0x2100A9, // control_mess[0]
        0, // control_mess[1]
        0x2100AB, // advice_mess
    },
    {
        52, // ovl
        5, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x17002C, // name_mess
        0x4B0000, // data_dir
        0x16002D, // inst_pic
        0, // unk_14
        0, // unk_18
        0x16002D, // mg_pic
        0, // unk_20
        0, // unk_24
        0, // rules_mess
        0, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        53, // ovl
        6, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x17002D, // name_mess
        0x4C0000, // data_dir
        0x16002E, // inst_pic
        0, // unk_14
        0, // unk_18
        0x16002E, // mg_pic
        0, // unk_20
        0, // unk_24
        0x2100AC, // rules_mess
        0x2100AD, // control_mess[0]
        0, // control_mess[1]
        0x2100AF, // advice_mess
    },
    {
        54, // ovl
        6, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x17002E, // name_mess
        0x4D0000, // data_dir
        0x16002F, // inst_pic
        0, // unk_14
        0, // unk_18
        0x16002F, // mg_pic
        0, // unk_20
        0, // unk_24
        0x2100B0, // rules_mess
        0x2100B1, // control_mess[0]
        0, // control_mess[1]
        0x2100B3, // advice_mess
    },
    {
        55, // ovl
        6, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x17002F, // name_mess
        0x4E0000, // data_dir
        0x160030, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160030, // mg_pic
        0, // unk_20
        0, // unk_24
        0x2100B4, // rules_mess
        0x2100B5, // control_mess[0]
        0, // control_mess[1]
        0x2100B7, // advice_mess
    },
    {
        56, // ovl
        6, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170030, // name_mess
        0x4F0000, // data_dir
        0x160031, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160031, // mg_pic
        0, // unk_20
        0, // unk_24
        0x2100B8, // rules_mess
        0x2100B9, // control_mess[0]
        0, // control_mess[1]
        0x2100BB, // advice_mess
    },
    {
        57, // ovl
        6, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170031, // name_mess
        0x500000, // data_dir
        0x160032, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160032, // mg_pic
        0, // unk_20
        0, // unk_24
        0x2100BC, // rules_mess
        0x2100BD, // control_mess[0]
        0, // control_mess[1]
        0x2100BF, // advice_mess
    },
    {
        58, // ovl
        8, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170032, // name_mess
        0x510000, // data_dir
        0x160033, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160033, // mg_pic
        0, // unk_20
        0, // unk_24
        0x2100C0, // rules_mess
        0x2100C1, // control_mess[0]
        0, // control_mess[1]
        0x2100C3, // advice_mess
    },
    {
        59, // ovl
        7, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170033, // name_mess
        0x520000, // data_dir
        0x160034, // inst_pic
        0x160035, // unk_14
        0x160036, // unk_18
        0x160034, // mg_pic
        0x160035, // unk_20
        0x160036, // unk_24
        0x2100C4, // rules_mess
        0x37000D, // control_mess[0]
        0, // control_mess[1]
        0x2100C7, // advice_mess
    },
    {
        58, // ovl
        7, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170033, // name_mess
        0x510000, // data_dir
        0x160037, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160037, // mg_pic
        0, // unk_20
        0, // unk_24
        0, // rules_mess
        0, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        60, // ovl
        7, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170034, // name_mess
        0x510000, // data_dir
        0x160032, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160032, // mg_pic
        0, // unk_20
        0, // unk_24
        0x2100C8, // rules_mess
        0x37000A, // control_mess[0]
        0, // control_mess[1]
        0x2100CB, // advice_mess
    },
    {
        58, // ovl
        7, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170033, // name_mess
        0x510000, // data_dir
        0x160037, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160037, // mg_pic
        0, // unk_20
        0, // unk_24
        0, // rules_mess
        0, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        61, // ovl
        4, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x170035, // name_mess
        0x540000, // data_dir
        0x160038, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160038, // mg_pic
        0, // unk_20
        0, // unk_24
        0x2100CC, // rules_mess
        0x2100CD, // control_mess[0]
        0, // control_mess[1]
        0x2100CF, // advice_mess
    },
    {
        62, // ovl
        0, // type
        3, // flag
        65280, // unk_4
        0, // unk_6
        0x170036, // name_mess
        0x550000, // data_dir
        0x160039, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160039, // mg_pic
        0, // unk_20
        0, // unk_24
        0x2100D0, // rules_mess
        0x2100D1, // control_mess[0]
        0, // control_mess[1]
        0x2100D3, // advice_mess
    },
    {
        63, // ovl
        8, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170037, // name_mess
        0x560000, // data_dir
        0x16003A, // inst_pic
        0, // unk_14
        0, // unk_18
        0x16003A, // mg_pic
        0, // unk_20
        0, // unk_24
        0, // rules_mess
        0, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        64, // ovl
        8, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170038, // name_mess
        0x570000, // data_dir
        0x16003B, // inst_pic
        0, // unk_14
        0, // unk_18
        0x16003B, // mg_pic
        0, // unk_20
        0, // unk_24
        0, // rules_mess
        0, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        65, // ovl
        7, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170038, // name_mess
        0x570000, // data_dir
        0x160032, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160032, // mg_pic
        0, // unk_20
        0, // unk_24
        0, // rules_mess
        0x370013, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        66, // ovl
        7, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170038, // name_mess
        0x570000, // data_dir
        0x160032, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160032, // mg_pic
        0, // unk_20
        0, // unk_24
        0, // rules_mess
        0x370016, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        67, // ovl
        7, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170038, // name_mess
        0x570000, // data_dir
        0x160032, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160032, // mg_pic
        0, // unk_20
        0, // unk_24
        0, // rules_mess
        0x370019, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        68, // ovl
        7, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170038, // name_mess
        0x570000, // data_dir
        0x160032, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160032, // mg_pic
        0, // unk_20
        0, // unk_24
        0, // rules_mess
        0x37001C, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        69, // ovl
        7, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0x170038, // name_mess
        0x570000, // data_dir
        0x160032, // inst_pic
        0, // unk_14
        0, // unk_18
        0x160032, // mg_pic
        0, // unk_20
        0, // unk_24
        0, // rules_mess
        0x370007, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        0xFFFF, // ovl
        0, // type
        0, // flag
        65280, // unk_4
        0, // unk_6
        0, // name_mess
        0, // data_dir
        0, // inst_pic
        0, // unk_14
        0, // unk_18
        0, // mg_pic
        0, // unk_20
        0, // unk_24
        0, // rules_mess
        0, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
};

void MGSeqPracticeExitCheck(omObjData*);

s16 mgTypeCurr;
s16 mgBattleStar[4];
s16 mgBattleStarMax;
u8 lbl_801D3E94;
s32 mgRecordExtra;
s32 mgQuitExtraF;
s32 mgPracticeEnableF;
s32 mgInstExitEnableF;
u8 mgBoardHostEnableF;

s16 mgTicTacToeGrid[3][3];
u8 mgIndexList[256];
GameStat mgGameStatBackup;

s16 omGetMGIndex(s16 overlay) {
    s32 i;
    MgInfo *info;

    info = mgInfoTbl;
    
    for (i = 0; info->ovl != 0xFFFF; i++) {
        if (info->ovl == overlay) {
            return i;
        }
        info++;
    }

    return -1;
}

void omGameSysInit(Process *objman) {
    s32 i;
    omObjData* obj;

    omSystemKeyCheckSetup(objman);
    Hu3DCameraScissorSet(1, 0, 0, 0x280, 0x1E0);
    omSysPauseEnable(0);
    
    for (i = 0; i < 4; i++) {
        if (_CheckFlag(0x1000C) == 0) {
            GWPlayer[i].coins_mg_gain = 0;
        }
        
        GWPlayer[i].unk_26 = 0;
    }
    
    if (mgPracticeEnableF != 0) {
        obj = omAddObjEx(objman, 0x7FDC, 0, 0, -1, MGSeqPracticeExitCheck);
        omSetStatBit(obj, 0xA0U);
    }
}

void omVibrate(s16 player, s16 duration, s16 off, s16 on) {
    s32 rumble = GWGameStat.rumble;
    
    if (rumble != 0 && GWPlayerCfg[player].iscom == 0) {
        HuPadRumbleSet(GWPlayerCfg[player].pad_idx, duration, off, on);
    }
}
