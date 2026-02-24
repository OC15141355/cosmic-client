# v83 NX Path Reference

**CRITICAL**: HeavenClient's `linux` branch was built for v167+ NX structure. v83 paths are significantly different. Always verify paths with the NX dumper tool before writing code that references NX nodes.

## NX Dumper Tool
```bash
tools/nxdump/build/nxdump <file.nx> <path> [depth]
# Example: tools/nxdump/build/nxdump build/UI.nx Login.img/WorldSelect 2
```

## WZ-to-NX Converter
```bash
tools/wztonx/build/wztonx -c <file.wz>
```

## WorldSelect (Login.img/WorldSelect) — v83
```
BtWorld/0-20           — World buttons (normal/pressed/mouseOver/disabled/keyFocused)
BtWorld/chBackgrn      — World panel background bitmap
channel/0-19           — Channel buttons (normal/disabled bitmaps only)
channel/chSelect/0-3   — Channel selection indicators
channel/chgauge        — Channel gauge bitmap
chBackgrn              — Channel selection background bitmap
BtGoworld              — Enter world button (MapleButton format)
BtViewAll              — View all worlds button
BtViewChoice           — View recommended button
alert/                 — Recommended world alert panel
world/0-20             — World name/logo display textures
scroll/                — Scroll UI for world list
```

## Map.nx Login Backgrounds
```
Back/login.img/back/0-33  — Static backgrounds
Back/login.img/ani/0-19   — Animated backgrounds
Obj/login.img/Title       — Title screen objects
Obj/login.img/WorldSelect — World select scenes: aran, neoCity, tema, ghostShip, killing
Obj/login.img/CharSelect  — Character select objects
Obj/login.img/Common      — Common frame objects
```

## Common (Login.img/Common) — v83
```
BtExit, BtStart, BtStart2, BtWselect
BtDisableSPW, BtEnableSPW — Second password buttons
SoftKey                    — On-screen keyboard
frame                      — Main border bitmap
selectWorld                — World selection header
step/1-5                   — Step indicators
shadow, loginlocation
```

## CharSelect (Login.img/CharSelect) — v83

Verified via nxdump. **Master branch expects many nodes that don't exist in v83.**

```
UI.nx Login.img/CharSelect:
├── BtDelete               — MapleButton (normal/pressed/mouseOver/disabled/keyFocused)
├── BtNew                  — MapleButton (same structure)
├── BtSelect               — MapleButton (same structure)
├── adventure/0 [bitmap]   — Explorer signpost
├── aran/0 [bitmap]         — Aran signpost
├── knight/0 [bitmap]       — Cygnus signpost
├── charInfo [bitmap]       — Character info panel background
├── charInfo1 [bitmap]      — Alt info panel (slightly different)
├── charInfo2 [bitmap]      — Alt info panel
├── charInfo3 [bitmap]      — Alt info panel
├── character/0/0-7         — Empty slot animation (8 frames)
├── character/1/0           — Empty slot static
├── effect/0/0-5            — Selection effect bottom (6 frames)
├── effect/1/0-4            — Selection effect top (5 frames)
├── icon/
│   ├── down [bitmap]       — Level down icon
│   ├── up [bitmap]         — Level up icon
│   ├── same [bitmap]       — Level same icon
│   ├── new [bitmap]        — New character icon
│   └── job/0-4 [bitmap]    — Job class icons (5 classes)
├── nameTag/0/0-2           — Name tag variant 0 (3 parts: left, center, right)
├── nameTag/1/0-2           — Name tag variant 1
├── pageL/0/0, 1/0          — Page left button (normal, pressed)
├── pageR/0/0, 1/0          — Page right button (normal, pressed)
└── scroll/0-3/0-3          — Scroll animation (4 variants × 4 frames)

Map.nx Obj/login.img/CharSelect:
├── character/0/0 [bitmap]  — Character platform/stand
├── character/1/0-1         — Platform glow animation (fade in/out, delay=800)
├── page/0/0 [bitmap]       — Page counter background (left half)
├── page/1/0 [bitmap]       — Page counter background (right half)
└── signboard/0/0 [bitmap]  — Character select signboard
```

