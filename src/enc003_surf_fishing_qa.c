#include "global.h"
#include "gba/isagbprint.h"
#include "wild_encounter.h"
#include "constants/maps.h"
#include "constants/species.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

struct ExpectedMon { u16 species; u8 minLevel; u8 maxLevel; };
struct Family { const struct ExpectedMon *water; const struct ExpectedMon *fish; };
struct MapCheck { u8 group; u8 num; u8 waterRate; u8 fishRate; const struct Family *family; };

#define M(s,l,h) {SPECIES_##s,l,h}

static const struct ExpectedMon wA[]={M(KRABBY,30,34),M(HORSEA,30,34),M(STARYU,32,36),M(SEADRA,35,38),M(KINGLER,37,40)};
static const struct ExpectedMon fA[]={M(MAGIKARP,5,10),M(KRABBY,15,20),M(KRABBY,28,33),M(HORSEA,28,33),M(STARYU,30,35),M(HORSEA,34,39),M(KRABBY,34,39),M(STARYU,36,41),M(SEADRA,40,44),M(KINGLER,42,45)};
static const struct ExpectedMon wB[]={M(PSYDUCK,32,36),M(SLOWPOKE,32,36),M(POLIWHIRL,35,38),M(GOLDUCK,37,40),M(SLOWBRO,39,42)};
static const struct ExpectedMon fB[]={M(MAGIKARP,5,10),M(POLIWAG,15,20),M(POLIWAG,30,35),M(GOLDEEN,30,35),M(SLOWPOKE,31,36),M(POLIWHIRL,35,40),M(GOLDEEN,35,40),M(SLOWPOKE,36,41),M(SEAKING,40,44),M(SLOWBRO,42,45)};
static const struct ExpectedMon wC[]={M(SEEL,36,41),M(SPHEAL,34,39),M(SHELLDER,36,41),M(DEWGONG,42,45),M(SEALEO,42,45)};
static const struct ExpectedMon fC[]={M(MAGIKARP,5,10),M(SHELLDER,20,25),M(SHELLDER,34,39),M(SEEL,36,41),M(SPHEAL,34,39),M(SEEL,40,44),M(SHELLDER,40,44),M(SPHEAL,39,43),M(DEWGONG,44,47),M(CLOYSTER,45,48)};
static const struct ExpectedMon wD[]={M(TENTACOOL,40,44),M(KRABBY,40,44),M(STARYU,42,46),M(TENTACRUEL,45,48),M(SEADRA,45,48)};
static const struct ExpectedMon fD[]={M(MAGIKARP,5,10),M(KRABBY,20,25),M(KRABBY,38,43),M(HORSEA,38,43),M(STARYU,40,45),M(HORSEA,42,47),M(STARYU,42,47),M(KRABBY,42,47),M(SEADRA,47,50),M(KINGLER,48,51)};
static const struct ExpectedMon wM[]={M(STARYU,42,46),M(KRABBY,42,46),M(HORSEA,42,46),M(SEADRA,46,49),M(KINGLER,48,51)};
static const struct ExpectedMon fM[]={M(MAGIKARP,5,10),M(KRABBY,20,25),M(STARYU,40,45),M(KRABBY,40,45),M(HORSEA,40,45),M(STARYU,44,49),M(HORSEA,44,49),M(KRABBY,44,49),M(SEADRA,49,52),M(KINGLER,50,53)};
static const struct ExpectedMon wL[]={M(HORSEA,42,46),M(SEADRA,45,49),M(DRATINI,43,47),M(DRAGONAIR,48,51),M(KINGLER,48,51)};
static const struct ExpectedMon fL[]={M(MAGIKARP,5,10),M(HORSEA,20,25),M(HORSEA,40,45),M(KRABBY,40,45),M(DRATINI,40,44),M(HORSEA,44,49),M(SEADRA,46,51),M(DRATINI,45,49),M(DRAGONAIR,50,53),M(KINGLER,50,53)};
static const struct ExpectedMon wE[]={M(PSYDUCK,42,46),M(SLOWPOKE,42,46),M(POLIWHIRL,44,48),M(GOLDUCK,47,50),M(SLOWBRO,49,52)};
static const struct ExpectedMon fE[]={M(MAGIKARP,5,10),M(POLIWAG,20,25),M(POLIWAG,40,45),M(GOLDEEN,40,45),M(SLOWPOKE,40,45),M(POLIWHIRL,44,49),M(GOLDEEN,44,49),M(SLOWPOKE,44,49),M(SEAKING,49,52),M(SLOWBRO,50,53)};
static const struct ExpectedMon wO[]={M(TENTACOOL,43,47),M(TENTACRUEL,46,50),M(STARYU,44,48),M(SEADRA,47,51),M(KINGLER,49,52)};
static const struct ExpectedMon fO[]={M(MAGIKARP,5,10),M(KRABBY,20,25),M(KRABBY,40,45),M(HORSEA,40,45),M(STARYU,42,47),M(STARYU,45,50),M(HORSEA,45,50),M(KRABBY,45,50),M(SEADRA,50,53),M(KINGLER,51,54)};
static const struct ExpectedMon wF[]={M(TENTACRUEL,46,50),M(STARYU,45,49),M(SEADRA,47,51),M(KINGLER,49,52),M(GYARADOS,50,53)};
static const struct ExpectedMon fF[]={M(MAGIKARP,5,10),M(KRABBY,20,25),M(HORSEA,42,47),M(KRABBY,42,47),M(STARYU,43,48),M(SEADRA,47,52),M(STARYU,47,52),M(KINGLER,48,53),M(GYARADOS,50,54),M(DRAGONAIR,52,55)};
static const struct ExpectedMon wCC[]={M(SLOWPOKE,50,54),M(PSYDUCK,50,54),M(SLOWBRO,55,58),M(GOLDUCK,55,58),M(POLIWHIRL,57,60)};
static const struct ExpectedMon fCC[]={M(MAGIKARP,5,10),M(POLIWAG,20,25),M(POLIWHIRL,48,53),M(SLOWPOKE,48,53),M(GOLDEEN,48,53),M(SLOWBRO,54,59),M(POLIWHIRL,54,59),M(SEAKING,55,60),M(GOLDUCK,58,61),M(DRAGONAIR,60,62)};

