#!/usr/bin/env python3
"""Host checks for the real Mt. Moon helper, plus baseline/map preservation."""
from pathlib import Path
import json
import re
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
BASE = 'ca15b79af8aea55664fc190e03b5d4672d4de940'
def old(path):
    return subprocess.check_output(['git', 'show', f'{BASE}:{path}'], cwd=ROOT, text=True)

with tempfile.TemporaryDirectory() as tmp:
    p = Path(tmp)
    (p / 'global.h').write_text('''#pragma once
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
    (p / 'test.c').write_text('''#include "global.h"
#include <assert.h>
#include "constants/opponents.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "sam_thomas.h"
struct Pokemon gPlayerParty[6]; u32 gBattleTypeFlags; u16 gTrainerBattleOpponent_A, gSpecialVar_Result; static u16 starter;
u16 VarGet(u16 v) {return starter;}
u32 GetMonData(struct Pokemon *m, int f) {switch(f) {case MON_DATA_HP:return m->hp; case MON_DATA_SPECIES_OR_EGG:return m->species; case MON_DATA_IS_EGG:return m->egg; case MON_DATA_PERSONALITY:return m->personality; case MON_DATA_OT_ID:return m->ot;} return 0;}
void SetMonData(struct Pokemon *m,int f,const void *v) {if(f==MON_DATA_HELD_ITEM)m->held=*(const u16*)v; if(f==MON_DATA_ABILITY_NUM)m->ability=*(const u8*)v;}
void CreateMon(struct Pokemon *m,u16 species,u8 level,u8 iv,u8 fixed,u32 personality,u8 otType,u32 ot) {memset(m,0,sizeof(*m));m->species=species;m->level=level;m->iv=iv;m->personality=personality;m->ot=ot;}
void SetMonMoveSlot(struct Pokemon *m,u16 move,u8 slot) {m->moves[slot]=move;}
int main(void) {
 int slot; struct Pokemon party[2], before[2];
 gTrainerBattleOpponent_A=TRAINER_THOMAS_MT_MOON; gBattleTypeFlags=BATTLE_TYPE_TRAINER|BATTLE_TYPE_DOUBLE;
 assert(CountThomasUsablePlayerMons()==0); assert(!IsThomasOneMonDoubleBattle());
 for(slot=0;slot<6;slot++) {
  memset(gPlayerParty,0,sizeof(gPlayerParty)); gPlayerParty[slot].species=SPECIES_EEVEE;gPlayerParty[slot].hp=10;
  assert(CountThomasUsablePlayerMons()==1); assert(IsThomasOneMonDoubleBattle());
  Script_CountThomasUsablePlayerMons();assert(gSpecialVar_Result==1);
  gPlayerParty[slot].egg=1;assert(CountThomasUsablePlayerMons()==0);gPlayerParty[slot].egg=0;
  gPlayerParty[slot].hp=0;assert(CountThomasUsablePlayerMons()==0);gPlayerParty[slot].hp=10;
 }
 gPlayerParty[0].species=SPECIES_PICHU;gPlayerParty[0].hp=10;assert(CountThomasUsablePlayerMons()==2);assert(!IsThomasOneMonDoubleBattle());
 gPlayerParty[0].hp=0;gTrainerBattleOpponent_A=TRAINER_THOMAS_NUGGET_BRIDGE;assert(!IsThomasOneMonDoubleBattle());
 gTrainerBattleOpponent_A=TRAINER_THOMAS_MT_MOON;gBattleTypeFlags|=BATTLE_TYPE_LINK;assert(!IsThomasOneMonDoubleBattle());gBattleTypeFlags=BATTLE_TYPE_TRAINER;assert(!IsThomasOneMonDoubleBattle());
 memset(party,0,sizeof(party));party[0].species=SPECIES_GASTLY;party[1].species=SPECIES_CHANSEY;party[1].personality=1234;party[1].ot=5678;memcpy(before,party,sizeof(party));
 starter=0;ApplyThomasMtMoonStarterBranch(party,TRAINER_THOMAS_MT_MOON);assert(!memcmp(before,party,sizeof(party)));
 starter=1;ApplyThomasMtMoonStarterBranch(party,TRAINER_THOMAS_MT_MOON);assert(party[1].species==SPECIES_CUBONE&&party[1].ability==1&&party[1].held==ITEM_THICK_CLUB);assert(party[1].moves[0]==MOVE_BONE_CLUB&&party[1].moves[1]==MOVE_HEADBUTT&&party[1].moves[2]==MOVE_GROWL&&party[1].moves[3]==MOVE_TAIL_WHIP);
 starter=2;ApplyThomasMtMoonStarterBranch(party,TRAINER_THOMAS_MT_MOON);assert(party[1].species==SPECIES_DRATINI&&party[1].ability==0&&party[1].held==ITEM_DRAGON_FANG);assert(party[1].moves[0]==MOVE_TWISTER&&party[1].moves[1]==MOVE_THUNDER_WAVE&&party[1].moves[2]==MOVE_WRAP&&party[1].moves[3]==MOVE_LEER);
 assert(party[1].level==15&&party[1].iv==0&&party[1].personality==1234&&party[1].ot==5678);assert(party[0].species==SPECIES_GASTLY);
 memcpy(before,party,sizeof(party));starter=1;ApplyThomasMtMoonStarterBranch(party,TRAINER_THOMAS_CINNABAR_MANSION);assert(!memcmp(before,party,sizeof(party)));
 return 0;
}
''')
    subprocess.run(['gcc', '-std=c99', '-Werror', '-I'+tmp, '-I'+str(ROOT/'include'), str(ROOT/'src/sam_thomas_mt_moon.c'), str(p/'test.c'), '-o', str(p/'test')], check=True)
    subprocess.run([str(p/'test')], check=True)

map_path = 'data/maps/MtMoon_B2F/map.json'
a = json.loads(old(map_path)); b = json.loads((ROOT/map_path).read_text())
assert b['object_events'][:len(a['object_events'])] == a['object_events']
for k in a:
    if k != 'object_events': assert a[k] == b[k], k
assert len(b['object_events']) == len(a['object_events'])+2
s = (ROOT/'data/maps/MtMoon_B2F/scripts.inc').read_text()
for i in range(1,5):
    label=f'MtMoon_B2F_EventScript_Grunt{i}::'
    assert s[s.index(label):].split('\n\n',1)[0] == label + old('data/maps/MtMoon_B2F/scripts.inc').split(label,1)[1].split('\n\n',1)[0]
# Later Cinnabar/Viridian Thomas implementations intentionally change
# trainer packages. Mt. Moon regression checks trainer symbol continuity,
# not byte-for-byte equality against the pre-Cinnabar historical baseline.
current_trainers=(ROOT/'src/data/trainers.h').read_text()
for name in re.findall(r'\[TRAINER_THOMAS_[A-Z_]+\]',old('src/data/trainers.h')):
    assert name in current_trainers, name
assert (ROOT/'src/data/sam_thomas_trainer_parties.h').exists()
assert (ROOT/'src/sam_thomas_trainer_traits.c').exists()
print('PASS: actual helper 0/1/2 usable, all party positions, egg/fainted exclusions, scoped fallback, all starter branches; Thomas trainer symbols and original map content preserved')