### Nodes that DON'T exist in v83 (master branch expects these)
| Node | Master uses for | Our workaround |
|------|----------------|----------------|
| `pos/avatarPos/avatarLT,RB,Space` | Character grid layout from NX | Hardcode positions |
| `pos/detailPos/*` | Stat label positions from NX | Hardcode positions |
| `charSlot` | Char slot counter widget | Skip (empty texture) |
| `pageNew` | Page nav base/numbers/positions | Use Map.nx `page/0`, `page/1` |
| `lv` (Charset) | Level number display | Skip (empty charset) |
| `selectedWorld/icon,name,ch` | World/channel display in header | Use Common/selectWorld only |
| `BtChangePIC` | PIC management button | Skip |
| `BtResetPIC` | PIC reset button | Skip |
| `BtCharacter` | Character button (master) | Skip |
| `BtPreview` | Preview button (master) | Skip |

## v83 StatusBar.img Structure
```
StatusBar.img:
├── base/
│   ├── backgrnd [bitmap]      — Main status bar background
│   ├── backgrnd2 [bitmap]     — Secondary background
│   ├── box [bitmap]           — Box element
│   ├── chat [bitmap]          — Chat area
│   ├── chatTarget [bitmap]    — Chat target indicator
│   ├── iconBlue [bitmap]      — Blue icon
│   ├── iconMemo [bitmap]      — Memo icon
│   ├── iconRed [bitmap]       — Red icon
│   └── quickSlot [bitmap]     — Quick slot area
├── gauge/
│   ├── bar [bitmap]           — HP/MP/EXP gauge bar
│   ├── graduation [bitmap]    — Gauge ticks
│   ├── gray [bitmap]          — Empty gauge
│   ├── hpFlash/               — HP flash animation
│   ├── mpFlash/               — MP flash animation
│   └── tempExp [bitmap]       — Temp EXP display
├── key/0-7 [bitmap]           — Quick key icons
├── number/0-9 [bitmap]        — Number font for gauges
├── FontMemo/0-9 [bitmap]      — Memo font
├── BtMenu, BtShop, BtWhisper  — MapleButton format
├── BtClaim, BtNPT, BtShort    — MapleButton format
├── EquipKey, InvenKey          — MapleButton with ani
├── SkillKey, StatKey           — MapleButton with ani
├── QuickSlot, QuickSlotD       — MapleButton with ani
└── KeySet                      — MapleButton with ani
```

## v167+ to v83 UI Path Mapping

**CRITICAL**: v167+ split UI into multiple .img files (`StatusBar2.img`, `StatusBar3.img`, `UIWindow2.img`, `UIWindow4.img`, `UIWindow6.img`). v83 has single files: `StatusBar.img` and `UIWindow.img`.

### StatusBar Remapping
| v167+ (code uses) | v83 (actual path) | Status |
|---|---|---|
| `StatusBar3.img/mainBar` | `StatusBar.img/base` | Needs porting |
| `StatusBar3.img/chat` | N/A (v83 chat is simpler) | Needs investigation |
| `StatusBar3.img/KeyConfig` | `UIWindow.img/KeyConfig` | Needs porting |
| `StatusBar3.img/OptionMenu` | N/A | Needs investigation |
| `StatusBar3.img/chat/common/scroll` | N/A (Slider.cpp) | Needs investigation |

