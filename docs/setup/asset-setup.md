# Asset Setup

TwinleafStory requires v83 MapleStory game assets in NX format. These are large files (~6.9 GB total) and are NOT stored in git.

## Option A: Pre-converted NX Files

If you already have NX files (from a previous conversion or shared by another developer):

```bash
# Symlink all 16 NX files into the client build directory
tools/scripts/setup-nx-symlinks.sh /path/to/your/nx/files
```

The script checks that all 16 required files exist (per `Util/NxFiles.h`).

## Option B: Convert from Community Repack

### 1. Get the Community Repack

The v83 GMS community repack contains .IMG directories with all game data. Place it somewhere accessible (e.g., `~/Downloads/Community Repack  .IMG/Data/`).

Contents:
```
Data/
├── Base/          (12 KB)
├── Character/     (1.9 GB)
├── Effect/        (265 MB)
├── Etc/           (1.8 MB)
├── Item/          (461 MB)
├── Map/           (1.4 GB)
├── Mob/           (1.3 GB)
├── Morph/         (6 MB)
├── Npc/           (579 MB)
├── Quest/         (5.7 MB)
├── Reactor/       (57 MB)
├── Skill/         (117 MB)
├── Sound/         (602 MB)
├── String/        (7.8 MB)
├── TamingMob/     (28 KB)
└── UI/            (30 MB)
```

### 2. Build the Converter

```bash
cd tools/wztonx
mkdir build && cd build
cmake .. && make
```

### 3. Convert

```bash
# Batch convert all files
tools/scripts/convert-wz-to-nx.sh \
  ~/Downloads/"Community Repack  .IMG"/Data \
  ~/Games/TwinleafStory/nx
```

This produces 16 NX files totaling ~6.9 GB.

### 4. Symlink

```bash
tools/scripts/setup-nx-symlinks.sh ~/Games/TwinleafStory/nx
```

## Verifying Assets

Use nxdump to inspect NX file structure:

```bash
cd tools/nxdump/build
./nxdump ../../../build/UI.nx Login.img 1
```

## Required NX Files

From `Util/NxFiles.h`:

| File | Content |
|------|---------|
| Base.nx | Core game data |
| Character.nx | Player sprites and animations |
| Effect.nx | Visual effects |
| Etc.nx | Miscellaneous data |
| Item.nx | Equipment and item sprites |
| Map.nx | Maps, backgrounds, tilesets |
| Mob.nx | Monster sprites |
| Morph.nx | Transformation sprites |
| Npc.nx | NPC sprites |
| Quest.nx | Quest data |
| Reactor.nx | Interactive map objects |
| Skill.nx | Skill animations |
| Sound.nx | BGM and sound effects |
| String.nx | Text and localization |
| TamingMob.nx | Mount/pet data |
| UI.nx | UI sprites and layouts |
