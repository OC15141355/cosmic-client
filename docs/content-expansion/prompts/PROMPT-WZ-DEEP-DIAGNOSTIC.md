# PROMPT: Deep Diagnostic — Why New Maps Crash the v83 Client

## Context

ALL visual assets have been patched (Batches 1-17: tilesets, backgrounds, objects, BGMs, MapHelper, BgmSG). But warping to ANY new map still crashes the v83 client.

**CONFIRMED — both maps AND mobs crash:**
- `!warp 541020632` (Singapore dungeon room with ZERO external assets) → crash
- `!spawn 8210000` (LHC mob, spawned in Henesys which is a vanilla v83 map) → crash

This proves the problem is NOT missing assets. It affects ALL patched .img data — Map.wz, Mob.wz, everything.

**Root cause**: The .img binary format from the Community Repack is incompatible with the v83 client. The WzPatcher copies raw .img bytes from the repack's WZ files into the vanilla WZ. But the repack is from a newer MapleStory version, and the binary .img format has changed (different canvas compression, encryption, internal structure). The v83 client crashes trying to parse these newer-format .img blobs.

## The Problem

The current WzPatcher does this:
1. Opens repack .img as raw binary bytes
2. Copies those bytes into the vanilla WZ
3. Saves

This preserves the **source format** — which is wrong for v83. The v83 client expects .img data serialized in v83 format.

## The Fix

Instead of copying raw bytes, the patcher needs to:
1. **Parse** the repack .img using MapleLib (deserialize from source format)
2. **Create a new WzImage** with those parsed properties
3. **Add** the new WzImage to the vanilla WZ
4. **Save** the vanilla WZ (MapleLib serializes in the target format)

MapleLib should handle the format conversion internally — it decodes whatever format the source uses, and encodes in whatever format the target WZ uses.

## Step 1: Diagnose the Format Mismatch

### 1a: Check WZ version info

Write a small diagnostic tool (or modify WzPatcher):

```csharp
using MapleLib.WzLib;

// Check vanilla WZ version
var vanilla = new WzFile(@"C:\Users\carbyne\Documents\MapleStory\Map.wz", WzMapleVersion.GMS);
vanilla.ParseWzFile();
Console.WriteLine($"Vanilla - Version: {vanilla.Version}, MapleVersion: {vanilla.MapleVersion}");

// Check repack - try different version enums
foreach (var ver in new[] { WzMapleVersion.GMS, WzMapleVersion.EMS, WzMapleVersion.BMS, WzMapleVersion.CLASSIC }) {
    try {
        var repack = new WzFile(@"C:\Users\carbyne\Documents\CommunityRepack\Map.wz", ver);
        repack.ParseWzFile();
        Console.WriteLine($"Repack ({ver}) - Version: {repack.Version}, MapleVersion: {repack.MapleVersion}");
        // Try parsing a known .img
        var map2 = repack.WzDirectory?.GetDirectoryByName("Map")?.GetDirectoryByName("Map2");
        var img = map2?.GetImageByName("211060000.img");
        if (img != null) {
            img.ParseImage();
            Console.WriteLine($"  211060000.img parsed OK: {img.Parsed}, properties: {img.WzProperties?.Count}");
        }
        repack.Dispose();
        break; // If we get here, this version works
    } catch (Exception ex) {
        Console.WriteLine($"Repack ({ver}) - FAILED: {ex.Message}");
    }
}
vanilla.Dispose();
```

### 1b: Check what WzPatcher is actually doing

Look at the current `Program.cs` in `C:\Shared\output\tools\wz-patcher\`. How does it add .img files? There are two approaches:

**Bad (current?)** — reads .img as raw FileStream, creates WzImage from bytes:
```csharp
// This preserves source format — WRONG for cross-version patching
byte[] data = File.ReadAllBytes(imgPath);
var newImg = new WzImage(name) { ... };
```

**Good** — parses .img from source WZ, clones properties into new WzImage:
```csharp
// This lets MapleLib handle format conversion
var sourceWz = new WzFile(repackPath, sourceVersion);
sourceWz.ParseWzFile();
var sourceImg = /* navigate to the .img */;
sourceImg.ParseImage();
// Deep-clone all properties into the target WZ
```

### 1c: Check if the repack has individual .img files or a WZ archive

The WzPatcher currently reads individual `.img` binary files from the repack directory (e.g., `CommunityRepack/Map/Map/Map2/211060000.img`). These are standalone binary blobs extracted from a WZ file.

**Key question**: Are these standalone .img files in a format MapleLib can parse directly? Try:

```csharp
// Try loading a standalone .img file
var img = new WzImage("211060000.img");
// img needs to be loaded from bytes and parsed
// Check if MapleLib can handle this
```

If the repack also has the full `Map.wz` file (not just extracted .img), it might be better to open the repack's Map.wz directly and copy parsed WzImages from it.

Check: `C:\Users\carbyne\Documents\CommunityRepack\` — is there a `Map.wz` file at the root, or only extracted subdirectories?

## Step 2: Rewrite WzPatcher for Cross-Version Patching

Once you understand the format mismatch, rewrite the patcher. The core change:

```csharp
// NEW APPROACH: Parse from source, re-serialize for target

