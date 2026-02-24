# Phase 3: Gameplay Verification

**Status**: NEXT

## Objective

Systematically verify all core gameplay systems work end-to-end: movement, combat, NPCs, shops, portals, channels, and all remaining packet handlers. Wire stubbed opcodes to their UI counterparts.

## Tasks

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

## Dependencies

- Phase 1 (Foundation) — client must build and connect to server.
- Phase 2 (UI Polish) — UI screens should be functional before gameplay testing reveals UI-related issues.

## Key Files

| Area | Files |
|------|-------|
| Packet switch | `Net/PacketSwitch.cpp` |
| Login handlers | `Net/Handlers/LoginHandlers.cpp` |
| Player handlers | `Net/Handlers/PlayerHandlers.cpp` |
| Map object handlers | `Net/Handlers/MapObjectHandlers.cpp` |
| Inventory handlers | `Net/Handlers/InventoryHandlers.cpp` |
| NPC handlers | `Net/Handlers/NpcInteractionHandlers.cpp` |
| Combat | `Gameplay/Combat/` |
| Stage / map | `Gameplay/Stage.cpp`, `Gameplay/MapleMap/` |
| Character | `Character/` |
| Status bar (quickslot) | `IO/UITypes/UIStatusBar.cpp` |
| User list (buddy) | `IO/UITypes/UIUserList.cpp` |
| Shop | `IO/UITypes/UIShop.cpp` |
| NPC talk | `IO/UITypes/UINpcTalk.cpp` |
