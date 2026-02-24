# TwinleafStory Client Roadmap

## Project

TwinleafStory is a custom MapleStory v83 experience: native client (macOS ARM64 + Windows), custom server (Cosmic/HeavenMS fork), curated content from community repack WZ files, and retuned balance for the ultimate vanilla v83 experience.

## Current State (Feb 2026)

The client is playable. Login, world select, character select, and entering the game all work. Character rendering, map loading, combat, mob/NPC spawning, and packet handling are 95%+ complete. Audio plays via miniaudio (BGM + SFX).

## Phase Summary

| Phase | Status | Description |
|-------|--------|-------------|
| [Phase 1: Client Foundation](phase-1-foundation.md) | COMPLETE | Build system, asset pipeline, login flow, core client fixes |
| [Phase 2: UI Polish & Layout](phase-2-ui-polish.md) | IN PROGRESS | Layout positioning fixes, UI screen verification, missing v83 features |
| [Phase 3: Gameplay Verification](phase-3-gameplay.md) | NEXT | Core gameplay testing, packet handler wiring, full game test matrix |
| [Phase 4: Audio Polish](phase-4-audio.md) | PARTIAL | Audio system implemented; testing and edge cases remain |
| [Phase 5: Server Fork](phase-5-server.md) | PLANNED | Fork Cosmic to TwinleafStory, configure rates, import content |
| [Phase 6: Custom Content](phase-6-content.md) | PLANNED | Visual updates, quality of life improvements, balance patches |
| [Phase 7: Polish & Distribution](phase-7-distribution.md) | PLANNED | Cross-platform builds, performance, project infrastructure, tech debt |

## Content Pipeline

```
WZ Files (community repack / custom)
    | wztonx converter
NX Files (client game data)
    | symlink to build/
Client Binary (cosmic-client)

Server Data (HeavenMS .sql / .xml)
    | import
Database (PostgreSQL on docker-01)
    |
Server Binary (Java, on 192.168.0.25)
```

## Key Files & Tools

| Item | Location |
|------|----------|
| Client source | ~/Projects/cosmic-client/ |
| NX files | ~/Projects/cosmic-client/build/*.nx |
| WZ source | ~/Games/MapleStoryCX/drive_c/MapleStory/*.wz |
| Community repack | ~/Downloads/Community Repack  .IMG/Data/ |
| WZ-to-NX converter | /tmp/wztonx-build/wztonx |
| NX dumper | /tmp/nxdump/build/nxdump |
| Cosmic server | 192.168.0.25:8484 |
| Server VM | homelab@192.168.0.25 (via ProxyJump core-01) |
