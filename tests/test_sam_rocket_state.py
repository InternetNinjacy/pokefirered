#!/usr/bin/env python3
"""Host-check the actual shared helper and execute Viridian transaction scripts."""
from pathlib import Path
from collections import defaultdict
import json
import re
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
BASE = '3d4063a825b914cbc9d8b50f9c8a00dd4b43e341'
def old(path):
    return subprocess.check_output(['git', 'show', BASE + ':' + path], cwd=ROOT, text=True)

with tempfile.TemporaryDirectory() as tmp:
    p = Path(tmp)
    (p/'global.h').write_text('#include <stdint.h>\ntypedef uint16_t u16; typedef uint8_t bool8;\n')
    (p/'event_data.h').write_text('#include "global.h"\nextern u16 gSpecialVar_0x8004, gSpecialVar_Result;\nu16 VarGet(u16); void VarSet(u16,u16);\n')
    (p/'test.c').write_text('''#include "global.h"
#include "constants/vars.h"
#include "constants/sam_rocket.h"
#include <assert.h>
u16 gSpecialVar_0x8004,gSpecialVar_Result; static u16 ops,evidence;
u16 VarGet(u16 v) {assert(v==VAR_SAM_ROCKET_OPERATIONS||v==VAR_SAM_ROCKET_EVIDENCE);return v==VAR_SAM_ROCKET_OPERATIONS?ops:evidence;}
void VarSet(u16 v,u16 n) {if(v==VAR_SAM_ROCKET_OPERATIONS)ops=n;else {assert(v==VAR_SAM_ROCKET_EVIDENCE);evidence=n;}}
void Script_SamRocketCompleteOperation(void); void Script_SamRocketCheckOperation(void);
void Script_SamRocketRecordEvidence(void); void Script_SamRocketCheckEvidence(void);
int main(void) {
 unsigned i; u16 before;
 for(i=0;i<16;i++) {
  gSpecialVar_0x8004=1u<<i; before=ops;Script_SamRocketCompleteOperation();
  assert(gSpecialVar_Result==(i<11));assert(ops==(i<11?(before|(1u<<i)):before));
  Script_SamRocketCheckOperation();assert(gSpecialVar_Result==(i<11));assert(evidence==0);
 }
 assert(ops==ROCKET_OPERATION_MASK);before=ops;
 for(i=0;i<65536;i++) {gSpecialVar_0x8004=i;Script_SamRocketCompleteOperation();assert(ops==before);}
 for(i=0;i<16;i++) {
  gSpecialVar_0x8004=1u<<i; before=evidence;Script_SamRocketRecordEvidence();
  assert(gSpecialVar_Result==(i<4));
  assert(evidence==(i<4?before|(1u<<i):before));
  Script_SamRocketCheckEvidence();assert(gSpecialVar_Result==(i<4));
 }
 assert(evidence==ROCKET_EVIDENCE_BOUND_MASK);before=evidence;
 for(i=0;i<65536;i++) {gSpecialVar_0x8004=i;Script_SamRocketRecordEvidence();assert(evidence==before);}
 // Preserve unrelated/reserved saved bits rather than overwriting state.
 ops=0x8000;evidence=0x4000;gSpecialVar_0x8004=1;Script_SamRocketCompleteOperation();Script_SamRocketRecordEvidence();assert(ops==0x8001&&evidence==0x4001);
 return 0;
}
''')
    subprocess.run(['gcc','-std=c99','-Wall','-Werror','-I'+tmp,'-I'+str(ROOT/'include'),str(ROOT/'src/sam_rocket_state.c'),str(p/'test.c'),'-o',str(p/'test')],check=True)
    subprocess.run([str(p/'test')],check=True)

# Execute the actual straight-line script commands/control flow. Native bit
# helpers are checked separately above; text, movement and warp are not emulated.
source = '\n'.join((ROOT/f).read_text() for f in ['data/maps/ViridianCity/scripts.inc','data/maps/ViridianCity_Mart/scripts.inc'])
labels={}; code=[]
for line in source.splitlines():
    line=line.strip()
    if not line or line.startswith('@'):continue
    if line.endswith('::'):labels[line[:-2]]=len(code)
    else:code.append(line)
