#include "global.h"
#include "gba/isagbprint.h"
#include "party_menu.h"
#include "pokemon.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

static void QaLog(const char *text)
{
    u32 i = 0;
    while (text[i] != '\0' && i < 255)
    {
        QA_MGBA_DEBUG_STRING[i] = text[i];
        i++;
    }
    QA_MGBA_DEBUG_STRING[i] = '\0';
    *QA_MGBA_DEBUG_FLAGS = MGBA_LOG_INFO | 0x100;
}

static void Fail(const char *text)
{
    QaLog(text);
    for (;;);
}

static void MakeMon(struct Pokemon *mon, u16 species)
{
    CreateMon(mon, species, 50, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
}

static bool8 IndexInList(u8 index, const u8 *list, u8 count)
{
    u8 i;
    for (i = 0; i < count; i++)
        if (list[i] == index)
            return TRUE;
    return FALSE;
}

static void ExpectTmSet(u16 species, const u8 *tmNumbers, u8 tmCount)
{
    struct Pokemon mon;
    u8 i;

    MakeMon(&mon, species);
    for (i = 0; i < NUM_TECHNICAL_MACHINES; i++)
    {
        bool8 expected = IndexInList(i + 1, tmNumbers, tmCount);
        bool8 actual = CanMonLearnTMHM(&mon, i) != 0;
        if (actual != expected)
            Fail("TM004005 FAIL exact TM set");
    }
}

static void ExpectFullSet(u16 species, const u8 *tmNumbers, u8 tmCount, const u8 *hmNumbers, u8 hmCount)
{
    struct Pokemon mon;
    u8 i;

    ExpectTmSet(species, tmNumbers, tmCount);
    MakeMon(&mon, species);
    for (i = 0; i < NUM_HIDDEN_MACHINES; i++)
    {
        bool8 expected = IndexInList(i + 1, hmNumbers, hmCount);
        bool8 actual = CanMonLearnTMHM(&mon, NUM_TECHNICAL_MACHINES + i) != 0;
        if (actual != expected)
            Fail("TM004005 FAIL exact HM set");
    }
}

static void CheckMachineMapping(void)
{
    static const u16 moves[NUM_TECHNICAL_MACHINES + NUM_HIDDEN_MACHINES] =
    {
        MOVE_BODY_SLAM, MOVE_RETURN, MOVE_HYPER_BEAM, MOVE_FACADE, MOVE_PROTECT,
        MOVE_FOCUS_PUNCH, MOVE_BULK_UP, MOVE_BRICK_BREAK, MOVE_SKY_UPPERCUT, MOVE_MACH_PUNCH,
        MOVE_AERIAL_ACE, MOVE_DRILL_PECK, MOVE_SKY_ATTACK, MOVE_TOXIC, MOVE_POISON_FANG,
        MOVE_SLUDGE_BOMB, MOVE_EARTHQUAKE, MOVE_DIG, MOVE_SPIKES, MOVE_MUD_SLAP,
        MOVE_ROCK_TOMB, MOVE_ROCK_SLIDE, MOVE_BOULDER_BASH, MOVE_SANDSTORM, MOVE_FURY_CUTTER,
        MOVE_SIGNAL_BEAM, MOVE_MEGAHORN, MOVE_SHADOW_PUNCH, MOVE_SHADOW_BALL, MOVE_GHOSTLY_WAIL,
        MOVE_METAL_CLAW, MOVE_STEEL_WING, MOVE_METEOR_MASH, MOVE_FIRE_PUNCH, MOVE_FLAMETHROWER,
        MOVE_FIRE_BLAST, MOVE_OVERHEAT, MOVE_SUNNY_DAY, MOVE_WILL_O_WISP, MOVE_WATER_PULSE,
        MOVE_MUDDY_WATER, MOVE_RAIN_DANCE, MOVE_GIGA_DRAIN, MOVE_SEED_STRIKE, MOVE_SOLAR_BEAM,
        MOVE_SHOCK_WAVE, MOVE_THUNDER_PUNCH, MOVE_THUNDERBOLT, MOVE_THUNDER, MOVE_THUNDER_WAVE,
        MOVE_CALM_MIND, MOVE_LIGHT_SCREEN, MOVE_REFLECT, MOVE_PSYCHIC, MOVE_ICY_WIND,
        MOVE_ICE_PUNCH, MOVE_ICE_BEAM, MOVE_BLIZZARD, MOVE_HAIL, MOVE_DRAGON_BREATH,
        MOVE_DRAGON_CLAW, MOVE_OUTRAGE, MOVE_DRAGON_DANCE, MOVE_THIEF, MOVE_CRUNCH,
        MOVE_NIGHT_TERROR, MOVE_TAUNT, MOVE_HIDDEN_POWER,
        MOVE_CUT, MOVE_FLY, MOVE_SURF, MOVE_STRENGTH, MOVE_FLASH, MOVE_ROCK_SMASH,
        MOVE_WATERFALL, MOVE_DIVE
    };
    u8 i;

    if (NUM_TECHNICAL_MACHINES != 68 || NUM_HIDDEN_MACHINES != 8)
        Fail("TM004005 FAIL machine counts");

    for (i = 0; i < ARRAY_COUNT(moves); i++)
    {
        u16 item = TMHMIndexToItemId(i);
        if (item == ITEM_NONE)
            Fail("TM004005 FAIL missing machine item");
        if (ItemIdToTMHMIndex(item) != i)
            Fail("TM004005 FAIL reverse machine index");
        if (ItemIdToBattleMoveId(item) != moves[i])
            Fail("TM004005 FAIL move mapping");
        if (IsItemHM(item) != (i >= NUM_TECHNICAL_MACHINES))
            Fail("TM004005 FAIL HM classification");
    }

    if (TMHMIndexToItemId(49) != ITEM_TM50
     || TMHMIndexToItemId(50) != ITEM_TM51
     || TMHMIndexToItemId(67) != ITEM_TM68
     || TMHMIndexToItemId(68) != ITEM_HM01
     || TMHMIndexToItemId(75) != ITEM_HM08
     || TMHMIndexToItemId(76) != ITEM_NONE)
        Fail("TM004005 FAIL boundary mapping");
}

static void CheckAllTmSpecialCases(void)
{
    struct Pokemon mon;
    u8 i;

    MakeMon(&mon, SPECIES_DITTO);
    for (i = 0; i < NUM_TECHNICAL_MACHINES; i++)
        if (!CanMonLearnTMHM(&mon, i))
            Fail("TM004005 FAIL Ditto all-68 rule");

    MakeMon(&mon, SPECIES_MEW);
    for (i = 0; i < NUM_TECHNICAL_MACHINES; i++)
        if (!CanMonLearnTMHM(&mon, i))
            Fail("TM004005 FAIL Mew all-68 rule");

    if (CanMonLearnTMHM(&mon, NUM_TECHNICAL_MACHINES + NUM_HIDDEN_MACHINES))
        Fail("TM004005 FAIL compatibility upper bound");
}

static void CheckCurrentSpecialistRows(void)
{
    static const u8 butterfree[] = {2,3,4,5,11,14,26,29,38,42,43,45,51,54,64,68};
    static const u8 beedrill[] = {2,3,4,5,8,11,14,15,16,25,27,38,43,45,64,68};
    static const u8 beautifly[] = {2,3,4,5,11,14,25,26,38,42,43,45,54,64,68};
    static const u8 dustox[] = {2,3,4,5,14,16,25,26,42,43,52,53,54,64,68};
    static const u8 gastly[] = {4,5,14,16,29,30,43,46,48,49,54,64,67,68};
    static const u8 gengar[] = {3,4,5,8,14,16,28,29,30,34,43,46,47,48,49,54,56,64,67,68};
    static const u8 spheal[] = {1,2,4,5,14,17,20,21,22,40,42,55,57,58,59,68};
    static const u8 walrein[] = {1,2,3,4,5,14,17,20,21,22,40,42,55,57,58,59,68};
    static const u8 sphealHms[] = {3,4,6,7};
    static const u8 miltank[] = {1,2,3,4,5,6,8,14,17,20,21,22,24,29,34,38,40,42,45,46,47,48,49,50,55,56,57,58,68};
    static const u8 miltankHms[] = {3,4,6};
    static const u8 babyFairy[] = {1,2,4,5,14,18,20,29,35,36,38,40,42,45,46,50,52,53,54,55,68};
    static const u8 flashOnly[] = {5};
    static const u8 magby[] = {1,2,4,5,6,8,14,20,34,35,36,38,47,54,64,68};
    static const u8 rockSmashOnly[] = {6};
    static const u8 elekid[] = {1,2,4,5,6,8,14,20,34,42,46,47,48,49,50,52,54,56,64,68};
    static const u8 elekidHms[] = {5,6};
    static const u8 scizor[] = {2,3,4,5,11,14,24,25,31,32,33,38,42,64,68};
    static const u8 ectoceon[] = {1,2,3,4,5,14,15,16,18,20,28,29,30,64,65,67,68};
    static const u8 flyOnly[] = {2};
    static const u8 rhydon[] = {1,2,3,4,5,6,8,14,17,18,20,21,22,23,24,25,27,34,35,36,38,42,46,47,48,49,55,57,58,64,68};
    static const u8 rhydonHms[] = {1,3,4,6};
    static const u8 noHms[] = {0};

    ExpectTmSet(SPECIES_BUTTERFREE, butterfree, ARRAY_COUNT(butterfree));
    ExpectTmSet(SPECIES_BEEDRILL, beedrill, ARRAY_COUNT(beedrill));
    ExpectTmSet(SPECIES_BEAUTIFLY, beautifly, ARRAY_COUNT(beautifly));
    ExpectTmSet(SPECIES_DUSTOX, dustox, ARRAY_COUNT(dustox));

    ExpectFullSet(SPECIES_GASTLY, gastly, ARRAY_COUNT(gastly), noHms, 0);
    ExpectFullSet(SPECIES_HAUNTER, gastly, ARRAY_COUNT(gastly), noHms, 0);
    ExpectFullSet(SPECIES_GENGAR, gengar, ARRAY_COUNT(gengar), noHms, 0);

    ExpectFullSet(SPECIES_SPHEAL, spheal, ARRAY_COUNT(spheal), sphealHms, ARRAY_COUNT(sphealHms));
    ExpectFullSet(SPECIES_SEALEO, spheal, ARRAY_COUNT(spheal), sphealHms, ARRAY_COUNT(sphealHms));
    ExpectFullSet(SPECIES_WALREIN, walrein, ARRAY_COUNT(walrein), sphealHms, ARRAY_COUNT(sphealHms));

    ExpectFullSet(SPECIES_MILTANK, miltank, ARRAY_COUNT(miltank), miltankHms, ARRAY_COUNT(miltankHms));
    ExpectFullSet(SPECIES_IGGLYBUFF, babyFairy, ARRAY_COUNT(babyFairy), flashOnly, ARRAY_COUNT(flashOnly));
    ExpectFullSet(SPECIES_CLEFFA, babyFairy, ARRAY_COUNT(babyFairy), flashOnly, ARRAY_COUNT(flashOnly));
    ExpectFullSet(SPECIES_MAGBY, magby, ARRAY_COUNT(magby), rockSmashOnly, ARRAY_COUNT(rockSmashOnly));
    ExpectFullSet(SPECIES_ELEKID, elekid, ARRAY_COUNT(elekid), elekidHms, ARRAY_COUNT(elekidHms));

    ExpectTmSet(SPECIES_SCIZOR, scizor, ARRAY_COUNT(scizor));
    ExpectFullSet(SPECIES_ECTOCEON, ectoceon, ARRAY_COUNT(ectoceon), flyOnly, ARRAY_COUNT(flyOnly));
    ExpectFullSet(SPECIES_RHYDON, rhydon, ARRAY_COUNT(rhydon), rhydonHms, ARRAY_COUNT(rhydonHms));
    ExpectFullSet(SPECIES_RHYPERIOR, rhydon, ARRAY_COUNT(rhydon), rhydonHms, ARRAY_COUNT(rhydonHms));
}

void Tm004005_RunRuntimeQa(void)
{
    CheckMachineMapping();
    CheckAllTmSpecialCases();
    CheckCurrentSpecialistRows();

    QaLog("TM004005 QA PASS all68 map all8hm exact specialist rows");
    for (;;);
}
