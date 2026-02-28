# Audit Results — Session 4 (2026-02-28)

Areas (NLC, Kampung, Omega), NPC IDs, Von Leon/Empress Equips, Katara Animations

---

## NPC IDs — Returning NPCs

All NPCs found in String.wz/Npc.img.xml with corresponding files in Npc.wz/.

| NPC | ID | Stock Function | Stock Dialogue Snippet | Npc.wz File |
|-----|----|---------------|----------------------|-------------|
| **Cassandra** | 9010010 | Event NPC | "You know, I got something fun to do..." | 9010010.img.xml |
| **Gaga** | 9000021 | Boss Rush Recruiter | "Do you know about the Boss Rush challenge?" | 9000021.img.xml |
| **Duey** | 9010009 | Package Deliverer | "Maple Package Service - your one-stop source to packages" | 9010009.img.xml |
| **Big Headward** | 1012117 | Hair salon (Prince) | "Actually, I...was the prince of Big Head Kingdom" | 1012117.img.xml |
| **Maple Admin** | 9010110 | Prison/Trooth Booth | "I can tell you more about the Trooth Booth" | 9010110.img.xml |
| **Cody** | 9200000 | Wizet Wizard | "I'm telling you, I really AM from WIZET!" | 9200000.img.xml |

### Notes for Implementation:
- Duey has `parcel="1"` flag in info — built-in delivery system support
- Big Headward is currently a hair salon NPC (`hair_royal` script) — needs complete script replacement for Dojo role
- Maple Admin uses `prisonMapleAdmin` script — needs replacement for lobby vendor role
- Gaga is Boss Rush — needs replacement for collection tracker
- Cassandra's event NPC role maps well to our rumor broker concept
- Cody's "Wizet Wizard" identity works perfectly for our progression guide

---

## Area Audit — New Leaf City

### Map Coverage
- **Range**: 600000000 - 600020600
- **Total Maps**: ~29

### Map Breakdown

**Town/Hub (7)**:
| Map ID | Name |
|--------|------|
| 600000000 | New Leaf City - Town Center |
| 600000001 | NLC Mall |
| 600010000 | Urban Underground |
| 600010001 | NLC Subway Station |
| 600010002-005 | Subway transit (connects to Kerning City) |

**Hunting Grounds (8)**:
| Map ID | Name | Level Estimate |
|--------|------|---------------|
| 600010100 | Jungle Clearing | 70-80 |
| 600010200 | Krakian Jungle Basin | 75-85 |
| 600010300 | Jungle Valley | 80-90 |
| 600010400 | Mountain Slopes | 85-90 |
| 600010500 | Mountain Cliffs | 85-95 |
| 600010600 | Highlands | 90-100 |
| 600020300 | Wolf Spider Cavern | 90-100 |

**Special/Boss Areas (6)**:
| Map ID | Name | Notes |
|--------|------|-------|
| 600020000 | Lobby | Pre-boss staging |
| 600020100 | Deity Room | Boss encounter? |
| 600020200 | Soul Corridor | Dungeon |
| 600020400 | Fire Chamber | Elemental challenge |
| 600020500 | Ice Chamber | Elemental challenge |
| 600020600 | Enigma Chamber | Final boss? |

### Notable Mobs
- Scorpion (9300157), Werewolf (7130200, 9500132), Wolf Spider (9400545)
- Elemental/chamber mobs TBD

### TwinleafStory Fit
- **Level range**: 70-100 (overlaps with Singapore, provides variety)
- **Unique features**: Subway connection to Kerning City, elemental chambers (Fire/Ice/Enigma)
- **Recommendation**: Good side-zone for 70-100 alongside Singapore. Urban/jungle aesthetic contrasts with Singapore's tropical theme. Elemental chambers could be repurposed as class-specific challenges or mini-bosses.

---

## Area Audit — Omega Sector

### Map Coverage
- **Range**: 221000000 - 221040402
- **Total Maps**: 123

