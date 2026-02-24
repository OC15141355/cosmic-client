# wztonx — WZ-to-NX Converter

Converts MapleStory WZ/IMG files to NX (PKG4) format for use with the TwinleafStory client.

Origin: [NoLifeWzToNx](https://github.com/angelsl/NoLifeWzToNx) by Peter Atashian (AGPL-3.0).

## Build

```bash
mkdir build && cd build
cmake ..
make
```

Dependencies: `lz4`, `zlib` (install via `brew install lz4 zlib`).

## Usage

```bash
# Convert a single .wz or .img directory to .nx
./wztonx -c /path/to/Data/UI.wz

# The community repack uses .img directories, not .wz files.
# wztonx handles both formats.
```

## Batch Conversion

Use `../scripts/convert-wz-to-nx.sh` to convert all files from the community repack at once.
