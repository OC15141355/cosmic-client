# PROMPT: Patch Missing Map Assets (Tilesets, Backgrounds, BGM, MapMarks)

## Context

All map .img files are patched into the vanilla Map.wz, and all server deployments are done. But warping to new maps crashes the client because the maps reference post-v83 assets:

- **Tilesets** (Map.wz/Tile/) — visual tile graphics for platforms/walls
- **Backgrounds** (Map.wz/Back/) — scrolling background images
- **Objects** (Map.wz/Obj/) — decorative objects (some may be missing too)
- **BGM** (Sound.wz) — background music
- **MapMarks** (Map.wz/MapHelper.img) — minimap icons

These assets exist in the Community Repack but not in the vanilla v83 client.

## What To Do

### Step 1: Audit ALL new maps for missing assets

Scan every map XML that was extracted (LHC, Singapore, Future Ereve) and collect all unique asset references:

```powershell
# Scan all extracted map XMLs for asset references
$mapDirs = @(
    "C:\Shared\output\lhc-maps",
    "C:\Shared\output\singapore\new-maps",
    "C:\Shared\output\fe-maps"
)

$tilesets = @()
$backgrounds = @()
$objects = @()
$bgms = @()
$mapMarks = @()

foreach ($dir in $mapDirs) {
    foreach ($xml in Get-ChildItem $dir -Filter "*.xml") {
        $content = Get-Content $xml.FullName -Raw
        # Extract tS values (tilesets)
        [regex]::Matches($content, 'name="tS" value="([^"]+)"') | ForEach-Object { $tilesets += $_.Groups[1].Value }
        # Extract bS values (backgrounds)
        [regex]::Matches($content, 'name="bS" value="([^"]+)"') | ForEach-Object { $backgrounds += $_.Groups[1].Value }
        # Extract oS values (objects)
        [regex]::Matches($content, 'name="oS" value="([^"]+)"') | ForEach-Object { $objects += $_.Groups[1].Value }
        # Extract bgm values
        [regex]::Matches($content, 'name="bgm" value="([^"]+)"') | ForEach-Object { $bgms += $_.Groups[1].Value }
        # Extract mapMark values
        [regex]::Matches($content, 'name="mapMark" value="([^"]+)"') | ForEach-Object { $mapMarks += $_.Groups[1].Value }
    }
}

$tilesets = $tilesets | Sort-Object -Unique
$backgrounds = $backgrounds | Sort-Object -Unique
$objects = $objects | Sort-Object -Unique
$bgms = $bgms | Sort-Object -Unique
$mapMarks = $mapMarks | Sort-Object -Unique

Write-Host "=== Unique Tilesets ===" ; $tilesets
Write-Host "=== Unique Backgrounds ===" ; $backgrounds
Write-Host "=== Unique Objects ===" ; $objects
Write-Host "=== Unique BGMs ===" ; $bgms
Write-Host "=== Unique MapMarks ===" ; $mapMarks
```

### Step 2: Check which assets already exist in vanilla

Check the vanilla Map.wz and Sound.wz to see which are already present:

```powershell
# Check vanilla Map.wz for existing assets
# Open vanilla Map.wz in code/MapleLib and list existing Tile/, Back/, Obj/ entries
# Or check the v83 server's copy:
# The server at 192.168.0.25 has the same v83 base data

# Known MISSING from v83 (from initial investigation):
# Tilesets: lioncastle, blizzardCastle (LHC)
# Backgrounds: bsc (LHC)
# BGM: Bgm23/BlizzardCastle (LHC)
# MapMarks: LionCastle (LHC)
# Objects: dungeon4 EXISTS in v83

# Singapore and Future Ereve maps will likely have their own missing assets too
```

### Step 3: Patch missing assets using WzPatcher

The WzPatcher tool at `C:\Shared\output\tools\wz-patcher\` may need modification to handle nested WZ directories (Tile/, Back/, Obj/ inside Map.wz).

For **Tilesets**: The repack should have individual .img files at `C:\Users\carbyne\Documents\CommunityRepack\Map\Tile\`
For **Backgrounds**: `C:\Users\carbyne\Documents\CommunityRepack\Map\Back\`
For **Objects**: `C:\Users\carbyne\Documents\CommunityRepack\Map\Obj\`
For **BGM/Sound**: `C:\Users\carbyne\Documents\CommunityRepack\Sound\` (may be a .wz file instead of individual .img)

**WzPatcher modification needed**: The current tool adds .img to the WZ root directory. For Map.wz sub-assets, you need to navigate into the correct subdirectory:
- `wz.WzDirectory["Tile"]` for tilesets
- `wz.WzDirectory["Back"]` for backgrounds
- `wz.WzDirectory["Obj"]` for objects

Add a `--subdir` parameter to the tool (it may already have this from Batch 7-9 work — check the current Program.cs).

For **Sound.wz**: This is a separate WZ file. Run WzPatcher against Sound.wz directly. BGM entries like `Bgm23/BlizzardCastle` mean there's a `Bgm23.img` inside Sound.wz containing the track.

For **MapMarks**: These are inside `MapHelper.img` in Map.wz. This is trickier — you need to add individual nodes inside an existing .img rather than adding a whole new .img. May need to:
1. Extract MapHelper.img from vanilla Map.wz
2. Add the missing mark entries from the repack's MapHelper.img
3. Re-inject the modified MapHelper.img

### Step 4: Verify

After patching, test by launching the vanilla client:
```
!warp 211060000    # LHC - Desolate Moor
!warp 541020000    # Singapore - Ulu City Entrance
!warp 271000000    # Future Ereve
```

Each should load without crashing.

## Key Paths

| Item | Path |
|------|------|
| WzPatcher | `C:\Shared\output\tools\wz-patcher\` |
| Vanilla Map.wz | `C:\Users\carbyne\Documents\MapleStory\Map.wz` |
| Vanilla Sound.wz | `C:\Users\carbyne\Documents\MapleStory\Sound.wz` |
| Repack Tile .img | `C:\Users\carbyne\Documents\CommunityRepack\Map\Tile\` |
| Repack Back .img | `C:\Users\carbyne\Documents\CommunityRepack\Map\Back\` |
| Repack Obj .img | `C:\Users\carbyne\Documents\CommunityRepack\Map\Obj\` |
| Repack Sound | `C:\Users\carbyne\Documents\CommunityRepack\Sound\` |
| WZ backups | `C:\Users\carbyne\Documents\MapleStory\backup\` |

## Update Tracker

After completing, update `C:\Shared\TRACKER.md`:
- Add a new "Asset Patching" section noting which tilesets/backgrounds/BGMs were added
- Update the "What needs WZ patching" section
- Note final Map.wz and Sound.wz file sizes
