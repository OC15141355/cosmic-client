# TwinleafStory — Explorer Skill Revamp & 4.5 Job Design

*Every skill earns its hotkey. No filler. No dead weight.*
*Last updated: 2026-02-28 — Session 3+*

---

## Design Philosophy

TwinleafStory is Explorer-only. With CK and Aran disabled, we have total freedom to streamline the Explorer skill trees. The goals:

1. **Cut dead skills** — if nobody uses it, delete it. No trap skill points.
2. **Merge weapon variants** — Sword Mastery / Axe Mastery → "Weapon Mastery". One skill, works for everything.
3. **Automate tedium** — Boosters, Maple Warrior, Hero's Will shouldn't need hotkeys.
4. **Fill gaps** — 4.5 job skills (post-Empress) give each final job 4 new skills that address class weaknesses.
5. **Preserve identity** — Hero still feels like Hero. NL still feels like NL. The cuts remove bloat, not personality.

---

## Universal Changes (All Explorers)

### Maple Warrior → Auto-Passive
- **Before**: 4th job buff, needs hotkey, 900s duration, everyone has it.
- **After**: Auto-passive at 4th job. Always active. No hotkey needed.
- **Rationale**: Every class gets it. Every player casts it. It's mandatory with zero gameplay. Just make it always on.

### Hero's Will → Quest-Granted Auto-Cleanse
- **Before**: 4th job active, 360s cooldown, cleanses Seduce/stun.
- **After**: Granted via quest (Rien 4.5 questline). Auto-triggers on debuff. 60s internal cooldown.
- **Rationale**: You never WANT to be seduced — the skill exists to undo something the game did to you. Make it automatic, reduce cooldown, earn it through gameplay.

### Boosters → Baked Into Mastery Passives
- **Before**: 2nd job buff, needs hotkey, 200s duration. Every class has one (Sword Booster, Spell Booster, etc.)
- **After**: Attack speed bonus baked into the corresponding Mastery passive. When you learn Weapon Mastery, you get the booster effect for free.
- **Rationale**: Same logic as Maple Warrior — mandatory buff that adds nothing to gameplay. Delete the button, keep the effect.

### Weapon Variant Merges (Warriors)
All weapon-specific skills are merged into single universal versions:

| Old Skills | New Skill | Notes |
|-----------|-----------|-------|
| Sword Mastery + Axe Mastery | **Weapon Mastery** | Works with any warrior weapon |
| Sword Booster + Axe Booster | *(baked into Weapon Mastery)* | See above |
| Sword FA + Axe FA | **Final Attack** | Universal |
| Panic (Sword) + Panic (Axe) | **Panic** | Single skill |
| Coma (Sword) + Coma (Axe) | **Coma** | Single skill |
| Sword/BW/Spear/PA Mastery | **Weapon Mastery** (per branch) | Each warrior branch gets one |
| Sword/BW/Spear/PA Booster | *(baked in)* | |

**Result**: Warriors pick ONE weapon they like. All skills work with it. No wasted SP on the "wrong" weapon type.

---

## Dead Skill Cuts — Full List

Every skill below is REMOVED from the game. SP previously spent on these is redistributed to remaining skills or refunded.

### Warrior Cuts

| Skill | Class | Why Cut |
|-------|-------|---------|
| Improving MP Recovery | 1st job | Useless. Pots exist. |
| Shield Mastery | All warrior | Shields optional, skill is trap. |
| Endure | Fighter/Page | Useless passive, negligible effect. |
| Mortal Blow | Fighter | RNG instant kill at low chance. Never reliable. |
| Threat (Threaten) | Page/WK | Mob debuff — irrelevant with decent gear. |
| Monster Magnet | Hero | Gimmick pull skill. Laggy, unreliable, rarely useful. |
| Guardian | Hero | Blocks 1 attack. 600s CD. Not worth the hotkey. |
| Power Stance | Hero | → **Auto-passive** (not cut, automated). Always on at 4th job. |
| Achilles | Hero/Paladin/DK | → **Auto-passive**. Always on at 4th job. |

### Mage Cuts

