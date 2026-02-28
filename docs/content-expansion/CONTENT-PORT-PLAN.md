# TwinleafStory — Content Port Plan
*Generated: 2026-02-27*

This document lists the concrete work required for each milestone, based on the community repack investigation.

---

## Milestone 1: Chaos Bosses (Pre-BB, v88 era) — Lv 120

### Chaos Zakum

**Map**: Same map as regular Zakum (211042300) — or a new dedicated Chaos Zakum map if one exists in the repack. The current server Zakum Altar is at 211042300.

**Mob IDs to add to server WZ:**

| ID | Name | Notes |
|----|------|-------|
| 8800100 | Chaos Zakum (Body 1) | Copy from repack, adjust stats |
| 8800101 | Chaos Zakum (Body 2) | |
| 8800102 | Chaos Zakum (Body 3) | |
| 8800103–8800110 | Chaos Zakum Arm 1–8 | 8 arms |
| 8800111 | Chaos Boogie | Summon |
| 8800112 | Chaos Puko | Summon |
| 8800113 | Chaos Poonko | Summon |
| 8800114 | Chaos Kusko | Summon |
| 8800115–8800116 | Additional summons | |

**Suggested Chaos Zakum stats (pre-BB tuned for 1-6 players):**

*Base philosophy: ~3x regular Zakum stats, but not a wall*

| Stat | Regular Zakum Body 2 | Suggested Chaos Zakum Body 2 |
|------|---------------------|------------------------------|
| Level | 140 | 155 |
| HP | 110,000,000 | 350,000,000 |
| PADamage | 1,080 | 1,400 |
| PDDamage (defense) | 1,200 | 1,500 |
| MDDamage (magic def) | 900 | 1,200 |
| EXP | 0 | 0 (reward via drops) |

**How to implement**: Export mob data from repack using HaRepacker → create XML files in server/wz/Mob.wz/ → modify stats. The repack .img files contain the full animation/skill data for Chaos Zakum.

**Drop Table (SQL to run on 192.168.0.21)**:
```sql
-- Chaos Zakum drops (add to drop_data table)
-- Suggested drops:
-- Zakum Helmet (1002357) - from regular Zakum (keep this)
-- Chaos Zakum Fragment (new item, create if needed)
-- Timeless gear pieces
-- Slot crystals / crafting mats
-- Large EXP coupons (for now, until Timeless gear is fully implemented)
```

**String data**: Already available in wz.zip Mob.img.xml. Run this on server:
```
server/wz/String.wz/Mob.img.xml — add entries for 8800100-8800116
```

---

### Chaos Horntail

**Status**: ⚠️ UNCLEAR — No dedicated "Chaos Horntail" mob IDs found in repack. Options:

1. The standard HT mob IDs (8810000–8810018) may be reused with higher stats
2. The 8810019–8810026 wyvern/cornian summons could form an extended Chaos HT fight
3. A "Chaos HT" may need to be custom-implemented using regular HT mob IDs + stat overrides

**Recommended approach**: Implement Chaos HT as a hardmode version of regular HT using the SAME mob IDs but with a separate expedition/party size requirement. The additional summon mobs (8810019–8810026: Red/Blue/Dark Wyvern, Green/Dark Cornian) are present in the repack and can be added as part of the extended fight.

**If we use same mob IDs**: Create a separate map (copy of HT map) with different spawn data pointing to a "Chaos" version, OR implement via a server-side hardmode toggle.

---

## Milestone 2: Lion Heart Castle + Von Leon (v96 era) — Lv 125

### Maps Needed (from repack — all 28 maps)

The full LHC map set needs to be:
1. Extracted from repack `.img` files using HaRepacker (export as XML)
2. Placed in `server/wz/Map.wz/Map/Map2/`

| ID | Name | Notes |
|----|------|-------|
| 211060000 | Desolate Moor | Entrance zone |
| 211060010 | Castle Entrance | |
| 211060100 | Under the Castle Walls 1 | Grinding area |
| 211060200–211060830 | Tower areas (1–5) + Castle Walls | Main grinding maps |
| 211060900 | Under the Castle Walls 5 | |
| 211061000–211061001 | Fifth Tower + Roof | |
| 211061100 | Ani's Jail | |
| 211070000 | Audience Room Corridor | Boss approach |
| 211070100 | **Audience Room** | **VON LEON BOSS ROOM** |
| 211070101 | Aerial Prison | |
| 211070110 | Roof of the Resurrection Tower | |

**Access**: Need an NPC to teleport players from Leafre (or nearest town) to 211060000. Or portal from existing map.

### Regular Mobs (grinding mobs for LHC area)

These need XML files created in `server/wz/Mob.wz/`:

