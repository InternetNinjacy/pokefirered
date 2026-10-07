#!/usr/bin/env python3
"""Host/static checks for RIV-016D Cinnabar Thomas fossil branching."""
from pathlib import Path
import re
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]

with tempfile.TemporaryDirectory() as tmp:
    p = Path(tmp)
    (p / 'global.h').write_text(r'''#pragma once
#include <stdint.h>
#include <string.h>
typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32; typedef uint8_t bool8;
#define TRUE 1
#define FALSE 0
#define PARTY_SIZE 6
#define MAX_MON_MOVES 4
#include "constants/species.h"
#include "constants/battle.h"
#include "constants/pokemon.h"
struct Pokemon {u16 hp, species, held, moves[4]; u8 egg, ability, level, iv; u32 personality, ot;};
extern struct Pokemon gPlayerParty[6]; extern u32 gBattleTypeFlags; extern u16 gTrainerBattleOpponent_A, gSpecialVar_Result;
u32 GetMonData(struct Pokemon *, int);
void SetMonData(struct Pokemon *, int, const void *);
void CreateMon(struct Pokemon *, u16, u8, u8, u8, u32, u8, u32);
void SetMonMoveSlot(struct Pokemon *, u16, u8);
u16 VarGet(u16);
''')
    for f in ['battle.h', 'battle_setup.h', 'event_data.h', 'pokemon.h']:
        (p / f).write_text('#include "global.h"\n')
    (p / 'test.c').write_text(r'''#include "global.h"
#include <assert.h>
#include "constants/opponents.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/vars.h"
#include "sam_thomas.h"

struct Pokemon gPlayerParty[6];
u32 gBattleTypeFlags;
u16 gTrainerBattleOpponent_A, gSpecialVar_Result;
static u16 theftState, starterState;

u16 VarGet(u16 v) {
    if (v == VAR_MAP_SCENE_MT_MOON_B2F) return theftState;
    if (v == VAR_STARTER_MON) return starterState;
    return 0;
}
u32 GetMonData(struct Pokemon *m, int f) {
    switch(f) {
    case MON_DATA_HP: return m->hp;
    case MON_DATA_SPECIES_OR_EGG: return m->species;
    case MON_DATA_IS_EGG: return m->egg;
    case MON_DATA_PERSONALITY: return m->personality;
    case MON_DATA_OT_ID: return m->ot;
    }
    return 0;
}
void SetMonData(struct Pokemon *m, int f, const void *v) {
    if (f == MON_DATA_HELD_ITEM) m->held = *(const u16*)v;
    if (f == MON_DATA_ABILITY_NUM) m->ability = *(const u8*)v;
}
void CreateMon(struct Pokemon *m, u16 species, u8 level, u8 iv, u8 fixed, u32 personality, u8 otType, u32 ot) {
    memset(m, 0, sizeof(*m));
    m->species = species; m->level = level; m->iv = iv; m->personality = personality; m->ot = ot;
}
void SetMonMoveSlot(struct Pokemon *m, u16 move, u8 slot) { m->moves[slot] = move; }

static void SeedParty(struct Pokemon *party) {
    int i;
    memset(party, 0, sizeof(struct Pokemon) * 6);
    for (i = 0; i < 6; i++) {
        party[i].species = 100 + i;
        party[i].level = 40 + i;
        party[i].personality = 1000 + i;
        party[i].ot = 2000 + i;
    }
    party[3].species = SPECIES_SEADRA;
    party[3].level = 45;
    party[3].iv = 24;
}

int main(void) {
    struct Pokemon party[6], before[6];

    SeedParty(party); memcpy(before, party, sizeof(party));
    theftState = 3;
    ApplyThomasCinnabarFossilBranch(party, TRAINER_THOMAS_SILPH_CO);
    assert(!memcmp(before, party, sizeof(party)));

    SeedParty(party); memcpy(before, party, sizeof(party));
    theftState = 0;
    ApplyThomasCinnabarFossilBranch(party, TRAINER_THOMAS_CINNABAR_MANSION);
    assert(!memcmp(before, party, sizeof(party)));

    SeedParty(party); memcpy(before, party, sizeof(party));
    theftState = 3;
    ApplyThomasCinnabarFossilBranch(party, TRAINER_THOMAS_CINNABAR_MANSION);
    assert(!memcmp(before, party, sizeof(struct Pokemon) * 3));
    assert(!memcmp(&before[4], &party[4], sizeof(struct Pokemon) * 2));
    assert(party[3].species == SPECIES_KABUTOPS);
    assert(party[3].level == 45 && party[3].iv == 24 && party[3].held == ITEM_MYSTIC_WATER);
    assert(party[3].personality == before[3].personality && party[3].ot == before[3].ot);
    assert(party[3].moves[0] == MOVE_ROCK_SLIDE);
    assert(party[3].moves[1] == MOVE_BRICK_BREAK);
    assert(party[3].moves[2] == MOVE_WATER_PULSE);
    assert(party[3].moves[3] == MOVE_PROTECT);

    SeedParty(party); memcpy(before, party, sizeof(party));
    theftState = 4;
    ApplyThomasCinnabarFossilBranch(party, TRAINER_THOMAS_CINNABAR_MANSION);
    assert(!memcmp(before, party, sizeof(struct Pokemon) * 3));
    assert(!memcmp(&before[4], &party[4], sizeof(struct Pokemon) * 2));
    assert(party[3].species == SPECIES_OMASTAR);
    assert(party[3].level == 45 && party[3].iv == 24 && party[3].held == ITEM_MYSTIC_WATER);
    assert(party[3].personality == before[3].personality && party[3].ot == before[3].ot);
    assert(party[3].moves[0] == MOVE_SURF);
    assert(party[3].moves[1] == MOVE_ICE_BEAM);
    assert(party[3].moves[2] == MOVE_ANCIENT_POWER);
    assert(party[3].moves[3] == MOVE_PROTECT);
    return 0;
}
''')
    subprocess.run([
        'gcc', '-std=c99', '-Werror', '-I'+tmp, '-I'+str(ROOT/'include'),
        str(ROOT/'src/sam_thomas_mt_moon.c'), str(p/'test.c'), '-o', str(p/'test')
    ], check=True)
    subprocess.run([str(p/'test')], check=True)

