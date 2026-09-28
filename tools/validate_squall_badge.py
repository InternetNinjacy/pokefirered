#!/usr/bin/env python3
"""Validate the approved Cloudburst Squall Badge source/display path."""

from pathlib import Path
import hashlib
import struct
import sys

ROOT = Path(".")
APPROVED_BADGE_SHEET_BLOB = "723b82dffd22afd9ad14149db419cd136e2f6c42"

def fail(msg):
    sys.exit("Squall Badge validation failed: " + msg)

def text(path):
    return (ROOT / path).read_text(encoding="utf-8")

def require(haystack, needle, label):
    if needle not in haystack:
        fail(f"{label}: missing {needle!r}")

def git_blob_sha1(data):
    return hashlib.sha1(f"blob {len(data)}\0".encode("ascii") + data).hexdigest()

badge = (ROOT / "graphics/trainer_card/badges.png").read_bytes()
if badge[:8] != b"\x89PNG\r\n\x1a\n" or badge[12:16] != b"IHDR":
    fail("graphics/trainer_card/badges.png is not a valid PNG")
width, height = struct.unpack(">II", badge[16:24])
bit_depth, color_type = badge[24], badge[25]
if (width, height, bit_depth, color_type) != (128, 16, 4, 3):
    fail(f"badge sheet must be 128x16, 4-bit indexed; got {(width,height,bit_depth,color_type)}")
if git_blob_sha1(badge) != APPROVED_BADGE_SHEET_BLOB:
    fail("approved Squall Badge sheet fingerprint changed")

flags = text("include/constants/flags.h")
require(flags,
        "#define FLAG_BADGE01_SQUALL                                         FLAG_BADGE01_GET",
        "Squall Badge flag")

gym = text("data/maps/PewterCity_Gym/scripts.inc")
require(gym, "setflag FLAG_BADGE01_SQUALL", "Cloudburst first-clear award")

card = text("src/trainer_card.c")
for needle in (
    'INCBIN_U32("graphics/trainer_card/badges.4bpp.lz")',
    "u16 tileNum = 192;",
    "for (i = 0, badgeFlag = FLAG_BADGE01_GET; badgeFlag <= FLAG_BADGE08_GET; badgeFlag++, i++)",
    "if (sTrainerCardDataPtr->hasBadge[i])",
    "for (i = 0; i < NUM_BADGES; i++, tileNum += 2, x += 3)",
):
    require(card, needle, "Trainer Card badge display path")

print("Squall Badge source/display path OK: approved badge sheet occupies badge slot 1.")
