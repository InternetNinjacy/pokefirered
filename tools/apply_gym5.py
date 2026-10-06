from pathlib import Path
import re

PARTIES = Path('src/data/trainer_parties.h')
TRAINERS = Path('src/data/trainers.h')
SCRIPTS = Path('data/maps/FuchsiaCity_Gym/scripts.inc')
TEXT = Path('data/maps/FuchsiaCity_Gym/text.inc')

parties = PARTIES.read_text()
trainers = TRAINERS.read_text()

def replace_party(name, struct_type, mons):
    global parties
    pat = re.compile(rf'static const struct \w+ {re.escape(name)}\[\] = \{{.*?\n\}};', re.S)
    m = pat.search(parties)
    if not m:
        raise SystemExit(f'Party block not found: {name}')
    old_ivs = [int(x) for x in re.findall(r'\.iv\s*=\s*(\d+)', m.group(0))] or [0]
    while len(old_ivs) < len(mons):
        old_ivs.append(old_ivs[-1])
    lines = [f'static const struct {struct_type} {name}[] = {{']
    for i, (species, lvl, moves, item) in enumerate(mons):
        lines += ['    {', f'        .iv = {old_ivs[i]},', f'        .lvl = {lvl},', f'        .species = SPECIES_{species},']
        if item is not None:
            lines.append(f'        .heldItem = {item},')
        lines.append('        .moves = {' + ', '.join('MOVE_' + x for x in moves) + '},')
        lines.append('    },')
    lines.append('};')
    parties = parties[:m.start()] + '\n'.join(lines) + parties[m.end():]

regular = {
    'sParty_JugglerNate': [
        ('RATICATE',34,['HYPER_FANG','QUICK_ATTACK','PURSUIT','SCARY_FACE'],None),
        ('FARFETCHD',34,['PECK','KNOCK_OFF','FURY_CUTTER','SWORDS_DANCE'],None)],
    'sParty_JugglerKayden': [('KANGASKHAN',38,['FAKE_OUT','MEGA_PUNCH','BITE','ENDURE'],None)],
    'sParty_JugglerKirk': [
        ('CLEFAIRY',31,['DOUBLE_SLAP','SING','ENCORE','METRONOME'],None),
        ('MEOWTH',31,['PAY_DAY','BITE','FAINT_ATTACK','SCREECH'],None),
        ('EEVEE',31,['QUICK_ATTACK','BITE','SAND_ATTACK','GROWL'],None),
        ('DODUO',31,['TRI_ATTACK','PECK','PURSUIT','FURY_ATTACK'],None)],
    'sParty_TamerEdgar': [
        ('LICKITUNG',33,['BODY_SLAM','KNOCK_OFF','ASTONISH','DISABLE'],None),
        ('DODRIO',33,['TRI_ATTACK','PECK','PURSUIT','FURY_ATTACK'],None),
        ('CHANSEY',33,['DOUBLE_SLAP','SOFT_BOILED','SING','TAIL_WHIP'],None)],
    'sParty_TamerPhil': [
        ('FEAROW',34,['PECK','FURY_ATTACK','PURSUIT','MIRROR_MOVE'],None),
        ('WIGGLYTUFF',34,['BODY_SLAM','ROLLOUT','REST','SING'],None)],
    'sParty_JugglerShawn': [
        ('PORYGON',34,['PSYBEAM','RECOVER','AGILITY','CONVERSION_2'],None),
        ('CLEFABLE',34,['DOUBLE_SLAP','SING','METRONOME','COSMIC_POWER'],None)],
}

for name, mons in regular.items():
    replace_party(name, 'TrainerMonNoItemCustomMoves', mons)

replace_party('sParty_LeaderKoga', 'TrainerMonItemCustomMoves', [
    ('DITTO',37,['TRANSFORM','NONE','NONE','NONE'],'ITEM_QUICK_CLAW'),
    ('PERSIAN',38,['FAKE_OUT','SLASH','BITE','SCREECH'],'ITEM_NONE'),
    ('SNORLAX',39,['BODY_SLAM','BRICK_BREAK','REST','SHADOW_BALL'],'ITEM_LEFTOVERS'),
    ('TAUROS',41,['BODY_SLAM','EARTHQUAKE','ROCK_TOMB','SCARY_FACE'],'ITEM_SILK_SCARF'),
    ('PORYGON2',43,['TRI_ATTACK','PSYCHIC','RECOVER','THUNDER_WAVE'],'ITEM_LUM_BERRY'),
])

for party_name in regular:
    trainers, n = re.subn(rf'\b[A-Z_]+\({re.escape(party_name)}\)', f'NO_ITEM_CUSTOM_MOVES({party_name})', trainers, count=1)
    if n != 1:
        raise SystemExit(f'Trainer party ref replacement failed: {party_name}: {n}')