### UIWindow Remapping
| v167+ (code uses) | v83 (actual path) | Status |
|---|---|---|
| `UIWindow2.img/Item` | `UIWindow.img/Item` | Path fix only |
| `UIWindow2.img/Skill` | `UIWindow.img/Skill` | Path fix only |
| `UIWindow2.img/Quest` | `UIWindow.img/Quest` | Path fix only |
| `UIWindow2.img/UserList` | `UIWindow.img/UserList` | Path fix only |
| `UIWindow2.img/MiniMap` | `UIWindow.img/MiniMap` | Path fix only |
| `UIWindow2.img/Channel` | `UIWindow.img/Channel` | Path fix only |
| `UIWindow2.img/UserInfo` | `UIWindow.img/UserInfo` | Path fix only |
| `UIWindow2.img/WorldMap` | `UIWindow.img/WorldMap` | Path fix only |
| `UIWindow2.img/Shop2` | `UIWindow.img/Shop` | Name change (Shop2 -> Shop) |
| `UIWindow2.img/socialChatEnter` | N/A (v83 has no social chat) | Skip |
| `UIWindow2.img/socialRank` | N/A | Skip |
| `UIWindow2.img/EventList` | `UIWindow.img/MapleEvent` | Name change |
| `UIWindow2.img/ToolTip/WorldMap` | `UIWindow.img/ToolTip/Equip` | Different structure |
| `UIWindow2.img/KeyConfig/KeyType` | `UIWindow.img/KeyConfig` | Path fix + structure diff |
| `UIWindow4.img/Equip` | `UIWindow.img/Equip` | Path fix only |
| `UIWindow4.img/Stat` | `UIWindow.img/Stat` | Path fix only |
| `UIWindow4.img/Skill/skillPoint` | `UIWindow.img/Skill` | Path fix, may lack node |
| `UIWindow6.img/askReward` | `UIWindow.img/GameMenu` | Different structure |

### Files Needing v83 Path Fixes
```
IO/UITypes/UIStatusBar.cpp      — StatusBar3.img/mainBar → StatusBar.img/base
IO/UITypes/UIChatBar.cpp        — StatusBar3.img/chat → needs investigation
IO/UITypes/UIKeyConfig.cpp      — StatusBar3.img/KeyConfig → UIWindow.img/KeyConfig
IO/UITypes/UIItemInventory.cpp  — UIWindow2.img/Item → UIWindow.img/Item
IO/UITypes/UISkillBook.cpp      — UIWindow2.img/Skill → UIWindow.img/Skill
IO/UITypes/UIStatsInfo.cpp      — UIWindow4.img/Stat → UIWindow.img/Stat
IO/UITypes/UIEquipInventory.cpp — UIWindow4.img/Equip → UIWindow.img/Equip
IO/UITypes/UIQuestLog.cpp       — UIWindow2.img/Quest → UIWindow.img/Quest
IO/UITypes/UIUserList.cpp       — UIWindow2.img/UserList → UIWindow.img/UserList
IO/UITypes/UIMiniMap.cpp        — UIWindow2.img/MiniMap → UIWindow.img/MiniMap
IO/UITypes/UIWorldMap.cpp       — UIWindow2.img/WorldMap → UIWindow.img/WorldMap
IO/UITypes/UIChannel.cpp        — UIWindow2.img/Channel → UIWindow.img/Channel
IO/UITypes/UICharInfo.cpp       — UIWindow2.img/UserInfo → UIWindow.img/UserInfo
IO/UITypes/UIShop.cpp           — UIWindow2.img/Shop2 → UIWindow.img/Shop
IO/UITypes/UIChat.cpp           — UIWindow2.img/socialChatEnter → N/A
IO/UITypes/UIEvent.cpp          — UIWindow2.img/EventList → UIWindow.img/MapleEvent
IO/UITypes/UIQuit.cpp           — UIWindow6.img/askReward → UIWindow.img/GameMenu
IO/UITypes/UIOptionMenu.cpp     — StatusBar3.img/OptionMenu → needs investigation
IO/UITypes/UILoginNotice.cpp    — UIWindow2.img/KeyConfig/KeyType → UIWindow.img/KeyConfig
IO/Components/MapTooltip.cpp    — UIWindow2.img/ToolTip → UIWindow.img/ToolTip
IO/Components/Slider.cpp        — StatusBar3.img/chat/common/scroll → needs investigation
```
