# Packet Protocol

See `docs/reference/opcode-table.md` for the full opcode tables.

## Encryption

- **Algorithm**: AES-OFB with MapleStory-specific encrypt/decrypt
- **Key**: Pre-v118 key (hardcoded in `Net/Cryptography/`)
- **Version**: MAPLEVERSION = 83
- **Handshake**: 16 bytes — sendiv at offset [7:11], recviv at offset [11:15]

## Packet Format

### Outbound (Client → Server)

```
[2 bytes: length] [2 bytes: opcode] [N bytes: payload]
```

Constructed via `OutPacket` classes in `Net/Packets/`, dispatched through `Session.write()`.

### Inbound (Server → Client)

```
[2 bytes: length] [2 bytes: opcode] [N bytes: payload]
```

Received by `Session.read()`, decrypted, routed by `PacketSwitch.forward()` to registered handlers.

## Handler Registration

Handlers are registered in `Net/PacketSwitch.cpp` by opcode number:

```cpp
emplace<LoginResultHandler>(0);       // LOGIN_RESULT
emplace<ServerStatusHandler>(3);      // SERVERSTATUS
emplace<ServerlistHandler>(10);       // SERVERLIST
emplace<CharlistHandler>(11);         // CHARLIST
// etc.
```

## Login Flow

```
Client                              Server
  │                                   │
  ├─── LoginPacket (op 1) ──────────►│
  │                                   │
  │◄── LOGIN_RESULT (op 0) ──────────┤
  │                                   │
  ├─── ServerlistRequest (op 11) ───►│
  │                                   │
  │◄── SERVERLIST (op 10) ───────────┤
  │                                   │
  ├─── CharlistRequest (op 5) ──────►│
  │                                   │
  │◄── CHARLIST (op 11) ─────────────┤
  │                                   │
  ├─── SelectCharPic (op 30) ───────►│
  │                                   │
  │◄── SERVER_IP (op 12) ────────────┤
  │                                   │
  ├─── PlayerLogin (op 20) ─────────►│
  │                                   │
  │◄── SET_FIELD (op 125) ───────────┤
```

## Character Creation Flow

```
Client                              Server
  │                                   │
  ├─── NameCharPacket (op ?) ───────►│
  │                                   │
  │◄── CHARNAME_RESPONSE (op 13) ────┤
  │                                   │
  ├─── CreateCharPacket (op ?) ─────►│
  │    (job type: 0=Cygnus,           │
  │     1=Explorer, 2=Aran)           │
  │                                   │
  │◄── ADD_NEWCHAR_ENTRY (op 14) ────┤
```

## Key Source Files

| File | Purpose |
|------|---------|
| `Net/PacketSwitch.cpp` | Opcode → handler registration |
| `Net/Session.cpp` | TCP connection, encrypt/decrypt |
| `Net/Cryptography/` | AES-OFB implementation |
| `Net/Handlers/LoginHandlers.cpp` | Login flow handlers |
| `Net/Packets/LoginPackets.h` | Login outbound packets |
| `server/constants/net/SendOpcode.java` | Server-side opcode enum |
| `server/constants/net/RecvOpcode.java` | Server-side opcode enum |
| `server/tools/PacketCreator.java` | Server packet construction |
