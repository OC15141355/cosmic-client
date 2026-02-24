# Phase 4: Audio Polish

**Status**: PARTIAL

## Objective

The audio system is implemented (miniaudio BGM + SFX via memory decoder pipeline). This phase covers testing audio across all game states, handling format edge cases, and adding volume controls.

## Tasks

### 4.1 Audio System — IMPLEMENTED

- [x] ma_engine initialization
- [x] SFX: fire-and-forget via ma_decoder_init_memory + end callback cleanup
- [x] BGM: looping playback with proper stop/start on track change
- [x] BGM: play_once (non-looping) for one-shot tracks

### 4.2 Audio Testing

- [ ] Verify login BGM plays
- [ ] Verify in-game BGM changes per map
- [ ] Verify SFX on button clicks, jumps, attacks
- [ ] Test audio format compatibility (some NX audio may not be WAV)
- [ ] Volume control (SFX and BGM sliders)
- [ ] Verify no audio memory leaks (SFX cleanup via end callbacks)

## Dependencies

- Phase 1 (Foundation) — miniaudio integration and NX file loading must work.
- Phase 3 (Gameplay) — in-game audio testing requires working gameplay (map transitions, combat, NPC interaction).

## Key Files

| Area | Files |
|------|-------|
| Audio engine | `Audio/Audio.cpp`, `Audio/Audio.h` |
| Sound data | `Sound.nx` (NX file, contains all BGM and SFX as audio nodes) |
| Option menu | `IO/UITypes/UIOptionMenu.cpp` (volume sliders) |
