# MAC PROMPT: Boss HP Rebalancing — Phase 0 Server Task

## Context

TwinleafStory implementation is underway. Windows Claude is extracting post-v83 content and patching the vanilla client WZ files. Meanwhile, Mac Claude handles server-side work via SSH.

This is the **boss HP rebalancing** task from Phase 0 of the Implementation Guide. All changes are to existing v83 mob XMLs on the server — no client changes needed. Declan can test these fights immediately on the vanilla v83 client with the `quiet` account (all characters are GM 6).

## What To Do

SSH to the server (192.168.0.25 via ProxyJump through core-01) and edit boss mob XMLs in `/home/homelab/Cosmic/wz/Mob.wz/`. Change `maxHP` (and `PDDamage`/`MDDamage` for Showa Boss) to the design targets below.

**Access pattern:**
```bash
ssh -o ProxyJump=kumo@192.168.0.105 homelab@192.168.0.25
```

The mob XMLs are at `/home/homelab/Cosmic/wz/Mob.wz/[MOBID].img.xml`. Edit the `<int name="maxHP" value="..."/>` line in each file's `<imgdir name="info">` section.

## Targets (from balance-design.md)

### Zakum (Priority 1 — most-run boss)
| Mob ID | Part | Current HP | Target HP |
|--------|------|-----------|-----------|
| 8800000 | Body 1 | 66,000,000 | 20,000,000 |
| 8800002 | Body 2 (main reward) | 110,000,000 | 30,000,000 |
| 8800003 | Arm A | 33,000,000 | 8,000,000 |
| 8800004 | Arm B | 33,000,000 | 8,000,000 |
| 8800005 | Arm C | 22,000,000 | 8,000,000 |
| 8800006 | Arm D | 22,000,000 | 8,000,000 |
| 8800007 | Arm E | 22,000,000 | 8,000,000 |
| 8800008 | Arm F | 22,000,000 | 8,000,000 |
| 8800009 | Arm G | 33,000,000 | 8,000,000 |
| 8800010 | Arm H | 33,000,000 | 8,000,000 |

### Horntail (Priority 2)
| Mob ID | Part | Current HP | Target HP |
|--------|------|-----------|-----------|
| 8810000 | Head A | 330,000,000 | 80,000,000 |
| 8810002 | Head B | 330,000,000 | 80,000,000 |
| 8810018 | Pivot (body) | 2,090,000,000 | 200,000,000 |

Note: HT has more parts (8810001, 8810003-8810017). Only adjust the heads and pivot — leave wings/legs/tail as-is for now, playtest first.

### Papulatus (Priority 3)
| Mob ID | Part | Current HP | Target HP |
|--------|------|-----------|-----------|
| 8500001 | Main body | 23,000,000 | 10,000,000 |

### Pianus (Priority 4)
| Mob ID | Part | Current HP | Target HP |
|--------|------|-----------|-----------|
| 8510000 | Pianus A | 30,000,000 | 12,000,000 |
| 8520000 | Pianus B | 24,000,000 | 10,000,000 |

### Pink Bean (Priority 5 — endgame, less urgent)
| Mob ID | Part | Current HP | Target HP |
|--------|------|-----------|-----------|
| 8820001 | Pink Bean | 2,100,000,000 | 500,000,000 |

### Showa Boss (Priority 6 — defense nerf, HP stays)
| Mob ID | Stat | Current | Target |
|--------|------|---------|--------|
| 9400300 | PDDamage | 5,000 | 1,500 |
| 9400300 | MDDamage | 4,300 | 1,500 |
| 9400300 | maxHP | 150,000,000 | 150,000,000 (no change) |

## How To Edit

Each mob XML looks like:
```xml
<imgdir name="8800002.img">
  <imgdir name="info">
    ...
    <int name="maxHP" value="110000000"/>
    ...
  </imgdir>
</imgdir>
```

Change the `value` attribute. For Showa Boss, also change `PDDamage` and `MDDamage`.

## After Editing

Restart the server:
```bash
ssh -o ProxyJump=kumo@192.168.0.105 homelab@192.168.0.25 \
  "cd /home/homelab/Cosmic && docker compose restart maplestory"
```

Note: the service name is `maplestory` (NOT `cosmic-server-1`).

## Also Do: ToT Kill Quest Reduction

While on the server, find and fix the Temple of Time kill quests (999 → 100):

```bash
# Search for 999-kill requirements
grep -r "999" /home/homelab/Cosmic/scripts/quest/ | grep -i "time\|temple\|memory\|regret\|oblivion"
grep -r "999" /home/homelab/Cosmic/wz/Quest.wz/
```

Change any `999` kill requirements to `100`.

## Test Plan (Declan on vanilla client)

After restart, login with `quiet` account (any character, all GM 6):

```
!warp 211042300          → Zakum altar
!spawn 8800002           → Zakum Body 2 (should be 30M HP now)
Attack it                → should die much faster than before
!killall

!warp 240060200          → Horntail cave
!spawn 8810000           → HT Head A (should be 80M HP)
!killall

!warp 220080001          → Papulatus map
!spawn 8500001           → Papulatus (should be 10M HP)
!killall
```

## Update Tracker

After completing, update `C:\Shared\TRACKER.md` (via SMB at `~/Shared-Win/Shared/TRACKER.md`):
- Mark "Boss HP rebalancing" as ✅ DONE
- Mark "ToT kill quests 999→100" as ✅ DONE (if found and fixed)
- Note which bosses were changed and any issues
