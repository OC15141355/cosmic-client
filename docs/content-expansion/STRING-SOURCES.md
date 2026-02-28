# TwinleafStory — String Data Sources
*Generated: 2026-02-27*

## Summary

**Great news**: The wz.zip on the T7 SSD (D:\wz.zip, 98MB) contains a significantly more comprehensive String.wz than what the server currently has. This is our primary string source.

---

## wz.zip String Data — What We Found

### File Comparison

| File | Server | wz.zip | Winner |
|------|--------|--------|--------|
| Eqp.img.xml | 835 KB | **3,239 KB** | wz.zip (4x larger — has all post-v83 equipment) |
| Mob.img.xml | 142 KB | 158 KB | wz.zip (has boss names) |
| Map.img.xml | 758 KB | 706 KB | Server (already more complete for maps) |
| Npc.img.xml | 2,408 KB | 2,458 KB | wz.zip (slightly more complete) |
| Etc.img.xml | 502 KB | 1,327 KB | wz.zip (much more) |

### Content Confirmed in wz.zip Mob.img.xml

All critical boss mob names are present:

```
8800100: Chaos Zakum
8800101: Chaos Zakum
8800102: Chaos Zakum
8800103: Chaos Zakum Arm 1
8800104: Chaos Zakum Arm 2
8800105: Chaos Zakum Arm 3
8800106: Chaos Zakum Arm 4
8800107: Chaos Zakum Arm 5
8800108: Chaos Zakum Arm 6
8800109: Chaos Zakum Arm 7
8800110: Chaos Zakum Arm 8
8800111: Chaos Boogie
8800112: Chaos Puko
8800113: Chaos Poonko
8800114: Chaos Kusko

8840000: Von Leon

8850000–8850004: Mihile, Oz, Irena, Eckhart, Hawkeye (commanders)
8850005–8850009: Same (powered-up forms)
8850010: Shinsoo
8850011: Cygnus (Empress)

8645000: Cygnus Support Troops
8645009: Guard Captain Darknell
```

### Content Confirmed in wz.zip Eqp.img.xml

All target equipment sets are named:

**Von Leon Armor Sets**:
- Lionheart (Warrior): Helm 1003172, Cape 1102275, Gloves 1082295, Mail 1052314, Boots 1072485
- Dragon Tail (Mage): Helm 1003173, Cape 1102276, Gloves 1082296, Robe 1052315
- Falcon Wing (Archer): Hat 1003174, Cape 1102277, Gloves 1082297, Suit 1052316, Boots 1072487
- Raven Horn (Thief): Hat 1003175, Cape 1102278, Gloves 1082298, Armor 1052317, Boots 1072488
- Shark Tooth (Pirate): Hat 1003176, Cape 1102279, Gloves 1082299, Coat 1052318, Boots 1072489

**Von Leon Belts**: 1132094–1132109 (various quality tiers)
**Von Leon Accessories**: 1142500 "Mystic Von Leon's Nightmare"

**Empress Gear**:
- 1003159: Empress's Fine Hat
- 1003160: Empress's Brilliant Hat
- 1082290: Empress's Fine Gloves
- 1082291: Empress's Brilliant Gloves

**Timeless/Reverse Gear** (level 120): Fully named (Timeless Pendant, Moonlight Cape, Bergamot/Hermosa/Presto Gloves, etc.)

---

## How to Apply the wz.zip String Data

### Step 1: Replace Eqp.img.xml (SAFE — additive)
The wz.zip Eqp.img.xml is 4x larger and a strict superset of the server's. It includes all v83 items plus post-v83.

```bash
# Backup and replace
cp server/wz/String.wz/Eqp.img.xml server/wz/String.wz/Eqp.img.xml.v83-backup
# Extract from wz.zip
unzip -o D:/wz.zip "wz/String.wz/Eqp.img.xml" -d /tmp/wzextract/
cp /tmp/wzextract/wz/String.wz/Eqp.img.xml server/wz/String.wz/Eqp.img.xml
```

### Step 2: Merge Mob.img.xml (careful — server may have custom entries)
The wz.zip Mob.img.xml has boss names we need (Chaos Zakum, Von Leon, Cygnus). The server's Mob.img.xml might have custom NPC mobs added. Do a diff first:

```bash
diff server/wz/String.wz/Mob.img.xml /tmp/wzextract/wz/String.wz/Mob.img.xml
```

Manually add the missing high-ID boss entries to the server's version. They will be entries like:
```xml
<imgdir name="8800100"><string name="name" value="Chaos Zakum"/></imgdir>
```

### Step 3: Check Etc.img.xml (wz.zip is 2.6x larger)
The Etc items likely include new quest items and crafting materials for post-v83 content. Safe to replace after backup.

---

## GitHub Sources (for future reference)

Based on research, the best community sources for MapleStory string data:

### Primary: wz.zip on T7 (already have this!)
- ✅ **Has all string data we need for v96-v99 content**
- Located at D:\wz.zip (98MB)
- Dated October 2024

### Secondary: GitHub Repositories

| Repo | URL | Coverage | Has String XML? |
|------|-----|----------|-----------------|
| P0nk/Valhalla | github.com/P0nk/Valhalla | v200+ | Possibly — check /wz dir |
| SwordieMS/Swordie | github.com/SwordieMS/Swordie | v179+ | Possibly — check /data dir |
| ronancpl/HeavenMS | github.com/ronancpl/HeavenMS | v83 | No (compiled WZ only) |
| TEAM-SPIRIT-Productions/Cosmic | github.com/TEAM-SPIRIT-Productions/Cosmic | v83 | No |

### Tool: HaRepacker Resurrected
For extracting string data directly from any WZ file:
- URL: https://github.com/lastbattle/Harepacker-resurrected/releases
- Install to: C:\Users\carbyne\Documents\HaRepacker\
- Use "GMS (old)" encryption for v83 files
- Can export any WZ file to XML format

### How to get later-version String.wz
If you need content beyond what wz.zip covers:
1. Get a copy of GMS v120 or KMS v120 client (the .wz files)
2. Open String.wz with HaRepacker
3. Export to XML (Private Server format)
4. Replace/merge with server's String.wz files

Community repack's String folder (binary .img files) appears to be v83-era data — it does NOT contain the post-v83 strings. The wz.zip is the better source.

---

## String Entries Still Needed

These were NOT found in wz.zip and may need manual creation or a later-version client:

1. **LHC map portal/area names** — The server's Map.img.xml already has these (confirmed: "Desolate Moor", "Castle Entrance", etc.)
2. **Empress equipment body/boots/cape** — Helm and gloves confirmed, other slots may need extraction from Character.wz
3. **Quest text** for LHC and GttF access quests — Needs custom scripting regardless
4. **NPC names** for new LHC/GttF NPCs — Can be added manually to Npc.img.xml

---

## Immediate Action

**Right now, without any additional tools**: Replace `server/wz/String.wz/Eqp.img.xml` with the wz.zip version. This gives the server string data for ALL Von Leon and Empress equipment that will be added later, at zero risk.

```bash
# On the server machine (192.168.0.25) or pre-deploy:
unzip -o D:/wz.zip "wz/String.wz/Eqp.img.xml" -d /tmp/
# Copy to server WZ location after backup
```
