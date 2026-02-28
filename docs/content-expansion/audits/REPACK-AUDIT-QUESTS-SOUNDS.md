# TwinleafStory Repack Audit: Quests & Sounds

**Source**: `/Users/ichiran/Downloads/wz/Quest.wz/` and `/Users/ichiran/Downloads/wz/Sound.wz/`
**Date**: 2026-02-27
**Purpose**: Catalog quest data and sound/BGM inventory for v83 community repack

---

## 1. Quest Data Summary

### Quest Count & ID Range

| Metric | Value |
|--------|-------|
| Total quests with names defined | 2,789 |
| Lowest quest ID | 1000 |
| Highest quest ID | ~29933 |
| Quest files analyzed | QuestInfo.img.xml, Check.img.xml, Act.img.xml, Say.img.xml, PQuest.img.xml |

### ID Range Distribution (approximate)

- **1000-1999**: Victoria Island beginner/early quests (Maple Island, Henesys, Kerning, etc.)
- **2000-2999**: Victoria Island mid-level quests, Ossyria quests
- **3000-3999**: El Nath, Ludibrium, Aqua Road, Temple of Time
- **4000-4999**: Nihal Desert, Magatia, Masteria
- **5000-5999**: Additional content quests
- **6000-6999**: Job advancement, equipment quests
- **7000-7999**: Extended quests
- **8000-8999**: Various chain quests (Lionel, etc.)
- **9000-9999**: Event/seasonal quests
- **10000-10399**: Event quests, Aran event quests (10341-10381)
- **20000-20999**: Cygnus Knights class quests
- **21000-21999**: Aran class quests
- **28000-28999**: Miscellaneous (Mardi Gras, Lilin gifts, etc.)
- **29900-29933**: Medal/title quests (Aran the Hero, Honorary Subway Worker, etc.)

---

## 2. Target Content Quest Chains

### Temple of Time (Quests 3500-3539)

**PRESENT IN REPACK** -- Full Temple of Time questline found.

| Quest ID | Name |
|----------|------|
| 3500 | Path to the Past |
| 3501 | The One Who Walks Down Memory Lane 1 |
| 3502 | The One Who Walks Down Memory Lane 2 |
| 3503 | The One Who Walks Down Memory Lane 3 |
| 3504 | The One Who Walks Down Memory Lane 4 |
| 3505 | The One Who Walks Down Memory Lane 5 |
| 3506 | Lost Memory |
| 3507 | Memory Keeper |
| 3508 | The One Who Walks Down the Road of Regrets 1 |
| 3509 | The One Who Walks Down the Road of Regrets 2 |
| 3510 | The One Who Walks Down the Road of Regrets 3 |
| 3511 | The One Who Walks Down the Road of Regrets 4 |
| 3512 | The One Who Walks Down the Road of Regrets 5 |
| 3513 | Frozen Emotions |
| 3514 | The Sorcerer Who Sells Emotions |
| 3515 | The One Who Walks Through the Road to Oblivion 1 |
| 3516 | The One Who Walks Through the Road to Oblivion 2 |
| 3517 | The One Who Walks Through the Road to Oblivion 3 |
| 3518 | The One Who Walks Through the Road to Oblivion 4 |
| 3519 | The One Who Walks Through the Road to Oblivion 5 |
| 3520 | The Goddess' Blessing |
| 3521 | Force Field |
| 3522 | Beyond the Ruins |
| 3523-3527, 3529 | In Search for the Lost Memory (multiple) |
| 3528 | Breaking the Force Field |
| 3530-3533 | The One Who Walks Through the Road to Oblivion 1-4 (alternate/repeat set) |
| 3534 | (Dialogue fragment - Record Keeper quest) |
| 3535 | The Goddess' Blessing (alt) |
| 3536 | Force Field (alt) |
| 3537 | Breaking the Force Field (alt) |
| 3538 | Beyond the Ruins (alt) |
| 3539 | Searching for Lost Memories |

### Temple of Time - 999 Kill Quests (CRITICAL DATA)

