# PROMPT-00: Windows Devbox Setup — Pull Repo + Prepare for Implementation

## Who You Are

You are Claude Code running on a Windows devbox (192.168.0.194, user: carbyne). This machine has:
- The TwinleafStory repo at `C:\Users\carbyne\Documents\TwinleafStory\`
- The community WZ repack at `C:\Users\carbyne\Documents\CommunityRepack\`
- HaRepacker at `C:\Users\carbyne\Documents\HaRepacker\`
- A shared SMB folder at `C:\Shared\` (accessible from the MacBook at ~/Shared-Win)
- wz.zip (98MB string data archive) at `D:\wz.zip`

## What To Do

### Step 1: Pull the latest repo changes

```powershell
cd C:\Users\carbyne\Documents\TwinleafStory
git fetch origin
git checkout content-dev
git pull origin content-dev
```

This brings in:
- Updated CLAUDE.md files (root, docs/, server/, docs/content-expansion/)
- 8 design documents in `docs/content-expansion/`
- 10 repack audit documents in `docs/content-expansion/audits/`
- 10 implementation prompts in `docs/content-expansion/prompts/`
- The master implementation guide: `docs/content-expansion/IMPLEMENTATION-GUIDE.md`

### Step 2: Read the design context

Read these files to understand the project:
1. `docs/content-expansion/CLAUDE.md` — design briefing, document map, locked decisions
2. `docs/content-expansion/IMPLEMENTATION-GUIDE.md` — the full implementation playbook

### Step 3: Verify the environment

Check that all tools and data sources are accessible:

```powershell
# Repo exists
Test-Path C:\Users\carbyne\Documents\TwinleafStory\CLAUDE.md

# Repack exists
Test-Path C:\Users\carbyne\Documents\CommunityRepack\Mob.wz
Test-Path C:\Users\carbyne\Documents\CommunityRepack\Map.wz
Test-Path C:\Users\carbyne\Documents\CommunityRepack\Character.wz

# wz.zip exists
Test-Path D:\wz.zip

# Shared folder exists
Test-Path C:\Shared\prompts

# Output directories
mkdir -p C:\Shared\output -ErrorAction SilentlyContinue
```

### Step 4: Verify prompt files are on the share

```powershell
ls C:\Shared\prompts\PROMPT-*.md
```

You should see PROMPT-01 through PROMPT-10. These are the implementation prompts you'll execute in order.

### Step 5: Report status

Tell the user:
- Whether the repo pulled successfully and which branch you're on
- Whether the repack, wz.zip, and HaRepacker are all accessible
- Whether the output directory is ready
- That you're ready to start PROMPT-01 (String.wz Merge) on their command

## What NOT To Do

- Do NOT start running prompts yet — wait for the user to say go
- Do NOT SSH anywhere — this machine handles local file extraction only
- Do NOT modify the server directly — outputs go to `C:\Shared\output\` for the MacBook to deploy

## Context: TwinleafStory in 30 Seconds

TwinleafStory is a custom MapleStory v83 private server extended with content from v84-v99+. The design is complete (8 docs, 4 sessions of work). The next phase is **implementation** — extracting content from the community WZ repack, adjusting stats, and producing server-ready XML files that get deployed to the Cosmic server at 192.168.0.25.

You are the extraction machine. The MacBook handles deployment and server SSH.