### Map Breakdown

**Town/Hub (7)**:
| Map ID | Name |
|--------|------|
| 221000000 | Omega Sector (main town) |
| 221000001 | Tunnel (entry) |
| 221000100 | HQ |
| 221000200 | Silo |
| 221000300 | Command Center |
| 221000400 | Safety Zone |

**Eos Tower (101 maps)**:
| Map Range | Notes |
|-----------|-------|
| 221020000-221024400 | Floors 1-101 (vertical progression) |
| 221020701 | Hidden Tower (secret area) |
| 221023401-221023425 | Drummer Bunny's Lair (25 variations) |

**Field Areas (15)**:
| Map Range | Name |
|-----------|------|
| 221030100-221030600 | Boswell Fields I-VI |
| 221030301 | Mateon Field |
| 221030401 | Plateon Field |
| 221030501 | Mecateon Field |
| 221040000-221040400 | Kulan Fields I-V |

**Boss Areas**:
| Map ID | Name |
|--------|------|
| 221040401-402 | Dogon's HQ |

### Notable Mobs
- Robot evolution chain: Roid → Neo Huroid → Frankenroid → Angry Frankenroid
- Xenoroid Echo Type A-C (8644400-8644414)
- Drumming Bunny (3230400) — boss with 25-map lair
- Nightshadow (9400579) — likely boss
- Dogon — primary boss (HQ)

### TwinleafStory Fit
- **Level range**: 45-65 (stock v83) — fits neatly as a Ludibrium-adjacent zone
- **Unique features**: 101-floor Eos Tower = built-in vertical progression challenge, robot/sci-fi theme unique in the game
- **Recommendation**: Strong candidate for integration. Eos Tower is essentially a built-in "dojo-lite" (101 floors of escalating difficulty). Drummer Bunny's 25-map lair could be a repeatable boss with phase mechanics. Robot mobs give a sci-fi aesthetic that's different from everything else.
- **Connection**: Already adjacent to Ludibrium in stock v83 (Eos Tower connects Ludi ↔ Omega Sector)

---

## Area Audit — Kampung Village (Malaysia)

### Map Coverage
- **Range**: 551000000 - 551030200
- **Total Maps**: 28

### Map Breakdown

**Village/Town (3)**:
| Map ID | Name |
|--------|------|
| 551000000 | Kampung Village (main town) |
| 551000100 | Hibiscus Road 1 |
| 551000200 | Hibiscus Road 2 |

**Fantasy Theme Park (5)**:
| Map ID | Name |
|--------|------|
| 551010000 | Fantasy Theme Park 1 |
| 551020000 | Fantasy Theme Park 2 |
| 551030000 | Fantasy Theme Park 3 |
| 551030100 | Entrance to the Spooky World |
| 551030200 | Spooky World |

**ByeBye Station (20)**:
| Map Range | Name |
|-----------|------|
| 551030001-551030020 | Longest Ride on ByeBye Station (20 variations) |

### Notable Mobs
- Homunculus (7110301, 9300142, 9300147)
- Giant Centipede (5220004, 9300188, 9500177)

### TwinleafStory Fit
- **Level range**: 50-70 (stock)
- **Unique features**: Theme park aesthetic, 20-map ride progression, Spooky World
- **Recommendation**: Lower priority than NLC and Omega Sector. Kampung is fun but small (28 maps, 3 hunting areas). Could be a novelty side-zone. The ByeBye Station ride (20 maps) is an interesting mini-game element if we want to offer non-combat content. Connects to Singapore/Ulu City area thematically.

---

## Equipment Audit — Von Leon Set

### String.wz Data (Names + IDs exist)
- **170+ total items** across 11 set variants
- **5 main variants**: Marx, Alma, Fox, Nox, Cora (Set IDs 6-10)
- **Additional variants**: Victor, Hex, Celine, Scar, Mer, Royal
- **Weapons**: Covers all weapon types (Saber, Axe, Hammer, Dagger, Wand, Staff, Bow, etc.)
- **Level requirement**: 120