**LHC castle mobs (required for 211060xxx maps to function):**
- 8210000–8210013: Crocky the Gatekeeper, Reindeer, Blood Reindeer, Bearwolf, Grey Vulture, Castle Golem, Prison Guard Boar, Prison Guard Rhino, Tower Ani × 3, Prison Guard Ani
- 8610000–8610033: Dawn, Blaze, Wind, Night, Thunder (Cygnus enemies), Official Knight A–G, etc.
- 8620000–8620027: Swollen Stumps, Pillaging Boars, Sinister Masks, Ancient Golem

**Suggested mob levels and EXP for LHC (pre-BB tuned):**

| Level Range | Mob Examples | Suggested Level | HP | EXP |
|-------------|-------------|-----------------|-----|-----|
| Entry (Lv 115–120 feel) | Prison Guard Boar, Swollen Stump | 130 | 500,000 | 15,000 |
| Mid (Lv 120–125 feel) | Castle Golem, Official Knight | 140 | 800,000 | 22,000 |
| High (Lv 125–130 feel) | Dawn, Blaze, Thunder | 150 | 1,200,000 | 35,000 |

### Von Leon Boss (8840000–8840002)

**Boss Room**: Map 211070100 (Audience Room)

| ID | Name | Suggested HP | Suggested Level | Notes |
|----|------|-------------|-----------------|-------|
| 8840000 | Von Leon | 500,000,000 | 160 | Main boss — 3 forms? |
| 8840001 | Demon Gargoyle | 20,000,000 | 145 | Mini-boss summon |
| 8840002 | Red Crocky | 5,000,000 | 135 | Regular summon |

*Note: In official GMS, Von Leon was a multi-phase fight. For pre-BB simplicity, implement as a single powerful boss with heavy summons. Tune HP for 1-6 players (~50M per player max effort).*

### Von Leon Equipment

All item IDs confirmed in wz.zip. Equipment XML files need to be extracted from repack Character.wz using HaRepacker.

**Priority set pieces to implement first (helmet + body + weapon):**

| Priority | Item ID | Name | Class |
|----------|---------|------|-------|
| 1 | 1003172 | Lionheart Battle Helm | Warrior |
| 1 | 1052314 | Lionheart Battle Mail | Warrior |
| 1 | 1003173 | Dragon Tail Mage Sallet | Mage |
| 1 | 1052315 | Dragon Tail Mage Robe | Mage |
| 1 | 1003174 | Falcon Wing Sentinel Cap | Archer |
| 1 | 1003175 | Raven Horn Chaser Hat | Thief |
| 1 | 1003176 | Shark Tooth Skipper Hat | Pirate |
| 2 | 1132094–1132109 | Von Leon Belts | All classes |
| 2 | 1003154–1003158 | Von Leon Helmets (Marx/Alma/Fox/Nox/Cora) | All |
| 3 | Full weapon list | Lionheart/DragonTail/etc. weapons | All |

**Target stats for Von Leon gear (pre-BB tuned, level 125 req):**
- Should be a clear upgrade from Timeless/Reverse gear (level 120)
- Should NOT have Potential system stats
- Focus on ATK/MATK, clean stat boosts (STR/DEX/INT/LUK)

### NPCs Needed

- 1 NPC at Leafre/Henesys to explain LHC and provide access
- 1 NPC inside LHC for teleportation between floors
- Von Leon expedition NPC (or use existing expedition system)

**SQL for Von Leon drops**:
```sql
-- Von Leon (8840000) drop table
INSERT INTO drop_data (dropperid, itemid, minimum_quantity, maximum_quantity, questid, chance, server_announcement)
VALUES
  (8840000, 1003172, 1, 1, 0, 30000, 0),  -- Lionheart Battle Helm (30%)
  (8840000, 1003173, 1, 1, 0, 30000, 0),  -- Dragon Tail Mage Sallet
  (8840000, 1003174, 1, 1, 0, 30000, 0),  -- Falcon Wing Cap
  (8840000, 1003175, 1, 1, 0, 30000, 0),  -- Raven Horn Hat
  (8840000, 1003176, 1, 1, 0, 30000, 0),  -- Shark Tooth Hat
  (8840000, 1052314, 1, 1, 0, 25000, 0),  -- Lionheart Mail
  -- ... add all set pieces
  (8840000, 4031800, 1, 5, 0, 500000, 0); -- Mesos/crystals
```

---

## Milestone 3: Future Ereve + Empress Cygnus (v99 era) — Lv 140

### Maps Needed (from repack — 42 maps in 271M range)

**Access chain**: Existing world map → NPC in Ereve or Henesys → Gate to the Future (271000000)

