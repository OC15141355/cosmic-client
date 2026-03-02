# PROMPT: Build Automated WZ Patcher Tool

## Context

HaRepacker is a GUI-only tool. We need to patch mob/map sprites into the vanilla v83 client WZ files for every extraction batch. Doing this manually through the GUI for 100+ mobs/maps is not viable.

HaRepacker uses **MapleLib.dll** (a .NET library) internally. We can load this DLL from PowerShell or a small C# console app and do the same operations programmatically.

## Goal

Create a PowerShell script (or C# console app) that:
1. Opens the vanilla Mob.wz (or Map.wz, Character.wz)
2. Opens individual .img files from the Community Repack
3. Adds/replaces those .img nodes in the vanilla WZ
4. Saves the patched WZ file

## Key Paths

| Item | Path |
|------|------|
| HaRepacker install | `C:\Users\carbyne\Documents\HaRepacker\` |
| MapleLib.dll | Look inside HaRepacker directory — likely `MapleLib.dll` or `MapleLib2.dll` |
| Vanilla Mob.wz | `C:\Users\carbyne\Documents\MapleStory\Mob.wz` |
| Vanilla Map.wz | `C:\Users\carbyne\Documents\MapleStory\Map.wz` |
| Vanilla Character.wz | `C:\Users\carbyne\Documents\MapleStory\Character.wz` |
| Repack mob .img files | `C:\Users\carbyne\Documents\CommunityRepack\Mob\` (individual .img files like `8800100.img`) |
| Repack map .img files | `C:\Users\carbyne\Documents\CommunityRepack\Map\` |
| WZ backups | `C:\Users\carbyne\Documents\MapleStory\backup\` (already done) |

## Step 1: Investigate

First, figure out what's available:

```powershell
# Find the DLL
Get-ChildItem "C:\Users\carbyne\Documents\HaRepacker\" -Recurse -Filter "*.dll" | Select Name, FullName

# Check if repack has individual .img files or a full Mob.wz
Get-ChildItem "C:\Users\carbyne\Documents\CommunityRepack\Mob\" | Select Name -First 20
Get-ChildItem "C:\Users\carbyne\Documents\CommunityRepack\" -Filter "*.wz" | Select Name

# Check what version of .NET the DLL targets
# (If it's .NET Framework, PowerShell 5.1 can load it. If .NET Core, use dotnet.)
```

## Step 2: Try Loading MapleLib

```powershell
# Load the DLL
Add-Type -Path "C:\Users\carbyne\Documents\HaRepacker\MapleLib.dll"

# Check available types
[AppDomain]::CurrentDomain.GetAssemblies() | Where-Object { $_.FullName -like "*Maple*" } |
    ForEach-Object { $_.GetTypes() | Where-Object { $_.IsPublic } | Select FullName }
```

Key classes to look for:
- `MapleLib.WzLib.WzFile` — opens/saves WZ archives
- `MapleLib.WzLib.WzImage` — represents a single .img inside a WZ
- `MapleLib.WzLib.WzMapleVersion` — encryption type (use GMS or CLASSIC)
- `MapleLib.WzLib.WzDirectory` — directory node inside WZ

## Step 3: Build the Patcher Script

The basic approach (pseudocode):

```powershell
# Load MapleLib
Add-Type -Path "path\to\MapleLib.dll"

# Open vanilla WZ
$vanillaWz = New-Object MapleLib.WzLib.WzFile("vanilla\Mob.wz", [MapleLib.WzLib.WzMapleVersion]::GMS)
$vanillaWz.ParseWzFile()

# For each mob ID to add:
$mobIds = @(8800100, 8800101, 8800102, ..., 8800116)

foreach ($id in $mobIds) {
    $imgPath = "repack\Mob\$id.img"

    # Method A: If repack has individual .img files
    # Load the .img binary and create a WzImage from it
    # Add it to the vanilla WZ's root directory

    # Method B: If repack has a Mob.wz file
    # Open repack Mob.wz, find the node, clone it, add to vanilla
}

# Save
$vanillaWz.SaveToDisk("vanilla\Mob.wz")
$vanillaWz.Dispose()
```

**IMPORTANT**: The exact API depends on the MapleLib version. Investigate the DLL's public methods first. Common variations:
- Some versions use `WzFile(path, version)`, others `WzFile(path, gameVersion, version)`
- Save methods vary: `SaveToDisk()` vs `Save()` vs `SaveAs()`
- Adding nodes: might be `wzDir.AddImage(img)` or `wzDir.WzImages.Add(img)`

## Step 4: Make It Reusable

Once the basic approach works, wrap it into a function:

```powershell
# Usage: .\patch-wz.ps1 -WzFile "Mob.wz" -ImgIds @(8800100..8800116) -RepackDir "CommunityRepack\Mob"
param(
    [string]$WzFile,      # Which vanilla WZ to patch (Mob.wz, Map.wz, etc.)
    [int[]]$ImgIds,       # List of .img IDs to add
    [string]$RepackDir    # Where to find the source .img files
)
```

## Alternative: If MapleLib doesn't work from PowerShell

If the DLL has dependency issues or won't load:

1. **Write a C# console app** that references MapleLib.dll directly — compile with `csc.exe` or `dotnet build`
2. **Check for WzPatcher** — some community repos have standalone CLI WZ patching tools
3. **Try Python**: `pip install wz` or other Python WZ libraries (less common, may not support writing)
4. **Use HaRepacker's own scripting** — some versions have a scripting panel

## Verification

After patching, verify by checking the file:

```powershell
# File size should increase after adding nodes
$before = (Get-Item "backup\Mob.wz").Length
$after = (Get-Item "MapleStory\Mob.wz").Length
Write-Host "Size change: $before -> $after bytes (+$($after - $before))"

# Re-open the patched WZ and verify the nodes exist
$check = New-Object MapleLib.WzLib.WzFile("MapleStory\Mob.wz", [MapleLib.WzLib.WzMapleVersion]::GMS)
$check.ParseWzFile()
$check.WzDirectory["8800100.img"]  # Should not be null
$check.Dispose()
```

## What To Produce

1. A working `patch-wz.ps1` script in `C:\Shared\output\tools\`
2. Run it for **Batch 1** (Chaos Zakum, 17 mobs) and **Batch 2** (Corrupted ToT, 6 mobs)
3. Update TRACKER.md with the results
4. Note the vanilla Mob.wz file size before/after

## Batch 1: Chaos Zakum (17 mobs)
IDs: 8800100 8800101 8800102 8800103 8800104 8800105 8800106 8800107 8800108 8800109 8800110 8800111 8800112 8800113 8800114 8800115 8800116

## Batch 2: Corrupted ToT (6 mobs)
IDs: 8220016 8220017 8220018 8220019 8220020 8220021
