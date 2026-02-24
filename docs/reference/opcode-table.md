# v83 Opcode Reference

## v83 Opcode Map (Server to Client)

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

## v83 Opcode Map (Server to Client) — In-Game

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

## v83 Opcode Map (Client to Server)

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

## Keyboard Mapping (Keytable)

Server sends keybindings using DIK scan code indices (0-89). `Keyboard.cpp` translates to GLFW keycodes.

Key index reference (DIK to physical key):
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
