# SYS-THOMAS — Thread 1A baseline reconciliation

Starting production: dc7b53826ef5cd4a5e13165dbc4ab79018f327c6.

## Live delta

Production contains none of the six Thomas records, arc-state contract, narrative helpers, Porygon event, Doll, or Mara/Tauros epilogue. Historical PRs #147, #149, #163, #181–184 and #186–187 were integrated on other ancestry, not the current production branch. PR #244 is draft, conflicted, and includes later Mt. Moon and Rocket operations; it is provenance only.

This fresh-production reconstruction recovers the Thomas-only baseline from PR #244's bounded recovery interval 2c989995b..90321519d, cross-checked against historical closure 0776e3c2ac3c2ce22b8be0a0993eccc83aad9162. No historical branch is merged.

## Authority and preserved package

Current user campaign instruction; current Thomas Decision Record / Implementation Addendum October 5 closure and October 6 reopening notice; current Symbol Registry. The closure supersedes older alternate Thomas rosters, characterization, Victory Road and postgame routing.

Preserve IDs 784–789, six original party arrays, moves/items/IVs, dialogue and Single Battle records (doubleBattle=FALSE), as explicitly required by the reopening's preserve-existing-data rule. The older alternate all-Double package is superseded; the newly reopened Mt. Moon mandatory Double is owned by Thread 1B.

Recovered order: Nugget Bridge -> Celadon B3F -> Tower 7F -> Silph 5F -> Mansion B1F -> Viridian before Giovanni. Stage advances only after victory. Nugget retry state 2 prevents repeated rewards; trainer defeat state allows Doll-only retry at Viridian. Quit transition follows successful Doll delivery. Mara remains available after terminal state 7.

Reuse VAR_THOMAS_ARC_STAGE=0x40A1; flags 0x350–0x35A; Porygon receipt 0x376; dedicated item slot ITEM_15B=347. NUM_TRAINERS remains 847 for current Green records. Existing stock portrait reuse is retained pending the separate asset campaign.

## Shared dependency corrections

Celadon selector 1 was occupying Thomas's centrally assigned 0x40A1. All six selectors now reuse VAR_TEMP_4..9: these map-local puzzle values already reset on every entry, while solved state persists in the existing puzzle flags. No new save allocation is introduced.

Restore GivePreOwnedMonToPlayer as the stock delivery path without overwriting OT; ordinary GiveMonToPlayer behavior is unchanged. Tauros retains MARA/24116, male Adamant, IV20, friendship70, authored moves and Sitrus Berry. Porygon retains SILPH/52007, Lv25, random nature/IVs, no item, generated moves. Its recovery requires stage >= Silph cleared, preserves the ball on NO or full storage, and sets its flag only on success. The narrow SILPH handler does not replace the current Hothouse acquisition handler. No new Thomas Rock Tunnel battle is created.

## Verification and handoff

Exact historical parties, trait code and dialogue compared byte-for-byte. Existing objects, layouts, connections, warps and background events preserved; only specialist-owned Rocket flags change. Thomas script references resolve. git diff --check passes. Production CI supplies compilation/link validation; assembled-ROM gameplay testing remains pending by explicit policy.

Remaining: Thread 1B Mt. Moon fossil operation; Threads 1C–1E Rocket organization/evidence/story and Five Island; Thread 1F closure. Thomas art is owned by Section 3. No new story content is included here.
