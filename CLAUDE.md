# TwinleafStory Client (cosmic-client)

Native macOS + Windows MapleStory v83 client. Fork of HeavenClient `linux` branch, rebuilt for ARM64 macOS with v83 NX asset support.

## Vision

Build a polished v83 MapleStory client with cherry-picked modern content. Part of the TwinleafStory project (custom server + native client). Target: the ultimate vanilla v83 experience with balance improvements and quality-of-life updates.

## Quick Start

```bash
# Dependencies
brew install cmake ninja glfw freetype lz4 asio

# Build
cd build && cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug .. && ninja

# NX files must be symlinked/copied into build/
# Run from build/ directory
./cosmic-client
```

## Architecture

### Client Stack
| Layer | Technology |
|-------|-----------|
| Windowing | GLFW 3 |
| Graphics | OpenGL 2.1 (Metal backend on macOS) via GLAD |
| Audio | miniaudio (BGM looping + SFX fire-and-forget via ma_decoder_init_memory) |
| Fonts | FreeType |
| Networking | ASIO (header-only, async TCP) |
| NX Files | NoLifeNx (memory-mapped PKG4 reader) |
| Image Loading | stb_image (header-only) |
| Compression | lz4 (NX bitmap decompression) |

### Key Directories
```
IO/UITypes/          — UI screens (UILogin, UIWorldSelect, UICharSelect, etc.)
IO/Components/       — Reusable UI components (MapleButton, TwoSpriteButton, etc.)
Graphics/            — OpenGL renderer (GraphicsGL), textures, animations
Net/                 — Networking: Session, Cryptography, PacketSwitch
Net/Handlers/        — Packet handlers (LoginHandlers, MapObjectHandlers, etc.)
Net/Packets/         — Outbound packet constructors
Gameplay/            — Game logic: Stage, Combat, MapleMap
Character/           — Player character: stats, inventory, skills, look
Audio/               — Audio subsystem (miniaudio wrapper)
Util/                — NxFiles loader, Configuration, Settings
includes/nlnx/       — NoLifeNx library (NX file reader)
thirdparty/          — GLAD, miniaudio, stb headers
```

### UI State Machine (Login Flow)
```
UILogo → UILogin → UIWorldSelect → UICharSelect → [UIRaceSelect → UIXxxCreation] → Game
```

### Packet Protocol
- **Encryption**: AES-OFB with MapleStory-specific encrypt/decrypt, pre-v118 key
- **Handshake**: 16 bytes — sendiv at [7:11], recviv at [11:15]
- **Version**: MAPLEVERSION = 83
- **Flow**: OutPacket.dispatch() → Session.write() → encrypt → socket
- **Receive**: Session.read() → socket.receive() → process() → PacketSwitch.forward()

### v83 Opcode Map (Server → Client)

Full v83 GMS inbound opcode table. Compared against HeavenClient `master` branch.

| Opcode | Name | Status | Handler |
|--------|------|--------|---------|
| 0 | LOGIN_RESULT | Active | LoginResultHandler |
| 1 | GUEST_ID_LOGIN | — | Not needed |
| 2 | ACCOUNT_INFO | — | Not needed |
| 3 | SERVERSTATUS | Active | ServerStatusHandler |
| 4 | GENDER_DONE | — | Not needed |
| 5 | CONFIRM_EULA_RESULT | — | Not needed |
| 6 | CHECK_PINCODE | — | Not implemented |
| 7 | UPDATE_PINCODE | — | Not implemented |
| 8 | VIEW_ALL_CHAR | — | Not implemented |
| 9 | SELECT_CHARACTER_BY_VAC | Active | ServerIPHandler (char select w/ PIC response) |
| 10 | SERVERLIST | Active | ServerlistHandler |
| 11 | CHARLIST | Active | CharlistHandler |
| 12 | SERVER_IP | Active | ServerIPHandler |
| 13 | CHARNAME_RESPONSE | Active | CharnameResponseHandler |
| 14 | ADD_NEWCHAR_ENTRY | Active | AddNewCharEntryHandler |
| 15 | DELCHAR_RESPONSE | Active | DeleteCharResponseHandler |
| 16 | CHANGE_CHANNEL | Active | ChangeChannelHandler |
| 17 | PING | Active | PingHandler |
| 26 | (unknown) | Unhandled | Logged, no crash |
| 27 | RECOMMENDED_WORLDS | Disabled | v83 format mismatch |
| 28 | CHECK_SPW_RESULT | Active | CheckSpwResultHandler |

