# TwinleafStory Client — Project Roadmap

## Project Overview

TwinleafStory is a custom MapleStory v83 experience with:
- **Native client** (macOS ARM64 + Windows) — fork of HeavenClient `linux` branch
- **Custom server** — fork of Cosmic/HeavenMS (Java)
- **Curated content** — community repack WZ files + custom additions
- **Balanced gameplay** — retuned for a "perfect vanilla" experience

---

## Current State (Feb 2026)

**The client is playable.** Login → world select → character select → enter game all work. Character rendering, map loading, combat, mob/NPC spawning, and packet handling are 95%+ complete. Audio now plays (BGM + SFX via miniaudio memory decoder pipeline).

### What Works
- Full login flow (UILogo → UILogin → UIWorldSelect → UICharSelect → Game)
- All 22+ UI screens ported from v167+ to v83 NX paths
- UIStatusBar, UIKeyConfig, UIQuit, UIChatBar, UIOptionMenu — v83 rewrites complete
- UIQuestLog, UISkillBook, UIStatsInfo, UIItemInventory, UIUserList — v83 intermediate node fixes
- UIChat disabled (v83 has no socialChatEnter), UIEvent rewritten for MapleEvent
- UIWorldMap rewritten (no search panel in v83)
- UIShop, UIMiniMap, UIChannel, UICharInfo, UILoginNotice, UINpcTalk — path fixes
- UIEquipInventory, UINotice, UIJoypad, UIBuffList, UIStatusMessenger — working
- Map/Equip/Item/Skill tooltips — working
- Audio: BGM looping + SFX fire-and-forget via ma_decoder_init_memory pipeline
- Map loading, mob/NPC rendering, combat/skills, portals — all working
- All critical opcodes handled, 9 stubs (quickslot, auto-pot, buddy, family, etc.)

### What Needs Work
- UI layout positioning (status bar, login signboard, char select — hardcoded pixel offsets need tuning)
- Quickslot handler parsed but not wired to UI
- Some v167+ button names may still not match v83 (invisible = safe, but missing functionality)
- Audio format edge cases (NX audio is mostly WAV/MP3 but some may fail to decode)

---

## Phase 1: Client Foundation — COMPLETE

### 1.1 Build System
- [x] ARM64 macOS compilation (191 compilation units)
- [x] CMake with find_package() (no hardcoded paths)
- [x] GLAD OpenGL loader (replaced GLEW)
- [x] miniaudio audio subsystem (replaced dead Alure2)
- [x] All dependencies via Homebrew
- [ ] Windows build (MSVC/MinGW) — untested but should work
- [ ] CI/CD pipeline (GitHub Actions for macOS + Windows)

### 1.2 Asset Pipeline
- [x] WZ-to-NX converter built for macOS (`/tmp/wztonx-build/wztonx`)
- [x] All 17 v83 WZ files converted to NX format
- [x] NX dumper diagnostic tool (`/tmp/nxdump/build/nxdump`)
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
- [x] Keyboard mapping — fix Keytable number row shift (DIK_1-0 → GLFW_KEY_1-0)
- [x] In-game opcode stubs — silence 9 unhandled opcodes
- [x] Audio playback — ma_decoder memory pipeline for SFX and BGM
- [x] Retina display — framebuffer viewport fix (glfwGetFramebufferSize)
- [x] Crash handler — SIGSEGV/SIGABRT with backtrace in MapleStory.cpp
- [x] Hair layer warnings — backHairBelowCapNarrow/Wide mapped to BELOWCAP
- [ ] Window icon — create TwinleafStory icon
- [ ] Font rendering — verify all fonts load correctly

---

## Phase 2: UI Polish & Layout — IN PROGRESS

### 2.1 Layout Fixes (requires visual testing)
- [ ] UIStatusBar — HP/MP gauge positions, button alignment, number font positions
- [ ] UILogin — signboard centering offset
- [ ] UICharSelect — element positions (v167+ layout assumptions)
- [ ] UIEquipInventory — minor asset position offsets

