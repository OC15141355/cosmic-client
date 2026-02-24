# Phase 1: Client Foundation

**Status**: COMPLETE

## Objective

Get the HeavenClient `linux` branch compiling on ARM64 macOS, establish the asset pipeline from WZ to NX, fix the full login flow for v83, and resolve core client issues (keyboard mapping, audio, Retina display, crashes).

## Tasks

### 1.1 Build System

- [x] ARM64 macOS compilation (191 compilation units)
- [x] CMake with find_package() (no hardcoded paths)
- [x] GLAD OpenGL loader (replaced GLEW)
- [x] miniaudio audio subsystem (replaced dead Alure2)
- [x] All dependencies via Homebrew
- [ ] Windows build (MSVC/MinGW) — untested but should work
- [ ] CI/CD pipeline (GitHub Actions for macOS + Windows)

### 1.2 Asset Pipeline

- [x] WZ-to-NX converter built for macOS (`tools/wztonx/build/wztonx`)
- [x] All 17 v83 WZ files converted to NX format
- [x] NX dumper diagnostic tool (`tools/nxdump/build/nxdump`)
- [ ] Convert community repack WZ/IMG files to NX
- [ ] Automate NX conversion in build pipeline

### 1.3 Login Flow — v83 UI Fixes

- [x] UILogo — click to skip animations
- [x] UILogin — v83 Map.nx paths, login works
- [x] UIWorldSelect — v83 BtWorld/channel paths, Scania renders
- [x] UIWorldSelect — crash fix (disabled opcode 27 handler, draw_world bug fix)
- [x] UICharSelect — v83 rewrite (removed v167+ nodes, TwoSpriteButton pages)
- [x] Audio crash — deferred ma_engine init (CoreAudio thread crash fix)
- [ ] UILogin — fix signboard positioning (slightly off-center)
- [ ] UICharSelect — fine-tune element positions for v83
- [ ] UIRaceSelect — verify v83 compatibility
- [ ] UIExplorerCreation / UIAranCreation / UICygnusCreation — verify v83 paths

### 1.4 Core Client Fixes

- [x] Keyboard mapping — fix Keytable number row shift (DIK_1-0 to GLFW_KEY_1-0)
- [x] In-game opcode stubs — silence 9 unhandled opcodes
- [x] Audio playback — ma_decoder memory pipeline for SFX and BGM
- [x] Retina display — framebuffer viewport fix (glfwGetFramebufferSize)
- [x] Crash handler — SIGSEGV/SIGABRT with backtrace in MapleStory.cpp
- [x] Hair layer warnings — backHairBelowCapNarrow/Wide mapped to BELOWCAP
- [ ] Window icon — create TwinleafStory icon
- [ ] Font rendering — verify all fonts load correctly

## Dependencies

None. This is the foundation phase.

## Key Files

| Area | Files |
|------|-------|
| Build system | `CMakeLists.txt` |
| Login flow | `IO/UITypes/UILogo.cpp`, `IO/UITypes/UILogin.cpp`, `IO/UITypes/UIWorldSelect.cpp`, `IO/UITypes/UICharSelect.cpp` |
| Keyboard | `IO/Keyboard.cpp` |
| Audio | `Audio/Audio.cpp`, `Audio/Audio.h` |
| Crash handler | `MapleStory.cpp` |
| Hair layers | `Character/Hair.cpp` |
| Opcode stubs | `Net/PacketSwitch.cpp`, `Net/Handlers/LoginHandlers.cpp`, `Net/Handlers/PlayerHandlers.cpp` |
| Asset tools | `tools/wztonx/build/wztonx`, `tools/nxdump/build/nxdump` |
