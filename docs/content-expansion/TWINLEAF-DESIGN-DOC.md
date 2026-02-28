# TwinleafStory — Master Design Document
*Last updated: 2026-02-28 (Session 4 — all design decisions locked, doc consistency pass)*

## Vision

TwinleafStory is **v83 Extended** — official MapleStory content from v84-v99 backported into a pre-Big Bang v83 foundation, with custom narrative, rebalanced for small groups, and served over Tailscale to 5-15 friends.

Not a custom server. Not stock v83. **What v83 should have been if it kept going without Big Bang.**

---

## Core Design Principles

1. **Small-group friendly** — 1-6 players is the sweet spot
2. **No Potential system** — pure scroll-based gearing, classic feel
3. **No post-BB stat formulas** — all content uses pre-BB damage calculations
4. **Explorer only** — CK/Aran character creation DISABLED. Ereve and Rien repurposed as Explorer-accessible content areas. (DECIDED 2026-02-27)
5. **Gear is the progression lever** — new areas drop new gear
6. **The world is a place, not a menu** — boats matter, discovery matters
7. **Custom 4.5 job skills** — 48 skills (4 per branch), unlocked via Rien trials at Lv 140+, animations from CK/Aran/DB assets in the repack. See `twinleaf-skills.md` for full design.
8. **In-game guidance** — Cody NPC in towns provides level-appropriate recommendations. Standalone progression doc for out-of-game reference. (DECIDED 2026-02-27)
9. **Zone completion vendors** — every zone has a completion condition that unlocks a vendor selling level-appropriate gear. Deterministic progression alongside boss RNG. See `world-design.md` for full tables.

---

## Progression Ladder

```
Lv 1-30   → Victoria Island (quests, grinding, exploration)
Lv 30-50  → Victoria Island + Orbis + Ludibrium + Ellin Forest (50)
Lv 35-64  → Mushroom Castle (Maple Weapons from King Pepe vendor)
Lv 50-70  → El Nath, Leafre, Mu Lung, party quests, KFT (60), Magatia (78)
Lv 70     → Zakum (prequest = jump quest only, helm buffed)
Lv 70-100 → Leafre, Temple of Time, Aqua Road, Zipangu/Showa (70)
Lv 80-100 → Singapore / Ulu City (Krexel boss at 85+)
Lv 80     → Kampung bosses (Scarlion/Targa hats — buffed ZHelm alternatives)
Lv 100    → Horntail (rebalanced for 4-6 players)
Lv 100-120 → Temple of Time (kill quests: 100 per stage), Corrupted ToT mobs
Lv 120    → Chaos Zakum / Chaos Horntail (hard mode)
Lv 120-130 → Lion Heart Castle (accessed from El Nath)
Lv 125    → Von Leon boss (LHC endgame) — Von Leon Coins for vendor gear
Lv 130-140 → Future Ereve (accessed from Temple of Time)
Lv 140    → Empress Cygnus (4-6 players, multi-phase) — Soul Shards for vendor gear
Lv 140+   → Rien: 4.5 job trials (8-step quest chain with Archive Keeper)
Lv 150-170 → Arcane River (3 zones, re-statted for pre-BB, gated by 4.5 mastery)
Lv 170    → Arcane Guardian (final boss)
```

## Gear Ladder

```
Zone vendors (every zone) → Zakum Helm (70) → HT Accessories (100)
→ Corrupted ToT gear (110) → Von Leon Set (125, vendor + boss drops)
→ Empress Set (140, vendor + boss drops) → Arcane Set (160, token exchange)
```

Zone completion vendors provide reliable baseline gear (~70-80% of boss drop quality). Boss drops remain the premium upgrade path. Token currencies (Von Leon Coins, Soul Shards, Arcane Tokens) provide bad luck protection. Full tables in `world-design.md` and `PROGRESSION-GUIDE.md`.

## Playable Classes

**Explorer only.** Cygnus Knights and Aran character creation disabled at character select.

**Ereve** → Post-Empress reward hub. Players who defeat Empress earn access to the restored Ereve. CK NPCs give unique quest chains with rewards (scrolls, pendants, gloves, chairs). Soul Shard vendor for Empress set pieces.

