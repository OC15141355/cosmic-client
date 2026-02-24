# Phase 7: Polish & Distribution

**Status**: PLANNED

## Objective

Prepare the client for distribution: verified Windows build, macOS app bundle, installers, auto-update, performance optimization, and project infrastructure (releases, website, bug tracker). Also address accumulated technical debt.

## Tasks

### 7.1 Cross-Platform

- [ ] Windows build verified and tested
- [ ] macOS .app bundle with proper Info.plist
- [ ] Installer/updater for both platforms
- [ ] Auto-update mechanism

### 7.2 Performance

- [ ] Profile and optimize rendering
- [ ] Optimize NX file loading
- [ ] Memory usage optimization
- [ ] Network latency optimization

### 7.3 Project Infrastructure

- [ ] GitHub releases with pre-built binaries
- [ ] Player-facing website
- [ ] Server status page
- [ ] Bug tracker / issue templates

### 7.4 Technical Debt

- [ ] Remove unused v167+ code paths (currently commented out in some files)
- [ ] Clean up UIWorldSelect.h — remove unused member variables
- [x] Fix `draw_world()` bug: `return` to `continue` for channelcount < 2
- [ ] Remove unused Worlds enum entries (v167+ world IDs)
- [ ] Investigate MoltenVK/Metal path for future macOS OpenGL removal
- [ ] Fix `constexpr char*` warnings in UIItemInventory (should be `const char*`)

## Dependencies

- Phase 1 (Foundation) — build system and CI/CD groundwork.
- Phase 2 (UI Polish) — UI must be finalized before distribution.
- Phase 3 (Gameplay) — gameplay must be solid before release.
- Phase 5 (Server) — server must be ready for players.
- Phase 6 (Content) — custom content should be in place for branded release.

## Key Files

| Area | Files |
|------|-------|
| Build system | `CMakeLists.txt` |
| Entry point | `MapleStory.cpp` |
| Configuration | `Util/Configuration.h` |
| World select (tech debt) | `IO/UITypes/UIWorldSelect.h` |
| Item inventory (tech debt) | `IO/UITypes/UIItemInventory.cpp` |
| NX loader | `Util/NxFiles.cpp`, `includes/nlnx/` |
| Graphics | `Graphics/GraphicsGL.cpp` |
