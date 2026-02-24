# TwinleafStory Documentation

Project documentation for TwinleafStory — custom MapleStory v83 private server + native client.

## Structure

```
docs/
├── architecture/    — System design, component relationships, protocols
├── setup/           — Build guides, asset setup, dev environment
├── milestones/      — Project roadmap, phase tracking
└── reference/       — v83 NX paths, opcodes, troubleshooting
```

## Conventions

- **File naming**: kebab-case, `.md` extension
- **Style**: Technical, concise, code examples where appropriate
- **Tables**: Use markdown tables for structured data (opcodes, paths, comparisons)
- **Milestone format**: Status, Objective, Tasks (checkbox), Dependencies, Key Files
- **Cross-references**: Link between docs using relative paths

## Content Sources

Most documentation is extracted and reorganized from the root `CLAUDE.md` (client context) and `TODO.md` (roadmap). When updating docs, keep the source files in sync — the root CLAUDE.md is the authoritative reference for client development, while docs/ provides organized standalone references.
