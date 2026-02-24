# Client Architecture

## Tech Stack

| Layer | Technology |
|-------|-----------|
| Windowing | GLFW 3 |
| Graphics | OpenGL 2.1 (Metal backend on macOS) via GLAD |
| Audio | miniaudio (BGM looping + SFX fire-and-forget via ma_decoder_init_memory) |
| Fonts | FreeType |
| Networking | ASIO (header-only, async TCP) |
| NX Files | NoLifeNx (memory-mapped PKG4 reader) |
| Image Loading | stb_image (header-only) |
| Compression | lz4 (NX bitmap decompression) |

## Key Directories

```
Audio/           — Audio subsystem (miniaudio wrapper)
Character/       — Player character: stats, inventory, skills, look
Data/            — Game data structures (items, skills, jobs, weapons)
Gameplay/        — Game logic: Stage, Combat, MapleMap, Physics
Graphics/        — OpenGL renderer, textures, animations, sprites
IO/              — UI framework, keyboard, window management
IO/Components/   — Reusable UI widgets (MapleButton, TwoSpriteButton, Slider, etc.)
IO/UITypes/      — Full UI screens (UILogin, UIWorldSelect, UICharSelect, etc.)
Net/             — Networking: Session, Cryptography, PacketSwitch
Net/Handlers/    — Inbound packet handlers
Net/Packets/     — Outbound packet constructors
Template/        — Generic C++ templates (cache, enums, singletons)
Util/            — NxFiles loader, Configuration, Settings
includes/nlnx/   — NoLifeNx library source
thirdparty/      — GLAD, miniaudio, stb headers
```

## UI State Machine (Login Flow)

```
UILogo → UILogin → UIWorldSelect → UICharSelect → [UIRaceSelect → UIXxxCreation] → Game
```

## Packet Protocol

- **Encryption**: AES-OFB with MapleStory-specific encrypt/decrypt, pre-v118 key
- **Handshake**: 16 bytes — sendiv at [7:11], recviv at [11:15]
- **Version**: MAPLEVERSION = 83
- **Flow**: OutPacket.dispatch() → Session.write() → encrypt → socket
- **Receive**: Session.read() → socket.receive() → process() → PacketSwitch.forward()

See `docs/reference/opcode-table.md` for the full opcode reference.

## Audio Pipeline

```
NX audio data (WAV/MP3 in memory)
    │
    ▼  ma_decoder_init_memory()
    │
ma_decoder (per-track)
    │
    ▼  ma_sound_init_from_data_source()
    │
ma_sound → ma_engine → audio device
```

- **BGM**: Static decoder/sound, looping, stops previous before starting new
- **SFX**: Per-sound decoder, fire-and-forget, cleanup via ma_sound_set_end_callback()
