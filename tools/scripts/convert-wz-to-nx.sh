#!/usr/bin/env bash
# Batch convert all WZ/IMG files from the community repack to NX format.
#
# Usage:
#   ./convert-wz-to-nx.sh <source_dir> <output_dir>
#
# Example:
#   ./convert-wz-to-nx.sh ~/Downloads/"Community Repack  .IMG"/Data ~/Games/MapleStoryCX/nx
#
# Requires: wztonx binary built in ../wztonx/build/

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
WZTONX="${SCRIPT_DIR}/../wztonx/build/wztonx"

if [[ $# -lt 2 ]]; then
    echo "Usage: $0 <source_dir> <output_dir>"
    echo "  source_dir: directory containing .wz or .img files/dirs"
    echo "  output_dir: where to write .nx files"
    exit 1
fi

SOURCE_DIR="$1"
OUTPUT_DIR="$2"

if [[ ! -x "$WZTONX" ]]; then
    echo "Error: wztonx not found at $WZTONX"
    echo "Build it first: cd ../wztonx && mkdir build && cd build && cmake .. && make"
    exit 1
fi

mkdir -p "$OUTPUT_DIR"

echo "Converting WZ/IMG files from: $SOURCE_DIR"
echo "Output directory: $OUTPUT_DIR"
echo "---"

for entry in "$SOURCE_DIR"/*; do
    name="$(basename "$entry")"
    echo "Converting: $name"
    (cd "$OUTPUT_DIR" && "$WZTONX" -c "$entry") || echo "  WARNING: Failed to convert $name"
done

echo "---"
echo "Done. NX files in: $OUTPUT_DIR"
ls -lh "$OUTPUT_DIR"/*.nx 2>/dev/null || echo "No .nx files found (check for errors above)"
