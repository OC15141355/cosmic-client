# PROMPT-02: Chaos Zakum Mob Extraction

## What

Extract the 17 Chaos Zakum mob data files (8800100-8800116) from the community repack and create server-ready XML files with stats adjusted for TwinleafStory's pre-BB small-group balance.

Chaos Zakum is a Lv 120 boss fight for 4-6 players. It uses the same map as regular Zakum (211042300).

## Where

### Input
- **Community Repack Mob.wz**: `C:\Users\carbyne\Documents\CommunityRepack\Mob.wz\`
  - Look for files: `8800100.img`, `8800101.img`, ..., `8800116.img`
  - These are binary .img files — use HaRepacker to open and export as XML
- **HaRepacker**: `C:\Users\carbyne\Documents\HaRepacker\`
  - Open with **"GMS (old)"** encryption
  - File → Private Server... → Export as XML

### Output
- `C:\Shared\output\chaos-zakum\mob-xml\` — 17 XML files, one per mob
- `C:\Shared\output\chaos-zakum\SUMMARY.md` — stat overview

## Design Targets (from balance-design.md)

Chaos Zakum is ~3x regular Zakum but NOT a wall. Target: 4-6 players, 15-20 min fight.

**Overall target HP**: 200,000,000 total across all bodies (from balance-design.md)

### Stat Adjustments

For each mob file, find and modify the `<imgdir name="info">` section:

| Mob ID | Name | Level | maxHP | PADamage | PDDamage | MDDamage | EXP |
|--------|------|-------|-------|----------|----------|----------|-----|
| 8800100 | Chaos Zakum Body 1 | 150 | 60,000,000 | 1,200 | 1,300 | 1,100 | 0 |
| 8800101 | Chaos Zakum Body 2 | 155 | 80,000,000 | 1,400 | 1,500 | 1,200 | 7,000,000 |
| 8800102 | Chaos Zakum Body 3 | 150 | 60,000,000 | 1,300 | 1,400 | 1,100 | 0 |
| 8800103-8800110 | Chaos Zakum Arms 1-8 | 145 | 12,000,000 | 800 | 900 | 900 | 500,000 |
| 8800111 | Chaos Boogie | 140 | 5,000,000 | 600 | 700 | 700 | 200,000 |
| 8800112 | Chaos Puko | 140 | 5,000,000 | 600 | 700 | 700 | 200,000 |
| 8800113 | Chaos Poonko | 140 | 5,000,000 | 600 | 700 | 700 | 200,000 |
| 8800114 | Chaos Kusko | 140 | 5,000,000 | 600 | 700 | 700 | 200,000 |
| 8800115-8800116 | Additional summons | 140 | 3,000,000 | 500 | 600 | 600 | 100,000 |

**Key XML fields to modify** in each mob's `info` section:
```xml
<int name="level" value="150"/>
<int name="maxHP" value="80000000"/>
<int name="maxMP" value="3000000"/>
<int name="PADamage" value="1400"/>
<int name="PDDamage" value="1500"/>
<int name="MADamage" value="1200"/>
<int name="MDDamage" value="1200"/>
<int name="exp" value="7000000"/>
```

Also ensure these flags are present on boss bodies (8800100-8800102):
```xml
<int name="boss" value="1"/>
<int name="noregen" value="1"/>
```

## Steps

1. **Open Mob.wz** in HaRepacker with "GMS (old)" encryption
2. **Navigate** to each mob ID (8800100 through 8800116)
3. **Export** each as XML via Private Server export
4. **Read** each exported XML file
5. **Modify** the stat values in the `info` section per the table above
6. **Preserve** everything else — animation data, skill data, AI behavior, sprite references
7. **Save** each modified file as `[MOBID].img.xml` in the output directory
8. **Generate SUMMARY.md** listing all 17 mobs with their final stats

## If HaRepacker Export Isn't Available

If the repack has already been exported to XML (check `C:\Users\carbyne\Documents\CommunityRepack\` for XML files), read those directly and modify stats.

If the mob files are already individual `.img.xml` files in the repack directory structure, copy and modify them directly.

## Verification

1. Count: exactly 17 files in output directory
2. Each file has a valid XML structure with `<imgdir name="info">` containing the stat fields
3. Body 2 (8800101) has `maxHP="80000000"` and `boss="1"` and `noregen="1"`
4. Arms (8800103-8800110) each have `maxHP="12000000"`
5. Summons (8800111-8800116) have lower HP (3-5M range)
6. No animation or sprite data was lost — only `info` section stats were changed

## Deployment (Done from MacBook)

```bash
scp ~/Shared-Win/output/chaos-zakum/mob-xml/*.xml \
  homelab@192.168.0.25:/home/homelab/Cosmic/wz/Mob.wz/
ssh homelab@192.168.0.25 "cd /home/homelab/Cosmic && docker compose restart cosmic-server-1"
```

## Test

```
!warp 211042300       (Zakum altar)
!spawn 8800100        (Body 1 — should appear)
!spawn 8800101        (Body 2 — main reward body)
!spawn 8800103        (Arm 1 — should appear)
Attack them — damage should register, HP should match targets
!killall              (clean up)
```