### 2.2 UI Screens Verification
Test each keybinding opens a working UI with no crashes:

| Key | UI Screen | Status |
|-----|-----------|--------|
| `j` | Quest Log | Fixed (v83 flat structure) |
| `k` | Skills | Fixed (v83 flat structure) |
| `s` | Stats | Fixed (v83 flat structure) |
| `i` | Items | Fixed (v83 button names) |
| `.` | Friends/Party | Fixed (v83 flat structure) |
| `c` | Maple Chat | Disabled (no v83 equivalent) |
| `w`/`n` | World Map | Fixed (no search panel) |
| `v` | Event | Fixed (MapleEvent) |
| `e` | Equipment | Working |
| `F12` | Key Config | Working |
| ESC | Quit Menu | Working (GameMenu) |
| Tab | Chat Bar | Working |

### 2.3 Missing v83 Features
- [ ] Investigate what v83 had for "Maple Chat" key (if anything)
- [ ] Verify all MapleButton nodes actually exist vs are invisibly null
- [ ] Run nxdump on each UI node to catalogue what v83 actually provides

---

## Phase 3: Gameplay Verification — NEXT UP

### 3.1 Core Gameplay
- [ ] Character movement and physics
- [ ] Monster spawning and AI patterns
- [ ] Combat: melee, ranged, magic damage
- [ ] Skill effects rendering and hitboxes
- [ ] Item drops and pickup
- [ ] NPC interaction and dialogue trees
- [ ] Shop buying/selling
- [ ] Portal/map transitions
- [ ] Channel switching

### 3.2 Packet Handlers
- [x] All critical opcodes handled (see CLAUDE.md for full table)
- [ ] QUICKSLOT_INIT — wire parsed data to UIStatusBar quickslot display
- [ ] AUTO_HP/MP_POT — store auto-potion configuration
- [ ] BUDDYLIST — wire to UIUserList friend tab
- [ ] SET_NPC_SCRIPTABLE — mark NPCs as interactable
- [ ] Fix opcode 26 (unknown — investigate what server sends it)
- [ ] Verify character stats parsing edge cases
- [ ] Verify inventory modification edge cases
- [ ] Verify skill/buff packet timing

### 3.3 Full Game Test Matrix
- [ ] Walk, jump, attack, use skills
- [ ] Talk to NPCs, complete dialogue
- [ ] Open shop, buy/sell items
- [ ] Use portals, change maps
- [ ] Equip/unequip items
- [ ] Use scrolls on equipment
- [ ] Party system
- [ ] Boss fights (Zakum/HT)
- [ ] PQ entry
- [ ] Change channel
- [ ] Cash shop entry
- [ ] Character creation flow

---

## Phase 4: Audio Polish

### 4.1 Audio System — IMPLEMENTED
- [x] ma_engine initialization
- [x] SFX: fire-and-forget via ma_decoder_init_memory + end callback cleanup
- [x] BGM: looping playback with proper stop/start on track change
- [x] BGM: play_once (non-looping) for one-shot tracks

### 4.2 Audio Testing
- [ ] Verify login BGM plays
- [ ] Verify in-game BGM changes per map
- [ ] Verify SFX on button clicks, jumps, attacks
- [ ] Test audio format compatibility (some NX audio may not be WAV)
- [ ] Volume control (SFX and BGM sliders)
- [ ] Verify no audio memory leaks (SFX cleanup via end callbacks)

---

## Phase 5: Server Fork — TwinleafStory Server

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

---

## Phase 6: Custom Content

### 6.1 Visual Updates
- [ ] Custom login screen (TwinleafStory branded)
- [ ] Custom hairstyles and equipment sprites
- [ ] Updated NPC appearances
- [ ] Custom background music

