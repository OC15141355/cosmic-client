# TwinleafStory Server (Cosmic Fork)

Fork of [P0nk/Cosmic](https://github.com/P0nk/Cosmic) — MapleStory v83 GMS server emulator.

## Quick Start

```bash
cd server
./mvnw clean package
java -jar target/cosmic-*.jar
```

Or via Docker: `docker-compose up -d`

## Architecture

Java server with Maven build. Key packages:

```
src/main/java/
├── client/           — Client sessions, characters, inventory management
├── config/           — Server config loading (config.yaml)
├── constants/net/    — SendOpcode.java (S→C) + RecvOpcode.java (C→S)
├── database/         — Database access (MySQL)
├── net/server/
│   ├── handlers/     — Packet handler implementations
│   │   └── login/    — Login flow (auth, charlist, char creation)
│   └── coordinator/
│       └── session/  — Session management, HWID validation (Hwid.java)
├── provider/         — WZ XML data providers (map, item, quest data)
├── scripting/        — NPC/quest/event JavaScript scripts
├── server/           — Server lifecycle, worlds, channels
├── service/          — Business logic
└── tools/
    └── PacketCreator.java  — Constructs all server→client packets
```

## Key Files

| File | Purpose |
|------|---------|
| `constants/net/SendOpcode.java` | Server→client opcode enum |
| `constants/net/RecvOpcode.java` | Client→server opcode enum |
| `tools/PacketCreator.java` | Packet construction (all S→C packets) |
| `net/server/coordinator/session/Hwid.java` | HWID format validation |
| `net/server/handlers/login/` | Login/charlist/char creation handlers |
| `config.yaml` | Server configuration (rates, DB, ports) |
| `database/cosmic.sql` | Database schema |
| `scripts/` | NPC dialogue and event scripts (JavaScript) |
| `wz/` | Server-side WZ XML data |

## Configuration

`config.yaml` — key settings:
- `server.host` / `server.port`: Listen address (default: 0.0.0.0:8484)
- `server.channel_ports`: Channel ports (default: 7575-7577)
- `database.*`: MySQL connection
- `server.exp_rate` / `server.meso_rate` / `server.drop_rate`: Game rates

## Protocol Reference

See `../docs/reference/opcode-table.md` for the full v83 opcode tables.

### HWID Validation

Client sends HWID as `[0-9A-F]{12}_[0-9A-F]{8}` (MAC_SerialReversed).
- MAC: 12 hex chars from network adapter
- Serial: 8 hex chars from volume serial, byte-reversed
- Validated in `Hwid.java` via regex
- Invalid → opcode 9, error code 17

### PIC / PIN

Two separate auth systems:
- **PIN** (opcodes 6/7): Login-level. Usually disabled on private servers.
- **PIC** (opcodes 28-30): Character-select level.
  - `require_pic=0` → client registers PIC (opcode 29)
  - `require_pic=1` → client sends existing PIC (opcode 30)
  - `require_pic=2` → no PIC needed (opcode 19)

### Character Creation

Client sends CreateCharPacket with job type:
- `0` = Cygnus Knight
- `1` = Explorer
- `2` = Aran

## Deployment

Current: Docker on 192.168.0.25 (Proxmox VM, accessible via ProxyJump through core-01).

```bash
ssh -J kumo@192.168.0.105 homelab@192.168.0.25
docker ps | grep cosmic   # verify running
docker logs cosmic         # check server logs
```

## TwinleafStory Design Decisions (Implementation-Impacting)

These are locked design decisions from Sessions 3-4. Full design docs are in `../docs/content-expansion/`.

### Character Creation — Block CK/Aran

CK (job type 0) and Aran (job type 2) creation must be blocked. Explorers only (job type 1).

**Where to implement**: `net/server/handlers/login/CreateCharHandler.java` (or similar). Reject or return error for job types 0 and 2. Alternatively, modify the CK/Aran creation NPC scripts to refuse.

### Trade Button → Kerning Night Market

The client's Free Market / Trade button should warp to map **103000007** (Kerning Night Market) instead of the FM. This is a client-side change, but the map must exist and be accessible on the server.

### Solo Expeditions

Already enabled: `USE_ENABLE_SOLO_EXPEDITIONS: true` in config.yaml. Players can attempt all bosses solo.

### Temple of Time Kill Quests: 999 → 100

Find and edit quest scripts that require 999 kills per stage. Change to 100.

**Where**: `scripts/quest/` — search for `999` in files related to Temple of Time, Memory, Regret, Oblivion. Also check `wz/Quest.wz/` for hardcoded values.

### Boss HP Rebalancing

Edit mob XMLs in `wz/Mob.wz/` for existing bosses. Key targets:

| Boss | Mob ID | Current HP | Target HP |
|------|--------|-----------|-----------|
| Zakum Body 2 | 8800002 | 110M | 30M |
| Zakum Body 1 | 8800000 | 66M | 20M |
| Zakum Arms | 8800003-8800010 | 22-33M | 8M each |
| Horntail Heads | 8810000, 8810002 | 330M | 80M |
| Horntail Pivot | 8810018 | 2.09B | 200M |
| Pink Bean | 8820001 | 2.1B | 500M |
| Papulatus | 8500001 | 23M | 10M |
| Pianus A/B | 8510000/8520000 | 30M/24M | 12M/10M |

Full targets in `../docs/content-expansion/balance-design.md`.

### Token Currencies — New ETC Items

Three new ETC items need creating:
- **Von Leon Coins** — dropped by LHC mobs (1-3 per kill) and Von Leon (10 per kill). Used at LHC vendor for Von Leon Set pieces (~50 coins per piece).
- **Soul Shards** — dropped by Future Ereve mobs and Empress (3-5 per kill). Used at Ereve vendor for Empress Set pieces (~10 shards per piece).
- **Arcane Tokens** — dropped by Arcane River mobs and Guardian. Used at M4 vendor. (Phase 4)

These need: ETC item IDs, String.wz entries, drop_data table entries, and NPC exchange scripts.

### Zone Completion Vendors

~20+ NPC scripts needed, each with unlock conditions. See `../docs/content-expansion/world-design.md` for the full vendor table. Each zone has a completion condition (quest, boss kill, exploration) that unlocks a vendor selling level-appropriate gear.

### 4.5 Skills — CK/Aran/DB Skill ID Ranges

Custom 4.5 job skills reuse CK/Aran/DB skill IDs. The client already has animations for these:

| Explorer Branch | Animation Source | Skill ID Range |
|----------------|-----------------|----------------|
| Warriors | Dawn Warrior + Aran | 1100-1111.img, 2100-2112.img |
| Mages | Blaze Wizard (element-reskinned) | 1200-1211.img |
| Bowmen | Wind Archer | 1300-1311.img |
| Thieves | Night Walker + Katara sprites | 1400-1411.img |
| Pirates | Thunder Breaker | 1500-1511.img |

Server-side implementation needs custom skill handlers (Java) that use these skill IDs but with new damage/effect logic. Full specs in `../docs/content-expansion/twinleaf-skills.md`.

### Universal Skill Changes

- **Maple Warrior** → auto-passive at Lv 120 (not a hotbar skill)
- **Hero's Will** → quest-granted auto-cleanse at Lv 140+
- **All Boosters** → baked into Mastery passives (remove booster skills)
- **30+ dead skills cut** — see `../docs/content-expansion/twinleaf-skills.md`

### New Content Bosses (Import from Repack)

| Boss | Mob IDs | Level | Target HP | Party |
|------|---------|-------|-----------|-------|
| Chaos Zakum | 8800100-8800116 | 120 | 200M total | 4-6 |
| Von Leon | 8840000-8840002 | 125 | 500M | 3-6 |
| Empress Cygnus | 8850000-8850011 | 140 | 1.5B (Empress) | 4-6 |
| Corrupted ToT | 8220016-8220021 | 110-120 | 250K-5M | Solo |

## Implementation Guide

For the full implementation playbook (phases, prompts, deploy steps), see `../docs/content-expansion/IMPLEMENTATION-GUIDE.md`. The design docs directory (`../docs/content-expansion/`) has its own CLAUDE.md with a complete document map.

## Upstream Sync

This is a git subtree of P0nk/Cosmic. To pull upstream fixes:

```bash
# From repo root
git subtree pull --prefix=server cosmic-server master --squash
```