| Skill | Class | Why Cut |
|-------|-------|---------|
| Improving MP Recovery | 1st job | Same as warrior. |
| MP Eater | 2nd job (all) | Passive mana sustain — pots handle this. |
| Slow | I/L, F/P | Mob debuff, outclassed by actual damage. |
| Seal | I/L, F/P | Same. Seal a mob or kill it? Kill it. |
| Magic Armor | 1st job | Negligible DEF bonus. |
| Partial Resistance | All mage | Elemental resist — too niche, too weak. |
| Elemental Resistance | All mage | Same. |

### Bowman Cuts

| Skill | Class | Why Cut |
|-------|-------|---------|
| Focus | 1st job | +20 ACC/AVOID. Negligible. |
| Eye of Amazon | 1st job | Range increase — baked into class identity. |
| Nimble Body | 1st job | Speed/jump — not meaningful enough. |
| Thrust | 2nd job | KB resist — irrelevant for ranged. |
| Puppet | 3rd job (both) | Decoy — gimmicky, rarely useful in practice. |

### Thief Cuts

| Skill | Class | Why Cut |
|-------|-------|---------|
| Keen Eyes | 1st job | Range/ACC — baked in. |
| Disorder | 1st job | Mob debuff — kill it instead. |
| Nimble Body | 1st job | Same as bowman. |
| Alchemist | Hermit/NL | Potion efficiency — pots are cheap. |
| Meso Up | Hermit | Meso drop rate — economy handled differently. |
| Shadow Meso | Hermit | Meso-as-damage — gimmick removed. |
| Taunt | NL | Mob aggro for a ranged class. Makes no sense. |
| Ninja Ambush | NL + Shadower | DoT trap on the ground. Clunky, rarely used. |
| Shadow Meso | Bandit/CB | Meso cost attacks — entire meso gimmick removed from Shadower line (see Shadower Overhaul). |
| Pickpocket (stock) | CB/Shadower | Replaced with "Marked for Death" (see below). |
| Meso Explosion (stock) | CB/Shadower | Replaced with "Shadow Flurry" (see below). |
| Meso Guard (stock) | CB/Shadower | Replaced with "Shadow Armor" (see below). |

### Pirate Cuts

| Skill | Class | Why Cut |
|-------|-------|---------|
| Bullet Time | 1st job | Speed/avoid — negligible. |
| MP Recovery (Brawler) | 2nd job | Same logic as warriors/mages. |
| Oak Barrel | Brawler | Turns into a barrel. Meme skill. |
| Invisible Shot | Gunslinger | Short-range push for a ranged class. Contradicts identity. |

---

## Class-Specific Revamps

### Hero — Streamlined Berserker

**4th Job Active Kit** (after cuts):
- **Brandish** — Primary attack. Multi-hit melee.
- **Enrage** — Self-buff. +ATK, drains HP. Risk/reward toggle.
- **Rush** — Charge forward, KB mobs. Mobility + positioning.

**Auto-Passives at 4th Job**:
- Achilles (damage reduction)
- Power Stance (KB resist)
- Maple Warrior (all stats %)

**Cut**: Monster Magnet, Guardian
**Result**: Clean 3-active 3-passive 4th job. Hero = hit things hard, charge through, tank with Enrage risk.

### Paladin — Holy Tank

**4th Job Active Kit**:
- **Blast** — Primary attack. Holy element.
- **Heaven's Hammer** — AoE nuke. Long cooldown.
- **Rush** — Same as Hero.
- **Guardian** — *(kept for Paladin only, reworked)* Party damage reduction for 30s.

**Auto-Passives**: Achilles, Power Stance, Maple Warrior

**Note**: Paladin keeps a defensive active (reworked Guardian) because tank identity fits. Hero loses it because Hero = offense.

### Dark Knight — Berserk Bruiser

**4th Job Active Kit**:
- **Crusher** — Primary attack.
- **Berserk** — Signature skill. Massive damage at low HP.
- **Rush** — Charge.

**Auto-Passives**: Achilles, Power Stance, Maple Warrior, Beholder (passive summon)

