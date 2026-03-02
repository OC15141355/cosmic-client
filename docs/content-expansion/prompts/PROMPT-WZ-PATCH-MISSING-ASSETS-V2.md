# PROMPT: Patch Remaining Missing Assets (Session 9 follow-up)

## Context

Session 9 patched Batches 10-14 (tilesets, backgrounds, objects, BGMs, MapHelper). But the client still crashes when warping to LHC (211060000). Mac Claude did a full audit of ALL new map XMLs against the v83 server data and found **6 assets that were missed**.

The WzPatcher tool already has `--subdir` and `--replace` support from Session 9. This should be a quick job.

## Audit Results

Mac Claude scanned every new map XML on the server and extracted all unique asset references, then cross-referenced against the vanilla v83 server's Map.wz and Sound.wz directories.

### What's ALREADY in vanilla v83 (no action needed)

| Type | Asset | Notes |
|------|-------|-------|
| Tileset | allblackTile | exists in v83 |
| Background | citySG | exists in v83 |
| Object | citySG | exists in v83 |
| Object | connect | exists in v83 |
| Object | dungeon4 | exists in v83 |
| Object | guide | exists in v83 |
| BGM | Bgm18 | exists in v83 (QueensGarden track is inside) |
| BGM | BgmSG | exists in v83 — **BUT check if Ulu_field track exists inside it** |

### What was PATCHED in Session 9 (already done)

| Type | Asset | Batch |
|------|-------|-------|
| Tileset | lionCastle | Batch 10 |
| Tileset | darkEreb | Batch 10 |
| Tileset | destructionField | Batch 10 |
| Background | blizzardCastle | Batch 11 |
| Background | darkEreb | Batch 11 |
| Background | destructionTown | Batch 11 |
| Object | acc14 | Batch 12 |
| Object | trapSG | Batch 12 |
| BGM | Bgm23 | Batch 13 |
| BGM | Bgm25 | Batch 13 |
| MapMarks | all 4 | Batch 14 |

### What's STILL MISSING — patch these now

| # | Type | Asset | Zone | Why missed |
|---|------|-------|------|------------|
| 1 | Tileset | `snowyLightrock3` | LHC | v83 has `snowyLightrock` + `snowyLightrock2` but NOT `3` |
| 2 | Tileset | `destructionTown1` | Future Ereve | only `destructionField` was patched, not the town variants |
| 3 | Tileset | `destructionTown2` | Future Ereve | same |
| 4 | Tileset | `jungleSG` | Singapore | Singapore-specific tileset |
| 5 | Background | `fakeDoors` | Future Ereve | FE-specific background |
| 6 | Background | `jungleSG` | Singapore | Singapore-specific background |

### Possibly missing — check this one

| Type | Asset | Notes |
|------|-------|-------|
| BGM | `BgmSG/Ulu_field` | `BgmSG.img` exists in v83 Sound.wz, but it may not contain the `Ulu_field` track. Open the vanilla Sound.wz and check if `BgmSG.img` has a `Ulu_field` entry. If not, replace it with the repack's `BgmSG.img` using `--replace`. |

## Commands to Run

```powershell
$proj = "C:\Shared\output\tools\wz-patcher"
$map = "C:\Users\carbyne\Documents\MapleStory\Map.wz"
$sound = "C:\Users\carbyne\Documents\MapleStory\Sound.wz"
$repackTile = "C:\Users\carbyne\Documents\CommunityRepack\Map\Tile"
$repackBack = "C:\Users\carbyne\Documents\CommunityRepack\Map\Back"
$repackSound = "C:\Users\carbyne\Documents\CommunityRepack\Sound"

# Batch 15: Missing tilesets (4x) -> Map.wz/Tile/
dotnet run --project $proj -- $map $repackTile --subdir Tile snowyLightrock3 destructionTown1 destructionTown2 jungleSG
Move-Item "${map}.patched" $map -Force

# Batch 16: Missing backgrounds (2x) -> Map.wz/Back/
dotnet run --project $proj -- $map $repackBack --subdir Back fakeDoors jungleSG
Move-Item "${map}.patched" $map -Force

# Batch 17 (conditional): BgmSG replacement — only if Ulu_field is missing
# First check: open vanilla Sound.wz in MapleLib and check BgmSG.img contents
# If Ulu_field is NOT present:
# dotnet run --project $proj -- $sound $repackSound --replace BgmSG
# Move-Item "${sound}.patched" $sound -Force
```

## Verification

After patching, check file sizes:
```powershell
(Get-Item $map).Length    # should be slightly larger than 675MB
(Get-Item $sound).Length  # unchanged unless BgmSG was replaced
```

## Test

Have Declan test in-game:
```
!warp 211060000    # LHC - Desolate Moor (was crashing due to snowyLightrock3)
!warp 541020000    # Singapore - Ulu City (jungleSG tile+back)
!warp 271000000    # Future Ereve (destructionTown1/2, fakeDoors)
```

All three should load without crashing.

## Update Tracker

After completing, update `C:\Shared\TRACKER.md`:
- Add Batches 15-16 (and 17 if applicable) to the batch list
- Update final Map.wz size
- Mark "What needs WZ patching" items as done if all zones load
