# Asset Pipeline

## Overview

TwinleafStory uses NX files (PKG4 format) as its game asset format. These are converted from MapleStory WZ/IMG files using the wztonx tool.

## File Formats

| Format | Description | Size | In Git? |
|--------|-------------|------|---------|
| WZ/IMG | MapleStory archive format (community repack) | 6.7 GB | No |
| NX (PKG4) | Memory-mapped read-only format (NoLifeNx) | 6.9 GB | No |

## NX Files Required

From `Util/NxFiles.h` — all 15 files must be present in `build/`:

```
Base.nx, Character.nx, Effect.nx, Etc.nx, Item.nx, Map.nx, Mob.nx,
Morph.nx, Npc.nx, Quest.nx, Reactor.nx, Skill.nx, Sound.nx, String.nx,
TamingMob.nx, UI.nx
```

Note: v167+ HeavenClient used MapPretty.nx, MapLatest.nx, and Map001.nx. We use a single Map.nx from v83 data.

## Conversion Process

### Source: Community Repack

Location: `~/Downloads/Community Repack  .IMG/Data/`

Contains .img directories for each asset category (Character/, Map/, UI/, Sound/, etc.). This is the canonical v83 GMS data from the 2023 community repack.

### Step 1: Build wztonx

```bash
cd tools/wztonx
mkdir build && cd build
cmake .. && make
```

### Step 2: Convert All Files

```bash
tools/scripts/convert-wz-to-nx.sh \
  ~/Downloads/"Community Repack  .IMG"/Data \
  ~/Games/MapleStoryCX/nx
```

Or convert individually:

```bash
cd ~/Games/MapleStoryCX/nx
/path/to/wztonx -c ~/Downloads/"Community Repack  .IMG"/Data/UI.wz
```

### Step 3: Symlink into Build

```bash
tools/scripts/setup-nx-symlinks.sh ~/Games/MapleStoryCX/nx
```

This creates symlinks in `build/` pointing to the NX files.

## Inspecting NX Structure

Use nxdump to verify node paths before writing code:

```bash
cd tools/nxdump/build
./nxdump ../../../build/UI.nx Login.img/NewChar 3
./nxdump ../../../build/Map.nx Obj/login.img/CharSelect 3
```

**Always verify v83 NX structure with nxdump before coding.** v83 paths differ significantly from v167+.

## File Sizes (v83)

| File | Size | Content |
|------|------|---------|
| Map.nx | 1.4 GB | World maps and backgrounds |
| Mob.nx | 1.1 GB | Monster sprites |
| Character.nx | 364 MB | Player sprites/animations |
| Sound.nx | 346 MB | BGM and sound effects |
| Skill.nx | 171 MB | Skill animations |
| Npc.nx | 126 MB | NPC sprites |
| Effect.nx | 120 MB | Visual effects |
| Reactor.nx | 114 MB | Interactive objects |
| UI.nx | 68 MB | Interface elements |
| Item.nx | 42 MB | Equipment/items |
| Morph.nx | 16 MB | Transformations |
| Quest.nx | 7.2 MB | Quest data |
| String.nx | 5.1 MB | Text/localization |
| Etc.nx | 3.5 MB | Misc data |
| Base.nx | 13 KB | Core data |
| TamingMob.nx | 1.3 KB | Mount data |