**Rien** → Lv 140+ endgame zone. Home of the Archive Keeper NPC who administers 4.5 job trials (8-step branch-specific quest chain). Also houses the sealed portal to Arcane River (opens after 4.5 mastery). Skill Stone vendor for 4.5 skill upgrades.

*Rationale*: Simplifies balancing, focuses the 4.5 job design on Explorer trees only, and repurposes CK/Aran areas as meaningful endgame content rather than dead zones.

---

## World Coherence

### Travel Philosophy
- **Boats/airships between continents** — keep them, they're atmospheric
- **Dimensional Mirror** — for boss instances only, not town-to-town
- **Hyper Teleport Rock** — rare endgame drop, not from a shop
- **Portal NPCs within regions** — e.g., LHC has internal network
- **New areas require physical discovery first** — NPCs mention them, quests lead there

### Area Access Flow
```
Victoria Island → Ossyria → El Nath → Leafre (stock v83)
       ↓                            ↓
  Singapore / Ulu City        Lion Heart Castle (from El Nath mountains)
  (from Changi Airport NPC)

El Nath → Temple of Time → Gate to the Future → Future Ereve
              ↓
      Corrupted ToT (deeper maps, higher level mobs)
```

### Narrative Flow
- Stock v83 quests for 1-100 (fix broken ones)
- Zakum prequest = jump quest only (cut the tedious fetch parts). Note: solo expeditions bypass prequest entirely — JQ-only enforcement is for when friends join.
- Temple of Time: kill quest counts reduced from 999 → **100 per stage** (DECIDED 2026-02-27)
- LHC narrative (DECIDED 2026-02-27): *A patrol of El Nath mountaineers discovered ruins in the deep peaks. The castle predates Ossyria's recorded history. Something inside is still alive — and still commanding an army. The Cygnus Knights sent a scouting party. None returned. Now their corrupted forms guard the castle walls.* This explains the Cygnus Knight enemies as the corrupted scouting party, the prison guards as Von Leon's centuries-old garrison, and gives players a mystery + rescue mission.
- Future Ereve narrative (DECIDED 2026-02-27): *The Temple of Time's deepest gate has destabilized. Beyond it lies a vision — not of the past, but of what comes if the darkness in Lion Heart Castle spreads unchecked. Ereve has fallen. The Empress is corrupted. Her knights fight each other in ruined streets. This isn't prophecy — it's a warning.* This ties LHC and Future Ereve together — Von Leon's corruption is the root cause, beating Empress breaks the vision / prevents the future.
- Empress fight: our own narrative (not Black Mage storyline) — the corrupted Empress is the manifestation of the dark future, not a Black Mage pawn

---

## Boss Rebalancing (for 1-6 players)

### Tier System
| Tier | Party Size | Bosses |
|------|-----------|--------|
| Solo | 1 | Mushmom, Jr. Balrog, Crimson Balrog, Nine-Tailed Fox, Bodyguard A |
| Duo | 2-3 | Papulatus, Pianus, Krexel, Scarlion, Targa |
| Party | 3-6 | Zakum, Horntail, Von Leon, Showa Boss |
| Raid | 4-6 | Chaos Zakum, Chaos HT, Empress Cygnus |
| Aspirational | 6+ | Chaos Pink Bean, Arcane Guardian |

### HP Targets
| Boss | Stock HP | Target HP | Status |
|------|---------|-----------|--------|
| Zakum Body 2 | 110M | 30M | Pending |
| Horntail Heads | 330M | 80M | Pending |
| Horntail Pivot | 2.09B | 200M | Pending |
| Showa Boss | 150M (PDef 5000) | 150M (PDef 1500) | ✅ DONE |
| Krexel | TBD | 60M | New content |
| Pink Bean | 2.1B | 500M | Pending |
| Von Leon | TBD | 500M | New content |
| Chaos Zakum | TBD | 200M | New content |
| Chaos Horntail | TBD | 600M | New content |
| Empress Cygnus | TBD | 1.5B | New content |
| Chaos Pink Bean | TBD | 3B | New content |
| Arcane Guardian | TBD | 2B | New content (M4) |

