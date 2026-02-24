# Client Build — macOS

## Dependencies

```bash
brew install cmake ninja glfw freetype lz4 asio
```

| Dependency | Purpose |
|-----------|---------|
| cmake | Build system generator |
| ninja | Fast build tool |
| glfw | Windowing and input |
| freetype | Font rendering |
| lz4 | NX bitmap decompression |
| asio | Async TCP networking (header-only) |

OpenGL is provided by macOS (Metal backend via GLAD loader).
Audio uses miniaudio (bundled in `thirdparty/`).

## Build

```bash
cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
ninja
```

Build output: `build/cosmic-client` (16 MB Mach-O ARM64 executable).

## Configuration

### Compile-time: `Configuration.h`
- `USE_ASIO`: Enable ASIO networking (default: on)
- `USE_CRYPTO`: Enable packet encryption (default: on)

### Runtime: `build/Settings`
Generated after first run. Key settings:
- `ServerIP` / `ServerPort`: Server address (default: 192.168.0.25:8484)
- `Fullscreen`: Window mode (default: false)
- `VSync`: Vertical sync (default: true)
- `BGMVolume` / `SFXVolume`: Audio levels (0-100, default: 50)

## Required Files in build/

- 16 NX files (see `Util/NxFiles.h` for the list)
- `fonts/` directory (symlinked automatically from source)

## Known Warnings

The build produces pre-existing deprecation warnings:
- `std::iterator` deprecated in C++17 (from `Template/EnumMap.h`)
- `!this` undefined behavior (from `Template/EnumMap.h`)

These are inherited from HeavenClient upstream and don't affect functionality.
