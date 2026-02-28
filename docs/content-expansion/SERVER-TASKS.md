# TwinleafStory — Server-Side Tasks (MacBook SSH)

These tasks are done from the MacBook via SSH to the server at 192.168.0.25 (homelab@192.168.0.25, via ProxyJump through core-01).

Server paths:
- WZ data: `/home/homelab/Cosmic/wz/`
- Config: `/home/homelab/Cosmic/config.yaml`
- NPC scripts: `/home/homelab/Cosmic/scripts/npc/`
- Quest scripts: `/home/homelab/Cosmic/scripts/quest/`
- MySQL: Docker container `cosmic-db-1` on .25 (root/root, db: cosmic)
- Docker restart: `docker compose restart` in `/home/homelab/Cosmic/`

---

## Priority 1: Immediate Fixes

### 1.1 Fix GM Account Login
**Problem**: The `admin` account has a password character limit issue (v83 client limits passwords to 12 characters). The `quiet` account was set to GM level 6 but may need a relog to activate.

**Steps**:
1. SSH to .25, exec into MySQL: `docker exec -it cosmic-db-1 mysql -uroot -proot cosmic`
2. Check GM levels: `SELECT name, gm FROM accounts WHERE name IN ('admin', 'quiet');`
3. If `quiet` isn't GM 6: `UPDATE accounts SET gm=6 WHERE name='quiet';`
4. Reset `admin` password to something ≤12 chars: `UPDATE accounts SET password='' WHERE name='admin';`
   (Cosmic auto-migrates to bcrypt on next login — set to empty string, then login with new short password)
5. Test login on Windows client

### 1.2 Verify Server Docker State
```bash
ssh homelab@192.168.0.25 "cd /home/homelab/Cosmic && docker compose ps"
```
Confirm both `cosmic-server-1` and `cosmic-db-1` are running.

---

## Priority 2: Boss HP Rebalancing (Existing Mobs)

These bosses already have XML files on the server. Edit stats directly.

### 2.1 Zakum Body 2 (mob ID: 8800002)
**File**: `/home/homelab/Cosmic/wz/Mob.wz/8800002.img.xml`
- Change `maxHP` from 110,000,000 → 30,000,000
- Change `PADamage` from 1,080 → 1,080 (keep)
- Change `PDDamage` from 1,200 → 800
- Change `MDDamage` from 900 → 600

Also adjust all Zakum arms (8800003-8800010) — reduce HP proportionally.

### 2.2 Zakum Body 1 (8800000) and Body 3 (8800001)
Reduce HP proportionally (~30% of original).

### 2.3 Horntail
**Heads** (8810002, 8810003): 330M → 80M each
**Wings/Legs** (8810004-8810008): Reduce proportionally
**Pivot** (8810018): 2.09B → 200M

### 2.4 Pink Bean
**Main body** (8820001): 2.1B → 500M
**Statues** (8820002-8820006): Reduce proportionally

### 2.5 Restart Server After All Edits
```bash
ssh homelab@192.168.0.25 "cd /home/homelab/Cosmic && docker compose restart cosmic-server-1"
```

---

## Priority 3: Temple of Time Kill Quest Reduction

### 3.1 Find ToT Quest Scripts
```bash
# On .25, find quest scripts related to Temple of Time
find /home/homelab/Cosmic/scripts/quest/ -name "*.js" | xargs grep -l "999"
```

The kill quests use quest IDs that track kill counts. Look for scripts that check for 999 kills and change to 100.

**Alternative**: The kill count might be in the quest data WZ rather than scripts:
```
/home/homelab/Cosmic/wz/Quest.wz/
```
Search for quest entries with `count` or `mob` requirements of 999.

### 3.2 Specific Quests to Edit
Temple of Time quests are in the 3500-3600 quest ID range. Look for:
- Road of Regrets quests
- Road to Oblivion quests
- Forgotten Passage quests
Each stage has a "kill 999 of X mob" requirement.

Change all `999` → `100`.

---

## Priority 4: Deploy Windows Claude Output

