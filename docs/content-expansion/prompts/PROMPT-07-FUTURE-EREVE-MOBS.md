# PROMPT-07: Future Ereve Mob Extraction

## What

Extract all Future Ereve area mobs from the community repack and create server-ready XML files with stats tuned for TwinleafStory's Lv 130-140 progression. This prompt depends on PROMPT-06 output — check its SUMMARY.md for the complete mob ID list.

## Where

### Input
- **PROMPT-06 output**: `C:\Shared\output\fe-maps\SUMMARY.md` — read this FIRST for the mob ID list
- **Community Repack Mob.wz**: `C:\Users\carbyne\Documents\CommunityRepack\Mob.wz\`
  - Expected ranges: 8641xxx, 8642xxx, 8644xxx, 8645xxx, possibly 8600xxx
- **HaRepacker**: `C:\Users\carbyne\Documents\HaRepacker\`

### Output
- `C:\Shared\output\fe-mobs\` — mob XML files (one per mob)
- `C:\Shared\output\fe-mobs\SUMMARY.md` — complete mob stat table

## Design Context

Future Ereve is a Lv 130-140 area. The narrative is a dark vision of the future — Ereve has fallen, the Empress is corrupted. Mobs are spirits, corrupted warriors, and fallen knights. Three progression tiers leading to the Empress boss room.

### Stat Targets (from balance-design.md / TWINLEAF-DESIGN-DOC.md)

**Tier 1 — Entry (Gate + Mutant Forests + Henesys Ruins, Lv 130-134)**

| Stat | Value |
|------|-------|
| Level | 148-152 |
| maxHP | 1,200,000-1,700,000 |
| maxMP | 1,000-2,000 |
| PADamage | 800-950 |
| MADamage | 750-900 |
| PDDamage | 1,100-1,300 |
| MDDamage | 1,000-1,200 |
| exp | 40,000-50,000 |

**Tier 2 — Mid (Dark Forest + Knight District, Lv 134-137)**

| Stat | Value |
|------|-------|
| Level | 153-157 |
| maxHP | 1,800,000-2,200,000 |
| maxMP | 1,500-2,500 |
| PADamage | 950-1,100 |
| MADamage | 900-1,050 |
| PDDamage | 1,300-1,500 |
| MDDamage | 1,200-1,400 |
| exp | 55,000-65,000 |

**Tier 3 — Hard (Knights' Chambers + Hall of Honor, Lv 137-140)**

| Stat | Value |
|------|-------|
| Level | 158-162 |
| maxHP | 2,300,000-2,800,000 |
| maxMP | 2,000-3,000 |
| PADamage | 1,100-1,300 |
| MADamage | 1,000-1,200 |
| PDDamage | 1,500-1,800 |
| MDDamage | 1,400-1,600 |
| exp | 70,000-85,000 |

### Mob Range → Tier Mapping (Use PROMPT-06 SUMMARY for exact assignments)

| Mob Range | Likely Identity | Suggested Tier |
|-----------|----------------|----------------|
| 8600000-8600006 | Mutant basic mobs (Gate entry) | Tier 1 (weakest) |
| 8641000-8641031 | Erda spirits | Tier 1 |
| 8642000-8642024 | Nature mobs (pinedeer, etc.) | Tier 1-2 |
| 8644000-8644009 | Elemental spirits (water, sun, earth) | Tier 2 |
| 8644100+ | Higher spirit variants | Tier 2-3 |
| 8645003-8645008 | Corrupted Warriors, Black Knights, Mad Mages | Tier 3 |
| 8645000-8645002 | Support Troops | Tier 2 |
| 8645009 | Guard Captain Darknell | Mini-boss (see below) |
| 8645051+ | Cygnus Soldiers | Tier 3 |

### Mini-Boss: Guard Captain Darknell (8645009)

Darknell guards the Hall of Honor before the Empress chamber. He should feel like a mini-boss gate check.

| Stat | Value |
|------|-------|
| Level | 160 |
| maxHP | 50,000,000 |
| PADamage | 1,400 |
| PDDamage | 1,600 |
| MDDamage | 1,500 |
| exp | 2,000,000 |
| boss | 1 |

## Steps

1. **Read PROMPT-06 SUMMARY.md** for the complete mob ID list
2. **Open Mob.wz** in HaRepacker with "GMS (old)" encryption
3. **Export** each required mob as XML
4. **Assign tiers** based on which maps they spawn in
5. **Modify stats** in each mob's `info` section per tier targets
6. **Special handling** for Darknell (8645009) — set boss=1 flag
7. **Preserve** all animation/sprite data
8. **Save** each as `[MOBID].img.xml`
9. **Generate SUMMARY.md** with all mobs, tiers, and final stats

## Important Note on Mob Count

Future Ereve has the LARGEST mob count of any new area — potentially 300+ mob files across the 864xxxx ranges. Many of these may be visual variants or unused entries. Focus on:

1. Mobs actually referenced in the PROMPT-06 map data (MUST have)
2. Named mobs with clear roles (prioritize)
3. Skip mob IDs that aren't referenced by any map

If the total is overwhelming (100+), extract in batches and note which are done in the SUMMARY.

## Verification

1. All mob IDs from PROMPT-06 SUMMARY have corresponding XML files
2. Tier progression makes sense (Tier 1 < Tier 2 < Tier 3 in all stats)
3. Darknell (8645009) has boss=1 and 50M HP
4. EXP values match the design targets (40K-50K → 55K-65K → 70K-85K)
5. No animation data was lost

## Deployment (Done from MacBook)

```bash
scp ~/Shared-Win/output/fe-mobs/*.xml \
  homelab@192.168.0.25:/home/homelab/Cosmic/wz/Mob.wz/
```

Deploy AFTER PROMPT-06 maps. Restart server once both are in place.