### v83 Opcode Map (Server → Client) — In-Game

Opcodes received after entering the game world. Mapped from Cosmic `SendOpcode.java`.

| Opcode | Hex | Name | Status | Handler |
|--------|-----|------|--------|---------|
| 29 | 0x1D | MODIFY_INVENTORY | Active | ModifyInventoryHandler |
| 31 | 0x1F | CHANGE_STATS | Active | ChangeStatsHandler |
| 32 | 0x20 | GIVE_BUFF | Active | ApplyBuffHandler |
| 33 | 0x21 | CANCEL_BUFF | Active | CancelBuffHandler |
| 35 | 0x23 | RECALCULATE_STATS | Active | RecalculateStatsHandler |
| 36 | 0x24 | UPDATE_SKILL | Active | UpdateSkillHandler |
| 39 | 0x27 | SHOW_STATUS_INFO | Active | ShowStatusInfoHandler |
| 47 | 0x2F | CLAIM_STATUS_CHANGED | Stub | ClaimStatusHandler |
| 52 | 0x34 | GATHER_RESULT | Active | GatherResultHandler |
| 53 | 0x35 | SORT_RESULT | Active | SortResultHandler |
| 58 | 0x3A | SET_GENDER | Stub | SetGenderHandler |
| 61 | 0x3D | CHAR_INFO | Active | CharInfoHandler |
| 63 | 0x3F | BUDDYLIST | Stub | BuddyListHandler |
| 68 | 0x44 | SERVER_MESSAGE | Active | ServerMessageHandler |
| 77 | 0x4D | WEEK_EVENT_MESSAGE | Active | WeekEventMessageHandler |
| 95 | 0x5F | FAMILY_INFO_RESULT | Stub | FamilyInfoHandler |
| 100 | 0x64 | FAMILY_PRIVILEGE_LIST | Stub | FamilyPrivilegeHandler |
| 124 | 0x7C | SKILL_MACROS | Active | SkillMacrosHandler |
| 125 | 0x7D | SET_FIELD | Active | SetFieldHandler |
| 127 | 0x7F | SET_CASH_SHOP | Active | SetCashShopHandler |
| 138 | 0x8A | FIELD_EFFECT | Active | FieldEffectHandler |
| 159 | 0x9F | QUICKSLOT_INIT | Stub | QuickSlotInitHandler |
| 160 | 0xA0 | SPAWN_CHAR | Active | SpawnCharHandler |
| 161 | 0xA1 | REMOVE_CHAR | Active | RemoveCharHandler |
| 162 | 0xA2 | CHAT_RECEIVED | Active | ChatReceivedHandler |
| 167 | 0xA7 | SCROLL_RESULT | Active | ScrollResultHandler |
| 168 | 0xA8 | SPAWN_PET | Active | SpawnPetHandler |
| 185 | 0xB9 | CHAR_MOVED | Active | CharMovedHandler |
| 186 | 0xBA | ATTACKED_CLOSE | Active | CloseAttackHandler |
| 187 | 0xBB | ATTACKED_RANGED | Active | RangedAttackHandler |
| 188 | 0xBC | ATTACKED_MAGIC | Active | MagicAttackHandler |
| 197 | 0xC5 | UPDATE_CHARLOOK | Active | UpdateCharLookHandler |
| 198 | 0xC6 | SHOW_FOREIGN_EFFECT | Active | ShowForeignEffectHandler |
| 206 | 0xCE | SHOW_ITEM_GAIN_INCHAT | Active | ShowItemGainInChatHandler |
| 234 | 0xEA | ADD_COOLDOWN | Active | AddCooldownHandler |
| 236 | 0xEC | SPAWN_MOB | Active | SpawnMobHandler |
| 237 | 0xED | KILL_MOB | Active | KillMobHandler |
| 238 | 0xEE | SPAWN_MOB_C | Active | SpawnMobControllerHandler |
| 239 | 0xEF | MOB_MOVED | Active | MobMovedHandler |
| 250 | 0xFA | SHOW_MOB_HP | Active | ShowMobHpHandler |
| 257 | 0x101 | SPAWN_NPC | Active | SpawnNpcHandler |
| 259 | 0x103 | SPAWN_NPC_C | Active | SpawnNpcControllerHandler |
| 263 | 0x107 | SET_NPC_SCRIPTABLE | Stub | SetNpcScriptableHandler |
| 268 | 0x10C | DROP_LOOT | Active | DropLootHandler |
| 269 | 0x10D | REMOVE_LOOT | Active | RemoveLootHandler |
| 277 | 0x115 | HIT_REACTOR | Active | HitReactorHandler |
| 279 | 0x117 | SPAWN_REACTOR | Active | SpawnReactorHandler |
| 280 | 0x118 | REMOVE_REACTOR | Active | RemoveReactorHandler |
| 304 | 0x130 | NPC_DIALOGUE | Active | NpcDialogueHandler |
| 305 | 0x131 | OPEN_NPC_SHOP | Active | OpenNpcShopHandler |
| 306 | 0x132 | CONFIRM_SHOP_TRANSACTION | Active | — |
| 335 | 0x14F | KEYMAP | Active | KeymapHandler |
| 336 | 0x150 | AUTO_HP_POT | Stub | AutoHpPotHandler |
| 337 | 0x151 | AUTO_MP_POT | Stub | AutoMpPotHandler |

