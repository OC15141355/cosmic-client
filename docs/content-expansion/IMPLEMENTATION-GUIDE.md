# TwinleafStory — Master Implementation Guide

*The game MapleStory was supposed to be.*
*Last updated: 2026-02-28 — Session 4 (design complete, consistency pass)*

---

## How to Read This Document

This is your playbook. It tells you:
- What to do, in what order
- Which prompts to run on the Windows devbox and when
- When to stop and test
- When to SSH to the server
- What we haven't explored yet and when to explore it
- How everything ties together into the final vision

Every phase has a **TEST checkpoint** before moving to the next. Don't skip them.

---

## The Vision

TwinleafStory is the game MapleStory was meant to be before Big Bang ruined it. We're building on a v83 foundation, but we're not limiting ourselves to v83 content. We're pulling from every version that had good ideas — v84 through v200+ — and re-statting everything for pre-BB formulas and small-group play.

**What makes this different from every other v83 server:**
- Content beyond 120 that actually works with pre-BB mechanics
- Explorers as the only class, with 48 custom 4.5 job skills using CK/Aran/DB animations from the v83 repack
- Ereve (post-Empress reward hub) and Rien (Lv 140+ endgame: 4.5 trials + Arcane River gate)
- A coherent narrative that ties LHC → Future Ereve → Empress into one story
- Chairs, cosmetics, and collectibles from every era as exploration rewards
- Arcane River re-statted for pre-BB as the ultimate endgame (eventually)
- A real cash shop filled with cosmetics (free or meso-based, not pay-to-win)

---

## What We Have (Repack Audit Status)

### Fully Audited
| WZ File | What's In It | Extra vs Server | Status |
|---------|-------------|-----------------|--------|
| Mob.wz | Monster data (sprites, stats, AI) | +523 mobs | ✅ Catalogued — IDs, names, groups |
| Map.wz | Map layouts (tiles, spawns, portals) | +579 maps | ✅ Catalogued — all areas identified |
| Character.wz | Equipment visuals (sprites) | +1,933 helmets alone | ✅ Partial — equipment sets IDed, bulk not |
| String.wz | Names for everything | wz.zip is richer source | ✅ wz.zip has everything we need |

### Audited in Sessions 3-4
| WZ File | What's In It | Findings | Status |
|---------|-------------|----------|--------|
| **Item.wz** | Chairs, scrolls, cash items, consumables | 1,881 chairs, 102 new pet equips, existing scroll IDs usable | ✅ Audited |
| **Skill.wz** | All skill animations + data | 333 CK/Aran skills found, 48 4.5 skills designed from them. CK→Warriors, BW→Mages, WA→Bowmen, NW+DB→Thieves, TB→Pirates. No DB skill files (430-434) but 96 Katara weapon sprites exist. | ✅ Audited |
| **Npc.wz** | NPC appearance sprites | All 6 returning NPCs found with valid IDs (Cassandra=9010010, Gaga=9000021, Duey=9010009, Big Headward=1012117, Maple Admin=9010110, Cody=9200000) | ✅ Audited |
| **Quest.wz** | Quest definitions | Stock v83 quests catalogued, ToT kill quests identified | ✅ Audited |

### NOT YET AUDITED
| WZ File | What's In It | Why We Care | Priority |
|---------|-------------|-------------|----------|
| **Etc.wz** | Commodity data, NPC shop lists, misc | Cash shop item definitions, shop inventories. | **LOW** |
| **Sound.wz** | BGM tracks, sound effects | New area music — LHC, Future Ereve, Arcane River. | **LOW** |
| **TamingMob.wz** | Mount/riding visuals | Mount collectibles as boss/quest rewards. | **LOW** |
| **Reactor.wz** | Interactive objects | Hidden portals, breakable objects, puzzles. | **LOW** |
| **Effect.wz** | Screen effects, buff visuals | Visual polish for custom skills/bosses. | **LOW** |

See `audits/AUDIT-SESSION4-AREAS-NPCS-EQUIPS.md` for detailed Session 4 findings (NLC/Omega Sector/Kampung maps, equipment model gaps, Katara animation structure).

---

## The Full Roadmap

```
PHASE 0: Foundation                          ← YOU ARE HERE
PHASE 1: Core Content (Milestones 1-3)
PHASE 2: World Audit + Expansion Content
PHASE 3: Systems + Polish (Cash Shop, Chairs, CK/Aran Repurpose)
PHASE 4: Endgame (4.5 Skills, Arcane River)
PHASE 5: Friends + Launch
```

---

## PHASE 0: Foundation

### Goal
Get the server into a workable state. Fix accounts, update strings, rebalance existing bosses. After this phase, you can login as GM and test everything.

### Step 0.1 — Fix GM Login (MacBook SSH)