trainers, n = re.subn(r'\b[A-Z_]+\(sParty_LeaderKoga\)', 'ITEM_CUSTOM_MOVES(sParty_LeaderKoga)', trainers, count=1)
if n != 1:
    raise SystemExit(f'Koga party ref replacement failed: {n}')

km = re.search(r'(\[TRAINER_LEADER_KOGA\]\s*=\s*\{.*?\n    \},)', trainers, re.S)
if not km:
    raise SystemExit('Koga trainer record not found')
koga, n = re.subn(r'\.aiFlags\s*=\s*[^,]+,', '.aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,', km.group(1), count=1)
if n != 1:
    raise SystemExit('Koga AI replacement failed')
trainers = trainers[:km.start(1)] + koga + trainers[km.end(1):]

PARTIES.write_text(parties)
TRAINERS.write_text(trainers)

SCRIPTS.write_text('''FuchsiaCity_Gym_MapScripts::
\t.byte 0

FuchsiaCity_Gym_EventScript_Koga::
\tfamechecker FAMECHECKER_KOGA, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
\ttrainerbattle_single TRAINER_LEADER_KOGA, FuchsiaCity_Gym_Text_KogaIntro, FuchsiaCity_Gym_Text_KogaDefeat, FuchsiaCity_Gym_EventScript_DefeatedKoga, NO_MUSIC
\tgoto_if_unset FLAG_GOT_TM06_FROM_KOGA, FuchsiaCity_Gym_EventScript_GiveTM42
\tmsgbox FuchsiaCity_Gym_Text_KogaPostBattle
\trelease
\tend

FuchsiaCity_Gym_EventScript_DefeatedKoga::
\tfamechecker FAMECHECKER_KOGA, 1
\tclearflag FLAG_HIDE_FAME_CHECKER_KOGA_JOURNAL
\tsetflag FLAG_DEFEATED_KOGA
\tsetflag FLAG_BADGE05_GET
\tset_gym_trainers 5
\tgoto FuchsiaCity_Gym_EventScript_GiveTM42
\tend

FuchsiaCity_Gym_EventScript_GiveTM42::
\tmsgbox FuchsiaCity_Gym_Text_KogaExplainVeilBadge
\tcheckitemspace ITEM_TM42
\tgoto_if_eq VAR_RESULT, FALSE, FuchsiaCity_Gym_EventScript_NoRoomForTM42
\tgiveitem_msg FuchsiaCity_Gym_Text_ReceivedTM42FromKoga, ITEM_TM42
\tsetflag FLAG_GOT_TM06_FROM_KOGA
\tmsgbox FuchsiaCity_Gym_Text_KogaExplainTM42
\trelease
\tend

FuchsiaCity_Gym_EventScript_NoRoomForTM42::
\tmsgbox FuchsiaCity_Gym_Text_MakeSpaceForThis
\trelease
\tend

FuchsiaCity_Gym_EventScript_Phil::
\ttrainerbattle_single TRAINER_TAMER_PHIL, FuchsiaCity_Gym_Text_PhilIntro, FuchsiaCity_Gym_Text_PhilDefeat
\tmsgbox FuchsiaCity_Gym_Text_PhilPostBattle, MSGBOX_AUTOCLOSE
\tend

FuchsiaCity_Gym_EventScript_Edgar::
\ttrainerbattle_single TRAINER_TAMER_EDGAR, FuchsiaCity_Gym_Text_EdgarIntro, FuchsiaCity_Gym_Text_EdgarDefeat
\tmsgbox FuchsiaCity_Gym_Text_EdgarPostBattle, MSGBOX_AUTOCLOSE
\tend

FuchsiaCity_Gym_EventScript_Kirk::
\ttrainerbattle_single TRAINER_JUGGLER_KIRK, FuchsiaCity_Gym_Text_KirkIntro, FuchsiaCity_Gym_Text_KirkDefeat
\tfamechecker FAMECHECKER_KOGA, 2
\tmsgbox FuchsiaCity_Gym_Text_KirkPostBattle, MSGBOX_AUTOCLOSE
\tend

FuchsiaCity_Gym_EventScript_Shawn::
\ttrainerbattle_single TRAINER_JUGGLER_SHAWN, FuchsiaCity_Gym_Text_ShawnIntro, FuchsiaCity_Gym_Text_ShawnDefeat
\tmsgbox FuchsiaCity_Gym_Text_ShawnPostBattle, MSGBOX_AUTOCLOSE
\tend

FuchsiaCity_Gym_EventScript_Kayden::
\ttrainerbattle_single TRAINER_JUGGLER_KAYDEN, FuchsiaCity_Gym_Text_KaydenIntro, FuchsiaCity_Gym_Text_KaydenDefeat
\tmsgbox FuchsiaCity_Gym_Text_KaydenPostBattle, MSGBOX_AUTOCLOSE
\tend

FuchsiaCity_Gym_EventScript_Nate::
\ttrainerbattle_single TRAINER_JUGGLER_NATE, FuchsiaCity_Gym_Text_NateIntro, FuchsiaCity_Gym_Text_NateDefeat
\tmsgbox FuchsiaCity_Gym_Text_NatePostBattle, MSGBOX_AUTOCLOSE
\tend

FuchsiaCity_Gym_EventScript_GymGuy::
\tlock
\tfaceplayer
\tgoto_if_set FLAG_DEFEATED_KOGA, FuchsiaCity_Gym_EventScript_GymGuyPostVictory
\tmsgbox FuchsiaCity_Gym_Text_GymGuyAdvice
\trelease
\tend

FuchsiaCity_Gym_EventScript_GymGuyPostVictory::
\tmsgbox FuchsiaCity_Gym_Text_GymGuyPostVictory
\trelease
\tend

FuchsiaCity_Gym_EventScript_GymStatue::
\tlockall
\tgoto_if_set FLAG_BADGE05_GET, FuchsiaCity_Gym_EventScript_GymStatuePostVictory
\tmsgbox FuchsiaCity_Gym_Text_GymStatue
\treleaseall
\tend

FuchsiaCity_Gym_EventScript_GymStatuePostVictory::
\tmsgbox FuchsiaCity_Gym_Text_GymStatuePlayerWon
\treleaseall
\tend
''')

