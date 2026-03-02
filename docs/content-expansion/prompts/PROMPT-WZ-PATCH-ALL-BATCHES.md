# PROMPT: Run WzPatcher Batches 3-9 — All Remaining Client Sprites

## Context

All 10 extraction prompts are DONE. All server deployments are DONE. The WzPatcher C# tool works (Batches 1+2 completed in Session 7). Now we need to run the remaining batches so the vanilla v83 client can render all the new content without crashing.

**WzPatcher location**: `C:\Shared\output\tools\wz-patcher\`
**Build command**: `dotnet run --project C:\Shared\output\tools\wz-patcher\`

**Usage**: `dotnet run --project C:\Shared\output\tools\wz-patcher\ -- <vanilla.wz> <repack-img-dir> <id1> [id2] ...`

The tool:
- Reads binary .img files from the repack directory
- Adds them to the vanilla WZ file
- Saves to `<file>.wz.patched` — you must rename it after verifying
- Skips IDs already present in the WZ (safe to re-run)

## Key Paths

| Item | Path |
|------|------|
| Vanilla Mob.wz | `C:\Users\carbyne\Documents\MapleStory\Mob.wz` |
| Vanilla Map.wz | `C:\Users\carbyne\Documents\MapleStory\Map.wz` |
| Repack mob .img | `C:\Users\carbyne\Documents\CommunityRepack\Mob\` |
| Repack map .img | `C:\Users\carbyne\Documents\CommunityRepack\Map\Map\Map2\` (LHC + FE) |
| Repack map .img | `C:\Users\carbyne\Documents\CommunityRepack\Map\Map\Map5\` (Singapore) |
| WZ backups | `C:\Users\carbyne\Documents\MapleStory\backup\` (already done) |

## Important Notes

- **Map.wz is different from Mob.wz**: Map.wz has a nested directory structure (`Map/Map2/`, `Map/Map5/`). The repack's individual .img files are inside those subdirs. The WzPatcher works at the WZ root level, so you may need to check whether map .img files need special handling vs mob .img files.
- **Test after each batch**: Verify the .patched file size increased, then rename.
- **The tool skips duplicates**: If a mob/map .img already exists in the WZ, it prints SKIP. This is safe.
- **Character.wz**: Von Leon + Empress equips may also need patching for visual rendering. Check if the repack has individual .img files for the equip IDs. Lower priority than mobs/maps since stats work without sprites.

## Batches to Run

### Batch 3: LHC Mobs (9 mobs) — Mob.wz

```powershell
$proj = "C:\Shared\output\tools\wz-patcher"
$mob = "C:\Users\carbyne\Documents\MapleStory\Mob.wz"
$repack = "C:\Users\carbyne\Documents\CommunityRepack\Mob"

dotnet run --project $proj -- $mob $repack 8210000 8210001 8210002 8210003 8210004 8210005 8210006 8210007 8210013

# Verify and rename
Move-Item "${mob}.patched" $mob -Force
```

### Batch 4: Singapore Mobs (13 mobs) — Mob.wz

```powershell
dotnet run --project $proj -- $mob $repack 9420514 9420515 9420516 9420517 9420518 9420519 9420520 9420521 9420522 9420525 9420526

# Verify and rename
Move-Item "${mob}.patched" $mob -Force
```

### Batch 5: Future Ereve Mobs (22 mobs) — Mob.wz

```powershell
dotnet run --project $proj -- $mob $repack 8600000 8600001 8600002 8600003 8600004 8600005 8600006 8610000 8610001 8610002 8610003 8610004 8610005 8610006 8610007 8610008 8610009 8610010 8610011 8610012 8610013 8610014

# Verify and rename
Move-Item "${mob}.patched" $mob -Force
```

### Batch 6: Empress Mobs (12 mobs) — Mob.wz

```powershell
dotnet run --project $proj -- $mob $repack 8850000 8850001 8850002 8850003 8850004 8850005 8850006 8850007 8850008 8850009 8850010 8850011

# Verify and rename
Move-Item "${mob}.patched" $mob -Force
```

### Batch 7: LHC Maps (28 maps) — Map.wz

**NOTE**: Map .img files are nested inside `Map/Map2/` in the repack. Check what the repack directory structure looks like first:

```powershell
# Check repack structure
ls "C:\Users\carbyne\Documents\CommunityRepack\Map\Map\Map2\" | Select-String "211060|211070" | Select -First 5