### Shadower — Complete Overhaul (Melee Assassin Identity)

**The Problem**: Stock Shadower is built around meso gimmicks (Meso Explosion, Pickpocket, Meso Guard, Shadow Meso). On a small private server, meso mechanics aren't fun — they're tedious. The class has no real identity beyond "thief who uses money."

**The Solution**: Rebuild Shadower as a **melee assassin** — fast, lethal, shadow-themed. Uses daggers like a surgical instrument. The fantasy is a rogue who strikes from the shadows, marks targets, and overwhelms with speed.

#### Base Kit Changes

| Stock Skill | Replacement | Description |
|------------|-------------|-------------|
| Meso Explosion | **Shadow Flurry** | Fast 4-hit combo attack. Primary damage skill. Each hit has a shadow afterimage effect. |
| Pickpocket | **Marked for Death** | Passive mark applied on attack. Marked mobs take 1.5x damage from you for 8s. Visual: dark cross appears over mob. |
| Meso Guard | **Shadow Armor** | Passive -20% damage taken. No meso cost. Always on. Shadow wisps orbit your character. |
| Chakra | **Chakra** (BUFFED) | Now heals HP + cleanses debuffs + grants +20 ATK buff for 30s. The self-sustain skill. |

#### Other Shadower Changes
- **Steal** (Bandit, 2nd job): Reworked. Guaranteed rare drop from any mob, once per mob type. Exploration tool — seek out every mob species, steal something unique. Makes leveling a treasure hunt.
- **Assassinate**: Unchanged. Still the big single-target nuke.
- **Boomerang Step**: Unchanged. AoE mobbing skill.
- **Smokescreen**: Unchanged. Party utility.
- **Band of Thieves**: Unchanged. Summon skill.

**Result**: Shadower goes from "meso gimmick class" to "fast melee assassin who marks targets and overwhelms with combos." Shadow Flurry (spam) → Marked for Death (auto-applied) → Assassinate (finisher) is the new rotation. Shadow Armor + Chakra handle survivability.

### Night Lord — Precision Star Thrower

**Cuts**: Taunt, Ninja Ambush, Alchemist, Shadow Meso, Meso Up
**Kept**: Triple Throw, Shadow Stars, Avenger, Shadow Shifter, Venom, Ninja Storm

**Result**: NL is clean ranged DPS. No gimmicks. Stars go in, damage comes out.

### Mages — Elemental Identity Preserved

**Cuts**: MP Eater, Slow, Seal, Magic Armor, Partial/Elemental Resistance, Improving MP Recovery
**Kept**: All core elemental attacks, Infinity, Bahamut/Ifrit/Elquines, Holy Shield, Resurrection, etc.

**Result**: Mages lose useless passives and niche debuffs. Core identity (elements, summons, party support) untouched.

### Bowmen — Mobile Rangers

**Cuts**: Focus, Eye of Amazon, Nimble Body, Thrust, Puppet
**Kept**: All arrow attacks, Sharp Eyes, Hurricane/Snipe, Concentrate, etc.

**Result**: Bowmen lose filler 1st job passives and the Puppet gimmick. Pure ranged DPS identity preserved.

### Pirates — Brawler / Gunner Split

**Cuts**: Bullet Time, MP Recovery, Oak Barrel, Invisible Shot
**Kept**: All core attacks, Barrage, Dragon Strike, Battleship, Rapid Fire, etc.

**Result**: Cleaner split between Bucc (melee brawler) and Corsair (ranged gunner).

### Cleric Line — Invincible Rework

**Invincible** (Cleric, 2nd job): Reworked → **"Sanctuary"**
- Party damage reduction aura for 30s.
- Replaces a useless self-buff with meaningful party utility.
- Fits Cleric's identity as the support class.

---

## 4.5 Job Skills — Branch-Specific Endgame

### Overview

After defeating Empress Cygnus, players travel to Rien and undergo class-specific trials. Each final job (12 total) receives **4 unique skills** — 3 from trials + 1 ultimate from the final challenge.

**Animation sources**: All 4.5 skills reuse existing CK/Aran visual effects and animations from the repack. No new sprites needed — we're repurposing disabled class content.

