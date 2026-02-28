# Balance Design — TwinleafStory v83

*Last updated: 2026-02-28 (Session 4 — new bosses added, gear progression updated)*

Design document for boss rebalancing and gear progression. This is the **DESIGN** phase — implementation comes after playtest validation. See `world-design.md` for full gear/vendor tables and `boss-audit.md` for stock boss stat audit.

---

## Core Principles

1. **1-6 players is the sweet spot** — all content should be achievable with a small group
2. **Gear is the progression lever** — new areas drop new gear, not wholesale stat rewrites
3. **Keep boss mechanics intact** — reduce HP/damage to make fights killable, don't trivialize them
4. **Proportional rewards** — if a boss has 1/5 the HP, adjust drop rates/EXP accordingly
5. **No damage cap changes** — there's no hardcoded cap in Cosmic; client display is separate

---

## Boss Tier Design

### Proposed Tiers

| Tier | Party Size | Boss Examples | Design Goal |
|------|-----------|---------------|-------------|
| **Solo** | 1 player | Mushmom, Zombie Mushmom, Jr. Balrog, Crimson Balrog, Nine-Tailed Fox, Bodyguard A | Quick farm, no prep needed |
| **Duo** | 2-3 players | Papulatus, Pianus, Krexel, Scarlion, Targa | Moderate challenge, casual grouping |
| **Party** | 3-6 players | Zakum, Horntail, Von Leon, Showa Boss | Requires coordination, main progression |
| **Hard Party** | 4-6 players | Chaos Zakum, Chaos Horntail, Empress Cygnus | Endgame, requires good gear |
| **Aspirational** | 6+ players | Chaos Pink Bean, Arcane Guardian | Ultimate challenge, group coordination |

### Proposed HP Adjustments

Based on WZ data audit. **These are starting proposals — playtest first.**

| Boss | Current HP | Proposed HP | Ratio | Reasoning |
|------|-----------|-------------|-------|-----------|
| Mushmom | 20,000 | 20,000 | 1.0x | Fine as-is (solo) |
| Zombie Mushmom | 35,000 | 35,000 | 1.0x | Fine as-is (solo) |
| Jr. Balrog | 50,000 | 50,000 | 1.0x | Fine as-is (solo) |
| Crimson Balrog | 100,000 | 100,000 | 1.0x | Fine as-is (solo) |
| Papulatus (Main) | 23,000,000 | 10,000,000 | 0.43x | 2-3 players should clear in ~10 min |
| Papulatus (Alt) | 1,590,000 | 1,590,000 | 1.0x | Already low |
| Pianus (A) | 30,000,000 | 12,000,000 | 0.40x | Similar to Papulatus tier |
| Pianus (B) | 24,000,000 | 10,000,000 | 0.42x | |
| Zakum (Body 2) | 110,000,000 | 30,000,000 | 0.27x | 4-6 players, ~15-20 min fight |
| Zakum (Body 1) | 66,000,000 | 20,000,000 | 0.30x | |
| Zakum Arms (each) | 22-33M | 8,000,000 | ~0.30x | Arms should fall fast with a party |
| Horntail (Heads) | 330,000,000 | 80,000,000 | 0.24x | 4-6 players, ~20-30 min fight |
| Horntail (Pivot) | 2,090,000,000 | 200,000,000 | 0.10x | Main body, longest phase |
| Showa Boss | 150,000,000 | 150,000,000 (PDef 1500) | 1.0x | ✅ DONE — defense nerfed, HP kept |
| Pink Bean | 2,100,000,000 | 500,000,000 | 0.24x | 6+ players, aspirational |

### New Content Bosses (Proposed HP)