static const struct Family A={wA,fA},B={wB,fB},C={wC,fC},D={wD,fD},MEM={wM,fM},LAB={wL,fL},E={wE,fE},OUT={wO,fO},F={wF,fF},CC={wCC,fCC};
#define MC(map,wr,fr,fam) {MAP_GROUP(map),MAP_NUM(map),wr,fr,fam}
static const struct MapCheck maps[]={
 MC(MAP_ONE_ISLAND_TREASURE_BEACH,2,20,&A),MC(MAP_TWO_ISLAND_CAPE_BRINK,2,20,&A),MC(MAP_THREE_ISLAND_BOND_BRIDGE,2,20,&A),
 MC(MAP_THREE_ISLAND_BERRY_FOREST,2,20,&B),
 MC(MAP_FOUR_ISLAND,2,20,&C),MC(MAP_FOUR_ISLAND_ICEFALL_CAVE_ENTRANCE,2,20,&C),MC(MAP_FOUR_ISLAND_ICEFALL_CAVE_BACK,2,20,&C),
 MC(MAP_FIVE_ISLAND,1,10,&D),MC(MAP_FIVE_ISLAND_MEADOW,2,20,&D),MC(MAP_FIVE_ISLAND_RESORT_GORGEOUS,2,20,&D),
 MC(MAP_FIVE_ISLAND_MEMORIAL_PILLAR,2,20,&MEM),MC(MAP_FIVE_ISLAND_WATER_LABYRINTH,2,20,&LAB),
 MC(MAP_SIX_ISLAND_WATER_PATH,2,20,&E),MC(MAP_SIX_ISLAND_GREEN_PATH,2,20,&E),MC(MAP_SIX_ISLAND_RUIN_VALLEY,2,20,&E),
 MC(MAP_SIX_ISLAND_OUTCAST_ISLAND,2,20,&OUT),
 MC(MAP_SEVEN_ISLAND_TRAINER_TOWER,2,20,&F),MC(MAP_SEVEN_ISLAND_TANOBY_RUINS,2,20,&F),
 MC(MAP_CERULEAN_CAVE_1F,2,20,&CC),MC(MAP_CERULEAN_CAVE_B1F,2,20,&CC)
};

static void Log(const char *s){u32 i=0;while(s[i]&&i<255){QA_MGBA_DEBUG_STRING[i]=s[i];i++;}QA_MGBA_DEBUG_STRING[i]=0;*QA_MGBA_DEBUG_FLAGS=MGBA_LOG_INFO|0x100;}
static void Fail(const char *s){Log(s);for(;;);}

static const struct WildPokemonHeader *Find(u8 group,u8 num)
{
    u32 i;
    for(i=0;gWildMonHeaders[i].mapGroup!=MAP_GROUP(MAP_UNDEFINED);i++)
        if(gWildMonHeaders[i].mapGroup==group&&gWildMonHeaders[i].mapNum==num)
            return &gWildMonHeaders[i];
    return NULL;
}

static void CheckOne(const struct WildPokemon *a,const struct ExpectedMon *e)
{
    if(a->species!=e->species||a->minLevel!=e->minLevel||a->maxLevel!=e->maxLevel)
        Fail("ENC003 FAIL compiled slot");
}

static void CheckMap(const struct MapCheck *m)
{
    const struct WildPokemonHeader *h=Find(m->group,m->num);
    u32 i;
    if(!h||!h->waterMonsInfo||!h->fishingMonsInfo) Fail("ENC003 FAIL compiled header");
    if(h->waterMonsInfo->encounterRate!=m->waterRate||h->fishingMonsInfo->encounterRate!=m->fishRate) Fail("ENC003 FAIL preserved rate");
    for(i=0;i<WATER_WILD_COUNT;i++) CheckOne(&h->waterMonsInfo->wildPokemon[i],&m->family->water[i]);
    for(i=0;i<FISH_WILD_COUNT;i++) CheckOne(&h->fishingMonsInfo->wildPokemon[i],&m->family->fish[i]);
}

void Enc003SurfFishing_RunRuntimeQa(void)
{
    u32 i;
    for(i=0;i<ARRAY_COUNT(maps);i++) CheckMap(&maps[i]);
    if(Find(MAP_GROUP(MAP_SEVEN_ISLAND),MAP_NUM(MAP_SEVEN_ISLAND))!=NULL) Fail("ENC003 FAIL invented Seven Island header");
    Log("ENC003 QA PASS 20 compiled surf fishing tables; Seven Island unresolved");
    for(;;);
}
