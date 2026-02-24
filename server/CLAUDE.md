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

## Upstream Sync

This is a git subtree of P0nk/Cosmic. To pull upstream fixes:

```bash
# From repo root
git subtree pull --prefix=server cosmic-server master --squash
```
