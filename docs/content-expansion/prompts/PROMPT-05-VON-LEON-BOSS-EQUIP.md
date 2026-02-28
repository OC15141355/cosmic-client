# PROMPT-05: Von Leon Boss + Equipment Extraction

## What

Extract the Von Leon boss mob data (8840000-8840002) and Von Leon equipment set from the community repack. Create server-ready mob XMLs with tuned stats, equipment XMLs, and a drop table SQL file.

Von Leon is a Lv 125 boss for 3-6 players, the endgame of Lion Heart Castle. Drops the Von Leon Set (Lv 125 equipment).

## Where

### Input
- **Community Repack Mob.wz**: `C:\Users\carbyne\Documents\CommunityRepack\Mob.wz\`
  - Files: `8840000.img`, `8840001.img`, `8840002.img`
- **Community Repack Character.wz**: `C:\Users\carbyne\Documents\CommunityRepack\Character.wz\`
  - Von Leon equipment files (see ID list below)
- **wz.zip String data**: `D:\wz.zip` → `wz/String.wz/Eqp.img.xml` (for equipment names/IDs)
- **HaRepacker**: `C:\Users\carbyne\Documents\HaRepacker\`

### Output
- `C:\Shared\output\von-leon\mob-xml\` — 3 boss mob XML files
- `C:\Shared\output\von-leon\equip-xml\` — equipment XML files (organized by slot)
- `C:\Shared\output\von-leon\drop-table.sql` — SQL INSERT statements for drop_data table
- `C:\Shared\output\von-leon\SUMMARY.md` — overview of all extracted content

## Boss Design Targets (from balance-design.md)

| Mob ID | Name | Level | maxHP | PADamage | PDDamage | MDDamage | EXP | Flags |
|--------|------|-------|-------|----------|----------|----------|-----|-------|
| 8840000 | Von Leon | 160 | 500,000,000 | 1,400 | 1,500 | 1,300 | 25,000,000 | boss=1, noregen=1 |
| 8840001 | Demon Gargoyle | 145 | 20,000,000 | 900 | 1,000 | 900 | 1,000,000 | boss=1 |
| 8840002 | Red Crocky | 135 | 5,000,000 | 600 | 700 | 600 | 300,000 | — |

Von Leon should be a challenging 15-20 minute fight for 4 players. Gargoyle is a mini-boss summon. Red Crocky is a regular summon.

## Equipment: Von Leon Set

**IMPORTANT CONSTRAINT**: The Von Leon equipment MODELS (Character.wz visual sprites) may NOT exist in the repack. Session 4 audit found that many post-v83 equipment models are missing. If the Character.wz files for these IDs don't exist, we use the **reskin strategy**: assign stats and names via server-side XML + String.wz, and the client will show a default/fallback visual.

### Equipment IDs (confirmed in wz.zip String data)

**Helmets (Cap/)**:
| Item ID | Name | Class |
|---------|------|-------|
| 1003172 | Lionheart Battle Helm | Warrior |
| 1003173 | Dragon Tail Mage Sallet | Mage |
| 1003174 | Falcon Wing Sentinel Cap | Archer |
| 1003175 | Raven Horn Chaser Hat | Thief |
| 1003176 | Shark Tooth Skipper Hat | Pirate |

**Body Armor (Coat/Longcoat/)**:
| Item ID | Name | Class |
|---------|------|-------|
| 1052314 | Lionheart Battle Mail | Warrior |
| 1052315 | Dragon Tail Mage Robe | Mage |
| 1052316 | Falcon Wing Sentinel Suit | Archer |
| 1052317 | Raven Horn Chaser Armor | Thief |
| 1052318 | Shark Tooth Skipper Coat | Pirate |

**Gloves (Glove/)**:
| Item ID | Name |
|---------|------|
| 1082295 | Lionheart Battle Bracelet |
| 1082296 | Dragon Tail Mage Cuffs |
| 1082297 | Falcon Wing Sentinel Gloves |
| 1082298 | Raven Horn Chaser Gloves |
| 1082299 | Shark Tooth Skipper Gloves |

**Capes (Cape/)**:
| Item ID | Name |
|---------|------|
| 1102275-1102279 | Class-specific Von Leon capes |

**Boots (Shoes/)**:
| Item ID | Name |
|---------|------|
| 1072485 | Lionheart Battle Boots |
| 1072487 | Falcon Wing Sentinel Boots |
| 1072488 | Raven Horn Chaser Boots |
| 1072489 | Shark Tooth Skipper Boots |

### Equipment Stat Targets (Lv 125, pre-BB tuned)

**Helmets**: reqLevel=125, STR/DEX/INT/LUK=+15 (class-appropriate primary), WATK or MATK=+5, PDD=+120, MDD=+80, tuc=7
**Body**: reqLevel=125, STR/DEX/INT/LUK=+20, WATK or MATK=+8, PDD=+150, MDD=+100, tuc=10
**Gloves**: reqLevel=125, primary stat=+12, WATK or MATK=+4, PDD=+60, MDD=+50, tuc=5
**Capes**: reqLevel=125, all stats=+8, PDD=+80, MDD=+60, tuc=5
**Boots**: reqLevel=125, primary stat=+10, speed=+5, jump=+3, PDD=+70, MDD=+55, tuc=5

### Set Bonuses (implemented server-side, not in WZ)
- 3 piece: +15 all stats, +300 HP/MP
- 6 piece: +30 all stats, +500 HP/MP, +10 ATK/MATK

## Steps

### Part A: Boss Mobs

1. Open Mob.wz in HaRepacker
2. Export 8840000, 8840001, 8840002 as XML
3. Modify stats per the boss design table above
4. Ensure boss flags are set
5. Save to output directory

### Part B: Equipment

1. For each equipment ID, check if it exists in Character.wz:
   - Look in the appropriate subdirectory (Cap/, Coat/, Longcoat/, Glove/, Cape/, Shoes/)
   - If found: export as XML, then modify stats
   - If NOT found: create a minimal equipment XML with just the `info` section containing stats
2. For each equipment file, set the stats per the targets above
3. Equipment XML `info` section example:
```xml
<imgdir name="info">
  <int name="reqLevel" value="125"/>
  <int name="reqSTR" value="0"/>
  <int name="reqDEX" value="0"/>
  <int name="reqINT" value="0"/>
  <int name="reqLUK" value="0"/>
  <int name="incSTR" value="15"/>
  <int name="incPAD" value="5"/>
  <int name="incPDD" value="120"/>
  <int name="incMDD" value="80"/>
  <int name="tuc" value="7"/>
  <int name="cash" value="0"/>
