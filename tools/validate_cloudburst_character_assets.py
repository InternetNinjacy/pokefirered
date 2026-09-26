#!/usr/bin/env python3
"""Static regression gate for Cloudburst Gym character graphics."""

from pathlib import Path
import json
import re
import struct
import sys

ROOT = Path(".")

def fail(msg):
    sys.exit("Cloudburst character asset validation failed: " + msg)

def text(path):
    return (ROOT / path).read_text(encoding="utf-8")

def png_meta(path):
    data = (ROOT / path).read_bytes()
    if data[:8] != b"\x89PNG\r\n\x1a\n" or data[12:16] != b"IHDR":
        fail(f"{path}: invalid PNG/IHDR")
    width, height = struct.unpack(">II", data[16:24])
    bit_depth = data[24]
    color_type = data[25]
    return width, height, bit_depth, color_type

def palette_count(path):
    lines = [line.strip() for line in text(path).splitlines() if line.strip()]
    if len(lines) < 3 or lines[0] != "JASC-PAL":
        fail(f"{path}: invalid JASC palette")
    declared = int(lines[2])
    actual = len(lines[3:])
    if declared != 16 or actual != 16:
        fail(f"{path}: expected 16 colors, declared={declared}, actual={actual}")

def require(haystack, needle, label):
    if needle not in haystack:
        fail(f"{label}: missing {needle!r}")

# Source-format checks.
battle_assets = {
    "Raina": (
        "graphics/trainers/front_pics/leader_raina_front_pic.png",
        "graphics/trainers/palettes/leader_raina.pal",
    ),
    "Wade": (
        "graphics/trainers/front_pics/hydrologist_front_pic.png",
        "graphics/trainers/palettes/hydrologist.pal",
    ),
    "Skye": (
        "graphics/trainers/front_pics/storm_chaser_front_pic.png",
        "graphics/trainers/palettes/storm_chaser.pal",
    ),
}
for name, (pic, pal) in battle_assets.items():
    meta = png_meta(pic)
    if meta[:2] != (64, 64) or meta[3] != 3:
        fail(f"{name} battle sprite: expected 64x64 indexed PNG, got {meta}")
    palette_count(pal)

overworld_assets = {
    "Raina": (
        "graphics/object_events/pics/people/raina.png",
        "graphics/object_events/palettes/raina.pal",
        (48, 32),
    ),
    "Wade": (
        "graphics/object_events/pics/people/hydrologist.png",
        "graphics/object_events/palettes/hydrologist.pal",
        (160, 32),
    ),
    "Skye": (
        "graphics/object_events/pics/people/storm_chaser.png",
        "graphics/object_events/palettes/storm_chaser.pal",
        (160, 32),
    ),
}
for name, (pic, pal, dims) in overworld_assets.items():
    meta = png_meta(pic)
    if meta[:2] != dims or meta[3] != 3:
        fail(f"{name} overworld sprite: expected {dims[0]}x{dims[1]} indexed PNG, got {meta}")
    palette_count(pal)

# Resource IDs.
trainers_h = text("include/constants/trainers.h")
for line in (
    "#define TRAINER_PIC_LEADER_RAINA           148",
    "#define TRAINER_PIC_HYDROLOGIST            149",
    "#define TRAINER_PIC_STORM_CHASER           150",
):
    require(trainers_h, line, "trainer picture IDs")

event_h = text("include/constants/event_objects.h")
for line in (
    "#define OBJ_EVENT_GFX_RAINA         152",
    "#define OBJ_EVENT_GFX_HYDROLOGIST   153",
    "#define OBJ_EVENT_GFX_STORM_CHASER  154",
    "#define NUM_OBJ_EVENT_GFX     155",
):
    require(event_h, line, "object graphics IDs")

# Battle-table integration and placeholder removal.
trainer_data = text("src/data/trainers.h")
checks = {
    "[TRAINER_LEADER_BROCK]": (
        ".trainerPic = TRAINER_PIC_LEADER_RAINA",
        '.trainerName = _("RAINA")',
    ),
    "[TRAINER_CAMPER_LIAM]": (
        ".trainerClass = TRAINER_CLASS_HYDROLOGIST",
        ".trainerPic = TRAINER_PIC_HYDROLOGIST",
        '.trainerName = _("WADE")',
    ),
    "[TRAINER_STORM_CHASER_SKYE]": (
        ".trainerClass = TRAINER_CLASS_STORM_CHASER",
        ".trainerPic = TRAINER_PIC_STORM_CHASER",
        '.trainerName = _("SKYE")',
    ),
    "[TRAINER_LEADER_RAINA_REMATCH]": (
        ".trainerPic = TRAINER_PIC_LEADER_RAINA",
        '.trainerName = _("RAINA")',
    ),
}
for marker, required in checks.items():
    start = trainer_data.find(marker)
    if start < 0:
        fail(f"trainer record missing: {marker}")
    end = trainer_data.find("\n    },", start)
    block = trainer_data[start:end + 7]
    for needle in required:
        require(block, needle, marker)
for bad in (
    ".trainerPic = TRAINER_PIC_SCIENTIST",
    ".trainerPic = TRAINER_PIC_PICNICKER",
):
    for marker in ("[TRAINER_CAMPER_LIAM]", "[TRAINER_STORM_CHASER_SKYE]"):
        start = trainer_data.find(marker)
        end = trainer_data.find("\n    },", start)
        if bad in trainer_data[start:end + 7]:
            fail(f"{marker}: legacy placeholder picture remains")