| Key Map ID | Name | Notes |
|------------|------|-------|
| 271000000 | Gate to the Future | Hub/entrance |
| 271010000 | Henesys Ruins | Grinding area 1 |
| 271010100–271010500 | Henesys Ruins Market, Park, Hill | Grinding areas |
| 271020000–271020100 | Dark Spore Hill, Creepy Humming Forest | Mid-level grind |
| 271030100–271030540 | Knight District 1–4, Knights' Chambers 1–5 | High-level grind |
| 271030600 | Hall of Honor | Pre-boss area |
| 271040100 | **Cygnus's Chamber** | **EMPRESS BOSS ROOM** |

### Regular Mobs (grinding mobs in Future Ereve area)

| Range | Names | Suggested Level | HP | EXP |
|-------|-------|-----------------|-----|-----|
| 8644000–8644009 | Water/Sun/Earth/Snow Cloud/Thunder Cloud Spirit etc. | 150 | 1,500,000 | 45,000 |
| 8644100+ | Higher variants of spirits | 155 | 2,000,000 | 60,000 |
| 8645003–8645008 | Corrupted Warriors, Black Knights, Mad Mages etc. | 158 | 2,500,000 | 75,000 |

### Empress Cygnus Boss Fight (8850000–8850011)

**Phase 1**: Fight each Cygnus Knight commander (8850000–8850004)
- Mihile, Oz, Irena, Eckhart, Hawkeye (one at a time or in sequence)
- Each commander spawns in sequence

**Phase 2**: Fight the powered-up commanders (8850005–8850009)

**Phase 3**: Shinsoo (8850010) + Empress Cygnus (8850011)

**Suggested Empress Cygnus stats (tuned for pre-BB, 1-6 players):**

| Boss Part | HP | Level | PADamage | Notes |
|-----------|-----|-------|----------|-------|
| Mihile (Phase 1) | 100,000,000 | 160 | 1,200 | Tank-heavy |
| Oz/Irena/Eckhart/Hawkeye (Phase 1) | 80,000,000 | 160 | 1,300 | Various attack types |
| Phase 2 commanders | 150,000,000 | 165 | 1,500 | Harder versions |
| Shinsoo | 50,000,000 | 155 | 800 | Support heals Empress? |
| Empress Cygnus | 1,500,000,000 | 170 | 1,800 | Final form |

### Empress Equipment

| Priority | Item ID | Name | Class |
|----------|---------|------|-------|
| 1 | 1003159 | Empress's Fine Hat | All |
| 1 | 1003160 | Empress's Brilliant Hat | All |
| 1 | 1082290 | Empress's Fine Gloves | All |
| 1 | 1082291 | Empress's Brilliant Gloves | All |
| 2 | Full set | Additional Empress armor pieces | Confirmed in wz.zip |

*Note: Empress gear IDs for body/boots/cape need to be extracted from the repack Character.wz using HaRepacker to confirm exact IDs.*

### Quest Chain: Gate to the Future Access

**Minimum requirement (simple approach)**:
- Level 140+ (enforced by NPC or map entry restriction)
- Requires completing a simple "unlock" quest
- No complex pre-quest chain needed (we want small-group friendly access)

---

## Implementation Order

```
Phase 1 (Next 2 weeks):
1. Extract LHC + Future Ereve map XMLs from repack using HaRepacker
2. Add to server/wz/Map.wz/
3. Add mob XMLs for LHC mobs (8210xxx, 8610xxx, 8620xxx) with tuned stats
4. Add Chaos Zakum mob XMLs (8800100–8800116) with tuned stats
5. Update String.wz with mob names from wz.zip
6. Create basic portal/NPC access to LHC and GttF

Phase 2 (Weeks 3-4):
7. Extract Von Leon and Empress equipment XMLs from repack
8. Add to server/wz/Character.wz/
9. Update String.wz Eqp.img.xml from wz.zip (it's already 4x more comprehensive)
10. Add Von Leon boss fight (8840000) + expedition/access system
11. Set up drop tables in MySQL

Phase 3 (Month 2):
12. Add Empress Cygnus boss fight (8850000–8850011)
13. Tune all stats based on playtesting
14. Add quest chains for access
```

---

## Database (SQL) Changes Required

All of these need to be run on MySQL at 192.168.0.21:

```sql
-- 1. Add new expedition types for Chaos Zakum and Von Leon
-- (May need to add to server constants/expedition definitions too)

-- 2. Drop tables for all new bosses
-- Template:
-- INSERT INTO drop_data (dropperid, itemid, minimum_quantity, maximum_quantity, questid, chance, server_announcement)
-- VALUES ([mob_id], [item_id], 1, 1, 0, [chance_out_of_1000000], 0);

-- 3. Monster book entries (if monster book is used)
-- INSERT INTO monster_book_data ...

-- Will document exact SQL once mob IDs and item IDs are finalized
```
