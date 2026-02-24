# Development Environment

TwinleafStory is developed using AI-assisted tools alongside traditional IDEs.

## AI-Assisted Development

### Claude Code (CLI)

Claude Code reads `CLAUDE.md` files automatically. The repo has a hierarchy:
- `CLAUDE.md` (root) — project vision, client architecture, v83 reference
- `server/CLAUDE.md` — Cosmic server context
- `tools/CLAUDE.md` — tool usage and asset pipeline
- `docs/CLAUDE.md` — documentation conventions

When working in the repo, Claude Code loads the relevant CLAUDE.md based on your working directory.

### Cursor Pro

Cursor reads `.cursorrules` at the project root. This provides a compact summary of conventions — tech stack, coding rules, git workflow. For deeper context, Cursor can read the CLAUDE.md files.

`.cursorignore` excludes large binary files and build artifacts from indexing.

## IDE Setup

### CLion / VS Code

Standard CMake project. Open the root directory, let the IDE detect `CMakeLists.txt`.

Build configuration:
- Generator: Ninja
- Build type: Debug
- Build directory: `build/`

### Debugging

The client has a built-in crash handler that prints stack traces on SIGSEGV/SIGABRT. For detailed debugging:

```bash
lldb ./build/cosmic-client
(lldb) run
# after crash:
(lldb) bt        # full backtrace
(lldb) frame 0   # inspect crash frame
```

## Git Workflow

### Branch Naming

```
feature/client-*    — client features
feature/server-*    — server features
fix/*               — bug fixes
docs/*              — documentation changes
```

### Commit Prefixes

```
[client] Fix UIStatusBar HP gauge positioning
[server] Configure custom EXP rates
[tools]  Add batch NX conversion script
[docs]   Update Phase 3 milestone status
```
