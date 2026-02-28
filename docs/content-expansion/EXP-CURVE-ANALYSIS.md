# TwinleafStory — EXP Curve Analysis
*Generated: 2026-02-27*

## Current Setup

| Setting | Value |
|---------|-------|
| Global EXP Rate | 10x |
| EXP Table | Hardcoded in `ExpTable.java` |
| Bosses EXP | 0 (bosses give no direct EXP) |
| Party Bonus | 5% per additional member |
| Holy Symbol | Full effect in party, 1/5 solo |

---

## How EXP Works (Technical Summary)

From `server/src/main/java/constants/game/ExpTable.java`:
- Level-up EXP requirements are a hardcoded static array (217 entries, levels 0-216)
- The `exp_rate: 10` in config.yaml multiplies ALL mob EXP by 10x

From `server/src/main/java/server/life/Monster.java`:
- EXP is distributed per-mob-kill, not from boss deaths
- **Bosses have `exp=0`** in their WZ XML — they give nothing directly
- Party members within 5 levels of the mob share EXP
- Leech range: 5 levels from any contributing party member

**Per-level or per-map EXP multipliers**: NOT IMPLEMENTED. Would require code changes.

---

## EXP Required at Key Levels (Base, no multiplier)

These are the raw values from `ExpTable.java`:

| Level | EXP Required (base) | At 10x rate | How it feels |
|-------|--------------------|--------------|----|
| 10 | 1,242 | ~125/kill needed | Trivial |
| 20 | 13,477 | 1,348/kill | Very fast |
| 30 | 63,800 | 6,380/kill | Fast |
| 40 | 235,372 | 23,537/kill | Smooth |
| 50 | 567,772 | 56,777/kill | Comfortable |
| 60 | 1,564,600 | 156,460/kill | Moderate |
| 70 | 2,667,496 | 266,750/kill | Starting to grind |
| 80 | 7,350,811 | 735,081/kill | Decent grind |
| 90 | 19,204,245 | 1,920,425/kill | Feels like work |
| 100 | 52,921,167 | 5,292,117/kill | Heavy grind |
| 110 | 131,075,474 | 13,107,547/kill | Very heavy |
| 120 | 341,739,xxx | ~34M/kill | Current ceiling |
| 130 | 770M+ | ~77M/kill | Would need new content |
| 140 | 1,700M+ | ~170M/kill | Aspirational |

---

## Current Feel Assessment

With 10x global rate, the progression feels like:
- **Lv 1–60**: Extremely smooth, almost too fast
- **Lv 60–80**: Good grind, satisfying
- **Lv 80–100**: Solid effort, takes a few sessions
- **Lv 100–120**: Feels like the "real" grind begins — 1-2 weeks
- **Lv 120+**: Wall — nothing new to grind, no gear incentive

---

## Proposed EXP Curve (No Code Changes Required)

The simplest approach: **keep the 10x global rate and use new area mob EXP values to create the curve**.

Since bosses give 0 EXP, all leveling 120-140 happens by grinding mobs in the new areas. By setting those mob EXP values appropriately, we control the effective rate in the new zones.

### Target Mob EXP Values for New Areas

| Area | Target Level | Mob Level | Suggested Base EXP | At 10x | Feel |
|------|-------------|-----------|-------------------|--------|------|
| Lion Heart Castle (entry) | 115-120 | 130 | 15,000 | 150,000 | Smooth |
| LHC (main) | 120-125 | 140 | 22,000 | 220,000 | Good |
| LHC (hard mobs) | 125-128 | 148 | 32,000 | 320,000 | Rewarding |
| Gate to the Future (entry) | 128-133 | 150 | 45,000 | 450,000 | Strong |
| Future Ereve (main) | 133-138 | 155 | 60,000 | 600,000 | Good |
| Future Ereve (hard) | 137-140 | 160 | 80,000 | 800,000 | Challenging |

### How many kills to level up?

With the above values, at 10x rate:
- **Lv 120→121**: 34M base ÷ 220,000 = ~155 LHC main mobs per level ✅ Good
- **Lv 125→126**: ~40M base ÷ 320,000 = ~125 LHC hard mobs per level ✅ Good
- **Lv 130→131**: ~60M base ÷ 450,000 = ~133 GttF entry mobs per level ✅ Good
- **Lv 135→136**: ~90M base ÷ 600,000 = ~150 Future Ereve mobs per level ✅ Good
- **Lv 139→140**: ~130M base ÷ 800,000 = ~163 hard mobs per level ✅ Aspirational but achievable

### Comparison to Official v83 Feel

At official rates (1x), it takes weeks to level past 120. At our rates with new content:
- 120-130: ~1 week of regular play per 10 levels
- 130-140: ~2 weeks per 10 levels

This aligns with our goal: "**Levels 120-140: Slower but new areas compensate with better mob EXP**"

---

## Alternative: Modify ExpTable.java

If we want to reduce early-game grind and increase late-game, we can modify the EXP table values directly. This is a code change that requires recompiling the server.

**Approach**: Multiply EXP requirements by:
- Levels 1-70: 0.5x (makes early game faster at same 10x rate)
- Levels 70-120: 1.0x (keep as-is)
- Levels 120-140: 1.5x (requires more effort, but compensated by higher mob EXP in new areas)

**File**: `server/src/main/java/constants/game/ExpTable.java`
**Method**: `getExpNeededForLevel(int level)` — add a multiplier based on level range

```java
public static int getExpNeededForLevel(int level) {
    int base = level > 200 ? 2000000000 : exp[level];
    // Custom TwinleafStory curve modifiers
    if (level <= 70) return (int)(base * 0.5);    // Smooth early game
    if (level <= 120) return base;                  // Standard mid-game
    if (level <= 140) return (int)(base * 1.3);   // Slower but rewarding endgame
    return base;
}
```

**Recommendation**: Start without this change. Monitor playtesting. If early game feels too slow, apply the code change then.

---

## Party EXP Analysis

With 6 players (max for small-group focus):
- Party bonus: 5% × 5 extra members = 25% bonus EXP
- Each member gets ~23% of total mob EXP (level-based distribution)
- At 10x rate with Holy Symbol (Bishop): effective ~25x EXP

For balanced small-group play, the 10x rate is already very generous in parties. The key is making sure mobs in new areas are beatable by small groups.

---

## Boss EXP Strategy

Since bosses give 0 EXP, the incentive to fight them is **loot only**. This is fine for our design — players grind to level, then gear up via bosses.

Consider adding a small EXP reward to chaos bosses:
```xml
<!-- In 8800102.img.xml (Chaos Zakum main body) -->
<int name="exp" value="500000"/>  <!-- 5M EXP at 10x rate -->
```

This gives a small "clear bonus" feel without making boss-rushing the primary leveling strategy.

---

## Summary Recommendations

1. **Keep 10x global rate** — no config.yaml changes needed
2. **Set new area mob EXP in WZ XML** when adding LHC/Future Ereve mobs (target values above)
3. **Optional code change** (ExpTable.java) to smooth early levels — defer until after playtesting
4. **Add small EXP to chaos bosses** (50,000–500,000 base) for clear satisfaction
5. **Party bonus stays at 1.0x** — the 5% per member stacking is already meaningful
