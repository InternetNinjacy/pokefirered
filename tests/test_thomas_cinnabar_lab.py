#!/usr/bin/env python3
"""Execute the authored Lab script paths under a small event-command harness.

This is static/host verification, not assembled-ROM movement or gameplay QA.
"""
from pathlib import Path
from itertools import product
import json
import re
import struct
import subprocess

ROOT = Path(__file__).resolve().parents[1]
BASE = '8c3bbdaaae97ff1e4c446aca7dbbcf8209d7fdf2'
MAP = 'data/maps/CinnabarIsland_PokemonLab_Entrance/'
source = (ROOT / (MAP + 'scripts.inc')).read_text()
labels = {}
current = None
for line in source.splitlines():
    if line.endswith('::'):
        current = line[:-2]
        labels[current] = []
    elif current and line.strip() and not line.strip().startswith('.'):
        labels[current].append(line.strip())

prefix = 'CinnabarIsland_PokemonLab_Entrance_'
complete = 'FLAG_THOMAS_CINNABAR_LAB_COMPLETE'
hide = 'FLAG_HIDE_THOMAS_CINNABAR_LAB'
stage = 'VAR_THOMAS_ARC_STAGE'
theft = 'VAR_MAP_SCENE_MT_MOON_B2F'
revive = 'VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_REVIVE_STATE'

def execute(label, state, xy=(4, 8), questlog=False):
    stack = []
    pc = 0
    while True:
        line = labels[label][pc]
        pc += 1
        cmd, _, tail = line.partition(' ')
        args = [a.strip() for a in tail.split(',')]
        def value(a):
            if a == 'THOMAS_ARC_SILPH_CLEARED':
                return 4
            if a.isdigit():
                return int(a)
            return state['vars'].get(a, 0)
        target = None
        if cmd == 'setvar':
            state['vars'][args[0]] = value(args[1])
        elif cmd in ('setflag', 'clearflag'):
            state['flags'][args[0]] = cmd == 'setflag'
        elif cmd == 'getplayerxy':
            state['vars'][args[0]], state['vars'][args[1]] = xy
        elif cmd == 'goto_if_questlog':
            if questlog:
                target = args[0]
        elif cmd in ('goto_if_set', 'goto_if_unset', 'call_if_set', 'call_if_unset'):
            if state['flags'].get(args[0], False) == cmd.endswith('_set'):
                target = args[1]
        elif cmd.startswith(('goto_if_', 'call_if_')):
            a, b = value(args[0]), value(args[1])
            condition = {'eq': a == b, 'ne': a != b, 'lt': a < b, 'gt': a > b}[cmd.rsplit('_', 1)[1]]
            if condition:
                target = args[2]
        elif cmd == 'msgbox':
            state['messages'] += 1
        elif cmd == 'applymovement':
            state['movements'].append(args)
        elif cmd == 'removeobject':
            state['removed'].append(args[0])
        elif cmd == 'end':
            return
        elif cmd == 'return':
            label, pc = stack.pop()
        elif cmd in ('lockall', 'releaseall', 'waitmovement'):
            pass
        else:
            raise AssertionError('Unmodelled event command: ' + line)
        if target:
            if cmd.startswith('call_'):
                stack.append((label, pc))
            label, pc = target, 0
        # The dialogue is intentionally reached by fallthrough.
        if pc == len(labels[label]):
            assert label == prefix + 'EventScript_ThomasExit'
            label, pc = prefix + 'EventScript_ThomasDialogue', 0