### Character.wz Visual Data (What's Actually In Repack)

| Item ID | Name | Type | Level | Set ID | In Repack? |
|---------|------|------|-------|--------|------------|
| 01102262 | Marx Von Leon Cape | Cape | 120 | 6 | YES |
| 01102263 | Alma Von Leon Cape | Cape | 120 | 7 | YES |
| 01102264 | Fox Von Leon Cape | Cape | 120 | 8 | YES |
| 01102265 | Nox Von Leon Cape | Cape | 120 | 9 | YES |
| 01102266 | Cora Von Leon Cape | Cape | 120 | 10 | YES |
| 01112929 | Von Leon Ring | Ring | 0 | - | YES |
| (Helmets) | Various | Hat | 120 | 6-10 | **MISSING** |
| (Battle Suits) | Various | Overall | 120 | 6-10 | **MISSING** |
| (War Boots) | Various | Shoes | 120 | 6-10 | **MISSING** |
| (Gloves) | Various | Gloves | 120 | 6-10 | **MISSING** |
| (Weapons) | Various | Weapon | 120 | - | **MISSING** |

### Impact on Design
- **String data exists** — items can be named and referenced in drop tables
- **Visual models mostly MISSING** — players would see "invisible" equipment for most Von Leon pieces
- **Solution needed**: Source complete WZ data from a fuller v83 GMS extract, or use the repack's existing similar-level equipment models with custom names

---

## Equipment Audit — Empress Set

### String.wz Data
- **50+ items** in two tiers: Fine (balanced) and Brilliant (enhanced)
- Each tier: Hat, Robe, Shoes, Gloves
- 8 hair color variants
- Weapons: Dagger, Wand/Scepter, Spear, Bow, Crossbow, Guards, Claw, Pistol
- **Expected level**: 120

### Character.wz Visual Data

**COMPLETELY ABSENT FROM REPACK**

No Empress equipment pieces found in any Character.wz subdirectory. This is a post-v83 addition — the community repack doesn't include Empress gear models.

### Impact on Design
- **Critical gap**: Empress Set is our Arc I BiS (Lv 140) — we NEED visual models
- **Options**:
  1. Source from a later GMS WZ extract (v90+) that includes Empress content
  2. Reskin existing high-level equips with Empress names
  3. Use the Lionheart set as the "Empress" tier (it has Set ID 25, Lv 140)
  4. Design custom equipment using existing model templates

---

## Equipment Audit — Lionheart Set

### String.wz Data
- **30+ items**: Helm, Mail, Boots, Bracers, Cape, Shoulder
- Weapons: Cutlass, Champion Axe, Battle Hammer, etc.
- **Level requirement**: 140

### Character.wz Visual Data
| Item ID | Name | Type | Level | Set ID | In Repack? |
|---------|------|------|------|--------|------------|
| 01102275 | Lionheart Battle Cape | Cape | 140 | 25 | YES |
| (All others) | Various | Various | 140 | 25 | **MISSING** |

### Design Note
Lionheart at Lv 140 with Set ID 25 is actually a good candidate for our "Empress Set" — it's the right level, has the right slot coverage (helm/armor/boots/gloves/cape/shoulder), and the name "Lionheart" fits the Lion Heart Castle connection. We could rename it "Empress Set" if we source the models.

---

## Equipment Audit — Shinsoo Items

| Item ID | Name | Type | Level | In Repack? |
|---------|------|------|-------|------------|
| 01182079 | Shinsoo School Badge | Accessory | 30 | YES |
| 01005243 | Shinsoo's Light | Accessory | ? | MISSING |
| 01050503 | Shinsoo's Descent | Longcoat | ? | MISSING |
| 01070103 | Shinsoo's Steps | Pants | ? | MISSING |

Combat Shinsoo items absent — educational item only.

---

## Katara Animation Audit