After Windows Claude completes its extraction prompts:

### 4.1 Copy Files to Server
From MacBook:
```bash
# SCP from shared drive to server
scp -r ~/Shared-Win/output/chaos-zakum/mob-xml/*.xml homelab@192.168.0.25:/home/homelab/Cosmic/wz/Mob.wz/
scp -r ~/Shared-Win/output/lhc-maps/*.xml homelab@192.168.0.25:/home/homelab/Cosmic/wz/Map.wz/Map/Map2/
scp -r ~/Shared-Win/output/lhc-mobs/*.xml homelab@192.168.0.25:/home/homelab/Cosmic/wz/Mob.wz/
# ... etc for each output directory
```

### 4.2 Deploy String.wz Updates
```bash
scp ~/Shared-Win/output/string-wz/Eqp.img.xml homelab@192.168.0.25:/home/homelab/Cosmic/wz/String.wz/Eqp.img.xml
scp ~/Shared-Win/output/string-wz/Mob.img.xml homelab@192.168.0.25:/home/homelab/Cosmic/wz/String.wz/Mob.img.xml
```

### 4.3 Run Drop Table SQL
```bash
ssh homelab@192.168.0.25 "docker exec -i cosmic-db-1 mysql -uroot -proot cosmic < /tmp/drop-table.sql"
```
(SCP the SQL file to .25 first, then pipe it in)

### 4.4 Restart Server
```bash
ssh homelab@192.168.0.25 "cd /home/homelab/Cosmic && docker compose restart cosmic-server-1"
```

---

## Priority 5: NPC Access Scripts

### 5.1 LHC Access NPC
Create NPC script that teleports players to LHC (211060000) from El Nath or Leafre.

**File**: `/home/homelab/Cosmic/scripts/npc/{npc_id}.js`

Need to decide: use an existing NPC in El Nath, or create a custom NPC.

Script template:
```javascript
var status = 0;
function start() { status = -1; action(1, 0, 0); }
function action(mode, type, selection) {
    if (mode == 1) status++;
    else { cm.dispose(); return; }

    if (status == 0) {
        cm.sendNext("The mountain patrol discovered ancient ruins beyond the peaks. Something stirs within the castle walls... Lion Heart Castle awaits those brave enough to enter.");
    } else if (status == 1) {
        cm.sendYesNo("Would you like to travel to Lion Heart Castle? (Recommended level: 120+)");
    } else if (status == 2) {
        cm.warp(211060000, 0);
        cm.dispose();
    }
}
```

### 5.2 Gate to the Future Access NPC
Teleport from Temple of Time to 271000000.

### 5.3 Singapore Travel
Check if Changi Airport NPC already exists in scripts. Singapore may already be accessible via an existing NPC.

### 5.4 Cody Progression Guide NPC
This is bigger — see PROGRESSION-GUIDE.md for the full Cody script spec.

---

## Priority 6: Disable CK/Aran Character Creation

### 6.1 Server-Side Character Creation Block
The character creation handler is in the Java server code. Look for:
```
server/src/main/java/net/server/handlers/login/
```
Find the handler that processes new character creation and add a job check to reject CK (job 1000) and Aran (job 2000) creation requests.

**Alternative (simpler)**: The character creation UI is client-side. If we can't easily patch the server, we can:
- Set CK/Aran creation NPCs to not warp to creation maps
- Or just leave it for now and tell friends "play Explorer" (enforcement via social contract)

### 6.2 Ereve/Rien Repurpose
Long-term: Add Explorer-accessible NPCs and content to Ereve (starting map 130000000) and Rien (starting map 914000000). This is future work.

---

## Server Restart Checklist

Before restarting, always:
1. Back up current config: `cp config.yaml config.yaml.bak`
2. Check Docker logs for any current errors: `docker compose logs --tail 50 cosmic-server-1`
3. Restart: `docker compose restart cosmic-server-1`
4. Wait 30s, then check logs again: `docker compose logs --tail 20 cosmic-server-1`
5. Test login on Windows client
