# Phase 6: Custom Content

**Status**: PLANNED

## Objective

Layer custom content on top of the working v83 base: TwinleafStory branding, visual updates, quality-of-life improvements, and balance patches to make all classes viable and the gameplay experience polished.

## Tasks

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

## Dependencies

- Phase 3 (Gameplay) — core gameplay must be verified before balance tuning.
- Phase 4 (Audio) — audio system needed for custom BGM.
- Phase 5 (Server) — server fork must exist for rate/balance configuration.

## Key Files

| Area | Files |
|------|-------|
| Login screen | `IO/UITypes/UILogin.cpp`, `IO/UITypes/UILogo.cpp` |
| Status bar (quickslot) | `IO/UITypes/UIStatusBar.cpp` |
| Inventory | `IO/UITypes/UIItemInventory.cpp` |
| Minimap | `IO/UITypes/UIMiniMap.cpp` |
| Chat | `IO/UITypes/UIChat.cpp`, `IO/UITypes/UIChatBar.cpp` |
| Character sprites | `Character/` directory |
| NX data files | `build/*.nx` (would need custom NX builds) |
| Server balance | Server-side Java config (rates, formulas, spawn tables) |
