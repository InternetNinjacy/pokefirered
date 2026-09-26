#!/usr/bin/env python3
"""Validate Pokémon: Weather's locked TM12 Weather Ball compatibility."""

from pathlib import Path
import re
import sys

TM_FILE = Path("src/data/pokemon/tmhm_learnsets.h")
ITEM_FILE = Path("include/constants/items.h")

EXPECTED = {
    "ALTARIA",
    "AMPHAROS",
    "ARTICUNO",
    "AZUMARILL",
    "AZURILL",
    "BANETTE",
    "BARBOACH",
    "BAYLEEF",
    "BELLOSSOM",
    "BELLSPROUT",
    "BLASTOISE",
    "BULBASAUR",
    "CACNEA",
    "CACTURNE",
    "CASTFORM",
    "CELEBI",
    "CHARIZARD",
    "CHARMANDER",
    "CHARMELEON",
    "CHIKORITA",
    "CHINCHOU",
    "CLAMPERL",
    "CLOYSTER",
    "DELIBIRD",
    "DEWGONG",
    "DIGLETT",
    "DRAGONAIR",
    "DRAGONITE",
    "DRATINI",
    "DUGTRIO",
    "DUSCLOPS",
    "DUSKULL",
    "EEVEE",
    "ELECTRIKE",
    "ENTEI",
    "ESPEON",
    "EXEGGCUTE",
    "EXEGGUTOR",
    "FEEBAS",
    "FLAAFFY",
    "FLAREON",
    "GASTLY",
    "GENGAR",
    "GLALIE",
    "GLIGAR",
    "GLOOM",
    "GOLDEEN",
    "GOLDUCK",
    "GOREBYSS",
    "GROUDON",
    "GYARADOS",
    "HAUNTER",
    "HOPPIP",
    "HORSEA",
    "HO_OH",
    "HUNTAIL",
    "IVYSAUR",
    "JOLTEON",
    "JUMPLUFF",
    "KABUTO",
    "KABUTOPS",
    "KINGDRA",
    "KYOGRE",
    "LANTURN",
    "LAPRAS",
    "LARVITAR",
    "LATIAS",
    "LATIOS",
    "LOMBRE",
    "LOTAD",
    "LUDICOLO",
    "LUGIA",
    "LUNATONE",
    "LUVDISC",
    "MAGIKARP",
    "MANECTRIC",
    "MANTINE",
    "MAREEP",
    "MARILL",
    "MARSHTOMP",
    "MASQUERAIN",
    "MEGANIUM",
    "MEW",
    "MEWTWO",
    "MILOTIC",
    "MISDREAVUS",
    "MOLTRES",
    "MUDKIP",
    "NINETALES",
    "NUZLEAF",
    "ODDISH",
    "OMANYTE",
    "OMASTAR",
    "PELIPPER",
    "PICHU",
    "PIKACHU",
    "PILOSWINE",
    "POLITOED",
    "POLIWAG",
    "POLIWHIRL",
    "POLIWRATH",
    "PSYDUCK",
    "PUPITAR",
    "QWILFISH",
    "RAICHU",
    "RAIKOU",
    "RAYQUAZA",
    "REGICE",
    "RELICANTH",
    "ROSELIA",
    "SABLEYE",
    "SANDSHREW",
    "SANDSLASH",
    "SEADRA",
    "SEAKING",
    "SEALEO",
    "SEEDOT",
    "SEEL",
    "SHEDINJA",
    "SHELLDER",
    "SHIFTRY",
    "SHUPPET",
    "SKIPLOOM",
    "SLOWBRO",
    "SLOWKING",
    "SLOWPOKE",
    "SNEASEL",
    "SNORUNT",
    "SOLROCK",
    "SPHEAL",
    "SQUIRTLE",
    "STARMIE",
    "STARYU",
    "SUICUNE",
    "SUNFLORA",
    "SUNKERN",
    "SURSKIT",
    "SWABLU",
    "SWAMPERT",
    "SWINUB",
    "TANGELA",
    "TENTACOOL",
    "TENTACRUEL",
    "TORKOAL",
    "TROPIUS",
    "TYRANITAR",
    "UMBREON",
    "VAPOREON",
    "VENUSAUR",
    "VICTREEBEL",
    "VILEPLUME",
    "VULPIX",
    "WAILMER",
    "WAILORD",
    "WALREIN",
    "WARTORTLE",
    "WEEPINBELL",
    "WHISCASH",
    "WINGULL",
    "ZAPDOS",
}

# These project-specific Eevee evolutions are documented as TM12-compatible and
# become mandatory as soon as their species constants/source entries exist.
FUTURE_REQUIRED = {"LEAFEON", "GLACEON", "ECTOCEON"}

tm_text = TM_FILE.read_text(encoding="utf-8")
item_text = ITEM_FILE.read_text(encoding="utf-8")

if "TM12_TAUNT" in tm_text or "ITEM_TM12_TAUNT" in item_text:
    sys.exit("Legacy TM12 Taunt compatibility/alias detected.")

entries = re.findall(
    r"\[SPECIES_([A-Z0-9_]+)\]\s*=\s*TMHM_LEARNSET\(([\s\S]*?)\),\n",
    tm_text,
)
actual = {species for species, body in entries if "TM12_WEATHER_BALL" in body}

species_header = Path("include/constants/species.h").read_text(encoding="utf-8")
for species in FUTURE_REQUIRED:
    if f"SPECIES_{species}" in species_header:
        EXPECTED.add(species)

missing = sorted(EXPECTED - actual)
unexpected = sorted(actual - EXPECTED)
if missing or unexpected:
    parts = []
    if missing:
        parts.append("missing: " + ", ".join(missing))
    if unexpected:
        parts.append("unexpected: " + ", ".join(unexpected))
    sys.exit("TM12 Weather Ball compatibility mismatch (" + "; ".join(parts) + ")")

if "#define ITEM_TM12_WEATHER_BALL ITEM_TM12" not in item_text:
    sys.exit("ITEM_TM12_WEATHER_BALL alias is missing.")

print(f"TM12 Weather Ball compatibility OK: {len(actual)} current species.")
