# Rhyperior SPRITE-003 QA v2 scope

Evidence-only QA branch from exact production head `f2c3e182dd9f97e868e4adbbab6ef4694cf28839`.

QA v1 failed before the build because its verification script referenced stale `src/data/pokemon/base_stats.h`, which does not exist on the current production ancestry. Current species data is stored in `src/data/pokemon/species_info.h`.

This v2 follows the already-proven Leafeon/Ectoceon asset-closure pattern and verifies only the Rhyperior graphics/UI integration contract plus the already-existing Protector evolution and Rhydon cry reuse, then performs a full `make modern` build.

This branch is QA evidence only and must never become production ancestry.