# Trainer 788 remains the existing single-battle Thomas record.
opponents = (ROOT / 'include/constants/opponents.h').read_text()
assert re.search(r'#define\s+TRAINER_THOMAS_CINNABAR_MANSION\s+788\b', opponents)
trainers = (ROOT / 'src/data/trainers.h').read_text()
record = re.search(r'\[TRAINER_THOMAS_CINNABAR_MANSION\] = \{.*?\n    \},', trainers, re.S).group()
assert '.doubleBattle = FALSE' in record
assert '.party = ITEM_CUSTOM_MOVES(sParty_ThomasCinnabar)' in record

# The protected six-line baseline remains static; only the runtime fourth slot is replaced.
parties = (ROOT / 'src/data/sam_thomas_trainer_parties.h').read_text()
cinnabar = re.search(r'sParty_ThomasCinnabar\[\] = \{(.*?)\n\};', parties, re.S).group(1)
assert cinnabar.count('.species =') == 6
assert '.species = SPECIES_SEADRA' in cinnabar
for species in ('SPECIES_CLAYDOL', 'SPECIES_HOUNDOOM', 'SPECIES_MAGNETON', 'SPECIES_MACHAMP', 'SPECIES_SALAMENCE'):
    assert species in cinnabar

# The runtime hook is scoped to party construction and does not allocate a new trainer.
battle = (ROOT / 'src/battle_main.c').read_text()
assert 'ApplyThomasMtMoonStarterBranch(party, trainerNum);\n        ApplyThomasCinnabarFossilBranch(party, trainerNum);' in battle

# Mansion battle remains optional with respect to the Lab preview. Victory alone advances;
# loss returns before the post-trainer commands, leaving stage 4/visibility retryable.
script = (ROOT / 'data/maps/PokemonMansion_B1F/scripts.inc').read_text()
block = script.split('PokemonMansion_B1F_EventScript_ThomasBattle::', 1)[1].split('\n\n', 1)[0]
assert 'FLAG_THOMAS_CINNABAR_LAB_COMPLETE' not in block
assert 'TRAINER_THOMAS_CINNABAR_MANSION' in block
assert block.index('trainerbattle_no_intro') < block.index('call EventScript_ThomasSetCinnabarCleared')
assert block.index('call EventScript_ThomasSetCinnabarCleared') < block.index('removeobject VAR_LAST_TALKED')

# Central stage routing keeps Thomas on Cinnabar at stage 4 and exposes Viridian only
# after the Cinnabar victory transition.
chain = (ROOT / 'data/maps/Route24/scripts.inc').read_text()
assert 'goto_if_eq VAR_THOMAS_ARC_STAGE, THOMAS_ARC_SILPH_CLEARED, EventScript_ThomasShowCinnabar' in chain
assert 'goto_if_eq VAR_THOMAS_ARC_STAGE, THOMAS_ARC_CINNABAR_CLEARED, EventScript_ThomasShowViridian' in chain

print('PASS: trainer 788 single battle branches Seadra->Kabutops/Omastar from theft state; Lab remains optional; victory advances and loss remains retryable')
