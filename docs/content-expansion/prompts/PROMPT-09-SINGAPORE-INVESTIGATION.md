# PROMPT-09: Singapore Investigation + Extraction

## What

Singapore / Ulu City is a Lv 80-100 area that may PARTIALLY already exist on the server (stock v83 had some Singapore maps). This prompt investigates what exists, identifies gaps, and extracts missing content from the repack.

**This is an investigation-first prompt.** Don't extract anything until you understand the current state.

## Where

### Input — Server Current State
- **Server Map.wz**: `C:\Users\carbyne\Documents\TwinleafStory\server\wz\Map.wz\Map\Map5\`
  - Singapore maps are in the 540xxxxxx-541xxxxxx range (Map5)
  - Check what already exists
- **Server Mob.wz**: `C:\Users\carbyne\Documents\TwinleafStory\server\wz\Mob.wz\`
  - Check for Singapore mob IDs
- **Server String.wz**: `C:\Users\carbyne\Documents\TwinleafStory\server\wz\String.wz\Map.img.xml`
  - Check for Singapore map names

### Input — Repack (for filling gaps)
- **Community Repack Map.wz**: `C:\Users\carbyne\Documents\CommunityRepack\Map.wz\`
  - Ulu City maps: 541020000-541020800 range
- **Community Repack Mob.wz**: `C:\Users\carbyne\Documents\CommunityRepack\Mob.wz\`
  - Singapore area mobs (IDs TBD — discover during investigation)
- **HaRepacker**: `C:\Users\carbyne\Documents\HaRepacker\`

### Output
- `C:\Shared\output\singapore\GAP-ANALYSIS.md` — what exists vs what's missing
- `C:\Shared\output\singapore\new-maps\` — only MISSING map XMLs (if any)
- `C:\Shared\output\singapore\new-mobs\` — only MISSING mob XMLs (if any)
- `C:\Shared\output\singapore\SUMMARY.md` — full investigation report

## Investigation Steps

### Step 1: Audit Server's Singapore Content

1. **List all Singapore maps** currently in server Map.wz:
   ```
   Check Map/Map5/ for files matching 540*.img.xml and 541*.img.xml
   ```
2. **List all Singapore map names** from String.wz/Map.img.xml:
   - Search for "Singapore", "Boat Quay", "CBD", "Ulu City", "Changi"
3. **Check for Singapore mobs** — look for mob XMLs that might be Singapore content:
   - Search String.wz/Mob.img.xml for "Singapore" or related names
   - Check Mob.wz for mob IDs that appear in Singapore map `life` sections

### Step 2: Identify Known Singapore Map IDs

Stock v83 Singapore typically includes:
| Map ID | Name | Expected Status |
|--------|------|----------------|
| 540000000 | Singapore: CBD | Likely exists |
| 540010000 | Boat Quay Town | Likely exists |
| 540010001 | Ulu City Entrance | Maybe |
| 540010100-540010300 | Various town maps | Maybe |
| 541000000-541000400 | Ghost Ship maps | Maybe |
| 541020000-541020800 | Ulu City proper | Probably MISSING (v90+ content) |

### Step 3: Gap Analysis

For each map in the 540-541 range:
- **EXISTS on server + has working mobs** → skip
- **EXISTS on server but mobs missing** → extract only missing mobs from repack
- **MISSING from server** → extract from repack

### Step 4: Extract Missing Content

Only extract what's actually missing. For each new map:
1. Export from repack via HaRepacker
2. Note all mob IDs in `life` sections
3. Check if those mobs exist on the server
4. Extract missing mobs

### Step 5: Tune New Mob Stats (if needed)

Singapore is Lv 80-100. If extracting mobs from the repack, tune stats:

| Area | Target Player Level | Mob Level | maxHP | exp |
|------|--------------------|-----------| ------|-----|
| Ulu City entrance | 80-85 | 90-95 | 40,000-80,000 | 3,000-5,000 |
| Ulu City mid | 85-90 | 95-105 | 80,000-150,000 | 5,000-8,000 |
| Ulu City deep | 90-95 | 105-115 | 150,000-300,000 | 8,000-12,000 |
| Krexel area | 95-100 | 115-120 | 300,000-500,000 | 12,000-15,000 |

### Krexel Boss (if found in repack)

Krexel is a giant tree boss — multi-body fight, Lv 90 target, 60M HP total, 2-3 player party.

Look for Krexel mob IDs in the repack. If found:
- Export and tune to: Level=120, HP=60,000,000 total across all bodies, PADamage=900, boss=1
- Note mob IDs in SUMMARY

## Output: GAP-ANALYSIS.md Format

```markdown
# Singapore Gap Analysis

## Server Current State
- Maps found: [list]
- Maps working (have mobs): [list]
- Maps empty (no mob spawns): [list]

## Missing from Server
- Maps to add: [list with IDs]
- Mobs to add: [list with IDs]

## Repack Content Available
- Maps in repack 540-541 range: [list]
- Mobs referenced by those maps: [list]

## Extraction Plan
- Extract these maps: [list]
- Extract these mobs: [list]
- Skip these (already exist): [list]
```

## Verification

1. GAP-ANALYSIS.md clearly shows what exists vs what's missing
2. Only missing content was extracted (no duplicates of existing server data)
3. New mob stats are tuned for Lv 80-100 range
4. If Krexel was found, its HP target matches the design (60M for 2-3 players)
5. SUMMARY.md has the complete picture

## Deployment (Done from MacBook)

```bash
# Only deploy new files (not ones that already exist!)
scp ~/Shared-Win/output/singapore/new-maps/*.xml \
  homelab@192.168.0.25:/home/homelab/Cosmic/wz/Map.wz/Map/Map5/
scp ~/Shared-Win/output/singapore/new-mobs/*.xml \
  homelab@192.168.0.25:/home/homelab/Cosmic/wz/Mob.wz/
```

## Test

```
!warp 540000000       (Singapore CBD — should already work)
!warp 541020000       (Ulu City — new map, if added)
Check mob spawns and levels
!search mob krexel    (find Krexel mob ID)
```
