# Quick Start

Get TwinleafStory running in 15 minutes.

## Prerequisites

- macOS (ARM64 or Intel) with Xcode Command Line Tools
- Homebrew
- v83 WZ/IMG files (community repack) OR pre-converted NX files

## 1. Clone and Install Dependencies

```bash
git clone git@github.com:OC15141355/TwinleafStory.git
cd TwinleafStory
brew install cmake ninja glfw freetype lz4 asio zlib
```

## 2. Build the Client

```bash
mkdir -p build && cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
ninja
```

## 3. Set Up Assets

If you have pre-converted NX files:

```bash
cd ..
tools/scripts/setup-nx-symlinks.sh /path/to/your/nx/files
```

If you have the community repack WZ/IMG files:

```bash
# Build the converter first
cd tools/wztonx && mkdir build && cd build && cmake .. && make && cd ../../..

# Convert all files
tools/scripts/convert-wz-to-nx.sh \
  ~/Downloads/"Community Repack  .IMG"/Data \
  ~/Games/TwinleafStory/nx

# Symlink into build
tools/scripts/setup-nx-symlinks.sh ~/Games/TwinleafStory/nx
```

## 4. Run

```bash
cd build
./cosmic-client
```

The client connects to the server configured in `build/Settings` (generated on first run). Default: `192.168.0.25:8484`.

## Next Steps

- See [client-build-macos.md](client-build-macos.md) for detailed build options
- See [asset-setup.md](asset-setup.md) for asset management details
- See [server-setup.md](server-setup.md) for running your own server
- See [dev-environment.md](dev-environment.md) for IDE setup with Claude Code / Cursor Pro
