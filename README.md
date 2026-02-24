# TwinleafStory

A custom MapleStory v83 experience — native client + custom server mono-repo.

## Overview

TwinleafStory is a from-scratch MapleStory v83 private server project combining:

- **Native client** — C++17, OpenGL 2.1, macOS ARM64 (Windows planned). Fork of HeavenClient's cross-platform `linux` branch, fully ported to v83 NX data.
- **Custom server** — Java 17, Maven. Fork of [Cosmic](https://github.com/P0nk/Cosmic) (v83 GMS emulator).
- **Development tools** — WZ-to-NX converter, NX structure inspector, setup scripts.

## Repo Structure

```
TwinleafStory/
├── Audio/, Character/, Data/, Gameplay/, Graphics/,
│   IO/, Net/, Template/, Util/          — Client source (C++)
├── includes/nlnx/                       — NoLifeNx library
├── thirdparty/                          — GLAD, miniaudio, stb
├── server/                              — Cosmic server (Java, git subtree)
├── tools/                               — wztonx, nxdump, setup scripts
├── docs/                                — Architecture, setup, milestones, reference
├── CMakeLists.txt                       — Client build
└── build/                               — Build output + NX file symlinks
```

## Quick Start (macOS)

```bash
# 1. Install dependencies
brew install cmake ninja glfw freetype lz4 asio

# 2. Build the client
mkdir -p build && cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
ninja

# 3. Set up NX files (see docs/setup/asset-setup.md)
# NX files must be symlinked or copied into build/
# Required: Character.nx, Effect.nx, Etc.nx, Item.nx, Map.nx,
#   Mob.nx, Morph.nx, Npc.nx, Quest.nx, Reactor.nx, Skill.nx,
#   Sound.nx, String.nx, TamingMob.nx, UI.nx

# 4. Run
./cosmic-client
```

See [docs/setup/client-build-macos.md](docs/setup/client-build-macos.md) for detailed build instructions.

## NX Files

The client requires 15 NX files converted from v83 WZ data (defined in [`Util/NxFiles.h`](Util/NxFiles.h)):

| File | Source |
|------|--------|
| Character.nx, Effect.nx, Etc.nx, Item.nx | v83 GMS WZ |
| Map.nx (single file) | v83 GMS WZ |
| Mob.nx, Morph.nx, Npc.nx, Quest.nx | v83 GMS WZ |
| Reactor.nx, Skill.nx, Sound.nx, String.nx | v83 GMS WZ |
| TamingMob.nx, UI.nx | v83 GMS WZ |

NX files are not included in the repository (~6.9GB total). Convert from WZ using `tools/wztonx/` — see [docs/setup/asset-setup.md](docs/setup/asset-setup.md).

## Client Stack

| Layer | Technology |
|-------|-----------|
| Windowing | GLFW 3 |
| Graphics | OpenGL 2.1 via GLAD (Metal backend on macOS) |
| Audio | miniaudio (BGM + SFX via `ma_decoder_init_memory`) |
| Fonts | FreeType |
| Networking | ASIO (header-only, async TCP) |
| NX Data | NoLifeNx (memory-mapped PKG4) |
| Compression | lz4 (NX bitmap decompression) |

## Current Status

**The client is playable.** Login, world select, character select, character creation, and entering the game all work. The server is stock Cosmic v83.

- All 26 UI files ported from v167+ to v83 NX paths
- Audio working (BGM looping + SFX fire-and-forget)
- Full login flow, map loading, combat, mob/NPC spawning
- 3 character creation paths (Explorer, Cygnus, Aran)

See [docs/milestones/overview.md](docs/milestones/overview.md) for the project roadmap.

## Documentation

- **[docs/setup/](docs/setup/)** — Build guides, asset setup, dev environment
- **[docs/architecture/](docs/architecture/)** — System design, protocols, asset pipeline
- **[docs/milestones/](docs/milestones/)** — Project roadmap and phase tracking
- **[docs/reference/](docs/reference/)** — v83 NX paths, opcodes, troubleshooting

## Server

The server is a git subtree of [Cosmic](https://github.com/P0nk/Cosmic) in `server/`. See [server/CLAUDE.md](server/CLAUDE.md) for architecture and deployment.

```bash
cd server
./mvnw clean package
java -jar target/cosmic-*.jar
```

## Credits

- [HeavenClient](https://github.com/HeavenClient/HeavenClient) — Original client (`linux` branch, cross-platform engine)
- [Cosmic](https://github.com/P0nk/Cosmic) — v83 GMS server emulator
- [NoLifeNx](https://github.com/ryantpayton/NoLifeNx) — NX file reader library
- [NoLifeWzToNx](https://github.com/NoLifeDev/NoLifeWzToNx) — WZ-to-NX converter
- MapleStory community — v83 WZ data preservation

## License

[AGPL-3.0](LICENSE)