```bash
# SSH to server
ssh homelab@192.168.0.25

# Check accounts
docker exec -it cosmic-db-1 mysql -uroot -proot cosmic \
  -e "SELECT name, gm, loggedin FROM accounts WHERE name IN ('admin','quiet');"

# Ensure quiet is GM 6
docker exec -it cosmic-db-1 mysql -uroot -proot cosmic \
  -e "UPDATE accounts SET gm=6 WHERE name='quiet';"

# Reset admin password to ≤12 chars (v83 client limit)
docker exec -it cosmic-db-1 mysql -uroot -proot cosmic \
  -e "UPDATE accounts SET password='' WHERE name='admin';"
# Then login on client with new short password — bcrypt auto-migrates
```

**Test**: Login on Windows client with `quiet` account. Verify GM commands work: type `!help` in chat.

### Step 0.2 — Run PROMPT-01: String.wz Merge (Windows Devbox)

This is the first prompt to run on Windows Claude. It updates all item and mob names.

1. Open Claude Code on Windows devbox
2. Feed it `C:\Shared\prompts\PROMPT-01-STRING-WZ-MERGE.md`
3. Review output in `C:\Shared\output\string-wz\`
4. Deploy to server (from MacBook):
```bash
scp ~/Shared-Win/output/string-wz/Eqp.img.xml homelab@192.168.0.25:/home/homelab/Cosmic/wz/String.wz/
scp ~/Shared-Win/output/string-wz/Mob.img.xml homelab@192.168.0.25:/home/homelab/Cosmic/wz/String.wz/
```

### Step 0.3 — Boss HP Rebalancing (MacBook SSH)

Edit existing boss XMLs directly on the server. See SERVER-TASKS.md §2 for full details.

Quick version:
```bash
ssh homelab@192.168.0.25
# Edit Zakum (8800000-8800010), Horntail (8810000-8810018), Pink Bean (8820001-8820006)
# Reduce HP values per the design doc targets
nano /home/homelab/Cosmic/wz/Mob.wz/8800002.img.xml  # etc.
```

### Step 0.4 — Temple of Time Kill Quest Reduction (MacBook SSH)

Find and edit quest scripts that require 999 kills → change to 100.

```bash
ssh homelab@192.168.0.25
# Find ToT kill quests
grep -r "999" /home/homelab/Cosmic/scripts/quest/ | grep -i "time\|temple\|memory\|regret\|oblivion"
# Also check Quest.wz
grep -r "999" /home/homelab/Cosmic/wz/Quest.wz/
```

### Step 0.5 — Restart + Test

```bash
ssh homelab@192.168.0.25 "cd /home/homelab/Cosmic && docker compose restart cosmic-server-1"
```

### 🧪 PHASE 0 TEST CHECKPOINT

Login as GM on Windows. Verify:
- [ ] GM commands work (`!help`, `!warp`, `!spawn`, `!item`)
- [ ] Zakum HP is reduced (`!warp 211042300`, `!spawn 8800002`, attack it — should die faster)
- [ ] New equipment names show up (`!item 1003172` — should show "Lionheart Battle Helm" in inventory even though the equip doesn't exist yet)
- [ ] New mob names display (`!spawn 8800100` — will fail because mob XML doesn't exist yet, but the name should be in String.wz)

---

## PHASE 1: Core Content

### Goal
Import all three milestones of new content. After this phase, there are new maps, mobs, bosses, and equipment from level 80 to 140.

### Milestone 1A: Chaos Zakum (Lv 120)

**Run on Windows**: PROMPT-02 (Chaos Zakum mobs)

**Deploy** (MacBook):
```bash
scp ~/Shared-Win/output/chaos-zakum/mob-xml/*.xml \
  homelab@192.168.0.25:/home/homelab/Cosmic/wz/Mob.wz/
```

**Server restart**, then test:
- `!warp 211042300` (Zakum altar)
- `!spawn 8800100` (Chaos Zakum body 1 — verify it appears)
- `!spawn 8800103` (arm — verify it appears)
- Attack them — check if HP feels right for a 4-6 player encounter
- `!killall` to clean up

### Milestone 1B: Singapore / Ulu City (Lv 80-100)

**Run on Windows**: PROMPT-09 (Singapore investigation + extraction)

This prompt INVESTIGATES first — Singapore might already partially exist on the server. Review the output summary before deploying.

**Deploy maps and mobs**, restart, test:
- `!warp 540000000` (Singapore CBD — may already work)
- If new maps were added: `!warp 541020000` (Ulu City)
- Verify mob spawns, levels, and EXP look right

### Milestone 1C: Corrupted Temple of Time (Lv 110-120)

**Run on Windows**: PROMPT-10 (6 corrupted ToT mobs)

**Deploy**, restart, test:
- `!spawn 8220016` through `!spawn 8220021` in a ToT map
- Verify they look correct and have appropriate stats
- Note: Adding them to actual map spawn tables is a separate server-side task (edit the ToT map XMLs to include these mob IDs in their `life` sections)

### 🧪 MILESTONE 1 TEST CHECKPOINT

As GM, playtest:
- [ ] Chaos Zakum spawns and has correct stats
- [ ] Singapore/Ulu City maps are accessible and mobs spawn
- [ ] Corrupted ToT mobs exist and have correct stats
- [ ] No server crashes from new content
- [ ] String data correct for all new mobs

**CREATE A NEW CHARACTER** (non-GM) and level it to ~30. Check the early game still feels smooth. Make sure we didn't break anything.

### Milestone 2: Lion Heart Castle + Von Leon (Lv 120-130)

This is the biggest single content drop. Run prompts in this order:

1. **PROMPT-03** (LHC maps) → Review the SUMMARY to see which mob IDs the maps reference
2. **PROMPT-04** (LHC mobs) → Uses mob IDs from PROMPT-03's output
3. **PROMPT-05** (Von Leon boss + equipment)

**Deploy all together** — maps, mobs, boss, and equipment in one batch:
```bash
# Maps
scp ~/Shared-Win/output/lhc-maps/*.xml \
  homelab@192.168.0.25:/home/homelab/Cosmic/wz/Map.wz/Map/Map2/

# Mobs
scp ~/Shared-Win/output/lhc-mobs/*.xml \
  homelab@192.168.0.25:/home/homelab/Cosmic/wz/Mob.wz/

# Von Leon boss mobs
scp ~/Shared-Win/output/von-leon/mob-xml/*.xml \
  homelab@192.168.0.25:/home/homelab/Cosmic/wz/Mob.wz/

# Von Leon equipment
scp ~/Shared-Win/output/von-leon/equip-xml/*.xml \
  homelab@192.168.0.25:/home/homelab/Cosmic/wz/Character.wz/  # (various subdirs)

# Von Leon drop table SQL
scp ~/Shared-Win/output/von-leon/drop-table.sql homelab@192.168.0.25:/tmp/
ssh homelab@192.168.0.25 "docker exec -i cosmic-db-1 mysql -uroot -proot cosmic < /tmp/drop-table.sql"
```

**Server restart**, then test:
- `!warp 211060000` (Desolate Moor — LHC entrance)
- Walk through the castle — check portals connect properly between maps
- Verify mob spawns in each map
- `!warp 211070100` (Von Leon boss room) → `!spawn 8840000` → verify Von Leon appears
- `!item 1003172` (Lionheart Battle Helm) → verify equipment exists and has correct stats
- Kill Von Leon with `!killall` → check if drops appear (need drop table SQL deployed)

### 🧪 MILESTONE 2 TEST CHECKPOINT

- [ ] LHC entrance accessible from `!warp`
- [ ] All 28 maps load without errors
- [ ] Portals connect correctly (walk through entire castle)
- [ ] Mobs spawn at correct levels and give correct EXP
- [ ] Von Leon spawns and has correct stats
- [ ] Von Leon drops Von Leon equipment
- [ ] Von Leon equipment has correct stats and can be equipped
- [ ] Create LHC access NPC (server-side task — see SERVER-TASKS.md §5.1)

### Milestone 3: Future Ereve + Empress (Lv 130-140)

Same pattern:

1. **PROMPT-06** (Future Ereve maps) → Review SUMMARY for mob IDs
2. **PROMPT-07** (Future Ereve mobs) → Uses mob IDs from PROMPT-06
3. **PROMPT-08** (Empress boss + equipment)

**Deploy all together**, restart, test:
- `!warp 271000000` (Gate to the Future)
- Walk through Henesys Ruins, Knight District, up to Cygnus's Chamber
- `!warp 271040100` (boss room) → `!spawn 8850011` → verify Empress appears
- `!item 1003159` (Empress's Fine Hat) → verify equipment
- Test drops

### 🧪 MILESTONE 3 TEST CHECKPOINT

- [ ] All 42 Future Ereve maps load
- [ ] Portal chain works from Gate → Henesys Ruins → Stronghold → Cygnus Chamber
- [ ] Mobs at correct levels and EXP values
- [ ] Empress Cygnus spawns (all 12 phase mobs)
- [ ] Empress drops equipment
- [ ] Equipment stats correct
- [ ] Create GttF access NPC (server-side)

### 🧪 PHASE 1 COMPLETE TEST — Full Progression Run

**The big test.** Create a fresh Explorer character. With 10x rates and GM item access (give yourself appropriate gear at each tier), play through the entire progression:

1. **Lv 1-70**: Victoria Island, Ossyria — stock v83 (should already work)
2. **Lv 70**: Zakum — verify rebalanced HP feels right
3. **Lv 80-100**: Singapore/Ulu City — verify area works as a grind zone
4. **Lv 100**: Horntail — verify rebalanced HP
5. **Lv 100-120**: Temple of Time — verify 100-kill quests, corrupted mobs
6. **Lv 120**: Chaos Zakum — verify fight
7. **Lv 120-130**: Lion Heart Castle — grind, check mob EXP at each tier
8. **Lv 125**: Von Leon — full boss fight, check drops
9. **Lv 130-140**: Future Ereve — grind, check mob EXP
10. **Lv 140**: Empress — attempt full fight

**Record every issue** in `C:\Shared\PLAYTEST-NOTES.md`. This informs Phase 2 tuning.

---

## PHASE 2: World Audit + Expansion Content

### Goal
Before building more systems, fully audit what the repack contains that we haven't explored. Then expand with CK/Aran repurposing and all the cosmetic/collectible content.

### Step 2.1 — Full Repack Audit (New Windows Prompts)

We need new prompts to investigate the un-audited WZ files. Write and run these:

**PROMPT-12: Item.wz Full Audit**
- Open Item.wz in HaRepacker
- Catalogue EVERYTHING extra vs server:
  - `Item.wz/Cash/` — Cash shop items (pets, cosmetics, teleport rocks, megaphones)
  - `Item.wz/Install/` — Setup items (**CHAIRS**, house items)
  - `Item.wz/Consume/` — Consumables (new potions, scrolls, EXP coupons)
  - `Item.wz/Etc/` — ETC items (quest items, crafting materials, ores)
  - `Item.wz/Pet/` — Pet data
- Record all item IDs, names, and categories
- Cross-reference with wz.zip Etc.img.xml for names
- Special attention to: **chairs** (what new chairs exist?), **scrolls** (any new scroll types?), **mounts** (mount summoning items)

**PROMPT-13: Skill.wz Full Audit**
- Focus on skills NOT in v83:
  - Cygnus Knight skills (10001xxx - 15001xxx) — animations we can steal
  - Aran skills (21000xxx - 21120xxx) — animations we can steal
  - Resistance skills (31000xxx - 33000xxx) — per PROMPT-11 but more thorough
  - All other post-v83 class skills
- For each skill: record ID, name, visual description, hit type (single/AoE/buff), element
- Categorize by "which Explorer class could use this"

**PROMPT-14: Ereve + Rien Map/Content Audit**
- What maps exist for Ereve (130000000 range)?
- What maps exist for Rien (914000000 range)?
- What mobs spawn in these areas?
- What NPCs are present?
- What quests reference these areas?
- How are they connected to the rest of the world (portals)?

**PROMPT-15: Character.wz Deep Audit**
- Beyond equipment sets, what else is in Character.wz?
- Cash equipment (NX covers): What cosmetic overrides exist?
- Face accessories, eye accessories, earrings not yet catalogued
- Weapons from all post-v83 classes (could become Explorer weapon skins)
- **Mounts** (TamingMob.wz cross-reference)

**PROMPT-16: Sound.wz Audit**
- What BGM tracks exist beyond v83?
- Which tracks are for LHC, Future Ereve, Arcane River?
- We want new areas to have their proper music

### Step 2.2 — CK/Aran Repurpose Design (DECIDED — Session 3)

**Ereve Repurpose** — Post-Empress reward hub (Lv 140+):
- Players who beat Empress earn access to restored Ereve via Rien Keystone
- CK NPCs (Mihile, Oz, Irena, Eckhart, Hawkeye) give unique quest chains with unique rewards
- Soul Shard vendor for Empress set piece exchange (bad luck protection)
- Narrative payoff: "You prevented this beautiful place from being destroyed"
- Full quest chain design in `quest-design.md` (7 steps)

**Rien Repurpose** — Lv 140+ endgame zone:
- Home of **Archive Keeper** NPC who administers 4.5 job trials
- 8-step branch-specific quest chain per job class
- Sealed portal to Arcane River (opens after ALL 4.5 trials mastered)
- **Skill Stone vendor** — boost 4.5 skills (2M each, +1 level, max 3 per skill)
- Full trial design in `quest-design.md` and `twinleaf-skills.md`

**CK/Aran Skill Repurpose** (DECIDED — all 48 skills designed):
- Dawn Warrior + Aran → Warrior 4.5 skills (Soul Driver, Rolling Spin, etc.)
- Blaze Wizard (element-reskinned) → Mage 4.5 skills (Fire/Ice Pillar, Flame/Frost Gear, etc.)
- Wind Archer → Bowman 4.5 skills (Wind Walk, Storm Break, etc.)
- Night Walker + Katara sprites → Thief 4.5 skills (Vanish, Bloody Storm, etc.)
- Thunder Breaker → Pirate 4.5 skills (Spark, Lightning Charge, etc.)
- See `twinleaf-skills.md` for complete skill specifications

### Step 2.3 — Implement Cosmetic/Collectible Systems

**Chairs** (post-audit):
- Import all chair items from the repack
- Assign chairs as rewards:
  - Boss drops (rare chairs — e.g., "Von Leon's Throne" from Von Leon)
  - Map exploration (hidden chairs in hard-to-reach spots)
  - Quest rewards (complete a chain, get a unique chair)
  - Achievement rewards (kill 1000 of X mob, etc.)
- Chair sitting is a core MapleStory social feature — people LOVE collecting chairs

**Cash Shop** (meso-based, not NX):
- Populate with cosmetic items from the repack
- Convert NX prices to meso prices (generous — this isn't P2W)
- Include: cosmetic hats, capes, NX covers, hairstyles, face changes
- Exclude: anything that gives stat advantages
- Add a Cash Shop NPC in towns (or use existing Dimensional Mirror)

**Mounts**:
- Import mount items + TamingMob.wz visuals
- Assign as boss/quest rewards
- Mounts are fun endgame flex items

### 🧪 PHASE 2 TEST CHECKPOINT

- [ ] Full repack audit docs completed — we know EVERYTHING in the repack
- [ ] Ereve accessible as Explorer (portal NPC created)
- [ ] Rien accessible as Explorer (portal NPC created)
- [ ] At least 10 collectible chairs importable and working
- [ ] Cash shop NPC functional with cosmetic items
- [ ] CK/Aran character creation actually disabled (server-side)

---

## PHASE 3: Systems + Polish

### Goal
Build the custom systems that make TwinleafStory unique. 4.5 job skills, the Cody guide NPC, quest chains, narrative, and progression polish. Zone completion vendors.

### Step 3.1 — 4.5 Job Skill Implementation

> **Full design in `twinleaf-skills.md`** — all 48 skills specified with types, CDs, and animation sources.

This is the hardest technical work. It requires:
1. **Skill animation data** — use CK/Aran/DB skill files already in the v83 repack (NOT later-version classes)
2. **Server-side skill handlers** (Java code in Cosmic) — custom damage/effect logic
3. **Rien Keystone item** — dropped by Empress, grants access to Rien 4.5 trials
4. **Client NX data** — repurpose existing CK/Aran skill IDs, client uses their animations

**Animation source mapping** (all from v83 repack):
| Explorer Branch | Animation Source | Skill Files |
|----------------|-----------------|-------------|
| Warriors (Hero/Pally/DK) | Dawn Warrior + Aran | 1100-1111.img.xml, 2100-2112.img.xml |
| Mages (F/P, I/L, Bishop) | Blaze Wizard (element-reskinned) | 1200-1211.img.xml |
| Bowmen (BM/MM) | Wind Archer | 1300-1311.img.xml |
| Thieves (NL/Shadower) | Night Walker + Katara sprites | 1400-1411.img.xml, Character.wz Kataras |
| Pirates (Bucc/Corsair) | Thunder Breaker | 1500-1511.img.xml |

**Unlock mechanism**: Kill Empress Cygnus → receive **Rien Keystone** item → travel to Rien → talk to **Archive Keeper** NPC → 8-step branch-specific trial quest → skills unlocked. Each trial is tailored to the player's exact job class.

**Universal skill changes** (implement alongside 4.5 skills):
- Maple Warrior → auto-passive at Lv 120
- Hero's Will → quest-granted auto-cleanse at Lv 140
- All Boosters → baked into Mastery passives
- 30+ dead skills cut (see twinleaf-skills.md for full list)
- Shadower complete overhaul (meso gimmicks → melee assassin)

### Step 3.2 — Cody Guide NPC

Write the Cody NPC script based on PROGRESSION-GUIDE.md. Cody appears in:
- Henesys, Kerning, Perion, Ellinia, Nautilus (low level towns)
- Orbis, Ludibrium, El Nath, Leafre (mid level towns)
- LHC, Future Ereve hubs (high level)

Script logic:
```javascript
// Cody checks player level and recommends:
// - Where to grind
// - Which boss to attempt next
// - What gear to aim for
// - How to get to the next area
```

### Step 3.3 — Quest Chains + Narrative

> **Full design in `quest-design.md`** — all quest chains designed with steps, NPCs, rewards, and dialogue tone.

Write NPC dialogue and quest scripts for:
1. **LHC access quest** (5 steps) — El Nath mountaineer sends you to investigate the castle
2. **Gate to the Future access quest** — Temple of Time sage warns of a dark vision
3. **Von Leon prequest** — simple (talk to NPC, enter boss room)
4. **Empress prequest** — beat Guard Captain Darknell, talk to hall NPC
5. **Ereve access quest** (7 steps) — post-Empress, Empress thanks you, CK NPCs give unique quests with rewards
6. **Rien 4.5 job trials** (8 steps) — Archive Keeper NPC, branch-specific trials at Lv 140+
7. **Singapore quest chain** (4 steps) — Krexel investigation
8. **Mu Lung Dojo quest** (4 steps) — Dojo challenge + Big Headward leaderboard
9. **Returning NPC scripts** — Cassandra (rumor broker), Gaga (collection tracker), Duey (mail), Maple Admin (QoL vendor), Cody (progression guide)
10. **Zone completion vendor NPCs** — unlock scripts for every zone's completion condition

### Step 3.4 — CK/Aran Disable (Server-Side)

Block character creation at the server level:
- Find the character creation handler in `server/src/main/java/net/server/handlers/login/`
- Reject job IDs 1000 (CK) and 2000 (Aran)
- OR: simpler approach — modify the CK/Aran creation NPCs to say "Coming soon..." and not proceed

### 🧪 PHASE 3 TEST CHECKPOINT

- [ ] At least 1-2 4.5 skills working per class (proof of concept)
- [ ] Cody NPC gives correct recommendations at each level range
- [ ] LHC access quest works
- [ ] GttF access quest works
- [ ] Ereve access quest works (post-Empress reward)
- [ ] CK/Aran creation blocked
- [ ] Full progression playthrough with quest chains feels coherent

---

## PHASE 4: Endgame Expansion

### Goal
Add the aspirational content that keeps players engaged past 140.

### Step 4.1 — Arcane River (Lv 150-170)

> **Full design in `world-design.md`** — all three zones with mobs, NPCs, and gating.

The big one. 379 maps from the repack. Confirmed feasible — community members run Arcane River on v83.

**Design decisions (ALL RESOLVED — Session 3):**
- **Level range**: 150-170 (compressed from official 200-275)
- **No Arcane Force** — gated by 4.5 job mastery + quest chains + level requirements
- **3 zones**: Vanishing Journey (150-157), Chu Chu Island (157-163), Lachelein (163-170)
- **Narrative**: NOT corruption. Elemental, ancient, awe. Erda spirits are guardians. The Source is the wellspring of all power, guarded by an Arcane Guardian.
- **Boss**: Arcane Guardian (Lv 170, ~2B HP, 6+ players)
- **Gear**: Arcane Set (Lv 160, Arcane Token exchange)

**New prompts needed:**
- PROMPT-XX: Arcane River map extraction (VJ + Chu Chu + Lachelein only — ~100 maps)
- PROMPT-XX: Arcane River mob extraction + re-stat for pre-BB
- PROMPT-XX: Arcane Guardian boss extraction
- PROMPT-XX: Arcane River equipment (or reskin existing — same strategy as VL/Empress)

**Implementation order:**
1. Vanishing Journey (entry zone, Lv 150-157) — establish tone
2. Chu Chu Island (mid zone, Lv 157-163) — whimsical contrast
3. Lachelein (high zone, Lv 163-170) — dreamy endgame
4. Arcane Guardian (boss, Lv 170) — final encounter

### Step 4.2 — Crimsonwood Keep (Lv 90-120)

Lower priority but fun content:
- Mobs 8220000-8220006 already in repack (Eliza, Snowman, Chimera, Leviathan, Dodo, Lilynouch, Lyka)
- Could be a party dungeon for 90-120 range
- No PQ mechanics — just import as a multi-boss dungeon

### Step 4.3 — Additional Content from Repack

Based on the Phase 2 audit, other content that might be worth importing:
- **Neo City** (time travel area, 8600xxx mobs already catalogued)
- **Twilight Perion** (if we find a narrative hook — maybe tie to Arcane River)
- **Event content** (holiday bosses, special maps — fun seasonal stuff)

### 🧪 PHASE 4 TEST CHECKPOINT

- [ ] Arcane River entry area (Vanishing Journey) functional
- [ ] Mobs re-statted correctly for pre-BB
- [ ] Level 150+ progression feels achievable from Future Ereve
- [ ] Arcane River has its proper BGM
- [ ] New gear tier exists and drops

---

## PHASE 5: Friends + Launch

### Goal
Invite friends, run playtests, tune balance, polish the experience.

### Step 5.1 — Pre-Launch Checklist
- [ ] Full progression 1-140+ is smooth with no blockers
- [ ] All boss encounters tested and tuned
- [ ] All equipment drops working
- [ ] All NPC scripts written and tested
- [ ] Cody NPC working in all major towns
- [ ] Progression guide doc shared with friends
- [ ] Cash shop functional with cosmetic items
- [ ] At least 20 collectible chairs in the game
- [ ] Server stable under expected load (2-6 concurrent players)

### Step 5.2 — Tailscale Invites
- Invite friends to tailnet (GitHub auth)
- Share client download (patched EXE + NX files)
- Share progression guide
- Set up Discord channel for coordination

### Step 5.3 — Balance Tuning (Ongoing)
- Track player feedback
- Adjust boss HP/damage based on actual party compositions
- Adjust mob EXP if leveling feels too fast/slow
- Add content as players reach it (stay 1 milestone ahead)

### Step 5.4 — Ongoing Content Cadence

Once friends are playing:
- **Weekly**: Small fixes, balance tweaks, bug fixes
- **Biweekly**: New quest chains, new chairs/cosmetics, minor content
- **Monthly**: New boss encounters, new areas, major content drops
- **Quarterly**: Major milestones (Arcane River, 4.5 job batches)

---

## GM Testing Playbook

### Essential GM Commands
```
!help                    — List all commands
!warp <mapid>            — Teleport to map
!warpto <player>         — Teleport to player
!spawn <mobid> [qty]     — Spawn mob(s)
!killall                 — Kill all mobs on map
!item <itemid> [qty]     — Give yourself an item
!drop <itemid> [qty]     — Drop item on ground
!level <level>           — Set your level
!job <jobid>             — Set your job
!str/dex/int/luk <amt>   — Set stats
!god                     — Toggle invincibility
!heal                    — Full heal
!search mob <name>       — Find mob IDs by name
!search item <name>      — Find item IDs by name
!search map <name>       — Find map IDs by name
!cleardrops              — Clear drops on map
!say <message>           — Server-wide message
```

### Testing a New Map
```
1. !warp <mapid>                    — Does it load?
2. Look around                       — Tiles/backgrounds correct?
3. Walk to portals                   — Do they work? Where do they go?
4. Wait for mob spawns               — Do mobs appear?
5. Attack mobs                       — Correct level? Correct HP? Correct EXP?
6. !killall                          — Do drops appear?
7. Pick up drops                     — Correct items?
```

### Testing a New Boss
```
1. !warp <bossmap>                   — Enter boss room
2. !god                              — Toggle invincibility (for stat checking)
3. !spawn <bossid>                   — Spawn boss
4. Attack for 30 seconds             — Note damage dealt, estimate time-to-kill
5. Let boss hit you (god off)        — Note damage taken, is it survivable?
6. !killall                          — Check drops
7. !item <equipid>                   — Equip drops, verify stats
8. Calculate: HP ÷ (your DPS × party size) = minutes to kill
   - Solo should be 20-30+ minutes (discouraging but possible)
   - 4 players should be 8-15 minutes (target for most bosses)
   - 6 players should be 5-10 minutes (smooth, rewarding)
```

### Testing New Equipment
```
1. !item <equipid>                   — Get item
2. Equip it                          — Does it show visually?
3. Check stats (equipment window)    — Correct ATK/DEF/stats?
4. Check reqLevel                    — Correct level requirement?
5. Try scrolling                     — Does tuc (upgrade slots) work?
```

---

## Prompt Execution Quick Reference

### Phase 0 (Foundation — do first)
| Order | Prompt | Where | Deploys To |
|-------|--------|-------|------------|
| 1 | PROMPT-01 (Strings) | Windows | Server String.wz |
| — | Boss rebalance | MacBook SSH | Server Mob.wz |
| — | ToT quest edit | MacBook SSH | Server scripts/quest |
| — | GM fix | MacBook SSH | Server MySQL |

### Phase 1 (Core Content — sequential milestones)
| Order | Prompt | Where | Deploys To |
|-------|--------|-------|------------|
| 2 | PROMPT-02 (CZak) | Windows | Server Mob.wz |
| 3 | PROMPT-09 (Singapore) | Windows | Server Map+Mob.wz |
| 4 | PROMPT-10 (Corrupted ToT) | Windows | Server Mob.wz |
| — | **TEST CHECKPOINT** | Windows client | — |
| 5 | PROMPT-03 (LHC maps) | Windows | Server Map.wz |
| 6 | PROMPT-04 (LHC mobs) | Windows | Server Mob.wz |
| 7 | PROMPT-05 (Von Leon) | Windows | Server Mob+Char.wz + SQL |
| — | **TEST CHECKPOINT** | Windows client | — |
| 8 | PROMPT-06 (FE maps) | Windows | Server Map.wz |
| 9 | PROMPT-07 (FE mobs) | Windows | Server Mob.wz |
| 10 | PROMPT-08 (Empress) | Windows | Server Mob+Char.wz + SQL |
| — | **TEST CHECKPOINT** | Windows client | — |
| — | NPC scripts | MacBook SSH | Server scripts/npc |
| — | **FULL PROGRESSION TEST** | Windows client | — |

### Phase 2 (World Audit — MOSTLY COMPLETE via Sessions 3-4)
| Order | Prompt | Where | Status |
|-------|--------|-------|--------|
| ~~11~~ | ~~PROMPT-12 (Item.wz audit)~~ | ~~Windows~~ | ✅ Done (Session 3): chairs, scrolls, cash items catalogued |
| ~~12~~ | ~~PROMPT-13 (Skill.wz audit)~~ | ~~Windows~~ | ✅ Done (Session 3): CK/Aran/DB skills audited, 48 4.5 skills designed |
| ~~13~~ | ~~PROMPT-14 (Ereve/Rien audit)~~ | ~~Windows~~ | ✅ Done (Session 3): maps/mobs/NPCs catalogued |
| 14 | PROMPT-15 (Character.wz deep) | Windows | Partial — Von Leon/Empress models MISSING (Session 4 finding) |
| 15 | PROMPT-16 (Sound.wz) | Windows | Not started — low priority |
| — | ~~**DESIGN SESSION**~~ | ~~MacBook~~ | ✅ Done (Sessions 3-4): all design complete |

### Phase 3-5 (See sections above for details)

---

## File Locations Reference

### Windows Devbox (192.168.0.194, user: carbyne)
```
C:\Users\carbyne\Documents\TwinleafStory\        — The repo
C:\Users\carbyne\Documents\TwinleafStory\server\  — Server source + WZ
C:\Users\carbyne\Documents\MapleStory\            — Clean v83 client
C:\Users\carbyne\Documents\CommunityRepack\       — Post-v83 WZ/IMG data
C:\Users\carbyne\Documents\HaRepacker\            — WZ editor tool
C:\Shared\                                        — SMB share to MacBook
C:\Shared\prompts\                                — Claude prompts
C:\Shared\output\                                 — Claude outputs
```

### MacBook (ichiran, 192.168.0.92)
```
~/Shared-Win/                                     — SMB share from Windows
~/Shared-Win/prompts/                             — Claude prompts (synced)
~/Shared-Win/output/                              — Claude outputs (synced)
```

### Server (homelab@192.168.0.25)
```
/home/homelab/Cosmic/wz/                          — Live WZ data
/home/homelab/Cosmic/wz/Mob.wz/                   — Monster XMLs
/home/homelab/Cosmic/wz/Map.wz/Map/               — Map XMLs
/home/homelab/Cosmic/wz/Character.wz/             — Equipment XMLs
/home/homelab/Cosmic/wz/String.wz/                — String XMLs
/home/homelab/Cosmic/wz/Item.wz/                  — Item XMLs
/home/homelab/Cosmic/wz/Skill.wz/                 — Skill XMLs
/home/homelab/Cosmic/config.yaml                  — Server config
/home/homelab/Cosmic/scripts/npc/                 — NPC scripts (JS)
/home/homelab/Cosmic/scripts/quest/               — Quest scripts (JS)
Docker: cosmic-server-1, cosmic-db-1 (MySQL)
```

---

## Decision Log

> Full decision log in `TWINLEAF-DESIGN-DOC.md`. Key implementation-relevant decisions below.

| Date | Decision | Impact on Implementation |
|------|----------|------------------------|
| 2026-02-27 | Explorer only (CK/Aran disabled) | Block CK/Aran creation in server handler |
| 2026-02-27 | ToT kill quests: 999 → 100 | Edit quest scripts on server |
| 2026-02-28 | Rien = Lv 140+ (Archive Keeper, 4.5 trials) | ~~Not Lv 50-70 with Lilin~~ — requires new NPC scripts |
| 2026-02-28 | 4.5 skills from CK/Aran/DB assets only | Repurpose skill IDs from 1100-1511 + 2100-2112 ranges |
| 2026-02-28 | Trade button → Kerning Night Market (103000007) | Client FM warp → map 103000007 |
| 2026-02-28 | Zone completion vendors — every zone | ~20+ vendor NPCs to script with unlock conditions |
| 2026-02-28 | Token currencies (VL Coins, Soul Shards, Arcane Tokens) | New ETC items + exchange NPC scripts |
| 2026-02-28 | Reskin existing v83 gear for VL/Empress | Reassign item IDs → existing Character.wz models |

---

## Open Questions (Resolved)

All previously open questions have been resolved in Sessions 3-4:

1. ~~**Arcane River level compression**~~ → **150-170** (3 zones)
2. ~~**Arcane Force replacement**~~ → **4.5 mastery + quest chains + level requirements**
3. ~~**Arcane River narrative**~~ → **Elemental/ancient/awe (not corruption), Erda spirits as guardians**
4. ~~**Level cap**~~ → **170** (Arcane Guardian is final boss)
5. ~~**4.5 skill specifics**~~ → **48 skills designed** (see `twinleaf-skills.md`)
6. ~~**Ereve content design**~~ → **Post-Empress reward hub, CK NPC quests, Soul Shard vendor**
7. ~~**Rien quest chain**~~ → **Archive Keeper NPC, 8-step branch-specific 4.5 trials**
8. ~~**Chair collection scope**~~ → **~50 launch, 80+ with Arcane, ~35 named so far**
9. **Mount collection scope** — still TBD (low priority, implementation-dependent)
10. **Event content** — still TBD (post-launch decision)

---

*This document is the source of truth for "what do I do next." Update it as phases complete. For "what is TwinleafStory," see TWINLEAF-DESIGN-DOC.md.*
