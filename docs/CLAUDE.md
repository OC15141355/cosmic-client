# TwinleafStory Documentation

Project documentation for TwinleafStory — custom MapleStory v83 private server + native client.

## Structure

```
docs/
├── architecture/        — System design, component relationships, protocols
├── content-expansion/   — Game design docs (8 design docs + 10 audits + 10 prompts)
│   ├── audits/          — Repack data audits (mobs, maps, skills, items, NPCs)
│   ├── prompts/         — Self-contained prompts for Windows devbox Claude
│   └── CLAUDE.md        — Design context briefing (start here for game design)
├── setup/               — Build guides, asset setup, dev environment
├── milestones/          — Project roadmap, phase tracking
└── reference/           — v83 NX paths, opcodes, troubleshooting
```

## Content Expansion (Game Design)

The `content-expansion/` directory contains the complete TwinleafStory game design — created across Sessions 1-4. It has its own `CLAUDE.md` with a full document map and locked design decisions.

**Key documents:**
- `TWINLEAF-DESIGN-DOC.md` — master design overview, vision, decision log
- `IMPLEMENTATION-GUIDE.md` — phase-by-phase implementation playbook
- `world-design.md` — all zones, vendors, NPCs, cosmetics (largest doc, ~69KB)
- `quest-design.md` — quest chains, NPC dialogue
- `twinleaf-skills.md` — 48 custom 4.5 job skills
- `balance-design.md` — boss HP targets, gear progression

**Audit subdirectory** (`audits/`): 10 documents covering mobs, maps, equipment, skills, chairs, cash shop, quests, NPCs, and comprehensive Session 4 findings.

**Prompts subdirectory** (`prompts/`): 10 self-contained prompt files (PROMPT-01 through PROMPT-10) for extracting repack content on the Windows devbox.

Design is **complete and implementation-ready** as of Session 4 (2026-02-28).

## Conventions

- **File naming**: kebab-case, `.md` extension
- **Style**: Technical, concise, code examples where appropriate
- **Tables**: Use markdown tables for structured data (opcodes, paths, comparisons)
- **Milestone format**: Status, Objective, Tasks (checkbox), Dependencies, Key Files
- **Cross-references**: Link between docs using relative paths

## Content Sources

Most documentation is extracted and reorganized from the root `CLAUDE.md` (client context) and `TODO.md` (roadmap). When updating docs, keep the source files in sync — the root CLAUDE.md is the authoritative reference for client development, while docs/ provides organized standalone references.
