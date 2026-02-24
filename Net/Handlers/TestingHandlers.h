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
#pragma once

#include "../PacketHandler.h"

namespace ms
{
	// TODO: Comment
	class CheckSpwResultHandler : public PacketHandler
	{
		void handle(InPacket& recv) const override;
	};

	// TODO: Comment
	class FieldEffectHandler : public PacketHandler
	{
		void handle(InPacket& recv) const override;
	};

	// v83: Buddy list operations (add, remove, update online status)
	// Opcode: BUDDYLIST(63)
	class BuddyListHandler : public PacketHandler
	{
		void handle(InPacket& recv) const override;
	};

	// v83: Family system info
	// Opcode: FAMILY_INFO_RESULT(95)
	class FamilyInfoHandler : public PacketHandler
	{
		void handle(InPacket& recv) const override;
	};

	// v83: Family privilege list
	// Opcode: FAMILY_PRIVILEGE_LIST(100)
	class FamilyPrivilegeHandler : public PacketHandler
	{
		void handle(InPacket& recv) const override;
	};

	// v83: Claim/reward status update
	// Opcode: CLAIM_STATUS_CHANGED(47)
	class ClaimStatusHandler : public PacketHandler
	{
		void handle(InPacket& recv) const override;
	};

	// v83: Set account gender
	// Opcode: SET_GENDER(58)
	class SetGenderHandler : public PacketHandler
	{
		void handle(InPacket& recv) const override;
	};

	// v83: Mark NPCs as scriptable/interactable
	// Opcode: SET_NPC_SCRIPTABLE(263)
	class SetNpcScriptableHandler : public PacketHandler
	{
		void handle(InPacket& recv) const override;
	};

	// v83: Cash shop operation result
	// Opcode: CS_OPERATION(324)
	class CashShopOperationHandler : public PacketHandler
	{
		void handle(InPacket& recv) const override;
	};

	// v83: Cash shop update (inventory/balance change)
	// Opcode: CS_UPDATE(325)
	class CashShopUpdateHandler : public PacketHandler
	{
		void handle(InPacket& recv) const override;
	};
}