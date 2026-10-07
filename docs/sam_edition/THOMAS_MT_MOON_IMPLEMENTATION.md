# RIV-016 / Thread 1B — Thomas Mt. Moon fossil encounter

Concurrent documentation-only production PR #293 (5dca0d7c412ef5d6fe12598c38fe22faeffd934e) is reconciled; it changes no ROM source. Implementation PR: #294.

Starting production: ca15b79af8aea55664fc190e03b5d4672d4de940 (Thread 1A / PR #292).

Authority: current campaign Thread 1B; Thomas Mt. Moon Fossil Reopening Decision Record and Implementation Addendum v1.0; latest preserve-existing-six-data instruction. Specialist sources: Google Docs IDs 16uXblLVnPHAcgxpJvmm9_Jq8ZTPA8m5YIEyFW_4KhvA and 1SHoXOsz6EaVQgaMSyQTD7YjiY6kLK_CRF9cyJ9m7SAc.

## Implemented delta

Miguel's battle and normal Helix/Dome selection remain. Successful bag delivery precedes removal/choice flags and Thomas arrival. NO or insufficient bag space leaves the fossils and pending event unchanged. Thomas and one ordinary Rocket use stock Rocket objects/presentation; the accomplice physically approaches and removes the remaining fossil only after Thomas loses. All locked dialogue wording is retained, with textbox wrapping only.

Trainer 847 is allocated from the current rival expansion block (840–879), after Green's live last record 846. NUM_TRAINERS becomes 848; the six Thomas records 784–789 retain byte-identical data. The trainer has no bag-healing items. Gastly Lv16/no item/Levitate opens with Hypnosis/Curse/Thief/Lick. Counter slot Lv15: Eevee -> Chansey/Sitrus/Seismic Toss/Softboiled/Thunder Wave/Light Screen; Pichu -> Cubone/Thick Club/Lightning Rod/Bone Club/Headbutt/Growl/Tail Whip; Ditto -> Dratini/Dragon Fang/Shed Skin/Twister/Thunder Wave/Wrap/Leer. Unspecified IV/nature traits use stock generation, not invented competitive traits. Starter mapping uses live VAR_STARTER_MON (0/1/2).

The real Double Battle starts through the no-intro script path, avoiding the ordinary two-mon gate. With one usable player mon, the right player battler is absent, uses a safe inactive party index, and is omitted from the send-out/shiny/healthbox flow. Opponent still sends two. No party cloning or artificial healing. Zero usable mons calls ordinary blackout without theft. Other trainers and link/multi battles are unchanged.

Reuse VAR_MAP_SCENE_MT_MOON_B2F (0x408B): 0 Miguel pending; 1 choice pending; 2 chosen fossil received/theft pending; 3 Rocket stole Dome; 4 Rocket stole Helix. Existing original-choice flags are the sole fossil branch authority. New hide flags 0x35B/0x35C use central Rocket/Thomas headroom. The frame hook makes a pending loss retry mandatory on re-entry; it stages the player at the existing fossil-room scene tile (14,11) through a same-map warp before restarting. Completion disables the frame hook and both Rockets remain hidden. The shared six-battle arc stage is unchanged.

## Live discrepancy retained for specialist reconciliation

The reopening documents claim an existing Cinnabar Thomas Lab scene and a fossil-dependent Mansion roster. Neither exists in starting production: Lab has no Thomas object/dialogue; Mansion uses the restored fixed six-lineage party. The current instruction also requires preserving those six records/data. This slice makes the stolen branch persistent/derivable and preserves fossil revival plus the independent opposite-fossil researcher, but does not invent missing later dialogue, a roster slot, levels, moves or held items. Later Cinnabar fossil integration requires explicit specialist reconciliation before SYS-THOMAS can close. The safe Mt. Moon encounter has no runtime dependency on those missing later hooks.

## Verification

Run python tests/test_thomas_mt_moon.py: executes the real helper under host stubs for 0/1/2 usable, every party position, egg/fainted exclusions, exact starter species/item/move/ability branches, identity retention and non-Mt-Moon isolation. Checks all original map objects/warps/layout/coordinates/background events, ordinary Rocket scripts and six Thomas data/trait packages unchanged.

Additional checks: script/native/symbol resolution, central ID collisions, exact dialogue comparison and deterministic movement/map bounds; git diff --check. Production CI validates compilation/linking in all seven variants with COMPARE=0. Full assembled-ROM playtesting remains deferred.

Next campaign thread: 1C, with the Cinnabar authority/source discrepancy carried explicitly into Thomas closure rather than marked complete.