### v83 Opcode Map (Client → Server)

| Opcode | Name | Packet Class |
|--------|------|-------------|
| 1 | LOGIN | LoginPacket |
| 5 | CHARLIST_REQUEST | CharlistRequestPacket |
| 6 | SERVERSTATUS_REQUEST | ServerStatusRequestPacket |
| 7 | ACCEPT_TOS | AcceptTosPacket |
| 8 | SET_GENDER | SetGenderPacket |
| 11 | SERVERLIST_REQUEST | ServerRequestPacket |
| 19 | SELECT_CHAR | SelectCharPacket (no PIC) |
| 20 | PLAYER_LOGIN | PlayerLoginPacket |
| 23 | DELETE_CHAR | DeleteCharPacket / DeleteCharPicPacket |
| 29 | REGISTER_PIC | RegisterPicPacket |
| 30 | SELECT_CHAR_PIC | SelectCharPicPacket (with PIC) |
| 35 | LOGIN_START | LoginStartPacket |
| 41 | MOVE_PLAYER | MovePlayerPacket (constant movement updates) |
| 45 | RANGED_ATTACK | RangedAttackPacket |
| 207 | PLAYER_MAP_TRANSFER | MapTransferPacket |

### Keyboard Mapping (Keytable)

Server sends keybindings using DIK scan code indices (0-89). `Keyboard.cpp` translates to GLFW keycodes.

Key index reference (DIK → physical key):
| Index | DIK Code | Physical Key | GLFW Keycode |
|-------|----------|-------------|--------------|
| 2-10 | DIK_1-DIK_9 | 1-9 | GLFW_KEY_1 through GLFW_KEY_9 |
| 11 | DIK_0 | 0 | GLFW_KEY_0 |
| 16-25 | DIK_Q-DIK_P | Q-P | GLFW_KEY_Q through GLFW_KEY_P |
| 30-38 | DIK_A-DIK_L | A-L | GLFW_KEY_A through GLFW_KEY_L |
| 44-50 | DIK_Z-DIK_M | Z-M | GLFW_KEY_Z through GLFW_KEY_M |
| 56 | DIK_LALT | Left Alt | GLFW_KEY_LEFT_ALT (default: Jump) |
| 29 | DIK_LCONTROL | Left Ctrl | GLFW_KEY_LEFT_CONTROL (default: Attack) |
| 57 | DIK_SPACE | Space | GLFW_KEY_SPACE |
| 59-70 | DIK_F1-DIK_F12 | F1-F12 | GLFW_KEY_F1 through GLFW_KEY_F12 |

## v83 NX Path Reference

**CRITICAL**: HeavenClient's `linux` branch was built for v167+ NX structure. v83 paths are significantly different. Always verify paths with the NX dumper tool before writing code that references NX nodes.

### NX Dumper Tool
```bash
/tmp/nxdump/build/nxdump <file.nx> <path> [depth]
# Example: /tmp/nxdump/build/nxdump build/UI.nx Login.img/WorldSelect 2
```

### WZ-to-NX Converter
```bash
/tmp/wztonx-build/wztonx -c <file.wz>
```

### WorldSelect (Login.img/WorldSelect) — v83
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

