# PROMPT-06: Future Ereve Map Extraction

## What

Extract all 42 Future Ereve / Gate to the Future maps from the community repack and create server-ready XML files. This area spans Lv 130-140 content, from the time-distorted Henesys Ruins through the Knight District up to Empress Cygnus's Chamber.

## Where

### Input
- **Community Repack Map.wz**: `C:\Users\carbyne\Documents\CommunityRepack\Map.wz\`
  - Maps are in the `Map/Map2/` subdirectory (271xxxxxx range = Map2)
  - Look for: `271000000.img` through `271040300.img`
- **HaRepacker**: `C:\Users\carbyne\Documents\HaRepacker\`
  - Open with **"GMS (old)"** encryption

### Output
- `C:\Shared\output\fe-maps\` — 42 XML files, one per map
- `C:\Shared\output\fe-maps\SUMMARY.md` — map list with portal connections and mob IDs referenced

## Target Maps (42 total)

### Entry Zone — Gate to the Future
| Map ID | Name | Role |
|--------|------|------|
| 271000000 | Gate to the Future | Hub/entrance |
| 271000100 | Mutant Tino Forest | Grinding (entry) |
| 271000200 | Mutant Tiru Forest | Grinding (entry) |
| 271000210 | Mutant Tiguru Forest | Grinding (entry) |
| 271000300 | Ereve Forked Road | Branch point |

### Henesys Ruins — Lv 130-134
| Map ID | Name | Role |
|--------|------|------|
| 271010000 | Henesys Ruins | Grinding zone 1 |
| 271010001 | Rina's House | NPC area |
| 271010100 | Henesys Ruins Market | Grinding |
| 271010200 | Henesys Ruins Park | Grinding |
| 271010300 | Hill North of Henesys Ruins | Grinding |
| 271010400 | Dreamy Forest Trail | Grinding |
| 271010500 | Six Path Crossway Ruins | Grinding |

### Dark Forest — Lv 134-137
| Map ID | Name | Role |
|--------|------|------|
| 271020000 | Dark Spore Hill | Grinding |
| 271020100 | Creepy Humming Forest Trail | Grinding |

### Stronghold / Knight District — Lv 137-140
| Map ID | Name |
|--------|------|
| 271030000 | Stronghold Entrance |
| 271030100-271030205 | Knight District 1-4 (training areas) |
| 271030500-271030540 | Knights' Chamber 1-5 (boss approach) |
| 271030600 | Hall of Honor |

### Boss Area — Lv 140
| Map ID | Name | Role |
|--------|------|------|
| 271040000 | Cygnus Garden | Pre-boss |
| 271040100 | Cygnus's Chamber | **EMPRESS BOSS ROOM** |
| 271040200 | Cygnus Rear Garden | Post-boss |
| 271040300 | Scrubby Garden | Post-boss |

## Steps

1. **Open Map.wz** in HaRepacker with "GMS (old)" encryption
2. **Navigate** to `Map/Map2/` and find each map ID in the 271xxxxxx range
3. **Export** each as XML via Private Server export
4. **For each map**, note:
   - Portal destinations (which map IDs they connect to)
   - Mob IDs referenced in `life` sections — **CRITICAL for PROMPT-07**
   - NPC IDs referenced
5. **Save** each as `[MAPID].img.xml` in the output directory
6. **Generate SUMMARY.md** with:
   - Full map list with names
   - Portal connection graph
   - **Complete list of all mob IDs** referenced in `life` sections (this feeds PROMPT-07)
   - Any NPC IDs found
   - Which maps are in each level tier

## Important: Do NOT Modify Map Data

Export maps exactly as they are. Preserve tile data, backgrounds, portals, spawn positions.

## Expected Mob ID Ranges

Based on the repack analysis, Future Ereve maps should reference mobs in these ranges:
- **8641000-8641031**: Erda spirit variants (entry/forest mobs)
- **8642000-8642024**: Nature-themed mobs (pinedeer, ewenana, etc.)
- **8644000-8644836**: Water/Sun/Earth/Spirit variants (main grinding mobs)
- **8645000-8645065**: Corrupted warriors, Black Knights, support troops (boss approach + Empress area)
- **8600000-8600006**: Mutant basic mobs (Gate entry maps)

The SUMMARY should capture the exact IDs so PROMPT-07 knows what to extract.

## Verification

1. Count: approximately 42 files (some map IDs between the ranges listed above)
2. Each file is valid XML with map structure intact
3. Portal chain connects from Gate (271000000) through ruins to Cygnus's Chamber (271040100)
4. SUMMARY.md lists ALL mob IDs found in life sections
5. Boss room map (271040100) exists and is not empty

## Deployment (Done from MacBook)

```bash
scp ~/Shared-Win/output/fe-maps/*.xml \
  homelab@192.168.0.25:/home/homelab/Cosmic/wz/Map.wz/Map/Map2/
```

## Test

```
!warp 271000000       (Gate to the Future — entrance)
Walk through — check tiles/backgrounds render
Walk portal chain toward Henesys Ruins
!warp 271040100       (Cygnus's Chamber — boss room)
Verify room loads
```
