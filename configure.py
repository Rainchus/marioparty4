#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import sys
import argparse

from pathlib import Path
from tools.project import (
    Object,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "GMPE01_00",  # USA 1.0
]

if len(VERSIONS) > 1:
    versions_str = ", ".join(VERSIONS[:-1]) + f" or {VERSIONS[-1]}"
else:
    versions_str = VERSIONS[0]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    default="configure",
    help="configure or progress (default: configure)",
    nargs="?",
)
parser.add_argument(
    "--version",
    dest="version",
    default=VERSIONS[DEFAULT_VERSION],
    help=f"version to build ({versions_str})",
)
parser.add_argument(
    "--build-dir",
    dest="build_dir",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--compilers",
    dest="compilers",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    dest="map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    dest="debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        dest="wrapper",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--build-dtk",
    dest="build_dtk",
    type=Path,
    help="path to decomp-toolkit source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    dest="sjiswrap",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--verbose",
    dest="verbose",
    action="store_true",
    help="print verbose output",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = args.version.upper()
if config.version not in VERSIONS:
    sys.exit(f"Invalid version '{config.version}', expected {versions_str}")
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.build_dtk_path = args.build_dtk
config.compilers_path = args.compilers
config.debug = args.debug
config.generate_map = args.map
config.sjiswrap_path = args.sjiswrap
if not is_windows():
    config.wrapper = args.wrapper

# Tool versions
config.compilers_tag = "20231018"
config.dtk_tag = "v0.6.3"
config.sjiswrap_tag = "v1.1.1"
config.wibo_tag = "0.6.3"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    # "-W all",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    "-i include",
    f"-i build/{config.version}/include",
    "-multibyte",
    f"-DVERSION={version_num}",
]

# Debug flags
if config.debug:
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-common off",
    "-inline auto,deferred",
]

# REL flags
cflags_rel = [
    *cflags_base,
    "-O0,p",
    "-enum int",
    "-char unsigned",
    "-fp_contract off",
    "-sdata 0",
    "-sdata2 0",
    "-pool off",
]

# Game flags
cflags_game = [
    *cflags_base,
    "-O0,p",
    "-enum int",
    "-char unsigned",
    "-fp_contract off",
]


config.linker_version = "GC/2.6"
config.rel_strip_partial = False
config.rel_empty_file = "REL/empty.c"


# Helper function for Dolphin libraries
def DolphinLib(lib_name, objects):
    return {
        "lib": lib_name,
        "mw_version": "GC/2.6",
        "cflags": cflags_base,
        "host": False,
        "objects": objects,
    }


# Helper function for REL script objects
def Rel(lib_name, objects):
    return {
        "lib": lib_name,
        "mw_version": "GC/2.6",
        "cflags": cflags_rel,
        "host": True,
        "objects": objects,
    }


Matching = True
NonMatching = False