### Map.nx Login Backgrounds
```
Back/login.img/back/0-33  — Static backgrounds
Back/login.img/ani/0-19   — Animated backgrounds
Obj/login.img/Title       — Title screen objects
Obj/login.img/WorldSelect — World select scenes: aran, neoCity, tema, ghostShip, killing
Obj/login.img/CharSelect  — Character select objects
Obj/login.img/Common      — Common frame objects
```

### Common (Login.img/Common) — v83
```
BtExit, BtStart, BtStart2, BtWselect
BtDisableSPW, BtEnableSPW — Second password buttons
SoftKey                    — On-screen keyboard
frame                      — Main border bitmap
selectWorld                — World selection header
step/1-5                   — Step indicators
shadow, loginlocation
```

### CharSelect (Login.img/CharSelect) — v83

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

#### Nodes that DON'T exist in v83 (master branch expects these)
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

### Key v83 vs v167+ Differences
| Feature | v167+ (original code) | v83 (our version) |
|---------|----------------------|-------------------|
| Map files | Map001.nx, MapLatest.nx, MapPretty.nx | Single Map.nx |
| World buttons | BtWorld/release/button:N | BtWorld/N directly |
| Channels | BtChannel/button:N (colon syntax) | channel/N (simple) |
| Channel bg | BtChannel/layer:bg | chBackgrn |
| Enter world | BtChannel/button:GoWorld | BtGoworld |
| Regions | Multiple regions with indices | No regions |
| UI version check | POSTCHAOS_BITMAP validation | Removed |

## Button Types

### MapleButton
Expects NX node with: `normal/0`, `pressed/0`, `mouseOver/0`, `disabled/0`
Supports animated normal state (multiple frames).

### TwoSpriteButton
Takes two sprite nodes: `nsrc` (shown in NORMAL/DISABLED) and `ssrc` (shown in MOUSEOVER/PRESSED).
Constructor: `TwoSpriteButton(nsrc, ssrc, position)`

## Server Configuration