The following quests require killing 999 of a specific Temple of Time mob. NPC for all is **2140000** (Memory Keeper / Temple guide).

| Quest ID | Quest Name | Mob ID | Kill Count | Min Level |
|----------|-----------|--------|------------|-----------|
| 3501 | Memory Lane 1 | 8200001 | 999 | -- |
| 3502 | Memory Lane 2 | 8200002 | 999 | -- |
| 3503 | Memory Lane 3 | 8200003 | 999 | -- |
| 3504 | Memory Lane 4 | 8200004 | 999 | -- |
| 3508 | Road of Regrets 1 | 8200005 | 999 | 106 |
| 3509 | Road of Regrets 2 | 8200006 | 999 | 109 |
| 3510 | Road of Regrets 3 | 8200007 | 999 | 113 |
| 3511 | Road of Regrets 4 | 8200008 | 999 | 116 |
| 3515 | Road to Oblivion 1 | 8200009 | 999 | 121 |
| 3516 | Road to Oblivion 2 | 8200010 | 999 | 124 |
| 3517 | Road to Oblivion 3 | 8200011 | 999 | 128 |
| 3518 | Road to Oblivion 4 | 8200012 | 999 | 131 |

**Alternate Oblivion set** (quests 3530-3533, all min level 120):

| Quest ID | Mob ID | Kill Count |
|----------|--------|------------|
| 3530 | 8200009 | 999 |
| 3531 | 8200010 | 999 |
| 3532 | 8200011 | 999 |
| 3533 | 8200012 | 999 |

**Boss quests** (kill 1 each):
- Quest 3512 (Road of Regrets 5): Kill 1x mob 8220005
- Quest 3519 (Road to Oblivion 5): Kill 1x mob 8220006

**Mob ID reference** (8200001-8200012 = ToT regular mobs in order of area progression):
- 8200001-8200004: Memory Lane mobs (Lv ~100-105)
- 8200005-8200008: Road of Regrets mobs (Lv ~106-120)
- 8200009-8200012: Road to Oblivion mobs (Lv ~121-135)
- 8220005, 8220006: Area bosses (single kill required)

### Non-ToT 999 Kill Quests

Also found 999-kill quests outside Temple of Time (DANGER/POLLUTED series, NPC 1061011):

| Quest ID | Quest Name | Mob ID | Kill Count | Max Level |
|----------|-----------|--------|------------|-----------|
| 2111 | DANGER! <1-G. Mushroom> | 9101000 | 999 | 45 |
| 2112 | DANGER! <2-H. Mushroom> | 2110200 | 999 | 52 |
| 2113 | DANGER! <3-Z. Mushroom> | 9101001 | 999 | 54 |
| 2114 | POLLUTED! <1-Evil Eye> | 2230100 | 999 | 57 |
| 2115 | POLLUTED! <2-Curse Eye> | 3230100 | 999 | 65 |

These are Ellin Forest / Victoria Island repeatable quests with level caps.

### LHC / Von Leon

**NOT PRESENT** -- No Lion Heart Castle, Von Leon, or Crimsonheart quests found. Only "Lionel's Necklace" quests (8037-8040) which are a different questline (NLC/Phantom Forest). This is expected for v83.

### Future Ereve / Cygnus Empress

**NOT PRESENT** -- No Future Ereve or Knight Stronghold quests found. Only one "Fight for the future" (quest 4513) which is unrelated. No Empress raid quests. This content was post-v83.

### Singapore / Ulu City

**NOT PRESENT** -- No Singapore, Ulu City, Boat Quay, CBD, or Krexel quests found in QuestInfo. Despite BgmSG existing in Sound.wz, the quest data for Singapore content is missing from this repack.

### Cygnus Knights (Quests 20000-20999)

**PRESENT** -- Full Cygnus Knight class questline found.

