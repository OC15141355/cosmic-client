# Phase 5: Server Fork — TwinleafStory Server

**Status**: PLANNED

## Objective

Fork the Cosmic/HeavenMS server into the TwinleafStory server repository. Configure rates, branding, and spawn settings. Import community repack data and verify all maps, NPCs, quests, and boss encounters function correctly.

## Tasks

### 5.1 Repository Setup

- [ ] Fork Cosmic/HeavenMS to TwinleafStory server repo
- [ ] Create CLAUDE.md for server repo
- [ ] Document server architecture and packet protocol
- [ ] Set up dev environment on 192.168.0.25

### 5.2 Server Configuration

- [ ] Rename to TwinleafStory branding
- [ ] Configure rates (EXP, drop, meso)
- [ ] Configure spawn rates
- [ ] Review and adjust class balance
- [ ] Custom welcome messages and NPCs

### 5.3 Content Integration

- [ ] Import community repack data files
- [ ] Verify all maps load correctly
- [ ] Verify all NPCs function
- [ ] Verify all quests work
- [ ] Test all boss encounters

## Dependencies

- Phase 1 (Foundation) — client must connect to server for testing.
- Phase 3 (Gameplay) — client gameplay should be verified before server-side tuning, so issues can be attributed to the correct side.

## Key Files

| Area | Location |
|------|----------|
| Current server | Cosmic v83 at 192.168.0.25:8484 |
| Server VM | homelab@192.168.0.25 (via ProxyJump core-01) |
| Cosmic source | [P0nk/Cosmic](https://github.com/P0nk/Cosmic) on GitHub |
| Server opcodes | `constants/net/SendOpcode.java`, `constants/net/RecvOpcode.java` |
| Packet creators | `tools/PacketCreator.java` |
| Login handlers | `net/server/handlers/login/` |
| HWID validation | `net/server/coordinator/session/Hwid.java` |
| Community repack | ~/Downloads/Community Repack  .IMG/Data/ |
