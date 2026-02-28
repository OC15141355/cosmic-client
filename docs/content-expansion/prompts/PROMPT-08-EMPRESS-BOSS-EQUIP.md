# PROMPT-08: Empress Cygnus Boss + Equipment Extraction

## What

Extract the Empress Cygnus boss fight mobs (8850000-8850011) and Empress equipment set from the community repack. Create server-ready mob XMLs with tuned stats, equipment XMLs, and a drop table SQL file.

The Empress fight is a multi-phase Lv 140 encounter for 4-6 players — the climax of TwinleafStory's Corruption arc. Five CK commanders in two phases, then Shinsoo + Empress Cygnus herself.

## Where

### Input
- **Community Repack Mob.wz**: `C:\Users\carbyne\Documents\CommunityRepack\Mob.wz\`
  - Files: `8850000.img` through `8850011.img` (12 mobs)
- **Community Repack Character.wz**: `C:\Users\carbyne\Documents\CommunityRepack\Character.wz\`
  - Empress equipment files (see ID list below)
- **wz.zip String data**: `D:\wz.zip` → `wz/String.wz/Eqp.img.xml`
- **HaRepacker**: `C:\Users\carbyne\Documents\HaRepacker\`

### Output
- `C:\Shared\output\empress\mob-xml\` — 12 boss mob XML files
- `C:\Shared\output\empress\equip-xml\` — equipment XML files
- `C:\Shared\output\empress\drop-table.sql` — SQL INSERT statements
- `C:\Shared\output\empress\SUMMARY.md` — overview

## Boss Design — Multi-Phase Fight

### Phase 1: CK Commanders (8850000-8850004)

Each commander fights individually (spawns one at a time in sequence).

| Mob ID | Name | Level | maxHP | PADamage | PDDamage | MDDamage | EXP |
|--------|------|-------|-------|----------|----------|----------|-----|
| 8850000 | Mihile | 160 | 100,000,000 | 1,200 | 1,400 | 1,200 | 3,000,000 |
| 8850001 | Oz | 160 | 80,000,000 | 900 | 1,100 | 1,500 | 2,500,000 |
| 8850002 | Irena | 160 | 80,000,000 | 1,300 | 1,200 | 1,100 | 2,500,000 |
| 8850003 | Eckhart | 160 | 80,000,000 | 1,350 | 1,300 | 1,200 | 2,500,000 |
| 8850004 | Hawkeye | 160 | 80,000,000 | 1,250 | 1,200 | 1,100 | 2,500,000 |

All Phase 1 commanders: `boss=1`

### Phase 2: Powered-Up Commanders (8850005-8850009)

Harder versions that appear after Phase 1 is cleared. May fight in groups of 2-3.

| Mob ID | Name | Level | maxHP | PADamage | PDDamage | MDDamage | EXP |
|--------|------|-------|-------|----------|----------|----------|-----|
| 8850005 | Mihile (P2) | 165 | 150,000,000 | 1,500 | 1,600 | 1,400 | 4,000,000 |
| 8850006 | Oz (P2) | 165 | 120,000,000 | 1,100 | 1,300 | 1,800 | 3,500,000 |
| 8850007 | Irena (P2) | 165 | 120,000,000 | 1,550 | 1,400 | 1,300 | 3,500,000 |
| 8850008 | Eckhart (P2) | 165 | 120,000,000 | 1,600 | 1,500 | 1,400 | 3,500,000 |
| 8850009 | Hawkeye (P2) | 165 | 120,000,000 | 1,450 | 1,400 | 1,300 | 3,500,000 |

All Phase 2 commanders: `boss=1`

### Phase 3: Shinsoo + Empress Cygnus (8850010-8850011)

| Mob ID | Name | Level | maxHP | PADamage | PDDamage | MDDamage | EXP | Flags |
|--------|------|-------|-------|----------|----------|----------|-----|-------|
| 8850010 | Shinsoo | 155 | 50,000,000 | 800 | 1,200 | 1,200 | 2,000,000 | boss=1 |
| 8850011 | Cygnus | 170 | 1,500,000,000 | 1,800 | 1,800 | 1,700 | 50,000,000 | boss=1, noregen=1 |

**Total fight HP**: ~2.67 billion across all phases. Target fight time: 20-30 minutes for 4-6 well-geared players.

## Equipment: Empress Set

### Equipment IDs (confirmed in wz.zip String data)

**SAME CONSTRAINT AS VON LEON**: Character.wz models may be missing. Use reskin strategy if needed.

| Item ID | Name | Slot |
|---------|------|------|
| 1003159 | Empress's Fine Hat | Cap |
| 1003160 | Empress's Brilliant Hat | Cap |
| 1082290 | Empress's Fine Gloves | Glove |
| 1082291 | Empress's Brilliant Gloves | Glove |

Additional Empress set pieces (check wz.zip Eqp.img.xml for IDs in the same naming pattern):
- Empress body armor, boots, cape, shoulder — search wz.zip for items with "Empress" in the name
- Record ALL Empress equipment IDs found

### Equipment Stat Targets (Lv 140, pre-BB tuned)

**"Fine" tier** (more common drops):
- reqLevel=140, primary stat=+18, ATK/MATK=+7, PDD=+140, MDD=+100, tuc=7

**"Brilliant" tier** (rare drops):
- reqLevel=140, primary stat=+25, ATK/MATK=+12, PDD=+180, MDD=+130, tuc=10

### Set Bonuses (implemented server-side)
- 4 piece: +25 all stats, +500 HP/MP, +10 ATK/MATK
- 7 piece: +50 all stats, +1000 HP/MP, +20 ATK/MATK, +10% boss damage

## Steps

### Part A: Boss Mobs (12 files)

1. Open Mob.wz in HaRepacker
2. Export 8850000 through 8850011 as XML
3. Modify stats per the phase tables above
4. Set boss=1 on all, noregen=1 on Cygnus (8850011)
5. Save to output directory

### Part B: Equipment

1. Search wz.zip Eqp.img.xml for ALL items with "Empress" in the name — record every ID
2. For each ID, check Character.wz for the visual model
3. If found: export and modify stats
4. If NOT found: create minimal equipment XML with stats only
5. Apply the Fine/Brilliant stat targets

### Part C: Drop Table SQL

```sql
-- Empress Cygnus (8850011) drops
INSERT INTO drop_data (dropperid, itemid, minimum_quantity, maximum_quantity, questid, chance)
VALUES
  -- Fine equipment (higher chance)
  (8850011, 1003159, 1, 1, 0, 120000),  -- Fine Hat (12%)
  (8850011, 1082290, 1, 1, 0, 120000),  -- Fine Gloves (12%)
  -- Brilliant equipment (rare)
  (8850011, 1003160, 1, 1, 0, 30000),   -- Brilliant Hat (3%)
  (8850011, 1082291, 1, 1, 0, 30000),   -- Brilliant Gloves (3%)
  -- Soul Shards (token currency, guaranteed 3-5)
  -- NOTE: Soul Shard item ID TBD — use placeholder ETC item
  -- (8850011, SOUL_SHARD_ID, 3, 5, 0, 1000000),
  -- Rien Keystone (guaranteed drop, quest item for 4.5 job access)
  -- NOTE: Rien Keystone item ID TBD
  -- (8850011, RIEN_KEYSTONE_ID, 1, 1, 0, 1000000),
  -- Meso crystals
  (8850011, 4031138, 5, 12, 0, 900000);
