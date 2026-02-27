# WZ Editing Pipeline — TwinleafStory v83

How to edit game content and get changes into both the server and client.

---

## Two Paths: Server-Side vs Client-Side

| Change Type | Affects | Pipeline | Restart Needed |
|-------------|---------|----------|---------------|
| Boss HP/damage/stats | Server only | Edit XML → restart server | Server restart |
| Drop tables | Server only | MySQL UPDATE → restart or hot-reload | Server restart |
| EXP/meso rates | Server only | Edit config.yaml → restart | Server restart |
| NPC dialogue/logic | Server only | Edit JS script → restart | Server restart |
| Map layouts/spawns | Both | Edit XML + convert NX | Server + client |
| New items/gear | Both | Edit XML + convert NX + add strings | Server + client |
| UI/visual changes | Client only | Edit WZ → convert NX | Client only |
| New maps/areas | Both | Full pipeline (see below) | Server + client |

---

## Server-Side Editing (XML Direct)

Cosmic loads WZ data from XML files at `server/wz/`. No conversion step needed.

### Workflow

1. Edit the XML file directly (VS Code, any text editor)
2. Restart the Cosmic server
3. Changes take effect immediately

### Examples

**Change boss HP** (`server/wz/Mob.wz/8800002.img.xml`):
```xml
<int name="maxHP" value="30000000"/>
```

**Change EXP rate** (`server/config.yaml`):
```yaml
exp_rate: 10
```

**Edit NPC script** (`server/scripts/npc/1002000.js`):
```javascript
// Full Nashorn JavaScript — cm.sendNext(), cm.sendSimple(), etc.
```

**Edit drop tables** (MySQL on docker-01):
```sql
-- Connect: mysql -h 192.168.0.21 -u root -p cosmic
UPDATE drop_data SET chance = 50000 WHERE itemid = 2000000 AND dropperid = 8800002;
INSERT INTO drop_data (dropperid, itemid, minimum_quantity, maximum_quantity, questid, chance)
VALUES (8800002, 1002357, 1, 1, 0, 100000);
```

---

## Client-Side Editing (WZ → NX Pipeline)

For changes visible to the client (maps, sprites, UI, item visuals).

### Required Tool: HaRepacker Resurrected

- **Download**: https://github.com/lastbattle/Harepacker-resurrected/releases
- **Recommended version**: v6.0 (uses .NET Framework 4.8, pre-installed on Windows 10/11)
- **Latest version**: v8.0.0 (requires .NET 8.0 Runtime, has map simulator + AI features)
- **Encryption**: Always use **"GMS (old)"** when opening v83 WZ files

### Client Pipeline

```
[WZ/IMG Source] ──HaRepacker──> [Modified WZ/IMG]
                                       │
                            ┌──────────┴──────────┐
                            │                     │
                    wztonx conversion      "Private Server" export
                            │                     │
                    [NX files → client]    [XML → server/wz/]
```

### Step-by-Step

1. **Open WZ** in HaRepacker
   - File → Open → select `.wz` file
   - Use "GMS (old)" encryption

2. **Edit content**
   - Navigate node tree
   - Modify values, add/remove nodes
   - Replace images/sprites if needed

3. **Export for server** (if server needs the changes too)
   - File → Private Server... → Export XML
   - Copy exported XML to `server/wz/` appropriate directory

4. **Save WZ** for client conversion
   - File → Save
   - HaRepacker auto-backs up the original

5. **Convert WZ → NX**
   ```bash
   # On MacBook or dev box (wherever wztonx is built)
   cd ~/Projects/cosmic-client
   tools/wztonx/wztonx -c /path/to/modified/Map.wz
   ```
   This produces `Map.nx`

6. **Deploy NX to client**
   ```bash
   cp Map.nx ~/Games/MapleStoryCX/
   ```

7. **Test** — launch client, verify changes

---

## Adding Content from Later Versions

To port maps/items/mobs from post-v83 MapleStory:

### Source Data

- Community WZ repacks from v90-v120 era (need to source these)
- WzComparerR2 can compare versions to identify what was added
  - Repo: https://github.com/Kagamia/WzComparerR2

### Porting Workflow

1. **Identify content to port** — specific maps, mobs, items from a later version
2. **Extract WZ data** — open later-version WZ in HaRepacker, export the relevant nodes
3. **Check ID conflicts** — ensure mob/item/map IDs don't collide with existing v83 content
4. **Add to server WZ** — place XML in appropriate `server/wz/` subdirectory
5. **Add to client NX** — add assets to WZ, convert to NX
6. **Add string data** — update `String.wz` / `String.nx` with names/descriptions
7. **Wire up access** — NPC scripts (transport), quest chains, portal entries
8. **Add spawns** — mob spawn entries in map life sections or `plife` DB table
9. **Add drops** — `drop_data` table entries for new mobs/bosses

### ID Ranges (Safe for Custom Content)

Use high ID ranges to avoid conflicts:
- **Custom mobs**: 9500000+ (stock v83 tops out around 9420000)
- **Custom items**: 1500000+ for equips (check existing ranges first)
- **Custom maps**: 900000000+ (check Map.wz for existing range)
- **Custom NPCs**: 9900000+ (stock NPCs go up to ~9900000, verify)

---

## Automation (Future)

HaRepacker is GUI-only. For automation, use **MapleLib** (C# library):

- **Repo**: https://github.com/lastbattle/MapleLib
- **Runtime**: .NET 8.0
- Write a C# console app that programmatically modifies WZ files
- Useful for batch operations (e.g., reduce all boss HP by 30%)

Example concept:
```csharp
var wzFile = new WzFile("Mob.wz", WzMapleVersion.GMS);
wzFile.ParseWzFile();
var mob = wzFile["8800002.img"]["info"]["maxHP"];
mob.SetValue(30000000);
wzFile.SaveToDisk("Mob_modified.wz");
```

---

## Existing Tools in Repo

| Tool | Location | Purpose |
|------|----------|---------|
| `wztonx` | `tools/wztonx/` | WZ/IMG → NX conversion |
| `nxdump` | `tools/nxdump/` | NX file inspector (view node trees) |
| `convert-wz-to-nx.sh` | `tools/scripts/` | Batch convert all WZ files |

### Building wztonx

```bash
cd tools/wztonx
mkdir -p build && cd build
cmake ..
make
```

### Using nxdump

```bash
cd tools/nxdump
mkdir -p build && cd build
cmake ..
make
./nxdump /path/to/file.nx
```

---

## Quick Reference: Where Things Live

| Content | Server Location | Client Location |
|---------|----------------|-----------------|
| Mob stats | `server/wz/Mob.wz/[id].img.xml` | N/A (server authority) |
| Mob sprites | N/A | `Mob.nx` |
| Map data | `server/wz/Map.wz/Map/Map[0-9]/` | `Map.nx` |
| Item stats | `server/wz/Item.wz/` | N/A |
| Item sprites | N/A | `Item.nx`, `Character.nx` |
| NPC scripts | `server/scripts/npc/[id].js` | N/A |
| NPC sprites | N/A | `Npc.nx` |
| Strings | `server/wz/String.wz/` | `String.nx` |
| Skills | `server/wz/Skill.wz/` | `Skill.nx` |
| Drop tables | MySQL `drop_data` | N/A |
| Spawn data | WZ `life` sections or `plife` table | N/A |
