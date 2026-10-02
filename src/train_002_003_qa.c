#include "global.h"
#include "battle.h"
#include "gba/isagbprint.h"
#include "constants/moves.h"
#include "constants/species.h"
#include "constants/trainers.h"

#define QA_MGBA_DEBUG_FLAGS  ((vu16 *)0x4FFF700)
#define QA_MGBA_DEBUG_STRING ((volatile char *)0x4FFF600)

static void Log(const char *s)
{
    u32 i = 0;
    while (s[i] && i < 255)
    {
        QA_MGBA_DEBUG_STRING[i] = s[i];
        i++;
    }
    QA_MGBA_DEBUG_STRING[i] = 0;
    *QA_MGBA_DEBUG_FLAGS = MGBA_LOG_INFO | 0x100;
}

static void Fail(const char *s)
{
    Log(s);
    for (;;);
}

static void CheckThomas(void)
{
    const struct Trainer *trainer = &gTrainers[TRAINER_GENTLEMAN_THOMAS];
    const struct TrainerMonNoItemDefaultMoves *party;

    if (trainer->partyFlags != 0)
        Fail("TRAIN QA FAIL Thomas flags");
    if (trainer->partySize != 3)
        Fail("TRAIN QA FAIL Thomas size");
    if (trainer->doubleBattle != FALSE)
        Fail("TRAIN QA FAIL Thomas format");

    party = trainer->party.NoItemDefaultMoves;
    if (party[0].species != SPECIES_GROWLITHE || party[0].lvl != 18)
        Fail("TRAIN QA FAIL Thomas slot1");
    if (party[1].species != SPECIES_LICKITUNG || party[1].lvl != 18)
        Fail("TRAIN QA FAIL Thomas slot2");
    if (party[2].species != SPECIES_PERSIAN || party[2].lvl != 20)
        Fail("TRAIN QA FAIL Thomas slot3");
}

static void CheckKent(void)
{
    const struct Trainer *trainer = &gTrainers[TRAINER_BUG_CATCHER_KENT];
    const struct TrainerMonNoItemCustomMoves *party;

    if (trainer->partyFlags != F_TRAINER_PARTY_CUSTOM_MOVESET)
        Fail("TRAIN QA FAIL Kent flags");
    if (trainer->partySize != 2)
        Fail("TRAIN QA FAIL Kent size");
    if (trainer->doubleBattle != TRUE)
        Fail("TRAIN QA FAIL Kent format");

    party = trainer->party.NoItemCustomMoves;
    if (party[0].species != SPECIES_WEEDLE || party[0].lvl != 11)
        Fail("TRAIN QA FAIL Kent slot1");
    if (party[0].moves[0] != MOVE_POISON_STING
     || party[0].moves[1] != MOVE_STRING_SHOT
     || party[0].moves[2] != MOVE_FURY_CUTTER
     || party[0].moves[3] != MOVE_SECRET_POWER)
        Fail("TRAIN QA FAIL Weedle moves");

    if (party[1].species != SPECIES_KAKUNA || party[1].lvl != 11)
        Fail("TRAIN QA FAIL Kent slot2");
    if (party[1].moves[0] != MOVE_HARDEN
     || party[1].moves[1] != MOVE_IRON_DEFENSE
     || party[1].moves[2] != MOVE_POISON_STING
     || party[1].moves[3] != MOVE_PROTECT)
        Fail("TRAIN QA FAIL Kakuna moves");
}

void Train002003_RunRuntimeQa(void)
{
    CheckThomas();
    CheckKent();

    if (gTrainers[TRAINER_BUG_CATCHER_ROBBY].doubleBattle != FALSE
     || gTrainers[TRAINER_BUG_CATCHER_ROBBY].partyFlags != 0)
        Fail("TRAIN QA FAIL control trainer");

    Log("TRAIN002003 QA PASS compiled Thomas and Kent corrections");
    for (;;);
}