| Source Class | Provides Animations For | Skill Count |
|-------------|------------------------|-------------|
| Dawn Warrior + Aran | Warriors (Hero/Paladin/DK) | 12 |
| Blaze Wizard | Mages (F/P, I/L, Bishop) | 12 |
| Wind Archer | Bowmen (BM/MM) | 8 |
| Night Walker + DB effects | Thieves (NL/Shadower) | 8 |
| Thunder Breaker | Pirates (Bucc/Corsair) | 8 |

**No Dual Blade in repack**: Skill files 430-434 don't exist. BUT 96 Katara weapon animations exist in Character.wz/Weapon/01342xxx. Shadower's 4.5 skills use DB-style shadow **effects** (shadow off-hand visuals), not actual Katara equipment.

### Trial Structure

Rien trials are **branch-specific**. The Archive Keeper identifies your exact job and assigns tailored challenges:

| Explorer Branch | Trial Element | Source Class | Trial Theme |
|----------------|--------------|-------------|-------------|
| Warrior | Light + Combo | Dawn Warrior + Aran | Endurance — survive escalating waves |
| Mage | Fire | Blaze Wizard | Precision — kill specific targets, avoid others |
| Bowman | Wind | Wind Archer | Speed — clear waves within time limit |
| Thief | Shadow | Night Walker | Stealth — reach the end without being detected |
| Pirate | Lightning | Thunder Breaker | Adaptation — mechanics change each wave |

3 trials = 3 skills. Final combined trial = ultimate (4th skill).

### Skill Stones (Rien Enhancement)

Rien's specialty vendor sells **Skill Stones** — consumables that enhance 4.5 skills:
- Cost: 2M meso each
- Effect: +1 skill level (max 3 enhancements per skill)
- Each enhancement: ~10% more damage/duration/effect
- Cannot exceed max level — just adds extra scaling on top

---

## 4.5 Skills by Class

### Hero (Warrior → Fighter → Crusader → Hero)

| # | Skill | Type | Description | Source |
|---|-------|------|-------------|--------|
| 1 | **Soul Driver** | Active, ranged | Launches a blade of light forward. Hits up to 6 mobs in a line. 8s CD. Gives Hero a ranged option they've never had. | Dawn Warrior |
| 2 | **Rolling Spin** | Active, AoE | 360-degree spinning slash. Hits all mobs around you. Short range, big damage. 12s CD. | Aran |
| 3 | **Final Charge** | Active, mobility | Dash forward dealing damage. Gap closer. Covers half a platform. 6s CD. | Aran |
| 4 | **Raging Tempest** | **ULTIMATE** | Screen-wide sword energy nuke. Massive damage to all mobs on screen. 120s CD. The "I win" button for emergencies. | Dawn Warrior |

**Hero identity after 4.5**: Melee powerhouse with a ranged poke (Soul Driver), a spin AoE (Rolling Spin), a gap close (Final Charge), and a panic button (Raging Tempest). Covers Hero's biggest weakness — no AoE/range.

### Paladin (Warrior → Page → White Knight → Paladin)

| # | Skill | Type | Description | Source |
|---|-------|------|-------------|--------|
| 1 | **Soul Blade** | Active, ranged | Holy energy blade projectile. Hits up to 4 mobs. Deals holy damage. 8s CD. | Dawn Warrior |
| 2 | **Soul Charge** | Buff | +30% damage for 30s. Stacks with elemental charges. 90s CD. | Dawn Warrior |
| 3 | **Snow Charge** | Active, CC | Ice AoE slam. Freezes all mobs in range for 5s. 15s CD. Crowd control tool. | Dawn Warrior (ice element) |
| 4 | **Divine Tempest** | **ULTIMATE** | Holy AoE explosion. Massive damage + heals party for 30% max HP. 120s CD. The holy nuke that also saves your party. | Dawn Warrior |

**Paladin identity after 4.5**: Holy tank with party utility. Soul Blade for range, Snow Charge for CC, Divine Tempest for clutch party heal + damage.

