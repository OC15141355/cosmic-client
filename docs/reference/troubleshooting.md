# Troubleshooting Guide

## Crash Debugging

The client has a built-in crash handler (`MapleStory.cpp`) that prints a stack trace on SIGSEGV/SIGABRT:

```
=== CRASH (signal 11) ===
0   cosmic-client    0x00000001001234  crash_handler + 40
1   libsystem_platform.dylib  ...
...
```

**How to use**: Just run `./cosmic-client` — crashes print the backtrace to stderr automatically. Pipe to a file with `./cosmic-client 2>crash.log` to capture.

For more detail, attach lldb:
```bash
lldb ./cosmic-client
(lldb) run
# after crash:
(lldb) bt        # full backtrace with line numbers
(lldb) frame 0   # inspect crash frame
```

## Common Crash Patterns

| Symptom | Likely Cause | Fix |
|---------|-------------|-----|
| Crash on startup before window | Missing NX files in build/ | Symlink all 15 .nx files |
| Crash in `ma_node_input_bus_read_pcm_frames` | miniaudio engine running without audio data | Don't call `ma_engine_init()` until playback is implemented |
| Crash after UI transition (login -> world) | v167+ NX path accessed on v83 data | Use nxdump to verify paths, rewrite for v83 |
| Crash in `Texture::draw` or `Sprite::draw` | NX node resolved to invalid bitmap | Check that node exists before creating Texture/Sprite |
| Crash in constructor (segfault) | MapleButton given empty/null NX node | Verify `normal/0`, `pressed/0`, `mouseOver/0` children exist |
| `terminate called after throwing` | nlnx threw on missing node | Wrap in try/catch or check node validity first |

## NX Path Debugging

When a UI screen crashes or renders wrong, the issue is almost always a v167+ NX path that doesn't exist in v83. Workflow:

1. **Identify the file**: crash backtrace -> which UIType constructor/draw
2. **Dump the v83 NX structure**:
   ```bash
   tools/nxdump/build/nxdump build/UI.nx Login.img/CharSelect 3
   tools/nxdump/build/nxdump build/Map.nx Obj/login.img/CharSelect 3
   ```
3. **Compare with code**: look for node paths in the .cpp that don't match the dump
4. **Fix paths**: update to match v83 structure, add `// v83:` comment

## Null NX Node Safety

When an NX node doesn't exist, `nl::node` returns a null/empty node. These are **safe** to pass to:
- `Sprite(node)` -> empty sprite (no-op draw)
- `Texture(node)` -> empty texture (no-op draw)
- `Animation(node)` -> empty animation
- `Charset(node, ...)` -> empty charset

These are also **safe** (verified in `MapleButton.cpp`):
- `MapleButton(node)` -> null node produces empty textures (no-op draw, zero-size bounds)

These are **NOT safe**:
- `NameTag(node)` -> crashes on missing bitmap children
- Indexing into null node children that are then dereferenced

## Server Connection Issues

- **Timeout on connect**: Verify Cosmic is running: `ssh -J kumo@192.168.0.105 homelab@192.168.0.25` -> `docker ps | grep cosmic`
- **Handshake fails**: Check MAPLEVERSION (must be 83) in `Net/Session.cpp`
- **Opcode not handled**: `PacketSwitch.cpp` logs unhandled opcodes — check if the opcode needs a handler or can be safely ignored
- **Packet parse crash**: Server sends unexpected format — add recv bytes logging to trace

## Audio

Audio engine is fully working via `ma_decoder_init_memory()` pipeline:
- **BGM**: `Music::play()` decodes NX audio from memory, plays with `ma_sound_set_looping(MA_TRUE)`. Static `bgm_decoder`/`bgm_sound`/`bgm_active` manage current track. Stops previous BGM before starting new one.
- **BGM (once)**: `Music::play_once()` — same but without looping (for one-shot tracks).
- **SFX**: `Sound::play()` creates per-sound `ma_decoder` + `ma_sound` from cached audio data. Fire-and-forget with `ma_sound_set_end_callback()` for cleanup (deletes decoder + sound when done).
- **Engine**: `ma_engine_init()` runs in `Music::init()`. Non-fatal on failure (game works without audio).
- **Cleanup**: `Sound::close()` stops BGM, uninits engine, clears caches.