- **Server**: Cosmic v83 at 192.168.0.25:8484 (fork of HeavenMS, Java)
- **Config file**: `Configuration.h` (compile-time defaults) + `Settings` file (runtime)
- **Settings file** generated in build/ after first run
- **Cosmic repo**: [P0nk/Cosmic](https://github.com/P0nk/Cosmic) on GitHub

### Cosmic Server Protocol Notes

**HWID validation**: Cosmic validates HWID as `[0-9A-F]{12}_[0-9A-F]{8}` (MAC_SerialReversed).
- MAC: 12 hex chars from network adapter (e.g., `001C429F65C6`)
- Serial: 8 hex chars from volume serial, zero-padded, byte-reversed
- Set in `HardwareInfo.h` → `Configuration::set_hwid(mac, serial)` → reversed and joined with `_`
- Invalid HWID → server sends opcode 9 error code 17

**PIC vs PIN** (two separate systems):
- **PIN**: Login-level authentication (opcode 6/7). Usually disabled on private servers.
- **PIC**: Character-selection authentication (opcode 28-30). `require_pic` from charlist response:
  - `0` = PIC exists server-side but client needs to register → RegisterPicPacket (opcode 29)
  - `1` = PIC required → SelectCharPicPacket (opcode 30)
  - `2` = No PIC needed → SelectCharPacket (opcode 19)

**Character selection flow** (opcode 30 success path):
1. Client sends SELECT_CHAR_PIC: `write_string(pic) + write_int(charId) + write_string(macs) + write_string(hwid)`
2. Server validates: HWID format → PIC match → session/multiclient checks
3. Success → SERVER_IP (opcode 12): IP + port + charID
4. Failure → SELECT_CHARACTER_BY_VAC (opcode 9): `write_short(reason)`

**Opcode 9 error codes** (getAfterLoginError):
| Code | Meaning |
|------|---------|
| 7 | Account already logged in elsewhere |
| 8 | Internal coordinator error |
| 9 | Generic session error |
| 10 | Too many connections / server busy |
| 17 | Invalid HWID format or HWID mismatch |

**Key Cosmic source files** (for protocol reference):
- `tools/PacketCreator.java` — server→client packet construction
- `net/server/handlers/login/` — login handler implementations
- `net/server/coordinator/session/Hwid.java` — HWID validation regex
- `constants/net/SendOpcode.java` — server→client opcode enum
- `constants/net/RecvOpcode.java` — client→server opcode enum

## NX Files (v83)

All 15 NX files must be in the build/ directory (symlinks OK):
Base.nx, Character.nx, Effect.nx, Etc.nx, Item.nx, Map.nx, Mob.nx,
Morph.nx, Npc.nx, Quest.nx, Reactor.nx, Skill.nx, Sound.nx, String.nx,
TamingMob.nx, UI.nx

Converted from v83 WZ files using wztonx converter. Fonts/ directory also needed.

## v167+ → v83 UI Path Mapping

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
| `UIWindow2.img/Shop2` | `UIWindow.img/Shop` | Name change (Shop2 → Shop) |
| `UIWindow2.img/socialChatEnter` | N/A (v83 has no social chat) | Skip |
| `UIWindow2.img/socialRank` | N/A | Skip |
| `UIWindow2.img/EventList` | `UIWindow.img/MapleEvent` | Name change |
| `UIWindow2.img/ToolTip/WorldMap` | `UIWindow.img/ToolTip/Equip` | Different structure |
| `UIWindow2.img/KeyConfig/KeyType` | `UIWindow.img/KeyConfig` | Path fix + structure diff |
| `UIWindow4.img/Equip` | `UIWindow.img/Equip` | Path fix only |
| `UIWindow4.img/Stat` | `UIWindow.img/Stat` | Path fix only |
| `UIWindow4.img/Skill/skillPoint` | `UIWindow.img/Skill` | Path fix, may lack node |
| `UIWindow6.img/askReward` | `UIWindow.img/GameMenu` | Different structure |

### v83 StatusBar.img Structure
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

## Known Issues

### In-Game
- **UI layout positioning**: UIStatusBar HP/MP gauge positions, button alignment need visual tuning
- **"stoi: no conversion" warnings**: Non-fatal — from `string_conversion::or_default<T>()` in Misc.h when NX node names aren't numeric
- **Stub handlers**: QUICKSLOT_INIT (parsed but not wired to UI), AUTO_HP/MP_POT, BUDDYLIST, FAMILY_*, CLAIM_STATUS, SET_GENDER, SET_NPC_SCRIPTABLE
- **Opcode 26**: Unhandled packet from server (logged, no crash)

### Login/Character Select
- **UICharSelect positioning**: Elements mispositioned — hardcoded positions need visual tuning
- **UILogin signboard**: Position slightly off (centered, should be offset down-left)
- **Opcode 27**: RECOMMENDED_WORLDS handler disabled (v83 format mismatch)

### Platform
- **Retina**: No HiDPI scaling — framebuffer is 2x logical size on Retina displays
- **Window icon**: Optional (no Icon.png required)
- **Audio format edge cases**: NX audio is mostly WAV/MP3 but some entries may fail to decode

### Resolved (previously listed here)
- ~~Audio stubbed~~ — FIXED: full ma_decoder_init_memory pipeline (BGM + SFX)
- ~~Hair layers unknown~~ — FIXED: backHairBelowCapNarrow/Wide mapped to BELOWCAP
- ~~UIQuit wrong .img~~ — FIXED: rewritten for UIWindow.img/GameMenu
- ~~Missing UI elements~~ — FIXED: all 26 files ported to v83 NX paths
- ~~UICharSelect missing textures~~ — FIXED: v83 rewrite with TwoSpriteButton pages

## Troubleshooting

### Crash Debugging

The client has a built-in crash handler (`MapleStory.cpp`) that prints a stack trace on SIGSEGV/SIGABRT:

```
=== CRASH (signal 11) ===
0   cosmic-client    0x00000001001234  crash_handler + 40
1   libsystem_platform.dylib  ...
...
```

**How to use**: Just run `./cosmic-client` — crashes print the backtrace to stderr automatically. Pipe to a file with `./cosmic-client 2>crash.log` to capture.

For more detail, attach lldb:
```bash
lldb ./cosmic-client
(lldb) run
# after crash:
(lldb) bt        # full backtrace with line numbers
(lldb) frame 0   # inspect crash frame
```

### Common Crash Patterns

| Symptom | Likely Cause | Fix |
|---------|-------------|-----|
| Crash on startup before window | Missing NX files in build/ | Symlink all 15 .nx files |
| Crash in `ma_node_input_bus_read_pcm_frames` | miniaudio engine running without audio data | Don't call `ma_engine_init()` until playback is implemented |
| Crash after UI transition (login → world) | v167+ NX path accessed on v83 data | Use nxdump to verify paths, rewrite for v83 |
| Crash in `Texture::draw` or `Sprite::draw` | NX node resolved to invalid bitmap | Check that node exists before creating Texture/Sprite |
| Crash in constructor (segfault) | MapleButton given empty/null NX node | Verify `normal/0`, `pressed/0`, `mouseOver/0` children exist |
| `terminate called after throwing` | nlnx threw on missing node | Wrap in try/catch or check node validity first |

### NX Path Debugging

When a UI screen crashes or renders wrong, the issue is almost always a v167+ NX path that doesn't exist in v83. Workflow:

1. **Identify the file**: crash backtrace → which UIType constructor/draw
2. **Dump the v83 NX structure**:
   ```bash
   /tmp/nxdump/build/nxdump build/UI.nx Login.img/CharSelect 3
   /tmp/nxdump/build/nxdump build/Map.nx Obj/login.img/CharSelect 3
   ```
3. **Compare with code**: look for node paths in the .cpp that don't match the dump
4. **Fix paths**: update to match v83 structure, add `// v83:` comment

### Null NX Node Safety

When an NX node doesn't exist, `nl::node` returns a null/empty node. These are **safe** to pass to:
- `Sprite(node)` → empty sprite (no-op draw)
- `Texture(node)` → empty texture (no-op draw)
- `Animation(node)` → empty animation
- `Charset(node, ...)` → empty charset

These are **NOT safe**:
- `MapleButton(node)` → crashes if `normal/0` doesn't exist (accesses child nodes)
- `NameTag(node)` → crashes on missing bitmap children
- Indexing into null node children that are then dereferenced

### Server Connection Issues

- **Timeout on connect**: Verify Cosmic is running: `ssh -J kumo@192.168.0.105 homelab@192.168.0.25` → `docker ps | grep cosmic`
- **Handshake fails**: Check MAPLEVERSION (must be 83) in `Net/Session.cpp`
- **Opcode not handled**: `PacketSwitch.cpp` logs unhandled opcodes — check if the opcode needs a handler or can be safely ignored
- **Packet parse crash**: Server sends unexpected format — add recv bytes logging to trace

### Audio (Implemented)

Audio engine is fully working via `ma_decoder_init_memory()` pipeline:
- **BGM**: `Music::play()` decodes NX audio from memory, plays with `ma_sound_set_looping(MA_TRUE)`. Static `bgm_decoder`/`bgm_sound`/`bgm_active` manage current track. Stops previous BGM before starting new one.
- **BGM (once)**: `Music::play_once()` — same but without looping (for one-shot tracks).
- **SFX**: `Sound::play()` creates per-sound `ma_decoder` + `ma_sound` from cached audio data. Fire-and-forget with `ma_sound_set_end_callback()` for cleanup (deletes decoder + sound when done).
- **Engine**: `ma_engine_init()` runs in `Music::init()`. Non-fatal on failure (game works without audio).
- **Cleanup**: `Sound::close()` stops BGM, uninits engine, clears caches.

## Porting Workflow

When fixing a UI screen for v83:

1. **Dump the v83 NX structure** with nxdump (see tools above)
2. **Fetch the master branch file** from `ryantpayton/MapleStory-Client` master for reference:
   ```bash
   gh api repos/ryantpayton/MapleStory-Client/contents/<path>?ref=master | jq -r .content | base64 -d
   ```
3. **Compare NX paths**: master branch reads from nodes that may not exist in v83
4. **Map available nodes**: document what v83 NX has in CLAUDE.md
5. **Port with fallbacks**: use v83 nodes where they exist, hardcode where they don't
6. **Add `// v83:` comments** explaining every deviation from master

### Branch Comparison

| Branch | Platform | NX Version | Status |
|--------|----------|-----------|--------|
| `linux` (our base) | Cross-platform (GLFW/ASIO) | v167+ paths | Engine works, UI paths wrong |
| `master` | Windows-only (DirectX/Winsock/Bass) | v83 paths (mostly) | Correct UI, wrong platform |

Our approach: `linux` branch engine + `master` branch UI logic, adapted for actual v83 NX data.

## Coding Conventions

- Use `nl::nx::map` for all map data (NOT map001/mapLatest/mapPretty)
- Always verify NX paths with nxdump before hardcoding
- Comment v83-specific changes with `// v83:` prefix
- Keep v167+ code commented out (not deleted) during initial port for reference
- Test with Cosmic server at 192.168.0.25:8484
- Document NX structure in CLAUDE.md before writing code that references NX nodes
- Compare with master branch when porting UI screens
