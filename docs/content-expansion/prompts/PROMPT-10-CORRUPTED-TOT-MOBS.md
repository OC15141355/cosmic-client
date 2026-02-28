# PROMPT-10: Corrupted Temple of Time Mob Extraction

## What

Extract 6 corrupted Temple of Time mob variants from the community repack and create server-ready XML files. These are higher-level versions of existing ToT mobs that add variety to the Lv 110-120 Temple of Time experience.

This is a low-effort, high-value extraction — just 6 mob files with stat adjustments.

## Where

### Input
- **Community Repack Mob.wz**: `C:\Users\carbyne\Documents\CommunityRepack\Mob.wz\`
  - Files: `8220016.img` through `8220021.img`
- **HaRepacker**: `C:\Users\carbyne\Documents\HaRepacker\`

### Output
- `C:\Shared\output\corrupted-tot\` — 6 mob XML files
- `C:\Shared\output\corrupted-tot\SUMMARY.md` — stat overview

## Target Mobs

| Mob ID | Name | Description |
|--------|------|-------------|
| 8220016 | Corrupted Wyvern | Corrupted version of Temple wyvern |
| 8220017 | Corrupted Cornian | Corrupted version of Temple cornian |
| 8220018 | Corrupted Skelegon | Corrupted version of skeletal dragon |
| 8220019 | Corrupted Kentaurus | Corrupted centaur variant |
| 8220020 | Corrupted Chief Memory Guardian | Corrupted mini-boss |
| 8220021 | Corrupted Time Monk Trainee | Corrupted monk variant |

## Design Context

These mobs bridge the Lv 100-120 gap in Temple of Time. They spawn in the deeper ToT maps alongside the regular mobs, providing a challenge for higher-level players who are past the normal ToT content but not yet ready for Chaos Zakum.

### Stat Targets

| Mob ID | Name | Level | maxHP | PADamage | MADamage | PDDamage | MDDamage | exp |
|--------|------|-------|-------|----------|----------|----------|----------|-----|
| 8220016 | Corrupted Wyvern | 125 | 350,000 | 700 | 650 | 1,000 | 900 | 10,000 |
| 8220017 | Corrupted Cornian | 128 | 400,000 | 750 | 700 | 1,050 | 950 | 11,500 |
| 8220018 | Corrupted Skelegon | 130 | 500,000 | 800 | 750 | 1,100 | 1,000 | 13,000 |
| 8220019 | Corrupted Kentaurus | 132 | 550,000 | 850 | 800 | 1,150 | 1,050 | 14,500 |
| 8220020 | Corrupted Chief Memory Guardian | 135 | 5,000,000 | 1,000 | 950 | 1,300 | 1,200 | 500,000 |
| 8220021 | Corrupted Time Monk Trainee | 122 | 250,000 | 600 | 550 | 900 | 800 | 8,000 |

**Note**: 8220020 (Corrupted Chief Memory Guardian) is a mini-boss — significantly higher HP and EXP, but NOT a full boss fight. Do NOT set `boss=1` flag.

## Steps

1. **Open Mob.wz** in HaRepacker with "GMS (old)" encryption
2. **Navigate** to each mob ID (8220016 through 8220021)
3. **Export** each as XML via Private Server export
4. **Modify stats** in each mob's `info` section per the table above
5. **Preserve** all animation data, skills, AI behavior
6. **Save** each as `[MOBID].img.xml`
7. **Generate SUMMARY.md** with all 6 mobs and their final stats

### Key XML Fields to Modify

```xml
<imgdir name="info">
  <int name="level" value="125"/>
  <int name="maxHP" value="350000"/>
  <int name="maxMP" value="1000"/>
  <int name="PADamage" value="700"/>
  <int name="MADamage" value="650"/>
  <int name="PDDamage" value="1000"/>
  <int name="MDDamage" value="900"/>
  <int name="exp" value="10000"/>
</imgdir>
```

## Verification

1. Exactly 6 files in the output directory
2. Each file has valid XML with the stat modifications applied
3. Stats follow the progression: Time Monk Trainee (lowest) → Corrupted Chief (highest)
4. Corrupted Chief (8220020) has 5M HP but NO boss flag
5. No animation or sprite data was lost — only `info` stats changed
6. Level range spans 122-135

## Deployment (Done from MacBook)

```bash
scp ~/Shared-Win/output/corrupted-tot/*.xml \
  homelab@192.168.0.25:/home/homelab/Cosmic/wz/Mob.wz/
ssh homelab@192.168.0.25 "cd /home/homelab/Cosmic && docker compose restart cosmic-server-1"
```

## Test

```
!warp 270030100       (Temple of Time — Road of Regrets or similar deep map)
!spawn 8220016        (Corrupted Wyvern — should appear)
!spawn 8220018        (Corrupted Skelegon — should appear)
!spawn 8220020        (Corrupted Chief — should appear, higher HP)
Attack them — verify HP and damage feel right for Lv 110-120 players
!killall
```

## Future Work

After these mobs are deployed and verified, a separate server-side task adds them to ToT map spawn tables:
- Edit the relevant Temple of Time map XMLs in `server/wz/Map.wz/`
- Add these mob IDs to the `life` sections of deeper ToT maps
- OR add entries to the `plife` database table (if Cosmic supports it)
- This is documented in SERVER-TASKS.md, NOT handled by this prompt