```

## Verification

1. Twelve mob XML files (8850000-8850011)
2. Cygnus (8850011) has HP=1,500,000,000, boss=1, noregen=1
3. Phase 1 commanders have 80-100M HP each
4. Phase 2 commanders have 120-150M HP each
5. Equipment files exist for at least hat + gloves (Fine + Brilliant = 4 files minimum)
6. Equipment stats match Lv 140 targets
7. drop-table.sql has valid SQL syntax
8. SUMMARY.md lists all content + notes on missing Character.wz models

## Deployment (Done from MacBook)

```bash
# Boss mobs
scp ~/Shared-Win/output/empress/mob-xml/*.xml \
  homelab@192.168.0.25:/home/homelab/Cosmic/wz/Mob.wz/
# Equipment
# Deploy SQL
scp ~/Shared-Win/output/empress/drop-table.sql homelab@192.168.0.25:/tmp/
ssh homelab@192.168.0.25 "docker exec -i cosmic-db-1 mysql -uroot -proot cosmic < /tmp/drop-table.sql"
```

## Test

```
!warp 271040100       (Cygnus's Chamber)
!spawn 8850000        (Mihile Phase 1 — should appear)
!spawn 8850011        (Cygnus — the Empress herself)
Attack — damage should register, HP should be massive
!killall              (check drops)
!item 1003159         (Empress's Fine Hat — verify equippable)
```
