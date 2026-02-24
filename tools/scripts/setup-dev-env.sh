#!/usr/bin/env bash
# Full development environment bootstrap for TwinleafStory.
# Installs dependencies, builds tools, and sets up the client build directory.
#
# Usage:
#   ./setup-dev-env.sh
#
# Run from anywhere — paths are relative to the script location.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$SCRIPT_DIR/../.."

echo "=== TwinleafStory Development Environment Setup ==="
echo ""

# Step 1: Install Homebrew dependencies
echo "--- Step 1: Installing dependencies via Homebrew ---"
brew install cmake ninja glfw freetype lz4 asio zlib 2>/dev/null || true
echo ""

# Step 2: Build wztonx
echo "--- Step 2: Building wztonx ---"
mkdir -p "$REPO_ROOT/tools/wztonx/build"
(cd "$REPO_ROOT/tools/wztonx/build" && cmake .. && make)
echo ""

# Step 3: Build nxdump
echo "--- Step 3: Building nxdump ---"
mkdir -p "$REPO_ROOT/tools/nxdump/build"
(cd "$REPO_ROOT/tools/nxdump/build" && cmake .. && make)
echo ""

# Step 4: Build client
echo "--- Step 4: Building client ---"
mkdir -p "$REPO_ROOT/build"
(cd "$REPO_ROOT/build" && cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug .. && ninja)
echo ""

echo "=== Setup complete ==="
echo ""
echo "Next steps:"
echo "  1. Convert WZ files to NX (if not already done):"
echo "     $SCRIPT_DIR/convert-wz-to-nx.sh <wz_source_dir> <output_dir>"
echo "  2. Symlink NX files into build/:"
echo "     $SCRIPT_DIR/setup-nx-symlinks.sh <nx_dir>"
echo "  3. Run the client:"
echo "     cd $REPO_ROOT/build && ./cosmic-client"
