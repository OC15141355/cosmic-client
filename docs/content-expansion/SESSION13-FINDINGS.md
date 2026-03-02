# Session 13 — ROOT CAUSE FOUND & FIXED

## Root Cause: Client String.wz Missing Mob Names

The v83 client crashes when it receives a spawn packet for a mob ID that has **no entry in the client-side String.wz/Mob.img**. We patched String.wz on the SERVER (PROMPT-01) but never on the CLIENT.

### Evidence Chain

| Test | String.wz | Mob.wz | Result |
|------|-----------|--------|--------|
| `!spawn 9300348` (vanilla mob) | Has entry ("Giant") | Has .img | ✅ Works |
| `!spawn 8210000` (LHC mob) | NO entry | Has .img (patched) | ❌ Crash |
| `!spawn 8210000` (LHC mob) | NO entry | NO .img (vanilla) | ❌ Crash |
| `!spawn 8888888` (fake mob) | N/A | Has .img | ✅ No crash (server has no data → no spawn packet) |
| **`!spawn 8210000` after String.wz patch** | **Has entry ("Castle Golem")** | **Has .img** | **✅ WORKS!** |

### What was NOT the problem (ruled out in Sessions 10-13)
- Canvas Format 2 (BGRA8888) — conversion still needed but wasn't the crash cause
- `_hash` properties — stripping still needed but wasn't the crash cause
- listWz vs standard-zlib encoding — irrelevant to crash
- Map.wz broken from previous sessions — wasn't causing the crash
- WzPatcher pipeline — proven working (9300348 --replace test passes)

### What IS still needed (and applied)
- **Format 2→1 conversion**: Required for v83 client to render post-v83 sprites correctly
- **_hash stripping**: Required because v83 parser doesn't understand this property
- **Client String.wz patching**: **THE ROOT CAUSE** — 80 mob names added

## Fix Applied: Client String.wz Patched

Tool: `C:\Shared\output\tools\string-patcher\`

Added 80 mob name entries to `C:\Users\carbyne\Documents\MapleStory\String.wz`:

| Content | Mob IDs | Count |
|---------|---------|-------|
| LHC mobs | 8210000-8210013 | 9 |
| Chaos Zakum | 8800100-8800116 | 17 |
| Corrupted ToT | 8220016-8220021 | 6 |
| Singapore/Ulu | 9420514-9420526 | 11 |
| Von Leon | 8840000-8840002 | 3 |
| Future Ereve | 8600000-8610014 | 22 |
| Empress | 8850000-8850011 | 12 |

## Still TODO: Map Names in String.wz

The client String.wz/Map.img is also missing entries for our post-v83 maps. Warping to these maps will likely crash the client the same way mob spawns did.

Missing map ranges:
- **LHC**: 211060000-211070110 (28 maps)
- **Future Ereve**: 271000000-271040300 (42 maps)
- **Ulu City**: 541020000-541020800 (30 maps)

These need to be added to String.wz/Map.img before the maps will work.

## Still TODO: Re-patch ALL WZ Files

Current state:
- **String.wz**: ✅ Patched (80 mob names, needs map names still)
- **Mob.wz**: Only has 8210000 — needs ALL batches re-applied
- **Map.wz**: Vanilla — needs ALL batches re-applied
- **Sound.wz**: Session 9 patches (BGM only, no canvases — probably fine)

Re-patching plan:
1. Restore vanilla Mob.wz from backup
2. Run batches 1-6 (CZak, ToT, LHC, Singapore, FE, Empress mobs)
3. Restore vanilla Map.wz from backup (already done)
4. Run batches 7-14 (LHC maps, SG maps, FE maps, tiles, backs, objs, BGM, MapHelper)

## No Server-Side Changes Needed

All fixes are CLIENT-SIDE (String.wz, Mob.wz, Map.wz patching). The server-side mob XMLs, map XMLs, and deployments from Sessions 7-9 are all correct.

## New Tools Created

| Tool | Path | Purpose |
|------|------|---------|
| string-check | `C:\Shared\output\tools\string-check\` | Verify String.wz entries for mob/map IDs |
| string-patcher | `C:\Shared\output\tools\string-patcher\` | Add mob/map names to client String.wz |

## Key Learning

When adding post-v83 content to a v83 private server, you must patch THREE things on the CLIENT:
1. **Content WZ files** (Mob.wz, Map.wz, Sound.wz) — the actual sprites/maps/audio
2. **String.wz** — mob names, map names (client crashes without these!)
3. **Format compatibility** — convert Format 2→1 canvases, strip modern properties