Key quests:
| Quest ID | Name |
|----------|------|
| 20000 | Greetings from the Young Empress |
| 20001 | Neinheart the Tactician |
| 20002-20007 | Kiku's Training Sessions (1-5 + instructor intro) |
| 20008 | The Path of a Knight |
| 20010 | Welcome to Ereve |
| 20014 | The Empress is Waiting |
| 20017-20019 | Knight Training (1st, 2nd, Last) |
| 20020 | 5 Different Paths of Cygnus Knights |
| 20100-20105 | Job selection (Dawn Warrior, Blaze Wizard, Wind Archer, Night Walker, Thunder Breaker) |
| 20200-20205 | Knighthood Exams |
| 20306-20310 | Ereve Investigation Permit (5 variants) |
| 20400 | Chasing the Knight's Target |
| 20406 | The Knight That Disappeared |
| 20408 | Chief Knight of the Empress |
| 20520-20527 | Knight's Dignity, Mounts, Pride |

### Aran (Quests 21000-21999 + 29924-29928)

**PRESENT** -- Full Aran class questline found.

Key quests:
| Quest ID | Name |
|----------|------|
| 21000-21001 | Find the Missing Kid 1-2 |
| 21010 | The Return of the Hero |
| 21011 | The Missing Weapon |
| 21012 | Abilities Lost |
| 21013 | A Gift for the Hero |
| 21014 | Lilin's Account |
| 21015-21018 | Basic Fitness Training 1-3 + Test |
| 21100-21101 | The Five Heroes, The Polearm-Wielding Hero |
| 21200-21202 | Weapon quests (In Search of Its Rightful Owner, Mirror of Desire, Ultimate Weapon) |
| 21300-21303 | Advanced quests (weapon, thief, Red Jade, Yeti) |
| 29924-29928 | Aran milestone quests (Revived, Memory, Agony, Hope, Hero) |

Supporting quests:
| Quest ID | Name |
|----------|------|
| 10341 | Aran's Revival |
| 10342-10352 | Aran Memories series (Vague, Dim, Faint, Cloudy, Lingering, Flickering) |
| 10360 | Aran Welcome Celebration |
| 10380 | Aran's Return |
| 10381 | Lilin's Present 3 |
| 28335-28336 | Lilin's Present 1-2 |

### Arcane River

**NOT PRESENT** -- No Arcane River quests. Expected, as Arcane River was added much later (v5th job era). However, the Sound.wz does contain Arcane River BGM (see Sound section below).

---

## 3. Party Quest Data (PQuest.img.xml)

13,363 bytes. Contains ranking data for party quests.

| PQ ID | Name | Ranking Metrics |
|-------|------|-----------------|
| 1200 | Moon Bunny's Rice Cake | Time (min), tries, CR (completion rate) |
| 1201 | First Time Together (KPQ) | Time, tries, CR |
| 1202 | The Crack of Dimension (Ludi PQ) | Time, tries, CR |
| 1203 | Remnants of Goddess (Nath PQ) | Time, tries, CR |
| 1204 | Lord Pirate | Tries, CR, item tiers |
| 1205 | Romeo and Juliet (R&J PQ) | Time, tries, CR |
| 1206 | Forest of Poison Haze (Elin PQ) | Time, tries, CR |
| 1300 | Ariant Hunting Competition | Tries, VR (victory rate) |
| 1301 | Monster Carnival (CPQ) | Tries, VR |
| 1302 | The 2nd Monster Carnival (CPQ2) | Tries, VR |

**Rank tiers**: S, A, B, C, D, F -- based on completion time (min), number of attempts (try), completion/victory rate (CR/VR), and item possession (have).

**Note**: No Zakum, Horntail, or other boss expeditions listed here. PQuest.img.xml only covers instanced party quests with ranking systems, not boss runs.

---

## 4. Dialogue Format (Say.img.xml)

File size: 4.33 MB (~4.3 million characters of NPC dialogue).

### Structure

