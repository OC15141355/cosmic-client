# TwinleafStory Changelog
*This file records all server changes made to the TwinleafStory project*

---

## 2026-02-27

### Server Config Changes

#### Enabled Solo Expeditions
**File**: `server/config.yaml` line 267
```yaml
# Before:
USE_ENABLE_SOLO_EXPEDITIONS: false

# After:
USE_ENABLE_SOLO_EXPEDITIONS: true
```
**Reason**: The server is designed for 1-6 players. Having solo expeditions disabled forces group play even when solo, which is not the design intent. This also bypasses the Zakum pre-quest, allowing testing without running through the entire questline.

**Effect**: Players can now start expeditions (Zakum, Horntail, etc.) alone or in small groups of any size. The Zakum pre-quest can be skipped.

**Requires server restart**: YES

---

#### Nerfed Showa Town Boss Defense
**File**: `server/wz/Mob.wz/9400300.img.xml`
```xml
<!-- Before: -->
<int name="PDDamage" value="5000"/>
<int name="MDDamage" value="4300"/>

<!-- After: -->
<int name="PDDamage" value="1500"/>
<int name="MDDamage" value="1500"/>
```
**Reason**: The Showa Boss (mob ID 9400300, "Yakuza Boss") had physical defense of 5000 and magic defense of 4300. At pre-Big Bang damage formulas, defense above ~2000 means most players deal 1 damage per hit. This made the boss effectively impossible for level 75-100 characters. The boss's HP is 150M (reasonable for this tier), but the defense made it a wall.

Setting both to 1500 aligns with other content-appropriate bosses in the same level range (Papulatus PDDef=1000, Pianus PDDef=1150).

**Effect**: Players at level 80+ with decent gear should be able to deal meaningful damage to Showa Boss.

**Requires server restart**: YES (WZ data is loaded at startup)

---

### Research Completed

A full investigation of the Community Repack (D:\CommunityRepack on T7 SSD) vs server WZ data was completed. Key findings documented in:

- `C:\Shared\REPACK-ANALYSIS.md` — Full comparison (523 extra mobs, 579 extra maps)
- `C:\Shared\CONTENT-PORT-PLAN.md` — Milestone-by-milestone port plan
- `C:\Shared\STRING-SOURCES.md` — String data sources (wz.zip is the key source)
- `C:\Shared\EXP-CURVE-ANALYSIS.md` — EXP system analysis and curve design

**Summary of repack findings**:
- Chaos Zakum mob data: ✅ Present (8800100–8800116)
- Von Leon mob data: ✅ Present (8840000–8840002)
- Empress Cygnus mob data: ✅ Present (8850000–8850011)
- LHC maps: ✅ Present (211060000–211070110, 28 maps)
- Future Ereve maps: ✅ Present (271000000–271040300, 42 maps)
- String data for all above: ✅ Available in wz.zip String.wz

---

### Tools

#### HaRepacker Installation
Latest version (v8.0.0) available at https://github.com/lastbattle/Harepacker-resurrected/releases
Download the `HaRepacker_win-x64.zip`, extract to `C:\Users\carbyne\Documents\HaRepacker\`
Use "GMS (old)" encryption when opening v83 WZ files.

---

## Pending Changes (Not Yet Applied)

### SQL Changes Needed (run on 192.168.0.21)

None yet — pending milestone implementation.

---

## Planned Changes

### Next Session
1. Extract LHC map XMLs from repack using HaRepacker → add to server/wz/Map.wz/
2. Add LHC mob XMLs with tuned stats → server/wz/Mob.wz/
3. Add Chaos Zakum mob XMLs with tuned stats
4. Replace server/wz/String.wz/Eqp.img.xml with wz.zip version
5. Merge new mob names into String.wz/Mob.img.xml

### Future
- Von Leon boss fight implementation
- Empress Cygnus boss fight
- Von Leon and Empress equipment set
- EXP table tuning (optional, pending playtesting)
