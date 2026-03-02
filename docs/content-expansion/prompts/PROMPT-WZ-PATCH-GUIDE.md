# WZ Patching Guide — Adding Post-v83 Sprites to the Vanilla Client

## Why This Exists

The vanilla v83 MapleStory client crashes when the server tells it to render a post-v83 mob or map — the sprite data doesn't exist in the v83 WZ files. We need to copy sprites from the community repack into the vanilla client's WZ files using HaRepacker.

This is done **alongside** each extraction prompt. When you extract mob XMLs for the server, you ALSO patch the vanilla Mob.wz with the same mob's sprites.

## Locations

| File | Path | Purpose |
|------|------|---------|
| Vanilla Mob.wz | `C:\Users\carbyne\Documents\MapleStory\Mob.wz` | Client mob sprites (PATCH THIS) |
| Vanilla Map.wz | `C:\Users\carbyne\Documents\MapleStory\Map.wz` | Client map data (PATCH THIS) |
| Vanilla Character.wz | `C:\Users\carbyne\Documents\MapleStory\Character.wz` | Client equipment sprites (PATCH THIS) |
| Repack Mob.wz | `C:\Users\carbyne\Documents\CommunityRepack\Mob.wz` | Source mob sprites (COPY FROM) |
| Repack Map.wz | `C:\Users\carbyne\Documents\CommunityRepack\Map.wz` | Source map data (COPY FROM) |
| Repack Character.wz | `C:\Users\carbyne\Documents\CommunityRepack\Character.wz` | Source equipment sprites (COPY FROM) |
| HaRepacker | `C:\Users\carbyne\Documents\HaRepacker\` | The tool |

**IMPORTANT**: Back up the vanilla WZ files before patching! Copy the originals to `C:\Users\carbyne\Documents\MapleStory\backup\` first.

## How to Patch (HaRepacker Workflow)

### One-Time Setup
1. Copy all vanilla WZ files to a backup folder
2. Open HaRepacker

### Per-Mob Patching (e.g., Chaos Zakum)
1. **Open repack Mob.wz** in HaRepacker (File → Open, "GMS (old)" encryption)
2. **Find the mob** (e.g., `8800101.img` for Chaos Zakum Body 2)
3. **Right-click → Copy** the entire `.img` node
4. **Open vanilla Mob.wz** in another HaRepacker tab/instance
5. **Right-click on the root → Paste** (adds the new mob .img)
6. **Save** the vanilla Mob.wz (File → Save, HaRepacker auto-backs up)
7. Repeat for all mobs in the batch

### Per-Map Patching (e.g., LHC maps)
Same process but with Map.wz:
1. Open repack Map.wz → navigate to `Map/Map2/`
2. Copy each LHC map .img (211060000.img, etc.)
3. Open vanilla Map.wz → navigate to `Map/Map2/`
4. Paste each map .img
5. Save

### Batch Approach
If HaRepacker supports it, you can copy multiple .img nodes at once. Otherwise do them one at a time — it's tedious but reliable.

## Verification

After patching, launch the vanilla client:
- Login, use `!spawn <mobid>` — mob should render without crashing
- Use `!warp <mapid>` — map should load without crashing

## Per-Prompt Patching Checklist

| Prompt | What to Patch | WZ File | IDs |
|--------|--------------|---------|-----|
| PROMPT-02 | Chaos Zakum sprites | Mob.wz | 8800100-8800116 (17 mobs) |
| PROMPT-10 | Corrupted ToT sprites | Mob.wz | 8220016-8220021 (6 mobs) |
| PROMPT-09 | Singapore mobs (if new) | Mob.wz | TBD from investigation |
| PROMPT-03 | LHC map data | Map.wz | 211060000-211070110 (28 maps) |
| PROMPT-04 | LHC mob sprites | Mob.wz | IDs from PROMPT-03 output |
| PROMPT-05 | Von Leon sprites + equips | Mob.wz + Character.wz | 8840000-8840002 + equip IDs |
| PROMPT-06 | Future Ereve map data | Map.wz | 271000000-271040300 (42 maps) |
| PROMPT-07 | Future Ereve mob sprites | Mob.wz | IDs from PROMPT-06 output |
| PROMPT-08 | Empress sprites + equips | Mob.wz + Character.wz | 8850000-8850011 + equip IDs |