</imgdir>
```

### Part C: Drop Table SQL

Create `drop-table.sql`:
```sql
-- Von Leon (8840000) drop table
-- chance is out of 1,000,000 (so 100000 = 10%)
INSERT INTO drop_data (dropperid, itemid, minimum_quantity, maximum_quantity, questid, chance)
VALUES
  -- Helmets (each 8% chance — one of 5 classes)
  (8840000, 1003172, 1, 1, 0, 80000),
  (8840000, 1003173, 1, 1, 0, 80000),
  (8840000, 1003174, 1, 1, 0, 80000),
  (8840000, 1003175, 1, 1, 0, 80000),
  (8840000, 1003176, 1, 1, 0, 80000),
  -- Body armor (each 5% chance)
  (8840000, 1052314, 1, 1, 0, 50000),
  (8840000, 1052315, 1, 1, 0, 50000),
  (8840000, 1052316, 1, 1, 0, 50000),
  (8840000, 1052317, 1, 1, 0, 50000),
  (8840000, 1052318, 1, 1, 0, 50000),
  -- Von Leon Coins (token currency, guaranteed)
  -- NOTE: Von Leon Coin item ID TBD — use a placeholder ETC item
  -- (8840000, VONLEON_COIN_ID, 5, 15, 0, 1000000),
  -- Meso crystals
  (8840000, 4031138, 3, 8, 0, 800000);
```

## Verification

1. Three mob XML files with correct stats
2. 8840000 has HP=500,000,000 and boss=1
3. Equipment files exist for at least helmets + body armor (10 files minimum)
4. Equipment stats match targets (reqLevel=125, appropriate stat bonuses)
5. drop-table.sql has valid SQL syntax
6. SUMMARY.md lists everything that was and wasn't found

## Deployment (Done from MacBook)

```bash
# Boss mobs
scp ~/Shared-Win/output/von-leon/mob-xml/*.xml \
  homelab@192.168.0.25:/home/homelab/Cosmic/wz/Mob.wz/
# Equipment (sort into correct subdirs on server)
# Deploy SQL
scp ~/Shared-Win/output/von-leon/drop-table.sql homelab@192.168.0.25:/tmp/
ssh homelab@192.168.0.25 "docker exec -i cosmic-db-1 mysql -uroot -proot cosmic < /tmp/drop-table.sql"
```
