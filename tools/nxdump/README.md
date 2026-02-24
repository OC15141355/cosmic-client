# nxdump — NX File Structure Inspector

Diagnostic tool for inspecting NX file node structure. Essential for v83 path verification when porting UI code.

## Build

```bash
mkdir build && cd build
cmake ..
make
```

Dependencies: `lz4` (install via `brew install lz4`). Uses NoLifeNx headers from `../../includes/nlnx/`.

## Usage

```bash
# Dump a node tree (default depth 2)
./nxdump /path/to/UI.nx Login.img/CharSelect

# Dump deeper (depth 4)
./nxdump /path/to/UI.nx Login.img/CharSelect 4

# Dump entire .img root
./nxdump /path/to/UI.nx Login.img 1
```

## When to Use

**Always run nxdump before writing code that references NX node paths.** v83 NX structure differs significantly from v167+. Verify that the nodes you need actually exist.