### 6.2 Quality of Life
- [ ] Improved inventory management
- [ ] Quick-slot improvements (wire QUICKSLOT_INIT to UI)
- [ ] Chat improvements
- [ ] Minimap enhancements

### 6.3 Balance Patches
- [ ] Class rebalancing (all classes viable)
- [ ] Boss difficulty tuning
- [ ] Item stat adjustments
- [ ] Skill damage formulas
- [ ] EXP curve adjustments

---

## Phase 7: Polish & Distribution

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

---

## Technical Debt

- [ ] Remove unused v167+ code paths (currently commented out in some files)
- [ ] Clean up UIWorldSelect.h — remove unused member variables
- [x] Fix `draw_world()` bug: `return` → `continue` for channelcount < 2
- [ ] Remove unused Worlds enum entries (v167+ world IDs)
- [ ] Investigate MoltenVK/Metal path for future macOS OpenGL removal
- [ ] Fix `constexpr char*` warnings in UIItemInventory (should be `const char*`)

---

## Content Pipeline

```
WZ Files (community repack / custom)
    ↓ wztonx converter
NX Files (client game data)
    ↓ symlink to build/
Client Binary (cosmic-client)

Server Data (HeavenMS .sql / .xml)
    ↓ import
Database (PostgreSQL on docker-01)
    ↓
Server Binary (Java, on 192.168.0.25)
```

---

## Key Files & Tools

| Item | Location |
|------|----------|
| Client source | ~/Projects/cosmic-client/ |
| NX files | ~/Projects/cosmic-client/build/*.nx |
| WZ source | ~/Games/MapleStoryCX/drive_c/MapleStory/*.wz |
| Community repack | ~/Downloads/Community Repack  .IMG/Data/ |
| WZ→NX converter | /tmp/wztonx-build/wztonx |
| NX dumper | /tmp/nxdump/build/nxdump |
| Cosmic server | 192.168.0.25:8484 |
| Server VM | homelab@192.168.0.25 (via ProxyJump core-01) |

---

## v83 UI Fixes Applied (Complete Reference)

### Files Modified for v83 Compatibility (26 files total)

**Top-level .img path fixes (UIWindow2→UIWindow, etc.):**
UIItemInventory, UISkillBook, UIQuestLog, UIUserList, UIMiniMap,
UIWorldMap, UIChannel, UICharInfo, UIChat, UIEvent, UILoginNotice,
MapTooltip, UINpcTalk, UIEquipInventory, UIStatsInfo, UIShop

**Structural rewrites (StatusBar3→StatusBar, etc.):**
UIStatusBar, UIKeyConfig, UIChatBar, UIOptionMenu, Slider, UIQuit

**Internal node structure fixes (removed v167+ intermediates):**
| File | v167+ Path | v83 Path | Fix |
|------|-----------|---------|-----|
| UIQuestLog | Quest/list/backgrnd | Quest/backgrnd | Removed `list` intermediate |
| UISkillBook | Skill/main/backgrnd | Skill/backgrnd | Removed `main` intermediate |
| UIStatsInfo | Stat/main/backgrnd | Stat/backgrnd | Removed `main`+`detail` |
| UIItemInventory | Item/BtCoin3 | Item/BtCoin | Renamed buttons (3→unnumbered) |
| UIUserList | UserList/Main/backgrnd | UserList/backgrnd | Removed `Main` intermediate |
| UIChat | socialChatEnter | N/A | Disabled (doesn't exist in v83) |
| UIWorldMap | WorldMap/WorldMapSearch | N/A | Removed search (doesn't exist in v83) |
| UIEvent | EventList/main | MapleEvent | Renamed + simplified |

**Cosmetic fixes:**
| File | Fix |
|------|-----|
| Hair.cpp | Added backHairBelowCapNarrow/Wide → BELOWCAP mappings |
| PlayerHandlers.cpp | QuickSlotInitHandler now parses flag + 8 int32 keys |
| Audio.cpp | Full ma_decoder memory pipeline (BGM + SFX) |