// 1. Open the repack's WZ file (or parse standalone .img with correct version)
var sourceWz = new WzFile(repackWzPath, repackVersion);  // e.g., WzMapleVersion.BMS or whatever works
sourceWz.ParseWzFile();

// 2. Navigate to the source .img
var sourceImg = /* find the .img in source WZ */;
sourceImg.ParseImage();  // MapleLib decodes from source format

// 3. Open vanilla WZ
var targetWz = new WzFile(vanillaWzPath, WzMapleVersion.GMS);
targetWz.ParseWzFile();

// 4. Deep-clone the parsed WzImage into target WZ
//    MapleLib should re-serialize in target format on save
var targetDir = targetWz.WzDirectory;  // or navigate to subdir
// Clone sourceImg properties into a new WzImage
var newImg = CloneWzImage(sourceImg);  // You may need to write this
targetDir.AddImage(newImg);

// 5. Save — MapleLib writes in GMS (old) format
targetWz.SaveToDisk(outputPath);
```

### Deep Clone Helper

MapleLib may not have a built-in deep clone. You might need:

```csharp
WzImage CloneWzImage(WzImage source) {
    var clone = new WzImage(source.Name);
    foreach (var prop in source.WzProperties) {
        clone.AddProperty(CloneProperty(prop));
    }
    return clone;
}

WzImageProperty CloneProperty(WzImageProperty prop) {
    // Handle each property type: WzSubProperty, WzCanvasProperty,
    // WzVectorProperty, WzConvexProperty, WzSoundProperty,
    // WzIntProperty, WzStringProperty, WzFloatProperty, etc.
    // Recursively clone sub-properties
    // For canvases: clone the bitmap data
    // For sounds: clone the audio data
}
```

**Alternative**: Some versions of MapleLib support serializing a WzImage to bytes and deserializing. Check if there's a `WzImage.SerializeImage()` / `WzImage.DeserializeImage()` or similar.

**Alternative 2**: Check if MapleLib's `WzBinaryWriter` / `WzBinaryReader` can be used to re-encode.

## Step 3: Test the Fix

After rewriting:

1. Re-patch a single map: `541020632` (the zero-asset Singapore room)
2. Have Declan test: `!warp 541020632`
3. If it works, re-patch all maps + tilesets + backgrounds + objects + BGMs

## Step 4: Re-patch ALL WZ files

**CONFIRMED**: Mob.wz is also broken (`!spawn 8210000` in Henesys crashes). The re-serialization fix must be applied to ALL patched WZ files:

- **Mob.wz**: All batches 1-6 (CZak, ToT, LHC, Singapore, FE, Empress mobs)
- **Map.wz**: All batches 7-9 (maps) + 10-11 (tiles/backs) + 12 (objs) + 14 (MapHelper)
- **Sound.wz**: Batches 13 + 17 (BGMs)

Start with one test case (e.g., map 541020632 or mob 8210000), confirm it works, then re-patch everything.

## Key Paths

| Item | Path |
|------|------|
| WzPatcher source | `C:\Shared\output\tools\wz-patcher\Program.cs` |
| Vanilla Map.wz | `C:\Users\carbyne\Documents\MapleStory\Map.wz` |
| Vanilla Mob.wz | `C:\Users\carbyne\Documents\MapleStory\Mob.wz` |
| Vanilla Sound.wz | `C:\Users\carbyne\Documents\MapleStory\Sound.wz` |
| Vanilla Npc.wz | `C:\Users\carbyne\Documents\MapleStory\Npc.wz` |
| Repack root | `C:\Users\carbyne\Documents\CommunityRepack\` |
| WZ backups | `C:\Users\carbyne\Documents\MapleStory\backup\` |

## Important Notes

- **Back up** the current patched WZ files before making changes (the vanilla backups already exist, but the patched versions have all the work from Batches 1-17)
- The repack directory has individual `.img` files — check if there's also a full `.wz` archive available
- MapleLib version matters — check which MapleLib build the WzPatcher uses and whether it supports the repack's format
- If MapleLib can't parse the repack's format at all, we may need a different library or a two-step conversion (repack → HaRepacker export → re-import)

## Update Tracker

After diagnosing, update `C:\Shared\TRACKER.md`:
- Note the root cause (binary format incompatibility confirmed)
- Record the repack's WZ version vs vanilla's version
- Document whether the re-serialization approach works
- Update batch status if re-patching is needed