$map = "C:\Users\carbyne\Documents\MapleStory\Map.wz"
$repackMap2 = "C:\Users\carbyne\Documents\CommunityRepack\Map\Map\Map2"

dotnet run --project $proj -- $map $repackMap2 211060000 211060010 211060100 211060200 211060201 211060300 211060400 211060401 211060410 211060500 211060600 211060601 211060610 211060620 211060700 211060800 211060801 211060810 211060820 211060830 211060900 211061000 211061001 211061100 211070000 211070100 211070101 211070110

# Verify and rename
Move-Item "${map}.patched" $map -Force
```

**IMPORTANT**: The WzPatcher was built for Mob.wz (flat structure). Map.wz has nested directories (`Map/Map2/`). If the tool doesn't find the .img files, you may need to:
1. Check if the repack has individual `211060000.img` files or if they're inside a WZ archive
2. If the tool can't handle Map.wz's nested structure, you may need to modify Program.cs to navigate into `WzDirectory["Map"]["Map2"]` instead of `WzDirectory` directly

### Batch 8: Singapore Maps (30 maps) — Map.wz

```powershell
$repackMap5 = "C:\Users\carbyne\Documents\CommunityRepack\Map\Map\Map5"

dotnet run --project $proj -- $map $repackMap5 541020000 541020100 541020200 541020300 541020400 541020500 541020600 541020610 541020620 541020621 541020622 541020623 541020624 541020625 541020626 541020627 541020628 541020629 541020630 541020631 541020632 541020633 541020634 541020635 541020636 541020637 541020638 541020639 541020700 541020800

# Verify and rename
Move-Item "${map}.patched" $map -Force
```

### Batch 9: Future Ereve Maps (42 maps) — Map.wz

```powershell
dotnet run --project $proj -- $map $repackMap2 271000000 271000100 271000200 271000210 271000300 271010000 271010001 271010100 271010200 271010300 271010301 271010400 271010500 271020000 271020100 271030000 271030010 271030100 271030101 271030102 271030200 271030201 271030202 271030203 271030204 271030205 271030300 271030310 271030320 271030400 271030410 271030500 271030510 271030520 271030530 271030540 271030600 271040000 271040100 271040200 271040210 271040300

# Verify and rename
Move-Item "${map}.patched" $map -Force
```

## Execution Order

Do all Mob.wz batches first (3-6), then Map.wz batches (7-9). This way you only rename Mob.wz once and Map.wz once if you chain the runs, or rename after each if you prefer incremental verification.

Actually — **you can chain Mob.wz batches**. After each batch, the tool saves `.patched`. Rename it, then run the next batch against the renamed file. Each batch builds on the previous.

## Verification

After all batches:
```powershell
# Check final file sizes
$mob = Get-Item "C:\Users\carbyne\Documents\MapleStory\Mob.wz"
$map = Get-Item "C:\Users\carbyne\Documents\MapleStory\Map.wz"
Write-Host "Mob.wz: $($mob.Length) bytes"
Write-Host "Map.wz: $($map.Length) bytes"

# Compare to backup
$mobBackup = Get-Item "C:\Users\carbyne\Documents\MapleStory\backup\Mob.wz"
$mapBackup = Get-Item "C:\Users\carbyne\Documents\MapleStory\backup\Map.wz"
Write-Host "Mob.wz grew by: $($mob.Length - $mobBackup.Length) bytes"
Write-Host "Map.wz grew by: $($map.Length - $mapBackup.Length) bytes"
```

## Update Tracker

After completing, update `C:\Shared\TRACKER.md`:
- Mark Batches 3-9 as DONE with file size changes
- Update the "What needs WZ patching" section
- Note any issues (missing .img files, Map.wz structure problems)

## What This Unblocks

Once all batches are patched, Declan can:
- `!warp 211060000` — enter Lion Heart Castle
- `!warp 541020000` — enter Ulu City
- `!warp 271000000` — enter Future Ereve
- `!spawn 8850011` — spawn Empress Cygnus
- All without client crashes