### Overview
- **96 Katara weapon files** in Character.wz/Weapon/ (01342000-01342108, not all sequential)
- **78 unique named variants** in String.wz/Eqp.img.xml

### Animation Structure (Consistent Across All 96)

| Animation Node | Type | Frames (typical) |
|---------------|------|-------------------|
| `swingO1` | Overhead swing 1 | 2 |
| `swingO2` | Overhead swing 2 | 3 |
| `swingO3` | Overhead swing 3 | 3 |
| `swingOF` | Overhead swing finish | 2 |
| `swingPF` | Power finish swing | 4 |
| `stabO1` | Overhead stab 1 | 2 |
| `stabO2` | Overhead stab 2 | 2 |
| `stabOF` | Overhead stab finish | 3 |
| `stabT1` | Thrust stab | 1 |
| `walk1` | Walking | varies |
| `stand1` | Idle | varies |
| `alert` | Ready stance | 3 |
| `fly` | Flying | varies |
| `jump` | Jumping | varies |
| `prone` | Lying down | varies |
| `proneStab` | Prone attack | 2 |
| `heal` | Healing | varies |

### Critical Finding: No Skill Effect Data

**Zero hit/effect/ball subnodes found across all 96 files.**

Katara weapon files contain ONLY sprite positioning data (canvas elements with origin/map/z-layer). They define how the weapon LOOKS on the character during each animation pose. They do NOT contain:
- Hit zone geometry
- Projectile (ball) data
- Skill visual effects
- Damage area definitions

### Impact on Shadower 4.5 Design

The Shadower 4.5 skills (Bloody Storm, Tornado Spin, Mirror Image, Final Cut) need:
1. **Weapon appearance**: Kataras CAN provide this (dual-wield visual on character model)
2. **Skill visual effects**: Must come from SKILL files, not weapon files

**Recommended animation sources for Shadower 4.5**:
| Skill | Weapon Animation | Effect Animation Source |
|-------|-----------------|----------------------|
| Bloody Storm | Katara swingO1-O3 + swingPF combo | Night Walker 1411.img.xml effects |
| Tornado Spin | Katara swingOF (360° spin) | Night Walker AoE effects |
| Mirror Image | N/A (summon) | Night Walker shadow clone effects |
| Final Cut | Katara stabT1 (thrust dash) | Night Walker dash/shadow effects |

The actual "shadow slash" visual effects come from Night Walker skill files (1400-1411.img.xml), layered ON TOP of the Katara weapon sprites. The Katara provides the "second weapon in off-hand" look; the NW skill files provide the skill's visual impact (shadows, trails, explosions).

### Named Katara Highlights

Notable named Kataras that could serve as Shadower endgame weapons:
- **Timeless Katara** / **Reverse Katara** — good thematic names for endgame
- **Moonshadow Katara** / **Legendary Moonshadow Katara** — perfect shadow theme
- **Zakum's Poisonic Katara** — boss drop variant
- **Raven Horn Shadow Katara** — shadow-themed
- **Blood Blossom Katara** — fits melee assassin aesthetic

---

## Key Takeaways

1. **All 6 returning NPCs have valid IDs** — ready for script development
2. **NLC (29 maps) and Omega Sector (123 maps) are strong zone candidates** — Kampung is lower priority
3. **Omega Sector's Eos Tower (101 floors) is a natural Dojo-like challenge** worth integrating
4. **Von Leon and Empress equipment models are largely MISSING from repack** — need external WZ source for visual models; string/name data exists
5. **Lionheart Set (Lv 140, Set ID 25) could serve as our "Empress" tier** with rename + model sourcing
6. **Kataras provide weapon sprites only, not skill effects** — Shadower 4.5 effects come from Night Walker skill files, Katara provides off-hand appearance
7. **The CK/Aran skill animation re-audit still needed** — fix regex for single-line XML to find hit/ball/effect data in Skill.wz 1100-1511 and 2100-2112 files
