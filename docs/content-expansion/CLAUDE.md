# TwinleafStory — Content Expansion Design Context

This directory contains the complete game design for TwinleafStory — a v83 MapleStory server extended with content from v84-v99+, rebalanced for small groups (1-6 players), with custom narrative and progression systems. Design is **complete as of Session 4** (2026-02-28).

## What Is TwinleafStory?

v83 Extended — official MapleStory content backported into a pre-Big Bang foundation. Not stock v83, not a custom server. What v83 should have been if it kept going without Big Bang.

**Key differences from stock v83:**
- Content beyond Lv 120 (LHC, Future Ereve, Arcane River) — all re-statted for pre-BB formulas
- Explorer only — CK/Aran creation disabled, their areas repurposed as endgame content
- 48 custom 4.5 job skills using CK/Aran/DB animations from the v83 repack
- Zone completion vendors in every area — deterministic gear progression
- Token currencies (Von Leon Coins, Soul Shards, Arcane Tokens) for bad luck protection
- Coherent narrative tying LHC → Future Ereve → Empress into one story arc
- Level cap 170 (Arcane River), compressed from official 200-275

## Document Map

| Document | Answers | Key Contents |
|----------|---------|-------------|
| **TWINLEAF-DESIGN-DOC.md** | "What is TwinleafStory?" | Vision, principles, progression ladder, decision log |
| **world-design.md** | "What's in each zone?" | All areas, vendors, NPCs, cosmetics, cash shop, zone completion tables |
| **quest-design.md** | "What quests exist?" | All quest chains (LHC, GttF, Ereve, Rien trials), NPC dialogue tone |
| **twinleaf-skills.md** | "What are 4.5 skills?" | 48 skills fully specified, dead skill cuts, Shadower overhaul |
| **balance-design.md** | "What are the HP/damage targets?" | Boss HP table, gear ladder, EXP curve, rate settings |
| **boss-audit.md** | "What do stock bosses look like?" | Current boss stats from WZ, playtest templates |
| **PROGRESSION-GUIDE.md** | "What should a player do at Lv X?" | Player-facing guide, also feeds Cody NPC script |
| **IMPLEMENTATION-GUIDE.md** | "What do I do next?" | Phase-by-phase playbook, prompt execution order, deploy commands |
| **CONTENT-PORT-PLAN.md** | "What data needs importing?" | Mob IDs, map IDs, equipment IDs, SQL templates |
| **REPACK-ANALYSIS.md** | "What's in the repack?" | 523 extra mobs, 579 extra maps, mob ID groups |
| **STRING-SOURCES.md** | "Where do item/mob names come from?" | wz.zip analysis, merge instructions |
| **wz-pipeline.md** | "How do I edit game data?" | Server-side XML, client NX pipeline, HaRepacker |

### Audit Subdirectory (`audits/`)

10 audit documents from Sessions 3-4 covering: mobs/maps, skills (4.5 job), scrolls/equips, chairs/mounts, cash shop, quests, and the Session 4 comprehensive audit (NPCs, NLC/Omega/Kampung, equipment models, Katara animations).

### Prompts Subdirectory (`prompts/`)

10 self-contained prompt files (PROMPT-01 through PROMPT-10) designed for the Windows devbox Claude. Each prompt extracts specific content from the community repack and produces server-ready output. See IMPLEMENTATION-GUIDE.md for execution order.

## Locked Design Decisions (Implementation-Impacting)

These are final. Do not change without explicit approval.

| Decision | Implementation Impact |
|----------|----------------------|
| Explorer only (CK/Aran disabled) | Block job type 0 (CK) and 2 (Aran) in character creation handler |
| Trade button → Kerning Night Market | Client FM warp → map 103000007 |
| Solo expeditions enabled | `USE_ENABLE_SOLO_EXPEDITIONS: true` in config |
| ToT kill quests: 999 → 100 | Edit quest scripts on server |
| 4.5 skills use CK/Aran/DB IDs | Repurpose skill IDs from 1100-1511, 2100-2112 ranges |
| Token currencies | New ETC items: Von Leon Coins, Soul Shards, Arcane Tokens |
| Zone completion vendors | ~20+ NPC scripts with unlock conditions per zone |
| Reskin existing v83 gear | VL/Empress models missing from repack — use existing visuals, custom stats |
| MW auto-passive at 120 | Remove from skill hotbar, apply automatically |
| Boosters baked into Mastery | Remove booster skills, bake speed into mastery passives |
| Shadower overhaul | Meso Explosion → Shadow Flurry, Pickpocket → Marked for Death |

## Technical Constraints

- **Reskin strategy**: Von Leon and Empress equipment models are NOT in the repack Character.wz. Use existing v83 equipment visuals with custom names/stats via String.wz and stat XML edits.
- **CK/Aran skill ranges**: 4.5 skills repurpose IDs 1100-1111 (DW), 1200-1211 (BW), 1300-1311 (WA), 1400-1411 (NW), 1500-1511 (TB), 2100-2112 (Aran). Client already has animations for these IDs.
- **String data**: wz.zip (D:\wz.zip on Windows, 98MB) is the primary source. Its Eqp.img.xml is 4x larger than server's. See STRING-SOURCES.md.
- **Server-side only for stats**: Mob HP/damage, drop tables, EXP rates — all server XML edits. No client update needed.
- **DB on Docker**: MySQL runs in `cosmic-db-1` container on 192.168.0.25. Drop tables are in the `drop_data` table.

## File Locations

| Machine | Path | Contents |
|---------|------|----------|
| Windows devbox (.194) | `C:\Users\carbyne\Documents\CommunityRepack\` | Post-v83 WZ/IMG repack data |
| Windows devbox (.194) | `C:\Shared\prompts\` | Prompt files for Claude |
| Windows devbox (.194) | `C:\Shared\output\` | Claude output files |
| MacBook (.92) | `~/Shared-Win/` | SMB share from Windows |
| Server (.25) | `/home/homelab/Cosmic/wz/` | Live WZ data (edit + restart) |
| Server (.25) | `/home/homelab/Cosmic/scripts/` | NPC/Quest JS scripts |

## What To Do Next

See **IMPLEMENTATION-GUIDE.md** — it's the step-by-step playbook organized by phase. Start at Phase 0 (Foundation).