### Dark Knight (Warrior → Spearman → Dragon Knight → Dark Knight)

| # | Skill | Type | Description | Source |
|---|-------|------|-------------|--------|
| 1 | **Final Blow** | Active, melee | Massive single hit. Damage scales with missing HP (synergy with Berserk). 10s CD. | Aran |
| 2 | **Combo Fenrir** | Active, charge | Summon a spectral wolf that charges forward. Hits up to 8 mobs in a line. 15s CD. | Aran |
| 3 | **Freeze Standing** | Active, AoE CC | Slam the ground, freeze all nearby mobs for 6s. Defensive tool. 20s CD. | Aran |
| 4 | **Blood Tempest** | **ULTIMATE** | Sacrifice 50% current HP for massive AoE dark damage. At <30% HP (Berserk active): deals 2x damage. 120s CD. The ultimate Berserk synergy skill. | Aran |

**Dark Knight identity after 4.5**: Risk/reward berserker. Final Blow rewards low HP. Blood Tempest + Berserk = the most dangerous glass cannon combo in the game.

### Fire/Poison Mage

| # | Skill | Type | Description | Source |
|---|-------|------|-------------|--------|
| 1 | **Fire Pillar** | Active, ground AoE | Summon a pillar of fire at target location. Persists for 8s, dealing DoT to all mobs inside. 15s CD. | Blaze Wizard |
| 2 | **Flame Gear** | Active, orbital | 3 fire orbs orbit your character for 30s. Each orb deals fire damage to mobs that touch it. 45s CD. | Blaze Wizard |
| 3 | **Elemental Reset** | Active, debuff | Strip elemental resistance from all mobs on screen for 20s. Your fire/poison does full damage even to fire-immune mobs. 60s CD. | Blaze Wizard |
| 4 | **Inferno** | **ULTIMATE** | Channel a massive fire beam forward for 3s. Hits all mobs in a wide line. Leaves burning ground for 5s after. 120s CD. | Blaze Wizard |

**F/P identity after 4.5**: DoT king. Fire Pillar + Flame Gear + Poison Mist = the entire screen is on fire. Elemental Reset removes the one thing that counters you.

### Ice/Lightning Mage

| # | Skill | Type | Description | Source |
|---|-------|------|-------------|--------|
| 1 | **Ice Pillar** | Active, ground AoE | Summon an ice pillar. Persists for 8s, freezing mobs that enter. 15s CD. | Blaze Wizard (ice reskin) |
| 2 | **Frost Gear** | Active, orbital | 3 ice orbs orbit you for 30s. Mobs that touch them are slowed 50% for 5s. 45s CD. | Blaze Wizard (ice reskin) |
| 3 | **Lightning Conduit** | Active, chain | Lightning bolt chains between up to 5 targets. Each chain deals 80% of previous hit. 10s CD. | Blaze Wizard (lightning reskin) |
| 4 | **Absolute Zero** | **ULTIMATE** | Ice beam + screen-wide freeze for 8s. All mobs frozen solid. During freeze: +50% damage from all sources. 120s CD. | Blaze Wizard (ice reskin) |

**I/L identity after 4.5**: CC specialist. Freeze everything, then shatter it. Absolute Zero is the ultimate "stop the world" button — 8s of free damage for the whole party.

### Bishop

| # | Skill | Type | Description | Source |
|---|-------|------|-------------|--------|
| 1 | **Sacred Pillar** | Active, AoE + heal | Holy pillar. Damages mobs in range AND heals party members in range. 15s CD. Dual-purpose. | Blaze Wizard (holy reskin) |
| 2 | **Holy Gear** | Active, orbital | 3 holy orbs orbit you. Party members near you regen 2% HP/s while orbs active. 30s duration, 60s CD. | Blaze Wizard (holy reskin) |
| 3 | **Radiance** | Buff | Party-wide buff: +20% EXP, +holy element on all attacks for 60s. 180s CD. The ultimate party buff. | Blaze Wizard (holy reskin) |
| 4 | **Divine Judgment** | **ULTIMATE** | Holy beam from the sky. Massive AoE damage + full party heal + 10s party invulnerability. 180s CD (longest in game). THE clutch button. | Blaze Wizard (holy reskin) |

