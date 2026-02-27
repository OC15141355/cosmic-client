# Boss Audit — TwinleafStory v83

Stock Cosmic boss stats extracted from `server/wz/Mob.wz/` XML data, plus columns for playtest findings.

## Current Server Rates

- EXP: 10x | Meso: 10x | Drop: 10x | Boss Drop: 10x | Quest: 5x
- Solo expeditions: **OFF** (`USE_ENABLE_SOLO_EXPEDITIONS: false`)

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

What's the best available gear at each level bracket?

| Level Bracket | Weapon | Armor | Accessories | Source | Notes |
|---------------|--------|-------|-------------|--------|-------|
| 1-30 | | | | Drops + quests | |
| 31-50 | | | | | |
| 51-70 | | | | | |
| 71-100 | | | | Zakum Helm territory | |
| 101-120 | | | | HT accessories | |
| 121-150 | | | | ??? (the gap) | |
| 150+ | | | | ??? (the gap) | |

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
