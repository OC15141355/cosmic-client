//////////////////////////////////////////////////////////////////////////////////
//	This file is part of the continued Journey MMORPG client					//
//	Copyright (C) 2015-2019  Daniel Allendorf, Ryan Payton						//
//																				//
//	This program is free software: you can redistribute it and/or modify		//
//	it under the terms of the GNU Affero General Public License as published by	//
//	the Free Software Foundation, either version 3 of the License, or			//
//	(at your option) any later version.											//
//																				//
//	This program is distributed in the hope that it will be useful,				//
//	but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				//
//	GNU Affero General Public License for more details.							//
//																				//
//	You should have received a copy of the GNU Affero General Public License	//
//	along with this program.  If not, see <https://www.gnu.org/licenses/>.		//
//////////////////////////////////////////////////////////////////////////////////
#include "TestingHandlers.h"

#include "../../Gameplay/Stage.h"
#include "../../IO/UI.h"

#include "../../IO/UITypes/UILoginNotice.h"
#include <string>

namespace ms
{
	void CheckSpwResultHandler::handle(InPacket& recv) const
	{
		int reason = recv.read_byte();

		if (reason == 0)
			UI::get().emplace<UILoginNotice>(UILoginNotice::Message::INCORRECT_PIC);
		else
			std::cout << "[CheckSpwResultHandler]: Unknown reason: [" << reason << "]" << std::endl;

		UI::get().enable();
	}

	void FieldEffectHandler::handle(InPacket& recv) const
	{
		int rand = recv.read_byte();

		// Effect
		if (rand == 3)
		{
			std::string path = recv.read_string();

			Stage::get().add_effect(path);

			return;
		}

		std::cout << "[FieldEffectHandler]: Unknown value: [" << rand << "]" << std::endl;
	}

	void BuddyListHandler::handle(InPacket&) const
	{
		// v83: BUDDYLIST (opcode 63) — buddy add/remove/online status
		// TODO: Implement buddy list UI
	}

	void FamilyInfoHandler::handle(InPacket&) const
	{
		// v83: FAMILY_INFO_RESULT (opcode 95) — family system info
		// TODO: Implement if family system is needed
	}

	void FamilyPrivilegeHandler::handle(InPacket&) const
	{
		// v83: FAMILY_PRIVILEGE_LIST (opcode 100) — family privileges
		// TODO: Implement if family system is needed
	}

	void ClaimStatusHandler::handle(InPacket&) const
	{
		// v83: CLAIM_STATUS_CHANGED (opcode 47) — event reward tracking
		// TODO: Implement if event system is needed
	}

	void SetGenderHandler::handle(InPacket&) const
	{
		// v83: SET_GENDER (opcode 58) — sets account gender on client
		// TODO: Store in account/player state if needed
	}

	void SetNpcScriptableHandler::handle(InPacket&) const
	{
		// v83: SET_NPC_SCRIPTABLE (opcode 263) — marks NPCs as scriptable
		// TODO: Implement NPC scriptability flags
	}

	void CashShopOperationHandler::handle(InPacket&) const
	{
		// v83: CS_OPERATION (opcode 324) — cash shop operation result
		// TODO: Handle purchase/gift/transfer responses
	}

	void CashShopUpdateHandler::handle(InPacket&) const
	{
		// v83: CS_UPDATE (opcode 325) — cash shop inventory/balance update
		// TODO: Update cash shop UI with new balance/items
	}
}