start = trainer_data.find("[TRAINER_LEADER_BROCK]")
end = trainer_data.find("\n    },", start)
if ".trainerPic = TRAINER_PIC_LEADER_BROCK" in trainer_data[start:end + 7]:
    fail("Raina first battle still uses Brock trainer picture")

front_tables = text("src/data/trainer_graphics/front_pic_tables.h")
for needle in (
    "TRAINER_SPRITE(LEADER_RAINA, gTrainerFrontPic_LeaderRaina, 0x800)",
    "TRAINER_SPRITE(HYDROLOGIST, gTrainerFrontPic_Hydrologist, 0x800)",
    "TRAINER_SPRITE(STORM_CHASER, gTrainerFrontPic_StormChaser, 0x800)",
    "TRAINER_PAL(LEADER_RAINA, gTrainerPalette_LeaderRaina)",
    "TRAINER_PAL(HYDROLOGIST, gTrainerPalette_Hydrologist)",
    "TRAINER_PAL(STORM_CHASER, gTrainerPalette_StormChaser)",
):
    require(front_tables, needle, "trainer graphics tables")

# Overworld frame tables and movement requirements.
pic_tables = text("src/data/object_events/object_event_pic_tables.h")
def frame_indices(table_name):
    m = re.search(
        rf"static const struct SpriteFrameImage {re.escape(table_name)}\[\] = \{{([\s\S]*?)\n\}};",
        pic_tables,
    )
    if not m:
        fail(f"missing frame table {table_name}")
    return [int(x) for x in re.findall(r"overworld_frame\([^,]+,\s*2,\s*4,\s*(\d+)\)", m.group(1))]

raina_frames = frame_indices("sPicTable_Raina")
wade_frames = frame_indices("sPicTable_Hydrologist")
skye_frames = frame_indices("sPicTable_StormChaser")
if raina_frames[:3] != [0, 1, 2]:
    fail(f"Raina directional frames malformed: {raina_frames}")
if wade_frames != list(range(10)):
    fail(f"Wade standard frame set malformed: {wade_frames}")
if skye_frames != list(range(10)):
    fail(f"Skye standard frame set malformed: {skye_frames}")

anims = text("src/data/object_events/object_event_anims.h")
require(anims, "ANIMCMD_FRAME(7, 8)", "standard west/east walk")
require(anims, "ANIMCMD_FRAME(8, 8)", "standard west/east walk")

gfx_info = text("src/data/object_events/object_event_graphics_info.h")
expected_info = {
    "Raina": ("OBJ_EVENT_PAL_TAG_RAINA", "PALSLOT_NPC_1", "sPicTable_Raina"),
    "Hydrologist": ("OBJ_EVENT_PAL_TAG_HYDROLOGIST", "PALSLOT_NPC_3", "sPicTable_Hydrologist"),
    "StormChaser": ("OBJ_EVENT_PAL_TAG_STORM_CHASER", "PALSLOT_NPC_4", "sPicTable_StormChaser"),
}
for name, required in expected_info.items():
    marker = f"gObjectEventGraphicsInfo_{name} = {{"
    start = gfx_info.find(marker)
    if start < 0:
        fail(f"missing {marker}")
    end = gfx_info.find("\n};", start)
    block = gfx_info[start:end + 3]
    for needle in required + (".width = 16", ".height = 32", ".anims = sAnimTable_Standard"):
        require(block, needle, marker)

movement = text("src/event_object_movement.c")
for tag in ("OBJ_EVENT_PAL_TAG_RAINA", "OBJ_EVENT_PAL_TAG_HYDROLOGIST", "OBJ_EVENT_PAL_TAG_STORM_CHASER"):
    require(movement, tag, "object palette registration")

# Map/object wiring and mandatory post-defeat movement.
map_data = json.loads(text("data/maps/PewterCity_Gym/map.json"))
objs = {(o["x"], o["y"]): o["graphics_id"] for o in map_data["object_events"]}
expected_objs = {
    (6, 5): "OBJ_EVENT_GFX_RAINA",
    (6, 11): "OBJ_EVENT_GFX_HYDROLOGIST",
    (6, 8): "OBJ_EVENT_GFX_STORM_CHASER",
}
for pos, gfx in expected_objs.items():
    if objs.get(pos) != gfx:
        fail(f"map object {pos}: expected {gfx}, got {objs.get(pos)}")

scripts = text("data/maps/PewterCity_Gym/scripts.inc")
for needle in (
    "applymovement LOCALID_CLOUDBURST_WADE, PewterCity_Gym_Movement_WadeStepAside",
    "PewterCity_Gym_Movement_WadeStepAside:\n\twalk_left",
    "setobjectxyperm LOCALID_CLOUDBURST_WADE, 5, 11",
    "applymovement LOCALID_CLOUDBURST_SKYE, PewterCity_Gym_Movement_SkyeStepAside",
    "PewterCity_Gym_Movement_SkyeStepAside:\n\twalk_right",
    "setobjectxyperm LOCALID_CLOUDBURST_SKYE, 7, 8",
):
    require(scripts, needle, "Cloudburst movement scripts")

print("Cloudburst character assets OK: Raina/Wade/Skye battle + overworld integration validated.")