for fossil, arc, done, quit_, restoration, researcher in product(range(5), range(8), (False, True), (False, True), range(3), (False, True)):
    state = {'vars': {theft: fossil, stage: arc, revive: restoration},
             'flags': {complete: done, 'FLAG_THOMAS_QUIT_ROCKET': quit_,
                       'FLAG_GOT_DOME_FOSSIL': fossil == 4 or researcher,
                       'FLAG_GOT_HELIX_FOSSIL': fossil == 3 or researcher},
             'inventory': ['player fossil'] if restoration == 0 else [],
             'messages': 0, 'movements': [], 'removed': []}
    inventory = state['inventory'][:]
    choice = {k: v for k, v in state['flags'].items() if k.startswith('FLAG_GOT_')}
    execute(prefix + 'OnTransition', state)
    eligible = fossil in (3, 4) and arc == 4 and not done and not quit_
    assert state['flags'][hide] == (not eligible)
    assert state['vars']['VAR_TEMP_0'] == eligible
    assert state['vars'][revive] == (2 if restoration == 1 else restoration)
    if eligible:
        execute(prefix + 'EventScript_ThomasExit', state)
        assert state['messages'] == 1 and state['flags'][complete] and state['flags'][hide]
        assert state['removed'] == ['LOCALID_THOMAS_LAB']
        # Serialized state is sufficient because only normal event storage is used.
        state = json.loads(json.dumps(state))
        execute(prefix + 'OnTransition', state)
        assert state['vars']['VAR_TEMP_0'] == 0 and state['flags'][hide]
    assert state['vars'][stage] == arc and state['vars'][theft] == fossil
    assert state['inventory'] == inventory
    assert {k: v for k, v in state['flags'].items() if k.startswith('FLAG_GOT_')} == choice

# All three entrance tiles and both possible arrival rows clear the exit path.
for x, y in product((3, 4, 5), (8, 9)):
    s = {'vars': {}, 'flags': {}, 'messages': 0, 'movements': [], 'removed': []}
    execute(prefix + 'EventScript_ThomasExit', s, (x, y))
    assert s['movements'][0][0] == 'OBJ_EVENT_ID_PLAYER'
    assert s['movements'][0][1].endswith('ClearDoorBottom' if y == 9 else 'ClearDoor')

def old(path):
    return subprocess.check_output(['git', 'show', BASE + ':' + path], cwd=ROOT, text=True)

a, b = json.loads(old(MAP + 'map.json')), json.loads((ROOT / (MAP + 'map.json')).read_text())
assert b['object_events'][:-1] == a['object_events']
for key in a:
    if key != 'object_events':
        assert a[key] == b[key], key
for label in re.findall(r'^(\w+)::', old(MAP + 'scripts.inc'), re.M)[2:]:
    def block(s):
        return s.split(label + '::', 1)[1].split('\n\n', 1)[0]
    assert block(source) == block(old(MAP + 'scripts.inc')), label
# Cinnabar Fossil battle and Viridian later updated Thomas party data and
# encounter-chain scripts. This Lab-local test checks symbol preservation,
# while separate downstream tests own final battle continuity.
trainers = (ROOT / 'src/data/trainers.h').read_text()
for name in re.findall(r'\[TRAINER_THOMAS_[A-Z_]+\]', old('src/data/trainers.h')):
    assert name in trainers, name
for path in ('src/data/sam_thomas_trainer_parties.h',
             'src/sam_thomas_trainer_traits.c',
             'data/maps/Route24/thomas_event_chain.inc',
             'data/maps/PokemonMansion_B1F/scripts.inc',
             'data/maps/MtMoon_B2F/scripts.inc',
             'data/maps/CinnabarIsland_PokemonLab_ExperimentRoom/scripts.inc',
             'data/maps/CinnabarIsland_PokemonLab_ResearchRoom/scripts.inc',
             'data/maps/CinnabarIsland_PokemonLab_Lounge/scripts.inc'):
    assert (ROOT / path).exists(), path

# Layout collision bits/elevation for NPC and player movement tiles.
blocks = (ROOT / 'data/layouts/CinnabarIsland_PokemonLab_Entrance/map.bin').read_bytes()
for x, y in ((6, 7), (6, 8), (5, 8), (5, 9), (3, 7), (4, 7), (5, 7)):
    tile = struct.unpack_from('<H', blocks, 2 * (y * 28 + x))[0]
    assert tile & 0xC00 == 0 and tile >> 12 == 3

# NG+ uses normal event initialization and never carries these flags forward.
ng = (ROOT / 'src/new_game.c').read_text()
assert 'InitEventData();' in ng and 'ClearSav1();' in ng
restore = ng.split('static void RestoreNewGamePlusCarryover(struct NewGamePlusCarryover *carryover)\n{', 1)[1].split('\nvoid ResetMenuAndMonGlobals', 1)[0]
assert '->flags' not in restore and '->vars' not in restore
print('PASS: 960 live-script gate/fossil/revival/researcher combinations; one-time completion/re-entry/persistence; entrance paths; maps, parties and Cinnabar systems preserved; NG+ reset contract')
