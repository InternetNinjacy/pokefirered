from pathlib import Path
p = Path('src/battle_main.c')
text = p.read_text()
old = '''                    static const u8 sJoeyNatures[PARTY_SIZE] =
                    {
                        NATURE_TIMID, NATURE_MODEST, NATURE_MODEST,
                        NATURE_BOLD, NATURE_ADAMANT, NATURE_TIMID
                    };'''
new = '''                    static const u8 sJoeyNatures[PARTY_SIZE] =
                    {
                        NATURE_TIMID, NATURE_TIMID, NATURE_TIMID,
                        NATURE_BOLD, NATURE_ADAMANT, NATURE_HASTY
                    };'''
if text.count(old) != 1:
    raise SystemExit('Joey nature block mismatch')
text = text.replace(old, new, 1)
old = '''                static const u8 sJoeyEvs[PARTY_SIZE][NUM_STATS] =
                {
                    {  4,   0,   0, 252, 252,   0}, // Zapdos
                    {252,   0,   0,   0, 252,   4}, // Gardevoir
                    {  4,   0,   0, 252, 252,   0}, // Moltres
                    {252,   0, 252,   0,   0,   4}, // Articuno
                    {  0, 252,   0, 252,   0,   4}, // Dragonite
                    {  4,   0,   0, 252, 252,   0}, // Mewtwo
                };
                static const u8 sJoeyHpGrassIvs[NUM_STATS] = {31, 30, 31, 30, 30, 31};
                u8 value;
                u8 abilityNum = 0;

                for (j = 0; j < NUM_STATS; j++)
                {
                    value = sJoeyEvs[i][j];
                    SetMonData(&party[i], MON_DATA_HP_EV + j, &value);
                    value = (i == 0 || i == 2) ? sJoeyHpGrassIvs[j] : 31;
                    SetMonData(&party[i], MON_DATA_HP_IV + j, &value);
                }
                SetMonData(&party[i], MON_DATA_ABILITY_NUM, &abilityNum);'''
new = '''                static const u8 sJoeyEvs[PARTY_SIZE][NUM_STATS] =
                {
                    {  4,   0,   0, 252, 252,   0}, // Zapdos: 4 HP / 252 SpA / 252 Spe
                    {  4,   0,   0, 252, 252,   0}, // Gardevoir: 4 HP / 252 SpA / 252 Spe
                    {  4,   0,   0, 252, 252,   0}, // Moltres: 4 HP / 252 SpA / 252 Spe
                    {252,   0, 252,   0,   0,   4}, // Articuno: 252 HP / 252 Def / 4 SpD
                    {  4, 252,   0, 252,   0,   0}, // Dragonite: 4 HP / 252 Atk / 252 Spe
                    {  0,   4,   0, 252, 252,   0}, // Mewtwo: 4 Atk / 252 SpA / 252 Spe
                };
                // Authority IV order is HP/Atk/Def/SpA/SpD/Spe; engine order is
                // HP/Atk/Def/Spe/SpA/SpD, hence the reordered tuple below.
                static const u8 sJoeyHpGrassIvs[NUM_STATS] = {31, 30, 31, 31, 30, 31};
                u8 value;
                u8 abilityNum = (i == 1) ? 1 : 0; // Gardevoir specifically uses Trace.

                for (j = 0; j < NUM_STATS; j++)
                {
                    value = sJoeyEvs[i][j];
                    SetMonData(&party[i], MON_DATA_HP_EV + j, &value);
                    value = (i == 0 || i == 2) ? sJoeyHpGrassIvs[j] : 31;
                    SetMonData(&party[i], MON_DATA_HP_IV + j, &value);
                }
                SetMonData(&party[i], MON_DATA_ABILITY_NUM, &abilityNum);'''
if text.count(old) != 1:
    raise SystemExit('Joey stat block mismatch')
text = text.replace(old, new, 1)
p.write_text(text)
print('Joey current authority correction applied')