const={'FALSE':0,'TRUE':1,'ROCKET_VIRIDIAN_PENDING':0,'ROCKET_VIRIDIAN_GOODS_RECOVERED':1,'ROCKET_VIRIDIAN_BALLS_OWED':2,'ROCKET_VIRIDIAN_DOSSIER_OWED':3,'ROCKET_VIRIDIAN_COMPLETE':4,'ROCKET_EVIDENCE_DELIVERY_01':1,'ROCKET_OPERATION_VIRIDIAN_THEFT':1}
class VM:
    def __init__(self):
        self.vars=defaultdict(int);self.items=defaultdict(int);self.flags={'FLAG_SYS_POKEDEX_GET'};self.blocked=set();self.messages=[];self.loss=False;self.ended=''
    def value(self,x):return const[x] if x in const else (int(x) if x.isdigit() else self.vars[x])
    def run(self,label):
        pc=labels[label]
        for _ in range(300):
            line=code[pc];pc+=1;op,*rest=line.split(' ',1);a=[x.strip() for x in rest[0].split(',')] if rest else []
            if op=='setvar':self.vars[a[0]]=self.value(a[1])
            elif op=='setflag':self.flags.add(a[0])
            elif op=='clearflag':self.flags.discard(a[0])
            elif op=='goto':pc=labels[a[0]]
            elif op in ('goto_if_eq','goto_if_ne','goto_if_ge'):
                x,y=self.value(a[0]),self.value(a[1]);ok={'goto_if_eq':x==y,'goto_if_ne':x!=y,'goto_if_ge':x>=y}[op]
                if ok:pc=labels[a[2]]
            elif op=='goto_if_unset':
                if a[0] not in self.flags:self.ended='guard';return
            elif op=='goto_if_questlog':pass
            elif op=='checkitem':self.vars['VAR_RESULT']=int(self.items[a[0]]>=self.value(a[1]))
            elif op=='checkitemspace':self.vars['VAR_RESULT']=int(a[0] not in self.blocked)
            elif op=='giveitem':
                self.vars['VAR_RESULT']=int(a[0] not in self.blocked)
                if self.vars['VAR_RESULT']:self.items[a[0]]+=self.value(a[1])
            elif op=='callnative':
                var='VAR_SAM_ROCKET_EVIDENCE' if a[0]=='Script_SamRocketRecordEvidence' else 'VAR_SAM_ROCKET_OPERATIONS'
                self.vars[var]|=self.vars['VAR_0x8004'];self.vars['VAR_RESULT']=1
            elif op=='trainerbattle_no_intro' and self.loss:self.ended='blackout';return
            elif op=='msgbox':self.messages.append(a[0])
            elif op in ('end','return','pokemart'):self.ended=op;return
            elif op in ('lock','lockall','release','releaseall','faceplayer','textcolor','closemessage','applymovement','waitmovement','removeobject','trainerbattle_no_intro','warp','waitstate','message','waitmessage'):pass
            else:raise AssertionError(line)
        raise AssertionError('script did not terminate')