config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "Game",
        "mw_version": config.linker_version,
        "cflags": cflags_game,
        "host": False,
        "objects": [
            Object(NonMatching, "game/main.c"),
            Object(NonMatching, "game/pad.c"),
            Object(Matching, "game/dvd.c"),
            Object(NonMatching, "game/data.c"),
            Object(Matching, "game/decode.c"),
            Object(Matching, "game/font.c"),
            Object(Matching, "game/init.c"),
            Object(NonMatching, "game/jmp.c"),
            Object(Matching, "game/malloc.c"),
            Object(Matching, "game/memory.c"),
            Object(Matching, "game/printfunc.c"),
            Object(Matching, "game/process.c"),
            Object(Matching, "game/sprman.c"),
            Object(Matching, "game/sprput.c"),
            Object(Matching, "game/hsfload.c"),
            Object(NonMatching, "game/hsfdraw.c"),
            Object(Matching, "game/hsfman.c"),
            Object(NonMatching, "game/hsfmotion.c"),
            Object(NonMatching, "game/hsfanim.c"),
            Object(NonMatching, "game/hsfex.c"),
            Object(NonMatching, "game/perf.c"),
            Object(Matching, "game/objmain.c"),
            Object(NonMatching, "game/fault.c"),
            Object(Matching, "game/gamework.c"),
            Object(NonMatching, "game/objsysobj.c"),
            Object(NonMatching, "game/objdll.c"),
            Object(Matching, "game/frand.c"),
            Object(NonMatching, "game/audio.c"),
            Object(NonMatching, "game/EnvelopeExec.c"),
            Object(NonMatching, "game/minigame_seq.c"),
            Object(Matching, "game/ovllist.c"),
            Object(NonMatching, "game/esprite.c"),
            Object(NonMatching, "game/code_8003FF68.c"),
            Object(NonMatching, "game/ClusterExec.c"),
            Object(NonMatching, "game/ShapeExec.c"),
            Object(NonMatching, "game/wipe.c"),
            Object(NonMatching, "game/window.c"),
            Object(Matching, "game/messdata.c"),
            Object(NonMatching, "game/card.c"),
            Object(NonMatching, "game/armem.c"),
            Object(NonMatching, "game/code_800498F0.c"),
            Object(NonMatching, "game/mapspace.c"),
            Object(NonMatching, "game/THPSimple.c"),
            Object(NonMatching, "game/THPDraw.c"),
            Object(NonMatching, "game/thpmain.c"),
            Object(NonMatching, "game/objsub.c"),
            Object(NonMatching, "game/flag.c"),
            Object(NonMatching, "game/saveload.c"),
            Object(NonMatching, "game/sreset.c"),
            Object(NonMatching, "game/board/main.c"),
            Object(NonMatching, "game/board/board.c"),
            Object(NonMatching, "game/board/model.c"),
            Object(NonMatching, "game/board/window.c"),
            Object(NonMatching, "game/board/com.c"),
            Object(NonMatching, "game/board/overhead.c"),
            Object(NonMatching, "game/board/space.c"),
            Object(NonMatching, "game/board/shop.c"),
            Object(NonMatching, "game/board/lottery.c"),
            Object(NonMatching, "game/board/basic_space.c"),
            Object(NonMatching, "game/board/warp.c"),
            Object(NonMatching, "game/board/char_roulette.c"),
            Object(NonMatching, "game/board/mushroom_space.c"),
            Object(NonMatching, "game/board/star.c"),
            Object(NonMatching, "game/board/dice_roll.c"),
            Object(NonMatching, "game/board/ui.c"),
            Object(NonMatching, "game/board/hidden_block.c"),
            Object(NonMatching, "game/board/item.c"),
            Object(NonMatching, "game/board/bowser.c"),
            Object(NonMatching, "game/board/battle.c"),
            Object(NonMatching, "game/board/fortune_space.c"),
            Object(NonMatching, "game/board/boo.c"),
            Object(NonMatching, "game/board/mg_setup.c"),
            Object(NonMatching, "game/board/boo_house.c"),
            Object(NonMatching, "game/board/start.c"),
            Object(NonMatching, "game/board/last5.c"),
            Object(NonMatching, "game/board/pause.c"),
            Object(NonMatching, "game/board/com_path.c"),
            Object(NonMatching, "game/board/tutorial.c"),
        ],
    },
    DolphinLib(
        "base",
        [
            Object(NonMatching, "dolphin/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "os",
        [
            Object(NonMatching, "dolphin/os/OS.c"),
            Object(NonMatching, "dolphin/os/OSAlarm.c"),
            Object(NonMatching, "dolphin/os/OSAlloc.c"),
            Object(NonMatching, "dolphin/os/OSArena.c"),
            Object(NonMatching, "dolphin/os/OSAudioSystem.c"),
            Object(NonMatching, "dolphin/os/OSCache.c"),
            Object(NonMatching, "dolphin/os/OSContext.c"),
            Object(NonMatching, "dolphin/os/OSError.c"),
            Object(NonMatching, "dolphin/os/OSFont.c"),
            Object(NonMatching, "dolphin/os/OSInterrupt.c"),
            Object(NonMatching, "dolphin/os/OSLink.c"),
            Object(NonMatching, "dolphin/os/OSMessage.c"),
            Object(NonMatching, "dolphin/os/OSMemory.c"),
            Object(NonMatching, "dolphin/os/OSMutex.c"),
            Object(NonMatching, "dolphin/os/OSReboot.c"),
            Object(NonMatching, "dolphin/os/OSReset.c"),
            Object(NonMatching, "dolphin/os/OSResetSW.c"),
            Object(NonMatching, "dolphin/os/OSRtc.c"),
            Object(NonMatching, "dolphin/os/OSStopwatch.c"),
            Object(NonMatching, "dolphin/os/OSSync.c"),
            Object(NonMatching, "dolphin/os/OSThread.c"),
            Object(NonMatching, "dolphin/os/OSTime.c"),
            Object(NonMatching, "dolphin/os/__start.c"),
            Object(NonMatching, "dolphin/os/__ppc_eabi_init.c"),
        ],
    ),
    DolphinLib(
        "db",
        [
            Object(NonMatching, "dolphin/db.c"),
        ],
    ),
    DolphinLib(
        "mtx",
        [
            Object(NonMatching, "dolphin/mtx/mtx.c"),
            Object(NonMatching, "dolphin/mtx/mtxvec.c"),
            Object(NonMatching, "dolphin/mtx/mtx44.c"),
            Object(NonMatching, "dolphin/mtx/vec.c"),
            Object(NonMatching, "dolphin/mtx/quat.c"),
            Object(NonMatching, "dolphin/mtx/psmtx.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            Object(NonMatching, "dolphin/dvd/dvdlow.c"),
            Object(NonMatching, "dolphin/dvd/dvdfs.c"),
            Object(NonMatching, "dolphin/dvd/dvd.c"),
            Object(NonMatching, "dolphin/dvd/dvdqueue.c"),
            Object(NonMatching, "dolphin/dvd/dvderror.c"),
            Object(NonMatching, "dolphin/dvd/fstload.c"),
        ],
    ),
    DolphinLib(
        "vi",
        [
            Object(NonMatching, "dolphin/vi.c"),
        ],
    ),
    DolphinLib(
        "demo",
        [
            Object(NonMatching, "dolphin/demo/DEMOInit.c"),
            Object(NonMatching, "dolphin/demo/DEMOFont.c"),
            Object(NonMatching, "dolphin/demo/DEMOPuts.c"),
            Object(NonMatching, "dolphin/demo/DEMOStats.c"),
        ],
    ),
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "host": False,
        "objects": [
            Object(Matching, "Runtime.PPCEABI.H/global_destructor_chain.c"),
            Object(Matching, "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
            Object(NonMatching, "Runtime.PPCEABI.H/Gecko_ExceptionPPC.cp"),
        ],
    },
    {
        "lib": "REL",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
            Object(Matching, "REL/executor.c"),
            Object(Matching, "REL/empty.c"),  # Must be marked as matching
        ],
    },
    {
        "lib": "_minigameDLL",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
            Object(Matching, "REL/executor.c"),
            Object(Matching, "REL/_minigameDLL/_minigameDLL.c"),
        ],
    },
    {
        "lib": "bootDll",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
            Object(Matching, "REL/executor.c"),
            Object(NonMatching, "REL/bootDll/bootDll.c"),
            Object(Matching, "REL/bootDll/nintendo_data.c"),
        ],
    },
    {
        "lib": "subchrselDll",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
            Object(Matching, "REL/executor.c"),
            Object(Matching, "REL/subchrselDll/subchrselDll.c"),
        ],
    },
    {
        "lib": "w10Dll",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
            Object(Matching, "REL/w10Dll/w10Dll_init.c"),
            Object(Matching, "REL/w10Dll/w10Dll.c"),
            Object(Matching, "REL/w10Dll/w10Dll2.c"),
            Object(Matching, "REL/w10Dll/w10Dll3.c"),
            Object(Matching, "REL/w10Dll/w10Dll4.c"),
        ],
    },
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    config.progress_each_module = args.verbose
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
