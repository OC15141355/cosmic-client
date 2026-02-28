# PROMPT-01: String.wz Merge — Add New Item and Mob Names

## What

Merge the comprehensive string data from `wz.zip` into the server's String.wz files. The wz.zip contains names for all post-v83 content (Von Leon equipment, Empress gear, Chaos Zakum mobs, LHC mobs, Future Ereve mobs, etc.) that the server doesn't know about yet.

**Two files to update:**
1. `Eqp.img.xml` — equipment names (wz.zip version is 4x larger, strict superset — safe to replace)
2. `Mob.img.xml` — mob names (wz.zip has boss names the server lacks — must MERGE, not replace)

## Where

### Input Files
- **wz.zip**: `D:\wz.zip` (98MB archive on the T7 SSD)
  - Extract: `wz/String.wz/Eqp.img.xml` (3,239 KB)
  - Extract: `wz/String.wz/Mob.img.xml` (158 KB)
- **Server current**: `C:\Users\carbyne\Documents\TwinleafStory\server\wz\String.wz\Eqp.img.xml` (835 KB)
- **Server current**: `C:\Users\carbyne\Documents\TwinleafStory\server\wz\String.wz\Mob.img.xml` (142 KB)

### Output
- `C:\Shared\output\string-wz\Eqp.img.xml` — the replacement Eqp file
- `C:\Shared\output\string-wz\Mob.img.xml` — the merged Mob file
- `C:\Shared\output\string-wz\MERGE-REPORT.md` — summary of what was added

## Steps

### Step 1: Extract wz.zip String Data

```powershell
mkdir -p C:\Shared\output\string-wz
# Extract the string files from wz.zip
Expand-Archive -Path D:\wz.zip -DestinationPath C:\Shared\output\string-wz\wzextract -Force
# The files will be at: C:\Shared\output\string-wz\wzextract\wz\String.wz\
```

### Step 2: Eqp.img.xml — Replace (Safe)

The wz.zip Eqp.img.xml is a strict superset of the server's version. It contains ALL v83 equipment names PLUS post-v83 names (Von Leon sets, Empress gear, Timeless/Reverse, etc.).

1. Backup server's current Eqp.img.xml
2. Copy wz.zip version as the replacement
3. Verify it contains the critical Von Leon IDs:
   - `1003172` (Lionheart Battle Helm)
   - `1003173` (Dragon Tail Mage Sallet)
   - `1003174` (Falcon Wing Sentinel Cap)
   - `1003175` (Raven Horn Chaser Hat)
   - `1003176` (Shark Tooth Skipper Hat)
   - `1052314` (Lionheart Battle Mail)
4. Verify Empress IDs:
   - `1003159` (Empress's Fine Hat)
   - `1003160` (Empress's Brilliant Hat)
   - `1082290` (Empress's Fine Gloves)

### Step 3: Mob.img.xml — Merge (Careful)

The server's Mob.img.xml may have custom entries. Do NOT replace — merge.

1. Read both files
2. Parse the XML structure (each mob is an `<imgdir name="MOBID">` with a `<string name="name" value="..."/>`)
3. Find all mob IDs present in wz.zip but MISSING from server
4. Add those entries to the server's file
5. Do NOT overwrite any existing server entries (server may have custom names)

**Critical mob IDs that MUST be in the merged output:**

| Mob ID | Name | Content |
|--------|------|---------|
| 8210000-8210013 | Crocky, Reindeer, Bearwolf, etc. | LHC regular mobs |
| 8220016-8220021 | Corrupted Wyvern/Cornian/Skelegon/etc. | Corrupted ToT |
| 8610000-8610033 | Dawn, Blaze, Wind, Night, Thunder, Official Knights | LHC CK enemies |
| 8620000-8620027 | Swollen Stump, Pillaging Boar, etc. | LHC forest mobs |
| 8644000-8644836 | Water/Sun/Earth Spirit, etc. | Future Ereve mobs |
| 8645000-8645065 | Cygnus Support Troops, Guard Captain Darknell | Empress area mobs |
| 8800100-8800116 | Chaos Zakum bodies, arms, summons | Chaos Zakum boss |
| 8840000-8840002 | Von Leon, Demon Gargoyle, Red Crocky | Von Leon boss |
| 8850000-8850011 | Mihile, Oz, Irena, Eckhart, Hawkeye, Shinsoo, Cygnus | Empress boss |

### Step 4: Generate Merge Report

Create `MERGE-REPORT.md` listing:
- Number of new equipment entries added to Eqp.img.xml
- Number of new mob entries added to Mob.img.xml
- List of all critical boss mob IDs confirmed present
- Any IDs that were expected but NOT found

## Verification

1. Open the output Eqp.img.xml and search for `1003172` — should find "Lionheart Battle Helm"
2. Open the output Mob.img.xml and search for `8800100` — should find "Chaos Zakum"
3. Search for `8840000` — should find "Von Leon"
4. Search for `8850011` — should find "Cygnus"
5. Confirm total mob count is HIGHER than the server's original (142 KB → should be ~158 KB or larger)
6. Confirm Eqp file is the larger wz.zip version (~3,239 KB)

## Deployment (Done from MacBook)

```bash
scp ~/Shared-Win/output/string-wz/Eqp.img.xml homelab@192.168.0.25:/home/homelab/Cosmic/wz/String.wz/
scp ~/Shared-Win/output/string-wz/Mob.img.xml homelab@192.168.0.25:/home/homelab/Cosmic/wz/String.wz/
# Restart server to pick up changes
ssh homelab@192.168.0.25 "cd /home/homelab/Cosmic && docker compose restart cosmic-server-1"
```