```xml
<imgdir name="Say.img">
  <imgdir name="QUEST_ID">         <!-- Quest ID -->
    <imgdir name="0">              <!-- Stage 0 = quest start dialogue -->
      <string name="0" value="First dialogue line"/>
      <string name="1" value="Second dialogue line"/>
      ...
      <int name="ask" value="1"/>  <!-- 1 = yes/no prompt -->
      <imgdir name="yes">
        <string name="0" value="Acceptance response"/>
      </imgdir>
      <imgdir name="no">
        <string name="0" value="Rejection response"/>
      </imgdir>
      <imgdir name="stop">         <!-- Stop/cancel dialogue -->
        <imgdir name="npc">
          <string name="0" value="NPC reminder text"/>
        </imgdir>
      </imgdir>
    </imgdir>
    <imgdir name="1">              <!-- Stage 1 = completion dialogue -->
      ...
    </imgdir>
  </imgdir>
</imgdir>
```

### Text Formatting Codes

| Code | Meaning |
|------|---------|
| `#b` | Blue text (bold) |
| `#k` | Black text (reset) |
| `#r` | Red text |
| `#e` | Bold |
| `#n` | Normal (reset bold) |
| `#h0` | Player name |
| `#p<NPC_ID>#` | NPC name by ID |
| `#m<MAP_ID>#` | Map name by ID |
| `#t<ITEM_ID>#` | Item name by ID |
| `#i<ITEM_ID>#` or `#i<ITEM_ID>:` | Item icon |
| `#c<ITEM_ID>#` | Item count (current/required) |
| `#L<N>#` | Selection option start |
| `#l` | Selection option end |

### Example (Quest 1000 - Borrowing Sera's Mirror)

Stage 0 (NPC talks to player):
```
"You must be the new traveler. Still foreign to this, huh? I'll be giving you
important informations here and there so please listen carefully..."
"Man... the sun is literally burning my beautiful skin! Can you get me a mirror
from #r#p2100##k, please?"
```
- Yes branch: "Thank you... #r#p2100##k will be on the hill down on the east side..."
- No branch: "Don't want to? Hmmm... come back when you change your mind."

---

## 5. Sound File Inventory

### Overview

| Metric | Value |
|--------|-------|
| Total files | 53 |
| BGM track files (BgmXX) | 38 (Bgm00-25, 46-50, BgmEvent, BgmGL, BgmJp, BgmMY, BgmSG, BgmUI) |
| SFX files | 15 (CashEffect, ConsumeEffect, Field, Game, Item, Jukebox, MiniGame, Mob, Object, Pet, Radio, Reactor, Skill, Summon, UI, Weapon) |

### File Format

These are **XML metadata/reference files only**, not actual audio data. Each file is 89-281,491 bytes of XML containing `<sound name="TrackName"/>` entries. The actual audio data (MP3/PCM) would have been in the original .wz binary format before extraction. These XML files serve as a **track listing/index** for the Sound.wz archive.

### Complete BGM Track Listing

#### Bgm00.img.xml (Victoria Island - Sleepywood/Dungeon)
- SleepyWood, FloralLife, GoPicnic, Nightmare, RestNPeace, Darnell

#### Bgm01.img.xml (Victoria Island - Perion/Dungeons)
- AncientMove, MoonlightShadow, WhereTheBarlogFrom, CavaBien, HighlandStar, BadGuys

#### Bgm02.img.xml (Victoria Island - Ellinia)
- MissingYou, WhenTheMorningComes, EvilEyes, JungleBook, AboveTheTreetops

#### Bgm03.img.xml (Various Towns)
- Subway, Elfwood, BlueSky, Beachway, SnowyVillage

#### Bgm04.img.xml (Ludibrium/Orbis)
- PlayWithMe, WhiteChristmas, UponTheSky, ArabPirate, Shinin'Harbor, WarmRegard

#### Bgm05.img.xml (El Nath Mines)
- WolfWood, DownToTheCave, AbandonedMine, MineQuest, HellGate

#### Bgm06.img.xml (Boss Fights/Dungeons)
- FinalFight, WelcomeToTheHell, ComeWithMe, FlyingInABlueDream, FantasticThinking