**Bishop identity after 4.5**: Ultimate support. Divine Judgment is the most powerful defensive skill in the game — full heal + 10s invuln for the whole party. Radiance makes Bishop THE party class.

### Bowmaster

| # | Skill | Type | Description | Source |
|---|-------|------|-------------|--------|
| 1 | **Wind Walk** | Active, mobility | Dash forward with i-frames (invincibility during dash). 4s CD. Repositioning tool. | Wind Archer |
| 2 | **Storm Break** | Active, AoE | Wind explosion around you. Knocks back all nearby mobs. Emergency space-maker. 10s CD. | Wind Archer |
| 3 | **Wind Piercing** | Active, ranged line | Charged arrow that pierces through all mobs in a line. Unlimited pierce. 8s CD. | Wind Archer |
| 4 | **Gale Force** | **ULTIMATE** | Massive charged shot. On hit, creates a slow field (50% slow for 10s) on the ground. Huge damage + area denial. 120s CD. | Wind Archer |

**Bowmaster identity after 4.5**: Mobile ranged DPS. Wind Walk gives desperately needed mobility. Hurricane spam → Wind Piercing for line-ups → Gale Force for area control.

### Marksman

| # | Skill | Type | Description | Source |
|---|-------|------|-------------|--------|
| 1 | **Wind Walk** | Active, mobility | Same as Bowmaster. Dash with i-frames. 4s CD. | Wind Archer |
| 2 | **Eagle Eye** | Active, mark | Mark up to 3 targets. Marked targets take +25% damage from Snipe. Lasts 15s. 20s CD. | Wind Archer |
| 3 | **Storm Break** | Active, AoE + debuff | Wind explosion. Knocks back mobs + applies "Vulnerable" debuff (+15% damage taken from all sources, 10s). 12s CD. | Wind Archer |
| 4 | **Death Arrow** | **ULTIMATE** | Channeled line shot. Snipe-level damage to ALL mobs in a straight line. Essentially a "line Snipe." 120s CD. | Wind Archer |

**Marksman identity after 4.5**: Precision sniper. Eagle Eye → Snipe on marked targets = massive single-target damage. Death Arrow turns Snipe's single-target power into a line nuke.

### Night Lord

| # | Skill | Type | Description | Source |
|---|-------|------|-------------|--------|
| 1 | **Vanish** | Active, stealth | 5s stealth. First attack from stealth deals 2x damage. 15s CD. Burst opener. | Night Walker |
| 2 | **Poison Bomb** | Active, ground DoT | Throw a poison bomb. Creates a DoT zone for 8s. Mobs in zone take poison damage/tick. 12s CD. Area denial. | Night Walker |
| 3 | **Darkness** | Buff | +30% crit rate, +20% star damage for 30s. 90s CD. The "I'm going all in" steroid. | Night Walker |
| 4 | **Shadow Veil** | **ULTIMATE** | Screen goes dark. All mobs blinded (miss rate +80%) for 6s. Your party gets +50% crit rate during the veil. 120s CD. Offensive+defensive hybrid. | Night Walker |

**Night Lord identity after 4.5**: Burst DPS from stealth. Vanish → Darkness → Triple Throw from stealth = nuclear opener. Shadow Veil is the ultimate party crit steroid.

### Shadower

| # | Skill | Type | Description | Source |
|---|-------|------|-------------|--------|
| 1 | **Bloody Storm** | Active, melee combo | 6-hit dagger combo. DB-style rapid slashing animation. Shadow off-hand visual effect. Fast, flashy, primary spam skill. 0s CD (spammable). | DB effects (shadow reskin) |
| 2 | **Tornado Spin** | Active, 360° AoE | Spin with both hands (shadow dual-slash visual). Hits all mobs around you. 8s CD. The mobbing skill. | DB effects (shadow reskin) |
| 3 | **Mirror Image** | Active, summon | Create a shadow clone that mimics your attacks for 30s. +50% effective DPS. 90s CD. Shadower's "double" fantasy. | Night Walker |
| 4 | **Final Cut** | **ULTIMATE** | Dash forward through all mobs in a line, dealing massive damage. On use: +30% speed, +20% damage buff for 30s. 120s CD. The initiation + steroid combo. | DB effects (shadow reskin) |