TEXT.write_text(r'''FuchsiaCity_Gym_Text_KogaIntro::
    .string "KOGA: Fwahahaha! A mere child dares\n"
    .string "challenge me?\p"
    .string "Very well. I am KOGA, master of\n"
    .string "techniques that leave an opponent\l"
    .string "doubting their own eyes.\p"
    .string "A careless TRAINER sees what stands\n"
    .string "before them and assumes they\l"
    .string "understand it. A skilled one asks\l"
    .string "what has been hidden... and why.\p"
    .string "My POKéMON may appear ordinary.\n"
    .string "That is precisely when you should\l"
    .string "be most cautious.\p"
    .string "Come! Let us see whether you can\n"
    .string "find the truth before the illusion\l"
    .string "closes around you!{PLAY_BGM}{MUS_ENCOUNTER_GYM_LEADER}$"

FuchsiaCity_Gym_Text_KogaDefeat::
    .string "Humph! You refused every false\n"
    .string "trail I laid before you.\p"
    .string "You did not battle the opponent you\n"
    .string "expected. You battled the one\l"
    .string "actually in front of you.\p"
    .string "Excellent. That kind of awareness\n"
    .string "is difficult to deceive.$"

FuchsiaCity_Gym_Text_KogaPostBattle::
    .string "Do not battle the opponent you\n"
    .string "imagine. Battle the one who is\l"
    .string "truly before you.\p"
    .string "Question what seems obvious, and\n"
    .string "even the finest deception will\l"
    .string "eventually reveal its seams.$"

FuchsiaCity_Gym_Text_KogaExplainVeilBadge::
    .string "Fwahahaha! You have earned this -\n"
    .string "the VEIL BADGE!\p"
    .string "It is proof that you can look past\n"
    .string "appearances and find the truth\l"
    .string "hidden beneath them.\p"
    .string "The VEIL BADGE also allows you to\n"
    .string "use SURF outside of battle, as long\l"
    .string "as one of your POKéMON knows the\l"
    .string "move.$"

FuchsiaCity_Gym_Text_ReceivedTM42FromKoga::
    .string "{PLAYER} received TM42\n"
    .string "from KOGA.$"

FuchsiaCity_Gym_Text_KogaExplainTM42::
    .string "Take this as well. TM42 contains\n"
    .string "FACADE.\p"
    .string "It appears to be a simple attack...\n"
    .string "until its user is poisoned,\l"
    .string "paralyzed, or burned. Then its true\l"
    .string "strength is revealed.\p"
    .string "Remember that lesson. What seems\n"
    .string "like a weakness may be hiding a\l"
    .string "weapon.$"

FuchsiaCity_Gym_Text_MakeSpaceForThis::
    .string "Make space for this, child!$"

FuchsiaCity_Gym_Text_NateIntro::
    .string "What you notice first is exactly\n"
    .string "what I want you looking at.\p"
    .string "Keep your eyes on the obvious...\n"
    .string "and you may miss the real attack!$"

FuchsiaCity_Gym_Text_NateDefeat::
    .string "You saw through the distraction!$"

FuchsiaCity_Gym_Text_NatePostBattle::
    .string "A good feint does not have to fool\n"
    .string "you forever. It only needs to fool\l"
    .string "you for one move.$"

FuchsiaCity_Gym_Text_KaydenIntro::
    .string "I'll show you something easy to\n"
    .string "read. The question is whether\l"
    .string "you'll believe it.$"

FuchsiaCity_Gym_Text_KaydenDefeat::
    .string "Hah! You didn't take the bait!$"

FuchsiaCity_Gym_Text_KaydenPostBattle::
    .string "KOGA says an opponent who thinks\n"
    .string "they understand you is easier to\l"
    .string "control than one who knows they\l"
    .string "don't.$"

FuchsiaCity_Gym_Text_KirkIntro::
    .string "Watch closely! The trick is not\n"
    .string "making something disappear.\p"
    .string "It is making you look in the wrong\n"
    .string "place.$"

FuchsiaCity_Gym_Text_KirkDefeat::
    .string "You kept your attention where it\n"
    .string "mattered!$"

FuchsiaCity_Gym_Text_KirkPostBattle::
    .string "Battles are full of little\n"
    .string "distractions. Moves, types, habits...\l"
    .string "even confidence can be used against\l"
    .string "you.$"

FuchsiaCity_Gym_Text_EdgarIntro::
    .string "Normal POKéMON can look\n"
    .string "straightforward. That makes it easy\l"
    .string "to forget how many different ways\l"
    .string "they can fight.$"

FuchsiaCity_Gym_Text_EdgarDefeat::
    .string "You were ready for more than one\n"
    .string "answer!$"

FuchsiaCity_Gym_Text_EdgarPostBattle::
    .string "Never confuse ordinary with\n"
    .string "predictable. KOGA certainly\l"
    .string "doesn't.$"

FuchsiaCity_Gym_Text_PhilIntro::
    .string "Go ahead. Decide what my plan is\n"
    .string "before we start. I'd love that.$"

FuchsiaCity_Gym_Text_PhilDefeat::
    .string "So much for catching you by\n"
    .string "surprise!$"

FuchsiaCity_Gym_Text_PhilPostBattle::
    .string "Assumptions save time... right up\n"
    .string "until somebody builds a trap around\l"
    .string "them.$"

FuchsiaCity_Gym_Text_ShawnIntro::
    .string "By the time you reach KOGA, you\n"
    .string "should know better than to trust\l"
    .string "the first thing you see.\p"
    .string "Shall I test that?$"

FuchsiaCity_Gym_Text_ShawnDefeat::
    .string "You didn't give me the opening I\n"
    .string "wanted.$"

FuchsiaCity_Gym_Text_ShawnPostBattle::
    .string "Good. KOGA's strongest weapon is\n"
    .string "not secrecy. It is making you\l"
    .string "certain about the wrong thing.$"

FuchsiaCity_Gym_Text_GymGuyAdvice::
    .string "Yo! Champ in the making!\p"
    .string "FUCHSIA GYM is built to make you\n"
    .string "trust what you see. Don't.\p"
    .string "Its invisible walls hide the path\n"
    .string "to KOGA. Look closely for the gaps.$"

FuchsiaCity_Gym_Text_GymGuyPostVictory::
    .string "You saw through KOGA's tricks.\n"
    .string "That's what a champ needs!$"

FuchsiaCity_Gym_Text_GymStatue::
    .string "FUCHSIA POKéMON GYM\n"
    .string "LEADER: KOGA\p"
    .string "WINNING TRAINERS:\n"
    .string "{RIVAL}$"

FuchsiaCity_Gym_Text_GymStatuePlayerWon::
    .string "FUCHSIA POKéMON GYM\n"
    .string "LEADER: KOGA\p"
    .string "WINNING TRAINERS:\n"
    .string "{RIVAL}, {PLAYER}$"
''')

required = ['SPECIES_PORYGON2','ITEM_QUICK_CLAW','ITEM_LEFTOVERS','ITEM_SILK_SCARF','ITEM_LUM_BERRY','MOVE_KNOCK_OFF','MOVE_COSMIC_POWER','MOVE_CONVERSION_2','MOVE_BRICK_BREAK','MOVE_ROCK_TOMB']
haystack = '\n'.join(Path(p).read_text(errors='ignore') for p in ['include/constants/species.h','include/constants/items.h','include/constants/moves.h'])
missing = [x for x in required if x not in haystack]
if missing:
    raise SystemExit('Missing constants: ' + ', '.join(missing))
combined = SCRIPTS.read_text() + TEXT.read_text()
stale = [x for x in ['ITEM_TM06','SOULBADGE','POISON-type POKéMON','TOXIC!'] if x in combined]
if stale:
    raise SystemExit('Stale Gym 5 content remains: ' + ', '.join(stale))
