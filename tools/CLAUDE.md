# TwinleafStory Tools

Development tools for the TwinleafStory asset pipeline and debugging.

## wztonx — WZ-to-NX Converter

Converts MapleStory WZ/IMG files to NX (PKG4) format for the client.

- **Origin**: NoLifeWzToNx by Peter Atashian (AGPL-3.0)
- **Source**: `wztonx/wztonx.cpp` + `wztonx/keys.cpp` (encryption key tables)
- **Build**: `cd wztonx/build && cmake .. && make`
- **Dependencies**: lz4, zlib (`brew install lz4 zlib`)
- **Usage**: `./wztonx -c /path/to/Data/UI.wz` (or .img directory)

The community repack at `~/Downloads/Community Repack  .IMG/Data/` contains .img directories (not .wz files). wztonx handles both formats.

## nxdump — NX File Structure Inspector

Diagnostic tool for inspecting NX file node trees. Essential for v83 path verification.

- **Source**: `nxdump/nxdump.cpp` (70 lines, custom tool)
- **Build**: `cd nxdump/build && cmake .. && make`
- **Dependencies**: lz4, NoLifeNx headers (from `../../includes/nlnx/`)
- **Usage**: `./nxdump <file.nx> <path> [depth]`

**Examples:**
```bash
# Check what's in v83 CashShop
./nxdump ../../build/UI.nx CashShop.img 2

# Verify a specific button node exists
./nxdump ../../build/UI.nx Login.img/NewChar/BtYes 3

# Dump map objects
./nxdump ../../build/Map.nx Obj/login.img/CharSelect 3
```

**When to use**: ALWAYS run nxdump before writing code that references NX node paths. v83 NX structure differs significantly from v167+. The client CLAUDE.md documents known v83 paths, but always verify with nxdump for undocumented nodes.

## scripts/ — Automation

| Script | Purpose |
|--------|---------|
| `convert-wz-to-nx.sh` | Batch convert all WZ/IMG files from the community repack |
| `setup-nx-symlinks.sh` | Create NX file symlinks in the client `build/` directory |
| `setup-dev-env.sh` | Full bootstrap: brew deps, build tools, build client |

## Asset Locations

| Asset | Location | Size |
|-------|----------|------|
| WZ/IMG source (community repack) | `~/Downloads/Community Repack  .IMG/Data/` | 6.7 GB |
| NX files (converted) | `~/Games/MapleStoryCX/drive_c/MapleStory/` | 6.9 GB |
| NX symlinks (client build) | `../../build/*.nx` | symlinks |

NX files are NOT in git (6.9GB). They are symlinked into the client build/ directory. See `setup-nx-symlinks.sh`.
