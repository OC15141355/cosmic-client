# Phase 2: UI Polish & Layout

**Status**: IN PROGRESS

## Objective

Fix remaining UI layout positioning issues (hardcoded pixel offsets from v167+ assumptions) and verify every UI screen keybinding opens without crashes. Catalogue what v83 NX data actually provides versus what the code expects.

## Tasks

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

## Dependencies

- Phase 1 (Foundation) — all login flow and core fixes must be in place.

## Key Files

| Area | Files |
|------|-------|
| Status bar | `IO/UITypes/UIStatusBar.cpp` |
| Login | `IO/UITypes/UILogin.cpp` |
| Char select | `IO/UITypes/UICharSelect.cpp` |
| Equipment | `IO/UITypes/UIEquipInventory.cpp` |
| Quest log | `IO/UITypes/UIQuestLog.cpp` |
| Skills | `IO/UITypes/UISkillBook.cpp` |
| Stats | `IO/UITypes/UIStatsInfo.cpp` |
| Items | `IO/UITypes/UIItemInventory.cpp` |
| Friends/Party | `IO/UITypes/UIUserList.cpp` |
| Chat | `IO/UITypes/UIChat.cpp` |
| World map | `IO/UITypes/UIWorldMap.cpp` |
| Event | `IO/UITypes/UIEvent.cpp` |
| Key config | `IO/UITypes/UIKeyConfig.cpp` |
| Quit menu | `IO/UITypes/UIQuit.cpp` |
| Chat bar | `IO/UITypes/UIChatBar.cpp` |
| NX dumper | `tools/nxdump/build/nxdump` |
