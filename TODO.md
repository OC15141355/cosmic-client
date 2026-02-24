# TwinleafStory — Quick Status

Detailed roadmap: [docs/milestones/overview.md](docs/milestones/overview.md)

## Phase Status

| Phase | Status | Details |
|-------|--------|---------|
| 1. Client Foundation | COMPLETE | [phase-1](docs/milestones/phase-1-foundation.md) |
| 2. UI Polish & Layout | IN PROGRESS | [phase-2](docs/milestones/phase-2-ui-polish.md) |
| 3. Gameplay Verification | NEXT UP | [phase-3](docs/milestones/phase-3-gameplay.md) |
| 4. Audio Polish | PARTIAL | [phase-4](docs/milestones/phase-4-audio.md) |
| 5. Server Fork | NOT STARTED | [phase-5](docs/milestones/phase-5-server.md) |
| 6. Custom Content | NOT STARTED | [phase-6](docs/milestones/phase-6-content.md) |
| 7. Polish & Distribution | NOT STARTED | [phase-7](docs/milestones/phase-7-distribution.md) |

## Immediate Priorities

- [ ] UI layout positioning (status bar, login signboard, char select pixel offsets)
- [ ] Verify all UI screens open without crash via keybindings
- [ ] Gameplay test matrix (walk, attack, skills, NPCs, portals, shops)
- [ ] Wire quickslot handler to UIStatusBar
- [ ] Investigate opcode 26 (unknown server packet)

## Technical Debt

- [ ] Remove unused v167+ code paths (commented out in some files)
- [ ] Clean up UIWorldSelect.h unused member variables
- [ ] Remove unused Worlds enum entries
- [ ] Fix `constexpr char*` warnings in UIItemInventory
- [ ] Investigate MoltenVK/Metal path for future macOS OpenGL deprecation
