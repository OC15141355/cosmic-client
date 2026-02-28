# PROMPT-04: Lion Heart Castle Mob Extraction

## What

Extract all LHC grinding mobs from the community repack and create server-ready XML files with stats tuned for TwinleafStory's Lv 120-130 progression. This prompt depends on PROMPT-03 output — check the SUMMARY.md from PROMPT-03 to confirm which mob IDs the maps actually reference.

## Where

### Input
- **PROMPT-03 output**: `C:\Shared\output\lhc-maps\SUMMARY.md` — read this FIRST to get the mob ID list
- **Community Repack Mob.wz**: `C:\Users\carbyne\Documents\CommunityRepack\Mob.wz\`
  - Look for files matching the mob IDs from the SUMMARY
  - Expected ranges: 8210000-8210013, 8610000-8610033, 8620000-8620027
- **HaRepacker**: `C:\Users\carbyne\Documents\HaRepacker\`

### Output
- `C:\Shared\output\lhc-mobs\` — mob XML files (one per mob)
- `C:\Shared\output\lhc-mobs\SUMMARY.md` — complete mob stat table

## Design Context

LHC is a Lv 120-130 grinding area. Mobs should feel challenging but farmable for a solo player at-level, and very smooth for a duo/trio. Three tiers of difficulty progressing deeper into the castle.

### Stat Targets (from balance-design.md / CONTENT-PORT-PLAN.md)

**Tier 1 — Entry (Outer walls, first tower areas)**
- Maps: 211060000-211060300
- Target player level: 120-122
- Mob stats:

| Stat | Value |
|------|-------|
| Level | 128-132 |
| maxHP | 400,000-600,000 |
| maxMP | 500-1,000 |
| PADamage | 500-650 |
| MADamage | 450-600 |
| PDDamage | 800-1,000 |
| MDDamage | 700-900 |
| exp | 12,000-18,000 |

**Tier 2 — Mid (Inner towers, castle walls)**
- Maps: 211060400-211060700
- Target player level: 122-126
- Mob stats:

| Stat | Value |
|------|-------|
| Level | 135-142 |
| maxHP | 650,000-900,000 |
| maxMP | 800-1,500 |
| PADamage | 650-800 |
| MADamage | 600-750 |
| PDDamage | 1,000-1,200 |
| MDDamage | 900-1,100 |
| exp | 18,000-25,000 |

**Tier 3 — Hard (Upper towers, boss approach)**
- Maps: 211060800-211061100, 211070000
- Target player level: 126-130
- Mob stats:

| Stat | Value |
|------|-------|
| Level | 145-152 |
| maxHP | 1,000,000-1,400,000 |
| maxMP | 1,000-2,000 |
| PADamage | 800-1,000 |
| MADamage | 750-900 |
| PDDamage | 1,200-1,500 |
| MDDamage | 1,100-1,300 |
| exp | 28,000-38,000 |

### Which Mob Gets Which Tier

Assign tiers based on mob identity (use your judgment + the map placement from PROMPT-03):

| Mob Range | Example Names | Suggested Tier |
|-----------|---------------|----------------|
| 8620000-8620009 | Swollen Stumps, Pillaging Boars, Sinister Masks, Ancient Golem | Tier 1-2 (outer mobs) |
| 8210000-8210007 | Crocky, Reindeer, Bearwolf, Castle Golem, Prison Guards | Tier 2 (castle interior) |
| 8610000-8610004 | Dawn, Blaze, Wind, Night, Thunder (CK enemies) | Tier 3 (elite mobs) |
| 8610005-8610033 | Official Knights A-G | Tier 2-3 (castle guards) |
| 8210010-8210013 | Tower Ani variants, Prison Guard Ani | Tier 2-3 (tower enemies) |

## Steps

1. **Read PROMPT-03 SUMMARY.md** to get the complete list of mob IDs referenced in LHC maps
2. **Open Mob.wz** in HaRepacker with "GMS (old)" encryption
3. **Export** each required mob as XML
4. **Assign each mob a tier** based on which maps it spawns in (from PROMPT-03 data)
5. **Modify stats** in each mob's `info` section per the tier targets above
6. **Preserve** everything else — animation data, skills, AI behavior, sprite references
7. **Save** each as `[MOBID].img.xml`
8. **Generate SUMMARY.md** with a table of ALL mobs, their tier, and final stats

## Stat Modification Reference

Modify these fields in `<imgdir name="info">`:
```xml
<int name="level" value="135"/>
<int name="maxHP" value="800000"/>
<int name="maxMP" value="1000"/>
<int name="PADamage" value="700"/>
<int name="MADamage" value="650"/>
<int name="PDDamage" value="1100"/>
<int name="MDDamage" value="1000"/>
<int name="exp" value="22000"/>
```

Do NOT add `boss` or `noregen` flags to regular mobs.

## Verification

1. All mob IDs from PROMPT-03 SUMMARY have a corresponding XML file
2. Each file has valid XML with `info` section containing all stat fields
3. Tier 1 mobs have HP in 400K-600K range
4. Tier 2 mobs have HP in 650K-900K range
5. Tier 3 mobs have HP in 1M-1.4M range
6. EXP values follow the tier progression (12K-18K → 18K-25K → 28K-38K)
7. No animation or sprite data was lost

## Deployment (Done from MacBook)

```bash
scp ~/Shared-Win/output/lhc-mobs/*.xml \
  homelab@192.168.0.25:/home/homelab/Cosmic/wz/Mob.wz/
```

Deploy AFTER PROMPT-03 maps are deployed. Restart server once both are in place.

## Test

```
!warp 211060000       (Desolate Moor)
Wait for mob spawns — should see outer area mobs
Attack one — check if HP/EXP feels right for Lv 120 character
!warp 211060600       (Third Tower — mid tier)
Check mob levels are higher
!warp 211070000       (Audience Room Corridor — high tier)
Check mobs are Tier 3 difficulty
```