#### Bgm07.img.xml (Ludibrium/Omega Sector)
- WaltzForWork, WhereverYouAre, FunnyTimeMaker, HighEnough, Fantasia

#### Bgm08.img.xml (Omega Sector/Elin Forest)
- LetsMarch, ForTheGlory, FindingForest, LetsHuntAliens, PlotOfPixie

#### Bgm09.img.xml (Various)
- DarkShadow, TheyMenacingYou, FairyTale, FairyTalediffvers, TimeAttack

#### Bgm10.img.xml (Leafre/Deep Dungeons)
- Timeless, TimelessB, BizarreTales, TheWayGrotesque, Eregos

#### Bgm11.img.xml (Aqua Road/Ludibrium)
- BlueWorld, Aquarium, ShiningSea, DownTown, DarkMountain

#### Bgm12.img.xml (Aqua Road/Deep)
- AquaCave, DeepSee, WaterWay, AcientRemain, RuinCastle, Dispute

#### Bgm13.img.xml (Leafre/Minar Forest)
- CokeTown, Leafre, Minar'sDream, AcientForest, TowerOfGoddess, FightSand

#### Bgm14.img.xml (Horntail/Ariant)
- DragonLoad, HonTale, CaveOfHontale, DragonNest, Ariant, HotDesert, ChaosPB

#### Bgm15.img.xml (Mu Lung/Pirate/Elin)
- MureungHill, MureungForest, WhiteHerb, Pirate, SunsetDesert, Nautilus, inNautilus, ElinForest, PoisonForest

#### **Bgm16.img.xml (TEMPLE OF TIME)**
- **TimeTemple** -- Temple of Time main theme
- **Remembrance** -- Road of Remembrance (Memory Lane)
- **Repentance** -- Road of Regrets
- **Forgetfulness** -- Road to Oblivion
- **Duskofgod** -- Dusk of the Gods / Goddess area
- **FightingPinkBeen** -- Pink Bean boss fight

#### Bgm17.img.xml (Mu Lung Dojo)
- MureungSchool1, MureungSchool2, MureungSchool3, MureungSchool4

