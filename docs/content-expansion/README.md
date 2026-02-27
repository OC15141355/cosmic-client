# TwinleafStory — Content Expansion

Master plan for taking stock Cosmic v83 and making it our own.

## Design Philosophy

- **Small-group friendly**: 1-6 players is the sweet spot, not 30-man raids
- **Gear as progression**: New areas with new drops are the lever, not wholesale rebalancing
- **Cygnus cap stays 120**: No level 200 for Knights of Cygnus
- **Ultimate vanilla v83**: Polish and extend, don't redesign

## Documents

| Document | Purpose |
|----------|---------|
| [Phase 1: Dev Box Setup](phase-1-devbox-setup.md) | Windows dev machine setup checklist |
| [Boss Audit](boss-audit.md) | Pre-filled boss stats + playtest findings template |
| [Balance Design](balance-design.md) | Rebalancing philosophy, boss tiers, gear progression |
| [WZ Pipeline](wz-pipeline.md) | Tool recommendations, edit → repack → deploy workflow |

## Current Server Config (Key Rates)

From `server/config.yaml`:

| Setting | Value | Notes |
|---------|-------|-------|
| EXP rate | 10x | Per-world setting |
| Meso rate | 10x | |
| Drop rate | 10x | |
| Boss drop rate | 10x | |
| Quest rate | 5x | |
| Channels | 3 | Per world |
| Solo expeditions | OFF | `USE_ENABLE_SOLO_EXPEDITIONS: false` |
| PIC/PIN | Both ON | With expiry bypass (20/15 min) |
| Auto-register | ON | New accounts auto-create |

## Key File Locations

| Asset | Path |
|-------|------|
| Server config | `server/config.yaml` |
| Mob WZ data | `server/wz/Mob.wz/[mobid].img.xml` |
| Map WZ data | `server/wz/Map.wz/Map/Map[0-9]/[mapid].img.xml` |
| Item WZ data | `server/wz/Item.wz/` |
| NPC scripts | `server/scripts/npc/[npcid].js` |
| Quest scripts | `server/scripts/quest/[questid].js` |
| Drop tables | MySQL `drop_data` table on docker-01 (.21) |
| WZ→NX converter | `tools/wztonx/wztonx` |
| NX inspector | `tools/nxdump/build/nxdump` |
| Client NX files | `~/Games/MapleStoryCX/*.nx` |
