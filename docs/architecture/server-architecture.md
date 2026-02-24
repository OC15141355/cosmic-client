# Server Architecture

## Overview

TwinleafStory server is a fork of [Cosmic](https://github.com/P0nk/Cosmic), a MapleStory v83 GMS server emulator. Written in Java, built with Maven.

## Tech Stack

| Component | Technology |
|-----------|-----------|
| Language | Java 17 |
| Build | Maven (wrapper: `./mvnw`) |
| Database | MySQL 8.0 |
| Scripting | JavaScript (Nashorn/GraalJS for NPC scripts) |
| Deployment | Docker + docker-compose |

## Key Directories

```
server/
├── src/main/java/
│   ├── client/              — Client session, character, inventory
│   ├── config/              — Server configuration loading
│   ├── constants/
│   │   └── net/
│   │       ├── SendOpcode.java   — Server→client opcode enum
│   │       └── RecvOpcode.java   — Client→server opcode enum
│   ├── database/            — Database access layer
│   ├── model/               — Game models (maps, items, quests)
│   ├── net/
│   │   └── server/
│   │       ├── handlers/    — Packet handler implementations
│   │       │   └── login/   — Login flow handlers
│   │       └── coordinator/ — Session management, HWID
│   ├── provider/            — Data providers (WZ XML data)
│   ├── scripting/           — NPC/quest/event scripts
│   ├── server/              — Server lifecycle, channels, worlds
│   ├── service/             — Business logic services
│   └── tools/
│       └── PacketCreator.java  — Server→client packet construction
├── database/                — SQL schema files
├── scripts/                 — NPC/event JavaScript scripts
├── wz/                      — Server-side WZ XML data (small, in git)
├── config.yaml              — Server configuration
├── pom.xml                  — Maven build file
└── docker-compose.yml       — Docker deployment
```

## Handler Chain

```
Client TCP packet
    │
    ▼  Decrypt (AES-OFB)
    │
    ▼  PacketProcessor.processPacket()
    │
    ▼  Route by opcode (RecvOpcode)
    │
    ▼  Handler.handlePacket(client, packet)
    │
    ▼  Business logic (update state, DB)
    │
    ▼  PacketCreator.createResponse()
    │
    ▼  Encrypt + send (SendOpcode)
```

## HWID Validation

Cosmic validates client HWID as `[0-9A-F]{12}_[0-9A-F]{8}`:
- First part: 12 hex chars from network MAC address
- Second part: 8 hex chars from volume serial (byte-reversed)
- Validation in: `net/server/coordinator/session/Hwid.java`
- Invalid HWID → server sends opcode 9, error code 17

## PIC / PIN System

Two separate authentication systems:

**PIN** (login-level, opcodes 6/7): Usually disabled on private servers.

**PIC** (character-select, opcodes 28-30): `require_pic` from charlist response:
- `0` = PIC needs to be registered → RegisterPicPacket (opcode 29)
- `1` = PIC required → SelectCharPicPacket (opcode 30)
- `2` = No PIC → SelectCharPacket (opcode 19)

## Database

MySQL schema in `database/cosmic.sql`. Key tables:
- `accounts` — Login credentials, HWID, ban status
- `characters` — Character data, stats, position
- `inventoryitems` — Item storage
- `skills` — Learned skills and levels
- `keymap` — Keyboard bindings per character
