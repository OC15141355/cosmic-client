# TwinleafStory Architecture Overview

## System Diagram

```
┌─────────────────────────────────────────────────┐
│                   Player                         │
│                                                  │
│  ┌──────────────┐         ┌──────────────────┐  │
│  │ Native Client │◄──TCP──►│  Cosmic Server   │  │
│  │  (C++/OpenGL) │  :8484  │  (Java/Maven)    │  │
│  └──────┬───────┘         └────────┬─────────┘  │
│         │                          │             │
│         ▼                          ▼             │
│  ┌──────────────┐         ┌──────────────────┐  │
│  │  NX Files    │         │    MySQL DB      │  │
│  │  (v83 assets)│         │  (game state)    │  │
│  └──────────────┘         └──────────────────┘  │
└─────────────────────────────────────────────────┘
```

## Components

### Client (root directory)
- **Language**: C++17
- **Build**: CMake + Ninja
- **Platform**: macOS ARM64 (primary), Linux, Windows (untested)
- **Graphics**: OpenGL 2.1 via GLAD (Metal backend on macOS)
- **Audio**: miniaudio (BGM looping + SFX fire-and-forget)
- **Networking**: ASIO (async TCP, AES-OFB encrypted)
- **Assets**: NX files (memory-mapped PKG4 via NoLifeNx)

### Server (`server/`)
- **Language**: Java
- **Build**: Maven (`./mvnw clean package`)
- **Origin**: Fork of P0nk/Cosmic (MapleStory v83 emulator)
- **Database**: MySQL
- **Deployment**: Docker on 192.168.0.25

### Tools (`tools/`)
- **wztonx**: WZ/IMG to NX converter (NoLifeWzToNx, AGPL-3.0)
- **nxdump**: NX file structure inspector (custom)
- **scripts**: Asset conversion, symlink setup, dev env bootstrap

## Asset Pipeline

```
Community Repack (.IMG dirs, 6.7GB)
    │
    ▼  tools/wztonx/wztonx -c
    │
NX Files (.nx, 6.9GB) — stored outside git
    │
    ▼  tools/scripts/setup-nx-symlinks.sh
    │
build/*.nx (symlinks) — client reads these at runtime
```

## Network Protocol

- **Version**: MapleStory v83 GMS
- **Encryption**: AES-OFB with MapleStory-specific pre-v118 key
- **Handshake**: 16 bytes (sendiv at [7:11], recviv at [11:15])
- **Port**: 8484 (login), 7575-7577 (channels)

See `docs/reference/opcode-table.md` for the full opcode reference.

## Repo Structure

Client source lives at the repo root (not in a subdirectory) to avoid breaking CMake paths. Server, tools, and docs are added alongside as peer directories.

```
TwinleafStory/
├── Audio/, Character/, Data/, ...   ← Client source (C++)
├── IO/UITypes/                      ← UI screens
├── Net/                             ← Networking + packet handlers
├── server/                          ← Cosmic Java server
├── tools/                           ← Dev tools + scripts
├── docs/                            ← Documentation
├── CLAUDE.md                        ← Client dev context (AI)
└── .cursorrules                     ← Cursor Pro context
```
