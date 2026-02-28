# Boss Audit — TwinleafStory v83

*Last updated: 2026-02-28 (Session 4 — new content bosses added)*

Stock Cosmic boss stats extracted from `server/wz/Mob.wz/` XML data, plus new content boss HP targets and playtest templates.

## Current Server Rates

- EXP: 10x | Meso: 10x | Drop: 10x | Boss Drop: 10x | Quest: 5x
- Solo expeditions: **ON** (`USE_ENABLE_SOLO_EXPEDITIONS: true`) ✅

---

## Boss Stats (From WZ Data)

### Endgame Bosses (Lv 140+)

| Mob ID | Boss | Level | HP | PA Dmg | MA Dmg | PD Def | MD Def | EXP | Notes |
|--------|------|-------|----|--------|--------|--------|--------|-----|-------|
| 8820001 | **Pink Bean** | 180 | **2,100,000,000** | 1,700 | 1,200 | 1,700 | 1,930 | 50,000,000 | hpRecovery=100k, pushed=140k, noregen |
| 8810018 | Horntail (Pivot) | 160 | **2,090,000,000** | 0 | 0 | 0 | 0 | 0 | Central pivot point, structural |
| 8810000 | Horntail (Head A) | 160 | 330,000,000 | 1,350 | 820 | 1,760 | 1,840 | 9,732,030 | noFlip, firstAttack |
| 8810002 | Horntail (Head B) | 160 | 330,000,000 | 1,350 | 820 | 1,760 | 1,840 | 13,902,900 | eva=43 |
| 9400300 | **Showa Boss** | 175 | **150,000,000** | 1,600 | 1,350 | **5,000** | **4,300** | 17,500,000 | Extremely high defense, noregen |
| 8800002 | Zakum (Body 2) | 140 | 110,000,000 | 1,080 | 570 | 1,200 | 1,500 | 7,000,000 | Main reward body, noregen |
| 8800000 | Zakum (Body 1) | 140 | 66,000,000 | 980 | 530 | 1,000 | 1,100 | 0 | Structural body (no EXP) |

### Zakum Arms

| Mob ID | Part | Level | HP | PA Dmg | MA Dmg | PD Def | MD Def | EXP |
|--------|------|-------|----|--------|--------|--------|--------|-----|
| 8800003 | Arm A | 140 | 33,000,000 | 505 | 460 | 800 | 800 | 1,344,000 |
| 8800004 | Arm B | 140 | 33,000,000 | 505 | 460 | 800 | 800 | 1,344,000 |
| 8800005 | Arm C | 140 | 22,000,000 | 530 | 485 | 800 | 950 | 896,000 |

### Mid-Tier Bosses (Lv 100-139)

| Mob ID | Boss | Level | HP | PA Dmg | MA Dmg | PD Def | MD Def | EXP | Notes |
|--------|------|-------|----|--------|--------|--------|--------|-----|-------|
| 8510000 | Pianus (A) | 110 | 30,000,000 | 790 | 780 | 1,150 | 1,270 | 1,300,000 | MP=3M |
| 8520000 | Pianus (B) | 110 | 24,000,000 | 670 | 670 | 1,000 | 1,100 | 900,000 | |
| 8500001 | Papulatus (Main) | 125 | 23,000,000 | 630 | 480 | 1,000 | 1,100 | 596,000 | MP=2M |
| 8500002 | Papulatus (Alt) | 125 | 1,590,000 | 800 | 1,000 | 800 | 1,200 | 970,000 | noregen, lower HP |
| 8150000 | Crimson Balrog | 100 | 100,000 | 500 | 720 | 800 | 800 | 3,500 | |

### Early Bosses (Lv < 100)

| Mob ID | Boss | Level | HP | PA Dmg | MA Dmg | PD Def | MD Def | EXP | Notes |
|--------|------|-------|----|--------|--------|--------|--------|-----|-------|
| 8130100 | Jr. Balrog | 80 | 50,000 | 450 | 605 | 420 | 450 | 2,000 | |
| 6300005 | Zombie Mushmom | 65 | 35,000 | 250 | 380 | 350 | 400 | 1,500 | undead=1 |
| 6130101 | Mushmom | 60 | 20,000 | 200 | 300 | 320 | 320 | 1,200 | |

### New Content Bosses (Proposed — Not Yet In Server)