**Shadower identity after 4.5**: Fast melee assassin with shadow clone support. Bloody Storm (spam) + Marked for Death (auto from base kit) → Tornado Spin (AoE) → Mirror Image (DPS double) → Assassinate (finisher). Final Cut for openers and emergency burst. This is the Shadower that Declan mains.

### Buccaneer

| # | Skill | Type | Description | Source |
|---|-------|------|-------------|--------|
| 1 | **Spark** | Active, chain AoE | Lightning fist that chains to nearby mobs. Hits up to 4 targets. 6s CD. | Thunder Breaker |
| 2 | **Lightning Charge** | Buff | Infuse fists with lightning. +element damage + attacks stun for 2s. 30s duration, 60s CD. | Thunder Breaker |
| 3 | **Energy Drain** | Active, AoE lifesteal | AoE punch that heals you for 30% of damage dealt. 15s CD. Sustain tool. | Thunder Breaker |
| 4 | **Thunder God** | **ULTIMATE** | Call lightning from the sky. Massive AoE damage + all mobs paralyzed (stunned) for 5s. 120s CD. The thunder god fantasy. | Thunder Breaker |

**Buccaneer identity after 4.5**: Lightning-infused brawler. Lightning Charge + Barrage combo. Energy Drain for sustain. Thunder God for the "I am become thunder" moment.

### Corsair

| # | Skill | Type | Description | Source |
|---|-------|------|-------------|--------|
| 1 | **Shark Wave** | Active, traveling AoE | Fire a shark-shaped projectile that travels forward, hitting all mobs in its path. 10s CD. | Thunder Breaker (reskin) |
| 2 | **Spark** | Passive + proc | Bullets occasionally chain lightning to nearby mobs (20% chance per hit, chains to 2 targets). No CD. | Thunder Breaker |
| 3 | **Overcharge** | Buff | +40% crit rate, +25% crit damage for 30s. 90s CD. Pure DPS steroid. | Thunder Breaker |
| 4 | **Thunderstrike Barrage** | **ULTIMATE** | Channeled skill (3s). Rain lightning-infused bullets across the screen. Massive DPS to all targets. Can't move during channel. 120s CD. | Thunder Breaker |

**Corsair identity after 4.5**: Ranged gunner with proc-based chain lightning. Shark Wave for AoE, Overcharge for boss burns, Thunderstrike Barrage for "hold still and delete the screen."

---

## Skill Summary Table

### Total Active Hotkeys by Class (4th Job + 4.5)

| Class | 4th Job Actives | 4.5 Actives | Total Hotkeys | Notes |
|-------|----------------|-------------|---------------|-------|
| Hero | 3 (Brandish, Enrage, Rush) | 4 | 7 | Clean and focused |
| Paladin | 4 (Blast, HH, Rush, Guardian) | 4 | 8 | Most buttons = tank/support |
| Dark Knight | 3 (Crusher, Berserk, Rush) | 4 | 7 | Berserk is toggle |
| F/P Mage | 4 (Meteor, Paralyze, Mist, Ifrit) | 4 | 8 | DoT management |
| I/L Mage | 4 (Blizzard, CL, Elquines, Ice) | 4 | 8 | CC management |
| Bishop | 4 (Genesis, Angel Ray, Bahamut, Res) | 4 | 8 | Support toolkit |
| Bowmaster | 3 (Hurricane, Dragon Pulse, SE) | 4 | 7 | Hurricane carry |
| Marksman | 3 (Snipe, Piercing, SE) | 4 | 7 | Snipe carry |
| Night Lord | 3 (Triple Throw, Ninja Storm, Venom) | 4 | 7 | Stars carry |
| Shadower | 4 (Assassinate, BStep, Smoke, BoT) | 4 | 8 | Highest APM class |
| Buccaneer | 4 (Barrage, Dragon Strike, TF, Demo) | 4 | 8 | Brawler combos |
| Corsair | 4 (Rapid Fire, Battleship, Bullseye, 8Legs) | 4 | 8 | Gunner procs |