Full boss design details in `balance-design.md` and `boss-audit.md`.

---

## EXP Curve

**Keep 10x global rate.** Control 120-140 via mob EXP in new areas:

| Area | Mob Level | Base EXP | At 10x | Kills/level |
|------|-----------|----------|--------|-------------|
| LHC entry | 130 | 15,000 | 150,000 | ~155 |
| LHC main | 140 | 22,000 | 220,000 | ~155 |
| LHC hard | 148 | 32,000 | 320,000 | ~125 |
| Future Ereve entry | 150 | 45,000 | 450,000 | ~133 |
| Future Ereve main | 155 | 60,000 | 600,000 | ~150 |
| Future Ereve hard | 160 | 80,000 | 800,000 | ~163 |

---

## Custom 4.5 Job Skills

> **Full design in `twinleaf-skills.md`** — 48 skills fully specified with sources, types, cooldowns.

### Philosophy
- **4 new skills per branch** (48 total across 12 Explorer jobs)
- Unlocked at Lv 140+ via 8-step Rien trial quest chain (Archive Keeper NPC)
- Animations sourced **exclusively from CK/Aran/Dual Blade assets** already in the v83 repack
- No post-v83 class animations used (no Kaiser, Luminous, Phantom, etc. — they're not in the repack)
- Server-side skill handlers in Java (Cosmic), client uses repurposed CK/Aran skill IDs

### Animation Sources
| Explorer Branch | Animation Source |
|----------------|-----------------|
| Warriors (Hero/Pally/DK) | Dawn Warrior + Aran |
| Mages (F/P, I/L, Bishop) | Blaze Wizard (element-reskinned) |
| Bowmen (BM/MM) | Wind Archer |
| Thieves (NL/Shadower) | Night Walker + Dual Blade Katara sprites |
| Pirates (Bucc/Corsair) | Thunder Breaker |

### Unlock Mechanism
Beat Empress Cygnus → receive **Rien Keystone** item → travel to Rien → Archive Keeper identifies your exact job → 8-step branch-specific trial quest → skills unlocked. Each trial is tailored to the player's class identity.

### Universal Skill Changes (Session 3)
- **Maple Warrior** → auto-passive at Lv 120 (not a skill slot)
- **Hero's Will** → quest-granted auto-cleanse (Lv 140+ quest reward)
- **Boosters** → baked into Mastery passives (free slot)
- **30+ dead skills cut** — see `twinleaf-skills.md` for full list and rationale
- **Shadower completely overhauled** — meso gimmicks removed, rebuilt as melee assassin

---

## Content Inventory (Confirmed in Repack)

### Chaos Zakum (Priority 1)
- Mob IDs: 8800100-8800116 (17 mobs) ✅
- Maps: Use existing Zakum altar ✅
- Strings: In wz.zip ✅

### Lion Heart Castle + Von Leon (Priority 2)
- Maps: 211060000-211070110 (28 maps) ✅
- Mobs: 8210000-8210013, 8610000-8610033, 8620000-8620027 (76 area mobs) ✅
- Boss: 8840000-8840002 (Von Leon + 2 summons) ✅
- Equipment: Lionheart/DragonTail/FalconWing/RavenHorn/SharkTooth sets ✅
- Strings: All in wz.zip ✅

### Future Ereve + Empress (Priority 3)
- Maps: 271000000-271040300 (42 maps) ✅
- Mobs: 8644000-8644836, 8645000-8645065 (300+ mobs) ✅
- Boss: 8850000-8850011 (5 commanders + Shinsoo + Empress) ✅
- Equipment: Empress Fine/Brilliant sets ✅
- Strings: All in wz.zip ✅

### Singapore / Ulu City (Priority 1.5 — added 2026-02-27)
- Maps: 541020000-541020800 (30 maps) ✅ in repack
- Mobs: Singapore area mobs (TBD — need to identify IDs in repack)
- Boss: Krexel (giant tree, multi-body) — need to confirm mob ID in repack
- Level range: 80-100, fills mid-game grinding gap
- Access: NPC at Changi Airport (stock v83 Singapore travel exists)

### Corrupted Temple of Time Mobs (Priority 1.5 — added 2026-02-27)
- Mobs: 8220016-8220021 (6 corrupted variants: Wyvern, Cornian, Skelegon, Kentaurus, etc.)
- Maps: Use existing deeper ToT maps, add these as higher-level spawns
- Level range: 110-120, gives ToT more variety at higher levels
- Low effort — just mob XMLs and spawn edits

### Neo City Mutant Mobs (Low Priority — added 2026-02-27)
- Mobs: 8600000-8600006 (7 mutant basic mobs)
- Could populate the Gate to the Future entry maps (Mutant Tino/Tiru/Tiguru forests)
- Very low effort

### Arcane River (Milestone 4 — Designed, added 2026-02-28)
- Maps: 450000000-450013870 (379 maps) ✅ in repack
- Confirmed feasible: community members have run Arcane River on v83 servers
- Requires complete mob re-stat for pre-BB damage formulas
- **Level range**: 150-170 (compressed from official 200-275)
- **3 zones**: Vanishing Journey (150-157), Chu Chu Island (157-163), Lachelein (163-170)
- **No Arcane Force** — gated by 4.5 job mastery + quest chains + level requirements
- **Narrative**: Not corruption. Elemental, ancient, awe. Erda spirits are guardians, not enemies. The Source is not evil — it's the wellspring of all power, guarded by an ancient Arcane Guardian.
- **Boss**: Arcane Guardian (Lv 170, ~2B HP, 6+ players)
- **Gear**: Arcane Set (Lv 160, token exchange via Arcane Tokens)
- Full design in `world-design.md`

---

## Server Infrastructure

| Component | Location | Notes |
|-----------|----------|-------|
| Cosmic server | 192.168.0.25:8484 | Docker, bind-mounted WZ/config/scripts |
| WZ data | /home/homelab/Cosmic/wz/ | Edit directly, restart to apply |
| Config | /home/homelab/Cosmic/config.yaml | |
| Scripts | /home/homelab/Cosmic/scripts/ | NPC + Quest JS |
| MySQL | Docker on .25 (cosmic-db-1) | drop_data, accounts, characters |
| Client | Windows devbox (.194) | Patched EXE, NX files |
| Repo | TwinleafStory (both machines) | Source of truth |
| Shared drive | C:\Shared ↔ ~/Shared-Win | Cross-machine file exchange |

---

## Current State (2026-02-28)

### Done
- [x] Windows dev box set up (R5 3600, .194)
- [x] Client patched and working (PIC screen confirmed!)
- [x] SMB share between Mac and Windows
- [x] Community repack analyzed (523 new mobs, 579 new maps)
- [x] String.wz blocker solved (wz.zip has everything)
- [x] Solo expeditions enabled on server
- [x] Showa Boss defense nerfed (5000→1500)
- [x] k8s-node3 bumped to 6 cores
- [x] Full design docs written
- [x] All Session 2 design decisions locked: narratives, ToT 100-kill, Explorer-only, Singapore, CK/Aran disable, Cody NPC, Arcane River M4
- [x] Full repack audits complete (Sessions 3-4): mobs, maps, equips, chairs, skills, cash items, quests, NPCs, areas
- [x] All Session 3-4 design decisions locked: 4.5 skills (48 designed), zone completion vendors, town vendor overhaul, cash shop philosophy, exploration tiers, returning NPCs, PQs, cosmetics, trade hub, Rien/Ereve endgame roles, Arcane River 3-zone design, side zone purposes (KFT/Zipangu/Magatia/Ariant/Ellin/Mushroom Castle/Amoria)

### Implementation Phase (See IMPLEMENTATION-GUIDE.md)
Implementation is tracked in the Implementation Guide. Key prompts and server tasks organized by phase.

---

## Decision Log

All design decisions, recorded for reference:

| Date | Decision | Rationale |
|------|----------|-----------|
| 2026-02-27 | Explorer only (CK/Aran disabled) | Simplifies balance, frees CK/Aran content for repurposing |
| 2026-02-27 | ToT kill quests: 999 → 100 | 999 is miserable, 100 = ~15 min per stage at 10x |
| 2026-02-27 | LHC narrative: corrupted CK scouting party | Explains hostile CK mobs, creates mystery + rescue mission |
| 2026-02-27 | Future Ereve narrative: dark vision from ToT gate | Ties LHC and Empress together, gives players reason to care |
| 2026-02-27 | Singapore/Ulu City included | Fills 80-100 gap, era-appropriate content |
| 2026-02-27 | Corrupted ToT mobs included | Low-effort, bridges 100-120 difficulty |
| 2026-02-27 | Arcane River = Milestone 4 | Confirmed feasible, massive scope, defer until core is done |
| 2026-02-27 | Ereve → Explorer endgame hub | Narrative reward for beating Empress, CK NPC quests |
| 2026-02-27 | Cody NPC + standalone guide | In-game + out-of-game progression guidance |
| 2026-02-27 | Cash shop = cosmetics only, no gacha | NX for looks, meso alternative for everything |
| 2026-02-28 | Rien → Lv 140+ endgame (4.5 job trials + Arcane River gate) | ~~Replaces earlier Lv 50-70 adventure zone idea~~. Archive Keeper NPC. |
| 2026-02-28 | 4.5 skills from CK/Aran/DB assets only | ~~Replaces earlier plan to use Kaiser/Luminous/etc~~. Only assets in the v83 repack. |
| 2026-02-28 | 48 skills designed (4 per branch) | Full spec in twinleaf-skills.md |
| 2026-02-28 | Trade button → Kerning Night Market (103000007) | Free Market dead on small server. Night market is atmospheric. |
| 2026-02-28 | Zone completion vendors — every zone | Deterministic progression (~70-80% of boss drops), reduces RNG dependency |
| 2026-02-28 | Token currencies for endgame bad luck protection | Von Leon Coins, Soul Shards, Arcane Tokens |
| 2026-02-28 | PQs: KPQ+LPQ+OPQ core, no scaling | Stock 3-6 player design is fine, buff EXP rewards |
| 2026-02-28 | Per-town hair/face salons, no Royal Hair | Each town curated, Mystery Stylist in Sleepywood |
| 2026-02-28 | Arcane River: 150-170, 3 zones, no Arcane Force | Gated by 4.5 mastery + level + quest chains |
| 2026-02-28 | Side zones all have completion vendors | KFT/Zipangu/Magatia/Ariant/Ellin/Mushroom Castle/Amoria |
| 2026-02-28 | Reskin existing v83 gear for VL/Empress | Models missing from repack, use existing visuals + custom names/stats |
| 2026-02-28 | Shadower overhaul: meso gimmicks → melee assassin | Meso Explosion → Shadow Flurry, Pickpocket → Marked for Death |
| 2026-02-28 | Universal: MW auto-passive, HW auto-cleanse, boosters baked in | Frees hotkey slots |

---

## Document Index

| Document | Purpose |
|----------|---------|
| **This file** (TWINLEAF-DESIGN-DOC.md) | Master design overview, vision, decisions |
| `world-design.md` | Detailed world design: areas, vendors, NPCs, cosmetics, exploration, cash shop |
| `quest-design.md` | Quest chains, NPC dialogue tone guide |
| `twinleaf-skills.md` | Full 4.5 skill revamp (48 skills), dead skill cuts, Shadower overhaul |
| `balance-design.md` | Boss rebalancing, damage/HP targets, gear progression |
| `boss-audit.md` | Stock boss stat audit, playtest templates |
| `PROGRESSION-GUIDE.md` | Player-facing progression guide (also used by Cody NPC) |
| `IMPLEMENTATION-GUIDE.md` | Implementation playbook: phases, prompts, deploy steps |
| `audits/AUDIT-SESSION4-AREAS-NPCS-EQUIPS.md` | Session 4 audit: NPC IDs, NLC/Omega/Kampung, equip models, Kataras |

---

*This document is the source of truth for "what is TwinleafStory." For "what do I do next," see IMPLEMENTATION-GUIDE.md.*