#### **Bgm18.img.xml (EREVE / Cygnus Knights)**
- **QueensGarden** -- Ereve main theme (Empress's Garden)
- **DrillHall** -- Ereve training grounds
- **BlackWing** -- Black Wings theme
- **RaindropFlower** -- Ereve ambient
- **WolfAndSheep** -- Knight quest theme

#### **Bgm19.img.xml (RIEN / Aran)**
- **RienVillage** -- Rien Island town theme
- **SnowDrop** -- Rien field/snow area
- **BambooGym** -- Training area
- **CrystalCave** -- Ice cave dungeon
- **MushCatle** -- Mushroom Castle

#### Bgm20.img.xml (Masteria/Phantom Forest)
- NetsPiramid, NetsPiramid2, UnderSubway, UnderSubway2, GhostShip

#### Bgm21.img.xml (Kerning Square / Time Travel)
- KerningSquare, KerningSquareField, KerningSquareSubway, TeraForest, 2021year, 2099year, 2215year, 2230year, 2503year

#### Bgm22.img.xml (Edelstein / Resistance)
- EdelsteinCity, NationalPark, PowerStation, GelimerLab, UndergroundPlace, LowGradeOre, DespairOnDevil, DecisiveBattle

#### **Bgm23.img.xml (LION HEART CASTLE / LHC)**
- **CrimsonTower** -- Crimson Tower
- **LionHeart** -- Lion Heart Castle main theme
- **BlizzardCastle** -- Von Leon's castle
- **Bramble** -- Bramble area

#### Bgm24.img.xml (Battle/PvP/Monster Park)
- KreaseField, KreaseAgit, KreaseColosseum, battleEntrance, battleBGMTypeA-D, monsterPark

#### **Bgm25.img.xml (FUTURE EREVE / Knights Stronghold)**
- profession -- Crafting/profession theme
- **timeGate** -- Time Gate to future
- **destructionTown** -- Destroyed future town
- **knightsStronghold** -- Knights' Stronghold (Future Ereve main)
- **CygnusGarden** -- Cygnus Garden (Future)
- WindAndFlower, FlowerInBlue, SoundOfElf
- CrackOfDimension, AltarOfAkayrum
- **destructionPerionShelter** -- Destroyed Perion shelter
- **destructionPerion** -- Destroyed Perion field

#### Bgm46.img.xml (Arcane River - Vanishing Journey/Chu Chu/Lachelein)
- Volcanic Zone Of Extinction, Lake Of Oblivion, Cave Of Rest
- ChewChew MainTheme, ChewChew WildWorld
- LachelntheIllusionCity, ClockTowerofNightmare
- WierldForestIntheGirlsdream, BrokenDream

#### Bgm47.img.xml (Arcane River - Arcana/Morass + Illium)
- GoGoRangers!, DancesWithAliens, VacuumCleaner
- TheTuneOfAzureLight, TheTuneOfAzureLight2, ArcanaBoss
- SavageTerminal, HuntingGround, MrHazard
- AsylumAmbience, AsylumPiano, Asylum, CrystalAcademia
- DeathOfAsylum, DeathOfAsylumChoir, DeathOfAsylumChoirExtended
- IlliumRebirth, AsylumAmbiencePiano

#### Bgm48.img.xml (Arcane River - Esfera/Morass + Verdel)
- Nowhere, WayBackHome, noname, ForgottenNames, gloryWing
- MemoryOfKritias, SwampOfMemoryMoras, BlackDungeon
- OverTheClouds, OverTheClouds_RhythmicVer, EveningPrimrose
- Title, VerdelTown, VerdelField, VerdelDungeon
- Doomsday_FULL, Doomsday_LOOP, Memory, Outpost

#### Bgm49.img.xml (Arcane River - Tenebris/Limina)
- SoupOfLife, ConteminatedSea, TempleInTheMirror
- Diffraction, MirrorCage, BloodCage, WarCloud, StrangeFog
- WaveofEmptiness, FerociousBattlefield (multiple variants)
- SecretLabyrinth, EternalSwamp, HeartofSuffering, DepthOfPain

#### Bgm50.img.xml (Tenebris / Black Mage)
- TearsOfTheWorld, BlackFury, SubterminalPoint, TheWorld'sEnd
- TempleOfDarkness, ThroneOfDarkness, WorldHorizon, LostSpace
- NewBeginningNotTheEnd

#### BgmEvent.img.xml (Events)
- FunnyRabbit, FunnyRabbitFaster, wedding, weddingDance, wichTower

#### BgmGL.img.xml (Masteria/NLC/Crimsonwood)
- amoria, chapel, cathedral, Amorianchallenge
- NLCupbeat, NLChunt, NLCtown
- HauntedHouse, CrimsonwoodKeep, Bigfoot, PhantomForest
- CrimsonwoodKeepInterior, GrandmastersGauntlet, PartyQuestGL, Courtyard

#### BgmJp.img.xml (Japan/Zipangu)
- Feeling, BizarreForest, Yume, Bathroom, BattleField
- Hana, FirstStepMaster
- CastleOutSide, CastleInside, CastleBoss, CastleTrap
- WhenTheMorningComes, Elfwoods

#### BgmMY.img.xml (Malaysia)
- KualaLumpur, Highland

#### **BgmSG.img.xml (SINGAPORE)**
- **CBD_town** -- Central Business District town
- **CBD_field** -- CBD field area
- **BoatQuay_field** -- Boat Quay field
- **Ghostship** -- Ghost Ship
- **BoatQuay_town** -- Boat Quay town
- **Ulu_field** -- Ulu City field

#### BgmUI.img.xml (UI/System)
- NxLogo, WzLogo, WCSelect, ShopBgm, Title, NxLogoMS

### SFX Files

| File | Size | Content |
|------|------|---------|
| CashEffect.img.xml | 1,812 B | Cash shop item effects |
| ConsumeEffect.img.xml | 148 B | Consumable item sounds |
| Field.img.xml | 1,494 B | Field/PQ sounds (Party1, Coconut, MobCarnival, Dojang, Aran events) |
| Game.img.xml | 781 B | Game system sounds |
| Item.img.xml | 15,186 B | Item drop/pickup/use sounds |
| Jukebox.img.xml | 121 B | Jukebox system |
| MiniGame.img.xml | 384 B | Mini-game sounds |
| Mob.img.xml | 281,491 B | Monster sounds (largest SFX file) |
| Object.img.xml | 113 B | Map object sounds |
| Pet.img.xml | 15,591 B | Pet sounds |
| Radio.img.xml | 89 B | Radio system |
| Reactor.img.xml | 68,642 B | Reactor/interactive object sounds |
| Skill.img.xml | 25,478 B | Skill effect sounds |
| Summon.img.xml | 231 B | Summon sounds |
| UI.img.xml | 888 B | UI interaction sounds |
| Weapon.img.xml | 805 B | Weapon swing/hit sounds |

---

## 6. Target Area BGM Summary

| Area | BGM File | Tracks | Status |
|------|----------|--------|--------|
| **Temple of Time** | Bgm16 | TimeTemple, Remembrance, Repentance, Forgetfulness, Duskofgod, FightingPinkBeen | PRESENT (6 tracks) |
| **LHC / Von Leon** | Bgm23 | CrimsonTower, LionHeart, BlizzardCastle, Bramble | PRESENT (4 tracks) |
| **Future Ereve** | Bgm25 | timeGate, destructionTown, knightsStronghold, CygnusGarden, destructionPerion* | PRESENT (5+ tracks) |
| **Singapore** | BgmSG | CBD_town, CBD_field, BoatQuay_field, Ghostship, BoatQuay_town, Ulu_field | PRESENT (6 tracks) |
| **Ereve (CK)** | Bgm18 | QueensGarden, DrillHall, RaindropFlower, WolfAndSheep | PRESENT (4 tracks) |
| **Rien (Aran)** | Bgm19 | RienVillage, SnowDrop, BambooGym, CrystalCave | PRESENT (4 tracks) |
| **Arcane River** | Bgm46-50 | ~45 tracks across 5 files | PRESENT (full set!) |

---

## 7. Key Findings & Anomalies

### Quest Data
1. **2,789 quests defined** -- comprehensive v83 quest set
2. **Temple of Time fully present** with complete 999-kill chains (12 grind quests + 2 boss quests)
3. **Cygnus Knights and Aran class quests fully present** -- both class storylines complete
4. **No LHC, Von Leon, Future Ereve, or Singapore quests** -- quest data does not include these areas despite BGM being present
5. **No Arcane River quests** -- expected for v83, but BGM exists (modern repack with backported sound)
6. **Duplicate Oblivion quests** (3515-3519 and 3530-3533) suggest two quest path variants

### Sound Data
1. **53 sound files = XML metadata only** (track name references, no actual audio embedded)
2. **BGM numbering gap**: Bgm26-45 are missing (jumps from Bgm25 to Bgm46)
3. **Bgm46-50 contain modern content** (Arcane River, Tenebris, Black Mage) -- this repack's Sound.wz includes content far beyond v83
4. **Singapore BGM present** despite no Singapore quests -- maps/BGM may exist without quest support
5. **LHC and Future Ereve BGM present** (Bgm23, Bgm25) -- sound data is more complete than quest data
6. Bgm22 contains **Edelstein/Resistance** content (also post-v83 addition)

### Implications for TwinleafStory
- Quest data is v83-era complete but some post-v83 content areas have BGM without quest support
- If implementing LHC, Future Ereve, or Singapore, quest data will need to be sourced or created separately
- The 999-kill ToT quests are a known grind wall -- consider adjusting kill counts server-side
- Sound.wz is a hybrid containing v83 through modern era BGM tracks
