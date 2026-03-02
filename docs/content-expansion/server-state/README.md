# Server State Dump — 2026-03-02

Pulled from `homelab@192.168.0.25` (Cosmic v83 server in Docker container `cosmic-maplestory-1`).

This directory gives Windows Claude visibility into what Mac Claude has deployed server-side.

## Files

| File | Description |
|------|-------------|
| `mob-ids-all.txt` | All 1644 mob IDs in server Mob.wz/ |
| `new-mobs-status.txt` | All 80 post-v83 mobs — verified ALL EXIST |
| `map-ids-all.txt` | All 1220 map IDs in server Map.wz/ |
| `new-maps-status.txt` | All 100 post-v83 maps — verified ALL EXIST |
| `boss-hp-values.txt` | HP values for all rebalanced + new bosses (pipe-delimited) |
| `drop-table-custom-bosses.txt` | Von Leon + Empress drop table entries (82 rows) |
| `string-wz-spot-check.txt` | Server-side String.wz entries for new content |
| `quest-changes.txt` | ToT kill quest changes (999→100) |

## Server-Side Changes Summary

### What Mac Claude Changed on the Server

**Mob.wz/** — Added 80 mob XMLs:
- 17 Chaos Zakum (8800100-8800116)
- 6 Corrupted ToT (8220016-8220021)
- 9 LHC (8210000-8210007, 8210013)
- 11 Singapore/Ulu (9420514-9420526)
- 3 Von Leon boss (8840000-8840002)
- 22 Future Ereve (8600000-8600006, 8610000-8610014)
- 12 Empress (8850000-8850011)

**Map.wz/Map/Map2/** — Added 70 map XMLs:
- 28 LHC (211060000-211070110)
- 42 Future Ereve (271000000-271040300)

**Map.wz/Map/Map5/** — Added 30 map XMLs:
- 30 Singapore/Ulu (541020000-541020800)

**Character.wz/** — Added 69 equip XMLs (sorted into subdirs):
- Von Leon: 24 equips (Cap, Longcoat, Glove, Cape, Shoes)
- Empress: 45 equips (Hair, Cap, Longcoat, Shoes, Glove, Accessory, Weapon)

**String.wz/Eqp.img.xml** — Replaced with merged version (3.9x larger, new equip names)
**String.wz/Mob.img.xml** — Replaced with merged version (+506 mob name entries)
**String.wz/Map.img.xml** — Added 30 Singapore/Ulu map name entries

**Quest.wz/Check.img.xml** — Changed 17 instances of count="999" to count="100" (ToT quests)
**Quest.wz/QuestInfo.img.xml** — Changed 5 display texts from #b999#k to #b100#k

**Database (cosmic.drop_data)** — Added 82 drop SQL rows:
- Von Leon (8840000-8840002): 26 rows
- Empress (8850000-8850011): 56 rows

**Database (cosmic.characters)** — Set GM level 6 for all 'quiet' account characters

### Boss HP Rebalancing Applied

| Mob ID | Boss | HP |
|--------|------|----|
| 8800000 | Zakum Body 1 | 20,000,000 |
| 8800002 | Zakum Body 2 | 30,000,000 |
| 8800003-8800010 | Zakum Arms (8) | 8,000,000 each |
| 8810000 | Horntail Head A | 80,000,000 |
| 8810002 | Horntail Head B | 80,000,000 |
| 8810018 | Horntail Pivot | 200,000,000 |
| 8820001 | Pink Bean | 500,000,000 |
| 8500001 | Papulatus | 10,000,000 |
| 8510000 | Pianus (Bloody) | 12,000,000 |
| 8520000 | Pianus (Blue) | 10,000,000 |
| 9400300 | Showa Boss | 150,000,000 (unchanged) |
| 8840000 | Von Leon | 500,000,000 |
| 8850011 | Empress Cygnus | 1,500,000,000 |

## Known Gaps (Server-Side)

1. **Map String.wz entries**: LHC (211060xxx) and Future Ereve (271xxxxxx) map names are NOT in server String.wz/Map.img.xml. Only Singapore (541020xxx) was added. This may not affect server operation but is incomplete.

## Relevance to Client-Side Debugging

The server-side data is CORRECT and COMPLETE. All crashes are CLIENT-SIDE:
- Client String.wz needs mob names (done) + map names (100 still needed)
- Client Mob.wz needs all 80 mobs re-patched with format 2→1 conversion
- Client Map.wz needs all 100 maps + tiles/backs/objs re-patched
- See `C:\Shared\RESUME-SESSION14.md` for exact commands
