# PROMPT-03: Lion Heart Castle Map Extraction

## What

Extract all 28 Lion Heart Castle maps from the community repack and create server-ready XML files. LHC is a Lv 120-130 grinding area accessed from El Nath, culminating in the Von Leon boss room.

## Where

### Input
- **Community Repack Map.wz**: `C:\Users\carbyne\Documents\CommunityRepack\Map.wz\`
  - Maps are in the `Map/Map2/` subdirectory (211xxxxxx range = Map2)
  - Look for: `211060000.img` through `211070110.img`
  - These are binary .img files — use HaRepacker to export as XML
- **HaRepacker**: `C:\Users\carbyne\Documents\HaRepacker\`
  - Open with **"GMS (old)"** encryption

### Output
- `C:\Shared\output\lhc-maps\` — 28 XML files, one per map
- `C:\Shared\output\lhc-maps\SUMMARY.md` — map list with portal connections and mob IDs referenced

## Target Maps (28 total)

| Map ID | Name | Role |
|--------|------|------|
| 211060000 | Desolate Moor | Entrance zone |
| 211060010 | Castle Entrance | Hub |
| 211060100 | Under the Castle Walls 1 | Grinding |
| 211060200 | First Tower | Grinding |
| 211060201 | Roof of the First Tower | Grinding |
| 211060300 | Under the Castle Walls 2 | Grinding |
| 211060400 | Second Tower | Grinding |
| 211060401 | Roof of the Second Tower | Grinding |
| 211060410 | Short Castle Walls 1 | Grinding |
| 211060500 | Under the Castle Walls 3 | Grinding |
| 211060600 | Third Tower | Grinding |
| 211060601 | Roof of the Third Tower | Grinding |
| 211060610 | Short Castle Walls 2 | Grinding |
| 211060620 | Tall Castle Walls 1 | Grinding |
| 211060700 | Under the Castle Walls 4 | Grinding |
| 211060800 | Fourth Tower | Grinding |
| 211060801 | Roof of the Fourth Tower | Grinding |
| 211060810 | Short Castle Walls 3 | Grinding |
| 211060820 | Tall Castle Walls 2 | Grinding |
| 211060830 | Very Tall Castle Walls | Grinding |
| 211060900 | Under the Castle Walls 5 | Grinding |
| 211061000 | Fifth Tower | Grinding |
| 211061001 | Roof of the Fifth Tower | Grinding |
| 211061100 | Ani's Jail | Special |
| 211070000 | Audience Room Corridor | Boss approach |
| 211070100 | Audience Room | Von Leon boss room |
| 211070101 | Aerial Prison | Special |
| 211070110 | Roof of the Resurrection Tower | Special |

## Steps

1. **Open Map.wz** in HaRepacker with "GMS (old)" encryption
2. **Navigate** to `Map/Map2/` and find each map ID
3. **Export** each as XML via Private Server export
4. **For each map**, note:
   - Portal destinations (which map IDs they connect to)
   - Mob IDs referenced in `life` sections (these will be needed for PROMPT-04)
   - NPC IDs referenced (for future NPC scripting)
5. **Save** each as `[MAPID].img.xml` in the output directory
6. **Generate SUMMARY.md** with:
   - Full map list with names
   - Portal connection graph (which map connects to which)
   - **Complete list of all mob IDs referenced** in the `life` sections across all maps — this is critical for PROMPT-04
   - Any NPC IDs found

## Important: Do NOT Modify Map Data

Export the maps exactly as they are in the repack. Map layouts, tile data, background data, portal positions, and mob spawn points should be preserved verbatim. The only modifications come later (mob stats in PROMPT-04).

## Map XML Structure Reference

Each map XML file typically has this structure:
```xml
<imgdir name="211060000.img">
  <imgdir name="info">
    <int name="town" value="0"/>
    <int name="returnMap" value="211060000"/>
    <string name="mapMark" value="..."/>
    <!-- map metadata -->
  </imgdir>
  <imgdir name="life">
    <!-- mob and NPC spawns -->
    <imgdir name="0">
      <string name="type" value="m"/>  <!-- m = mob, n = NPC -->
      <string name="id" value="8620000"/>  <!-- mob ID -->
      <int name="x" value="..."/>
      <int name="y" value="..."/>
      <!-- spawn position and behavior -->
    </imgdir>
  </imgdir>
  <imgdir name="portal">
    <!-- portal connections to other maps -->
  </imgdir>
  <!-- tile, obj, back layers for visual data -->
</imgdir>
```

## Verification

1. Count: exactly 28 files in output directory
2. Each file is valid XML with the map structure intact
3. Portal connections form a logical path from entrance (211060000) to boss room (211070100)
4. SUMMARY.md lists ALL mob IDs found — cross-reference with known LHC mob ranges:
   - 8210000-8210013 (castle mobs)
   - 8610000-8610033 (CK enemy mobs)
   - 8620000-8620027 (forest/ruin mobs)
5. No map files are empty or truncated

## Deployment (Done from MacBook)

```bash
scp ~/Shared-Win/output/lhc-maps/*.xml \
  homelab@192.168.0.25:/home/homelab/Cosmic/wz/Map.wz/Map/Map2/
ssh homelab@192.168.0.25 "cd /home/homelab/Cosmic && docker compose restart cosmic-server-1"
```

## Test

```
!warp 211060000       (Desolate Moor — LHC entrance)
Walk around — tiles and backgrounds should render
Walk to portals — should connect to next map
Check mob spawns — mobs should appear (if mob XMLs deployed)
!warp 211070100       (Audience Room — Von Leon boss room)
```