v=VM();v.loss=True;v.run('ViridianCity_EventScript_RocketOperation');assert v.ended=='blackout' and v.vars['VAR_SAM_ROCKET_VIRIDIAN']==0 and not v.items and 'FLAG_HIDE_ROCKET_VIRIDIAN_OPERATION' not in v.flags
v=VM();v.flags.clear();v.run('ViridianCity_EventScript_RocketOperation');assert v.ended=='guard' and not v.items
for balls_full in (False,True):
 for keys_full in (False,True):
  for carried_dossier in (False,True):
   v=VM();v.items['ITEM_ROCKET_DOSSIER']=int(carried_dossier);v.run('ViridianCity_EventScript_RocketOperation');assert v.vars['VAR_SAM_ROCKET_VIRIDIAN']==1 and not v.vars['VAR_SAM_ROCKET_OPERATIONS'] and not v.vars['VAR_SAM_ROCKET_EVIDENCE']
   if balls_full:v.blocked.add('ITEM_POKE_BALL')
   if keys_full:v.blocked.add('ITEM_ROCKET_DOSSIER')
   v.run('ViridianCity_Mart_EventScript_ReturnRocketGoods')
   stage=2 if balls_full else (3 if keys_full and not carried_dossier else 4)
   assert v.vars['VAR_SAM_ROCKET_VIRIDIAN']==stage
   for _ in range(3):
    if stage<4:v.run('ViridianCity_Mart_EventScript_Clerk')
   assert v.items['ITEM_POKE_BALL']==(0 if balls_full else 5)
   v.blocked.clear()
   if stage<4:v.run('ViridianCity_Mart_EventScript_Clerk')
   assert v.vars['VAR_SAM_ROCKET_VIRIDIAN']==4 and v.items['ITEM_POKE_BALL']==5 and v.items['ITEM_ROCKET_DOSSIER']==1
   assert v.vars['VAR_SAM_ROCKET_OPERATIONS']==1 and v.vars['VAR_SAM_ROCKET_EVIDENCE']==1
   v.run('ViridianCity_Mart_EventScript_Clerk');assert v.ended=='pokemart' and v.items['ITEM_POKE_BALL']==5 and v.items['ITEM_ROCKET_DOSSIER']==1

# Delivery 02 is bound only after the successful physical Mt. Moon theft.
mtmoon=(ROOT/'data/maps/MtMoon_B2F/scripts.inc').read_text()
theft=mtmoon[mtmoon.index('MtMoon_B2F_EventScript_TheftComplete::'):].split('\n\n',1)[0]
assert 'ROCKET_OPERATION_MT_MOON' in theft
assert 'Script_SamRocketCompleteOperation' in theft
assert 'ROCKET_EVIDENCE_DELIVERY_02' in theft
assert 'Script_SamRocketRecordEvidence' in theft
assert theft.index('ROCKET_OPERATION_MT_MOON') < theft.index('ROCKET_EVIDENCE_DELIVERY_02')
dossier=(ROOT/'data/scripts/sam_rocket.inc').read_text()
assert 'SamRocket_EventScript_ReadDelivery02::' in dossier
assert 'MT. MOON ACQUISITION -\\n' in dossier
assert 'UNCHOSEN FOSSIL - SECURED' in dossier
assert 'THOMAS RETAINS ASSET' in dossier

# Existing maps, trainer records and warehouse work must survive reconciliation.
path='data/maps/ViridianCity/map.json';a=json.loads(old(path));b=json.loads((ROOT/path).read_text())
assert b['object_events'][:len(a['object_events'])]==a['object_events']
assert b['coord_events'][:len(a['coord_events'])]==a['coord_events']
for k in a:
 if k not in ('object_events','coord_events'):assert a[k]==b[k],k
assert len(b['object_events'])==12
# map_events.s does not import the operation header; use the numeric scene value.
assert b['coord_events'][-1]['var_value']=='0'
for path in ['src/data/trainers.h']:
 for name in re.findall(r'\[TRAINER_[A-Z0-9_]+\]',old(path)):
  pattern=re.escape(name)+r' = \{.*?\n    \},'
  assert re.search(pattern,old(path),re.S).group()==re.search(pattern,(ROOT/path).read_text(),re.S).group(),name
for path in ['data/maps/FiveIsland_RocketWarehouse/scripts.inc','data/maps/FiveIsland_RocketWarehouse/map.json','src/battle_ai_switch_items.c','src/new_game.c','data/maps/MtMoon_B2F/scripts.inc']:
 assert (ROOT/path).read_text()==old(path),path
items=json.loads((ROOT/'src/data/items.json').read_text())['items'];baseline=json.loads(old('src/data/items.json'))['items']
assert len(items)==len(baseline)==375
assert all(items[i]==baseline[i] for i in range(375) if i!=247)
assert len(items[247]['english'])<14 and items[247]['registrability']==0
print('PASS: actual state helper, invalid/combined bits, persistence; loss, reward capacity/retry, exactly-five Balls, NG+ Dossier carryover; production map/trainer/warehouse/Thomas preservation')