These bosses need importing from the repack. HP values are design targets from `balance-design.md`.

| Boss | Level | Proposed HP | Party Size | Source Area | Key Drops |
|------|-------|-------------|-----------|-------------|-----------|
| **Krexel** | 90 | 60,000,000 | 2-3 | Singapore/Ulu City | Singapore accessories, accessory scrolls |
| **Scarlion** | 80 | 30,000,000 | 2-3 | Kampung Village | Scarlion Hat (DEX/LUK focus, ZHelm alternative) |
| **Targa** | 80 | 30,000,000 | 2-3 | Kampung Village | Targa Hat (STR/INT focus, ZHelm alternative) |
| **Chaos Zakum** | 130 | 200,000,000 | 4-6 | Zakum Altar (instance) | Enhanced Zakum gear, rare scrolls |
| **Von Leon** | 125 | 500,000,000 | 3-6 | Lion Heart Castle | Von Leon Set (Lv 125, 6pc), Von Leon Coins |
| **Chaos Horntail** | 140 | 600,000,000 | 4-6 | Horntail Cave (instance) | Enhanced HT accessories |
| **Empress Cygnus** | 140 | 1,500,000,000 | 4-6 | Future Ereve | Empress Set (Lv 140, 7pc), Soul Shards, Rien Keystone |
| **Chaos Pink Bean** | 150 | 3,000,000,000 | 6+ | Temple of Time (instance) | Cosmetic rewards, medals, rare chairs |
| **Arcane Guardian** | 170 | 2,000,000,000 | 6+ | Arcane River (M4) | Arcane Set (Lv 160), Arcane Tokens |

#### Mob IDs (from repack audit)
- **Chaos Zakum**: 8800100-8800116 (17 mobs) ✅ confirmed in repack
- **Von Leon**: 8840000-8840002 (boss + 2 summons) ✅ confirmed
- **Empress**: 8850000-8850011 (5 commanders × 2 phases + Shinsoo + Empress) ✅ confirmed
- **Krexel**: TBD — need to confirm mob ID in Singapore data
- **Scarlion/Targa**: TBD — Kampung boss IDs
- **Arcane Guardian**: TBD (Milestone 4)

#### Von Leon Set Bonuses
- 3 piece: +15 all stats, +300 HP/MP
- 6 piece: +30 all stats, +500 HP/MP, +10 ATK/MATK

#### Empress Set Bonuses
- 4 piece: +25 all stats, +500 HP/MP, +10 ATK/MATK
- 7 piece: +50 all stats, +1000 HP/MP, +20 ATK/MATK, +10% boss damage

---

## Playtest Template

Fill in during Phase 2 gameplay testing on the dev box.

### Per-Boss Playtest

#### Zakum
- **Tested with**: ___ players, classes: ___
- **Time to clear**: ___
- **Deaths**: ___
- **Damage dealt per hit**: ___ range
- **Damage received per hit**: ___
- **Notable drops**: ___
- **Broken mechanics**: ___
- **Feel**: Too hard / About right / Too easy
- **Recommended party size (current)**: ___
- **Recommended party size (target)**: ___
- **Notes**: ___

#### Horntail
- **Tested with**: ___ players, classes: ___
- **Time to clear**: ___
- **Deaths**: ___
- **Damage dealt per hit**: ___ range
- **Damage received per hit**: ___
- **Notable drops**: ___
- **Broken mechanics**: ___
- **Feel**: Too hard / About right / Too easy
- **Notes**: ___

#### Pink Bean
- **Tested with**: ___ players, classes: ___
- **Time to clear**: ___
- **Deaths**: ___
- **Feel**: Too hard / About right / Too easy
- **Notes**: ___

#### Showa Boss
- **Tested with**: ___ players, classes: ___
- **Time to clear**: ___
- **Deaths**: ___
- **Feel**: Too hard / About right / Too easy
- **Notes**: ___ (user previously complained about difficulty)

#### Papulatus
- **Tested with**: ___ players, classes: ___
- **Time to clear**: ___
- **Feel**: Too hard / About right / Too easy
- **Notes**: ___

#### Pianus
- **Tested with**: ___ players, classes: ___
- **Time to clear**: ___
- **Feel**: Too hard / About right / Too easy
- **Notes**: ___