| Boss | Level | Proposed HP | Party Size | Tier | Drops |
|------|-------|-------------|-----------|------|-------|
| Krexel | 90 | 60,000,000 | 2-3 | Duo | Singapore accessories, scrolls |
| Scarlion | 80 | 30,000,000 | 2-3 | Duo | Scarlion Hat (DEX/LUK ZHelm alt) |
| Targa | 80 | 30,000,000 | 2-3 | Duo | Targa Hat (STR/INT ZHelm alt) |
| Von Leon | 125 | 500,000,000 | 3-6 | Party | Von Leon Set (Lv 125), Von Leon Coins |
| Chaos Zakum | 120 | 200,000,000 | 4-6 | Hard Party | Enhanced Zakum gear, rare scrolls |
| Chaos Horntail | 130 | 600,000,000 | 4-6 | Hard Party | Enhanced HT accessories |
| Empress Cygnus | 140 | 1,500,000,000 | 4-6 | Hard Party | Empress Set (Lv 140), Soul Shards |
| Chaos Pink Bean | 150 | 3,000,000,000 | 6+ | Aspirational | Cosmetic rewards, medals, rare chairs |
| Arcane Guardian | 170 | 2,000,000,000 | 6+ | Aspirational | Arcane Set (Lv 160), Arcane Tokens |

### Proposed Damage Adjustments

Boss damage may also need tuning. Wait for playtest data before changing.

| Boss | Current PA | Proposed PA | Notes |
|------|-----------|-------------|-------|
| Zakum bodies | 980-1080 | TBD | Playtest first |
| Horntail heads | 1,350 | TBD | |
| Showa Boss | 1,600 | TBD | Currently highest PA after PB |
| Pink Bean | 1,700 | TBD | Keep challenging |

**Rule of thumb**: If a boss can one-shot a reasonably geared player at the intended level, reduce damage by 20-30%. If it two-shots, that's probably fine.

### Defense Adjustments

| Boss | Current PDef | Notes |
|------|-------------|-------|
| Showa Boss | 5,000 / 4,300 | Absurdly high — most players will deal 1 damage. Reduce to ~1,500/1,500 |
| All others | 800-1,840 | Seem reasonable for their level |

---

## Gear Progression Design

> **Full gear tables in `world-design.md`** (zone completion vendors) and **`PROGRESSION-GUIDE.md`** (player-facing guide).

### Gear Ladder (Decided — Session 4)

| Level | Best Available | Source | Notes |
|-------|---------------|--------|-------|
| 1-30 | Class-specific quest gear | Quests, NPC shops, zone vendors | Victoria completion vendor: basic adventurer set |
| 35-64 | **Maple Weapons** | Mushroom Castle vendor (King Pepe quest) | Iconic early-game upgrade |
| 50-70 | KFT armor, Ellin accessories | Zone completion vendors | KFT Lv 60 armor, Ellin Lv 50 earring+ring |
| 70 | Zakum Helmet | Zakum boss | Still core progression |
| 78 | Magatia faction weapons | Magatia completion vendor | Alcadno vs Zenumist faction choice |
| 80-100 | Singapore accessories, Scarlion/Targa hats | Zone vendors + bosses | Kampung hats = ZHelm alternatives |
| 100 | Horntail Necklace, Pendant | Horntail boss | |
| 110 | **Corrupted ToT gear** | ToT completion vendor | Bridges the 100-120 gap |
| 120 | **Chaos Zakum/HT drops** | Boss drops | Enhanced versions of Zak/HT gear |
| 125 | **Von Leon Set** (6 pc) | VL boss drops + Von Leon Coin vendor | 3pc: +15 all +300 HP/MP, 6pc: +30 all +500 HP/MP +10 ATK/MATK |
| 140 | **Empress Set** (7 pc) | Empress drops + Soul Shard vendor (Ereve) | 4pc: +25 all +500 HP/MP +10 ATK/MATK, 7pc: +50 all +1000 HP/MP +20 ATK/MATK +10% boss |
| 160 | **Arcane Set** | Arcane Token vendor (M4) | TBD stats |

### Zone Completion Vendor System

Every zone has a completion condition → vendor unlocks selling level-appropriate gear. Vendor gear = reliable baseline (~70-80% of boss drop quality). Boss drops = premium upgrade path. Token currencies provide endgame bad luck protection.

**Token currencies:**
| Token | Source | Exchange |
|-------|--------|----------|
| Von Leon Coins | LHC mobs + Von Leon boss | ~50 coins = specific Von Leon piece (mobs 1-3, boss 10) |
| Soul Shards | Future Ereve mobs + Empress (3-5/kill) | 10 shards = specific Empress piece |
| Arcane Tokens | Arcane River mobs + Guardian | TBD exchange rate |