**Average: 7-8 active hotkeys per class.** Down from 10-14 in stock v83. Every remaining skill matters.

---

## Animation Source Mapping

### How 4.5 Skills Get Their Visuals

Each 4.5 skill reuses an existing animation from a disabled class. The server defines the skill behavior; the client shows the animation. We map 4.5 skill IDs to existing animation data.

| 4.5 Skill | Animation Source | Source Skill ID Range | Notes |
|-----------|-----------------|----------------------|-------|
| Soul Driver | Dawn Warrior slash | 1100-1111.img.xml | Soul element slash |
| Rolling Spin | Aran combo | 2100-2112.img.xml | Spinning combo finisher |
| Final Charge | Aran rush | 2100-2112.img.xml | Forward charge |
| Raging Tempest | Dawn Warrior AoE | 1111.img.xml | Screen-wide slash effect |
| Fire/Ice/Sacred Pillar | Blaze Wizard pillar | 1200-1211.img.xml | Element-reskinned pillar |
| Flame/Frost/Holy Gear | Blaze Wizard orbital | 1210.img.xml | Orbiting element balls |
| Wind Walk | Wind Archer dash | 1300-1311.img.xml | Wind dash effect |
| Storm Break | Wind Archer AoE | 1311.img.xml | Wind explosion |
| Vanish | Night Walker stealth | 1400-1411.img.xml | Shadow fade |
| Bloody Storm | DB-style slash | Katara animations (01342xxx) | Shadow dual-slash |
| Tornado Spin | DB-style spin | Katara animations (01342xxx) | Spinning dual-slash |
| Mirror Image | Night Walker shadow | 1411.img.xml | Shadow clone |
| Final Cut | DB-style dash | Katara animations (01342xxx) | Shadow dash-through |
| Spark | Thunder Breaker chain | 1500-1511.img.xml | Lightning chain |
| Lightning Charge | Thunder Breaker buff | 1510.img.xml | Lightning infuse |
| Thunder God | Thunder Breaker AoE | 1511.img.xml | Sky lightning |

### Implementation Strategy

**Option A (preferred): Repurpose CK/Aran skill IDs**
- Use the actual CK/Aran skill IDs (e.g., Dawn Warrior skill 11111004 becomes Hero's "Soul Driver")
- Server grants Explorer characters these skill IDs via custom logic
- Client already has the animation data for these IDs
- Risk: CK/Aran code paths may interfere — need testing

**Option B: New skill IDs with copied animations**
- Create new skill IDs in the Explorer range
- Copy animation data from CK/Aran skill entries into the new IDs
- Cleaner separation but requires Skill.wz editing
- More work upfront, less risk of side effects

**Recommendation**: Start with Option A (less work), switch to Option B if there are conflicts. The server (Cosmic Java) handles skill grants — the client just needs to know "when I use skill X, show animation Y."

---

## Open Questions

1. **Skill animation re-audit needed**: The regex-based audit found 333 skills but 0 hit/ball/effect data (parsing issue on single-line XML). Need fixed parser to confirm which specific CK/Aran animations are suitable for each 4.5 skill.

2. **Katara animations**: 96 entries exist in Character.wz/Weapon/01342xxx. Need visual preview (HaRepacker on Windows) to confirm they provide the dual-slash effects we want for Shadower's 4.5 kit.

3. **Server-side implementation**: How to grant CK/Aran skill IDs to Explorer characters in Cosmic's Java codebase. Need to investigate `PlayerSkill`, `SkillFactory`, and the job advancement handlers.

4. **Skill Stone balancing**: Max 3 enhancements per skill at 2M each = 24M meso per class for full enhancement. Is this the right price point? Adjust after playtesting.

5. **Cooldown tuning**: All CDs listed are initial values. Will need playtesting — especially ultimates (120-180s CDs). Too long = never used. Too short = spammy.
