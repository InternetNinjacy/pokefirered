#include "global.h"
#include "gba/isagbprint.h"
#include "item.h"
#include "item_use.h"
#include "pokemon.h"
#include "constants/items.h"
#include "constants/pokemon.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

struct LevelEvolutionCase
{
    u16 species;
    u8 level;
    u16 target;
};

struct ItemEvolutionCase
{
    u16 species;
    u16 item;
    u16 target;
};

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

static void MakeMon(struct Pokemon *mon, u16 species, u8 level)
{
    CreateMon(mon, species, level, 20, FALSE, 0, OT_ID_PLAYER_ID, 0);
}

static void CheckLevelEvolutions(void)
{
    static const struct LevelEvolutionCase cases[] =
    {
        {SPECIES_KADABRA, 42, SPECIES_ALAKAZAM},
        {SPECIES_MACHOKE, 42, SPECIES_MACHAMP},
        {SPECIES_GRAVELER, 42, SPECIES_GOLEM},
        {SPECIES_HAUNTER, 42, SPECIES_GENGAR},
        {SPECIES_PICHU, 15, SPECIES_PIKACHU},
        {SPECIES_CLEFFA, 15, SPECIES_CLEFAIRY},
        {SPECIES_IGGLYBUFF, 22, SPECIES_JIGGLYPUFF},
        {SPECIES_TOGEPI, 20, SPECIES_TOGETIC},
        {SPECIES_AZURILL, 15, SPECIES_MARILL},
        {SPECIES_GOLBAT, 36, SPECIES_CROBAT},
        {SPECIES_CHANSEY, 40, SPECIES_BLISSEY},
        {SPECIES_FEEBAS, 20, SPECIES_MILOTIC},
    };
    struct Pokemon mon;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(cases); i++)
    {
        MakeMon(&mon, cases[i].species, cases[i].level - 1);
        if (GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE) != SPECIES_NONE)
            Fail("EVOLQA FAIL level route activates early");

        MakeMon(&mon, cases[i].species, cases[i].level);
        if (GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE) != cases[i].target)
            Fail("EVOLQA FAIL level route target");
    }
}

static void CheckItemMetadata(u16 item)
{
    if (ItemId_GetType(item) != ITEM_TYPE_PARTY_MENU)
        Fail("EVOLQA FAIL direct item type");
    if (ItemId_GetFieldFunc(item) != FieldUseFunc_EvoItem)
        Fail("EVOLQA FAIL direct item field func");
}

static void CheckItemEvolution(struct ItemEvolutionCase c)
{
    struct Pokemon mon;

    MakeMon(&mon, c.species, 30);
    if (GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, c.item) != c.target)
        Fail("EVOLQA FAIL item check target");
    if (GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, c.item) != c.target)
        Fail("EVOLQA FAIL item use target");
    if (PokemonItemUseNoEffect(&mon, c.item, 0, 0))
        Fail("EVOLQA FAIL valid item rejected");
}

static void CheckDirectItemEvolutions(void)
{
    static const struct ItemEvolutionCase cases[] =
    {
        {SPECIES_POLIWHIRL, ITEM_KINGS_ROCK, SPECIES_POLITOED},
        {SPECIES_SLOWPOKE, ITEM_KINGS_ROCK, SPECIES_SLOWKING},
        {SPECIES_ONIX, ITEM_METAL_COAT, SPECIES_STEELIX},
        {SPECIES_SCYTHER, ITEM_METAL_COAT, SPECIES_SCIZOR},
        {SPECIES_SEADRA, ITEM_DRAGON_SCALE, SPECIES_KINGDRA},
        {SPECIES_PORYGON, ITEM_UP_GRADE, SPECIES_PORYGON2},
        {SPECIES_RHYDON, ITEM_PROTECTOR, SPECIES_RHYPERIOR},
    };
    static const u16 items[] =
    {
        ITEM_KINGS_ROCK,
        ITEM_METAL_COAT,
        ITEM_DRAGON_SCALE,
        ITEM_UP_GRADE,
        ITEM_PROTECTOR,
    };
    struct Pokemon mon;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(items); i++)
        CheckItemMetadata(items[i]);

    for (i = 0; i < ARRAY_COUNT(cases); i++)
        CheckItemEvolution(cases[i]);

    MakeMon(&mon, SPECIES_PICHU, 15);
    for (i = 0; i < ARRAY_COUNT(items); i++)
    {
        if (GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, items[i]) != SPECIES_NONE)
            Fail("EVOLQA FAIL invalid item target");
        if (!PokemonItemUseNoEffect(&mon, items[i], 0, 0))
            Fail("EVOLQA FAIL invalid item accepted");
    }

    if (ItemId_GetPrice(ITEM_PROTECTOR) != 0)
        Fail("EVOLQA FAIL Protector sell path");

    MakeMon(&mon, SPECIES_CLAMPERL, 30);
    if (GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_DEEP_SEA_TOOTH) != SPECIES_NONE
     || GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_DEEP_SEA_SCALE) != SPECIES_NONE)
        Fail("EVOLQA FAIL conditional Clamperl direct route activated");
}

static void CheckExistingDeterministicRoutes(void)
{
    struct Pokemon mon;

    MakeMon(&mon, SPECIES_PIKACHU, 34);
    if (GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE) != SPECIES_NONE)
        Fail("EVOLQA FAIL Pikachu level route early");
    MakeMon(&mon, SPECIES_PIKACHU, 35);
    if (GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE) != SPECIES_RAICHU
     || GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_THUNDER_STONE) != SPECIES_RAICHU)
        Fail("EVOLQA FAIL Pikachu deterministic routes");

    MakeMon(&mon, SPECIES_EEVEE, 15);
    if (GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_WATER_STONE) != SPECIES_VAPOREON
     || GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_THUNDER_STONE) != SPECIES_JOLTEON
     || GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_FIRE_STONE) != SPECIES_FLAREON
     || GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_SUN_STONE) != SPECIES_ESPEON
     || GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_MOON_STONE) != SPECIES_UMBREON
     || GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_LEAF_STONE) != SPECIES_LEAFEON
     || GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_BRICK) != SPECIES_ECTOCEON)
        Fail("EVOLQA FAIL Eevee deterministic routes");
}

void Evol001003_RunRuntimeQa(void)
{
    CheckLevelEvolutions();
    CheckDirectItemEvolutions();
    CheckExistingDeterministicRoutes();

    QaLog("EVOL001003 QA PASS level42 directitems fixedlevels protector invalidroutes eevee");
    for (;;);
}