#### Krexel (NEW — Singapore)
- **Tested with**: ___ players, classes: ___
- **Time to clear**: ___
- **Deaths**: ___
- **Feel**: Too hard / About right / Too easy
- **Notes**: ___

#### Von Leon (NEW — LHC)
- **Tested with**: ___ players, classes: ___
- **Time to clear**: ___
- **Deaths**: ___
- **Damage dealt per hit**: ___ range
- **Damage received per hit**: ___
- **Notable drops**: ___ (Von Leon Set pieces? Von Leon Coins?)
- **Feel**: Too hard / About right / Too easy
- **Notes**: ___

#### Empress Cygnus (NEW — Future Ereve)
- **Tested with**: ___ players, classes: ___
- **Time to clear**: ___
- **Deaths**: ___
- **Phase transitions**: Smooth / Buggy
- **CK Commander phases**: All working / Some broken
- **Notable drops**: ___ (Empress Set? Soul Shards? Rien Keystone?)
- **Feel**: Too hard / About right / Too easy
- **Notes**: ___

#### Chaos Zakum (NEW)
- **Tested with**: ___ players, classes: ___
- **Time to clear**: ___
- **Feel**: Too hard / About right / Too easy
- **Notes**: ___

#### Chaos Horntail (NEW)
- **Tested with**: ___ players, classes: ___
- **Time to clear**: ___
- **Feel**: Too hard / About right / Too easy
- **Notes**: ___

---

## Party Quest Audit

| PQ | Level Range | Tested? | Works? | Notes |
|----|-------------|---------|--------|-------|
| Kerning City PQ | 21-30 | | | |
| Ludibrium PQ | 35-50 | | | |
| Orbis PQ | 51-70 | | | |
| Pirate PQ | 55-100 | | | |
| Romeo & Juliet PQ | 71-85 | | | |
| Crimsonwood Keep PQ | 90+ | | | |
| Horntail PQ (prequest) | 130+ | | | |

---

## Gear Ceiling Audit

> Full vendor tables in `world-design.md`. Full player-facing guide in `PROGRESSION-GUIDE.md`.

| Level Bracket | Weapon | Armor | Accessories | Source |
|---------------|--------|-------|-------------|--------|
| 1-30 | Quest weapons | Quest gear | — | Victoria zone vendors, quests |
| 31-50 | **Maple Weapons** (35-64) | Various drops | Ellin earring+ring (50) | Mushroom Castle vendor, Ellin vendor |
| 51-70 | KFT/Magatia vendor weapons | KFT armor set (60) | — | Zone completion vendors |
| 71-100 | Boss drops, Zipangu vendor | **Zakum Helm** (70), Scarlion/Targa hat (80) | Singapore accessories | Zakum, Kampung, Singapore |
| 101-120 | Corrupted ToT gear (110) | Corrupted ToT armor (110) | **HT Necklace/Pendant** (100) | ToT vendor, Horntail |
| 121-130 | **Von Leon Set weapons** (125) | **Von Leon Set armor** (125) | Von Leon Ring (125) | Von Leon boss + VL Coin vendor |
| 131-140 | **Empress Set weapons** (140) | **Empress Set armor** (140) | Empress accessories (140) | Empress boss + Soul Shard vendor |
| 150-170 | **Arcane Set** (160) | **Arcane Set** (160) | Arcane accessories (160) | Arcane Token vendor (M4) |

---

## Economy Audit

| Metric | Value | Notes |
|--------|-------|-------|
| Meso rate (config) | 10x | |
| Average meso/hour at lv 70 | | Measure during playtest |
| Average meso/hour at lv 120 | | |
| Key shop prices | | NPC shop scrolls, pots, etc. |
| Scroll availability | | Which scrolls drop? Which don't? |
| FM functionality | | Does Free Market work? |

---

## Damage Formula Notes

Key question: Are v83 Cosmic damage formulas pre-BB or post-BB?

- [ ] Check `server/src/main/java/` for damage calculation code
- [ ] Compare damage output to expected v83 GMS values
- [ ] Note: pre-BB damage cap was ~99,999 (unfunded) to ~50k+ (funded), post-BB removed caps

Files to check:
- `server/src/main/java/client/processor/action/AbstractDealDamageHandler.java`
- `server/src/main/java/server/life/MonsterStats.java`
- Any `DamageCalc` or similar class