**Key constraint**: Don't make old content irrelevant. Zakum Helm is still a good stepping stone. Each tier is ~10-15% improvement, not 2x.

---

## EXP/Rate Adjustments

Current rates (from `config.yaml`):

| Rate | Current | Proposed | Notes |
|------|---------|----------|-------|
| EXP | 10x | 10x (keep) | Fast leveling is fine for small server |
| Meso | 10x | 10x (keep) | |
| Drop | 10x | 5x-10x | May be too generous — playtest |
| Boss Drop | 10x | 10x (keep) | Boss drops should feel rewarding |
| Quest EXP | 5x | 5x (keep) | |

### Solo Expeditions

`USE_ENABLE_SOLO_EXPEDITIONS` — **ENABLED** on the server (set to true). Players can attempt bosses solo. They're still hard, just not gated by party size requirements. Essential for a 5-15 player server.

```yaml
USE_ENABLE_SOLO_EXPEDITIONS: true  # ✅ Already set
```

---

## Implementation Priority

After playtest validation:

1. **Enable solo expeditions** — one config change, immediate QoL
2. **Showa Boss defense nerf** — PDef 5000→1500, most impactful single change
3. **Zakum HP reduction** — most-run boss, affects most players
4. **Horntail HP reduction** — second most important
5. **Pianus/Papulatus HP reduction** — mid-tier cleanup
6. **Pink Bean HP reduction** — endgame, less urgent
7. **New gear design** — requires WZ editing pipeline working first

---

## How to Edit Boss Stats

All boss changes are server-side XML edits in `server/wz/Mob.wz/`:

```xml
<!-- Example: Reduce Zakum Body 2 HP from 110M to 30M -->
<!-- File: server/wz/Mob.wz/8800002.img.xml -->
<!-- Find: -->
<int name="maxHP" value="110000000"/>
<!-- Replace with: -->
<int name="maxHP" value="30000000"/>
```

Restart server to pick up changes. No client update needed for stat-only changes.

For defense changes:
```xml
<!-- Showa Boss: Reduce PDef from 5000 to 1500 -->
<!-- File: server/wz/Mob.wz/9400300.img.xml -->
<int name="PDDamage" value="1500"/>
<int name="MDDamage" value="1500"/>
```

---

## Skill Balance Impact (Session 3-4)

The 4.5 skill revamp (see `twinleaf-skills.md`) significantly changes class balance:
- **30+ dead skills cut** — frees hotkey slots, simplifies rotations
- **Shadower completely rebuilt** — from meso gimmick DPS to melee assassin (Shadow Flurry, Marked for Death, Mirror Image, Final Cut)
- **Hero gets ranged option** (Soul Driver) — no longer pure melee
- **Bishop gets ULTIMATE** (Divine Judgment: full party heal + 10s invuln, 180s CD) — changes raid healing calculus
- **MW auto-passive + boosters baked in** — frees 2 hotkey slots per class, affects total DPS calculations

Boss HP targets were designed BEFORE 4.5 skills. May need re-tuning upward once 4.5 skills are implemented (more DPS available per player).

---

## Open Questions (Resolve During Playtest)

- [ ] What damage does a well-geared level 120 deal per hit? (Determines if HP values are right)
- [ ] Are Cosmic damage formulas pre-BB or post-BB?
- [ ] Do PQs all work correctly? (Core 3: KPQ/LPQ/OPQ)
- [ ] Is the Showa boss even accessible? (Need to verify quest/map chain)
- [ ] What's the actual meso economy like at 10x rates?
- [ ] ~~Does Free Market work?~~ → Free Market replaced by Kerning Night Market (Trade button)
- [ ] Are there any broken quests in the 1-120 leveling path?
- [ ] Do Von Leon Coins / Soul Shards feel right as token accumulation rate?
- [ ] Is 4-6 the right Empress party size or does it need 6+?
- [ ] How do 4.5 skills affect boss time-to-kill? (Re-tune HP after implementation)
