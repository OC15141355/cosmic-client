# Balance Design — TwinleafStory v83

Design document for boss rebalancing and gear progression. This is the **DESIGN** phase — implementation comes after playtest validation.

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
| **Solo** | 1 player | Mushmom, Zombie Mushmom, Jr. Balrog, Crimson Balrog | Quick farm, no prep needed |
| **Duo** | 2-3 players | Papulatus, Pianus | Moderate challenge, casual grouping |
| **Party** | 4-6 players | Zakum, Horntail, Showa Boss | Requires coordination, main progression |
| **Raid** | 6+ players | Pink Bean | Aspirational endgame, guild content |

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
| Showa Boss | 150,000,000 | 40,000,000 | 0.27x | 4-6 players, high def stays |
| Pink Bean | 2,100,000,000 | 500,000,000 | 0.24x | 6+ players, aspirational |

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

### Current Gear Ceiling (v83 Stock)

| Level | Best Available | Source |
|-------|---------------|--------|
| 1-30 | Class-specific quest gear | Quests, NPC shops |
| 30-50 | Stiff Feather Hat, various | Monster drops, crafting |
| 50-70 | Various 50+ equips | Drops, quest rewards |
| 70 | Zakum Helmet | Zakum |
| 80-100 | Various weapons, armors | Drops |
| 110+ | Horntail Necklace, Pendant | Horntail |
| 120+ | **NOTHING NEW** | ← The gap |

### Proposed New Gear (Level 120-150+)

New areas (Phase 5) drop gear that fills the 120+ gap. This gear should be:
- **Better than Zakum/HT accessories** but not game-breaking
- **Themed to the new area** (visual identity)
- **Tradeable** to support the economy
- **Scrollable** for customization

Placeholder ideas (finalize after playtest):

| Level | Item Slot | Stats (Base) | Source Area | Notes |
|-------|-----------|-------------|-------------|-------|
| 120 | Weapon | +5-10 ATT over current 120 weapons | New Area 1 | Class-specific drops |
| 130 | Helmet | Better than Zakum Helm by ~5 stats | New Area 1 | Rare drop |
| 140 | Pendant | Better than HT Pendant by ~3-5 stats | New Area 2 | Boss drop |
| 150 | Earring | New slot option | New Area 2 | Quest reward |
| 150 | Overall/Top | Level 150 armor set | New Area 2 | Set bonus |

**Key constraint**: Don't make old content irrelevant. Zakum Helm should still be a good stepping stone. New gear should be a ~10-15% improvement, not 2x.

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

`USE_ENABLE_SOLO_EXPEDITIONS` is currently **false**. For a small-group server, consider enabling this so players can attempt bosses solo (they'll still be hard, just not gated by party requirements).

```yaml
USE_ENABLE_SOLO_EXPEDITIONS: true
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

## Open Questions (Resolve During Playtest)

- [ ] What damage does a well-geared level 120 deal per hit? (Determines if HP values are right)
- [ ] Are Cosmic damage formulas pre-BB or post-BB?
- [ ] Do PQs all work correctly?
- [ ] Is the Showa boss even accessible? (Need to verify quest/map chain)
- [ ] What's the actual meso economy like at 10x rates?
- [ ] Does Free Market work?
- [ ] Are there any broken quests in the 1-120 leveling path?
