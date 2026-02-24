#!/usr/bin/env bash
# Create NX file symlinks in the client build directory.
#
# Usage:
#   ./setup-nx-symlinks.sh <nx_source_dir> [build_dir]
#
# Example:
#   ./setup-nx-symlinks.sh ~/Games/MapleStoryCX/drive_c/MapleStory
#   ./setup-nx-symlinks.sh ~/Games/MapleStoryCX/nx ../../build

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="${2:-$SCRIPT_DIR/../../build}"

if [[ $# -lt 1 ]]; then
    echo "Usage: $0 <nx_source_dir> [build_dir]"
    echo "  nx_source_dir: directory containing .nx files"
    echo "  build_dir: client build directory (default: ../../build)"
    exit 1
fi

NX_DIR="$(cd "$1" && pwd)"

# Required NX files (from Util/NxFiles.h)
NX_FILES=(
    Base.nx Character.nx Effect.nx Etc.nx Item.nx Map.nx Mob.nx
    Morph.nx Npc.nx Quest.nx Reactor.nx Skill.nx Sound.nx
    String.nx TamingMob.nx UI.nx
)

mkdir -p "$BUILD_DIR"

echo "Symlinking NX files from: $NX_DIR"
echo "To build directory: $BUILD_DIR"
echo "---"

missing=0
for nx in "${NX_FILES[@]}"; do
    if [[ -f "$NX_DIR/$nx" ]]; then
        ln -sf "$NX_DIR/$nx" "$BUILD_DIR/$nx"
        echo "  OK: $nx"
    else
        echo "  MISSING: $nx"
        missing=$((missing + 1))
    fi
done

echo "---"
if [[ $missing -gt 0 ]]; then
    echo "WARNING: $missing NX file(s) missing. Client may not start."
    exit 1
else
    echo "All 16 NX files symlinked."
fi
