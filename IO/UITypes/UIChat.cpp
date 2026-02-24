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
#include "UIChat.h"

#include "../UI.h"

#include "../Components/MapleButton.h"

#include <nlnx/nx.hpp>

namespace ms
{
	UIChat::UIChat() : UIDragElement<PosMAPLECHAT>()
	{
		// v83: socialChatEnter and socialRank nodes DON'T EXIST in v83 UIWindow.img
		// Maple Chat is not a v83 feature — UIChatBar handles all chat functionality
		// Immediately deactivate so the UI does nothing
		deactivate();
	}

	void UIChat::draw(float inter) const
	{
		UIElement::draw(inter);

		charset.draw("0", position + origin_left + rank_shift);
		charset.draw("0", position + origin_right + rank_shift);

		name_left.draw(position + origin_left + name_shift);
		name_right.draw(position + origin_right + name_shift);
	}

	void UIChat::send_key(int32_t keycode, bool pressed, bool escape)
	{
		if (pressed && escape)
			close();
	}

	UIElement::Type UIChat::get_type() const
	{
		return TYPE;
	}

	Button::State UIChat::button_pressed(uint16_t buttonid)
	{
		switch (buttonid)
		{
			case Buttons::CLOSE:
				close();
				break;
			case Buttons::CHAT_DUO:
				break;
			case Buttons::CHAT_FRIEND:
				break;
			case Buttons::CHAT_RANDOM:
				break;
			default:
				break;
		}

		return Button::State::NORMAL;
	}

	void UIChat::close()
	{
		deactivate();
	}

	UIRank::UIRank() : UIDragElement<PosMAPLECHAT>()
	{
		// v83: socialRank node DOESN'T EXIST in v83 UIWindow.img
		// Immediately deactivate
		deactivate();
	}

	void UIRank::draw(float inter) const
	{
		UIElement::draw(inter);

		charset.draw("0", position + origin_left + rank_shift);
		charset.draw("0", position + origin_right + rank_shift);

		name_left.draw(position + origin_left + name_shift);
		name_right.draw(position + origin_right + name_shift);
	}

	void UIRank::send_key(int32_t keycode, bool pressed, bool escape)
	{
		if (pressed && escape)
			close();
	}

	UIElement::Type UIRank::get_type() const
	{
		return TYPE;
	}

	Button::State UIRank::button_pressed(uint16_t buttonid)
	{
		switch (buttonid)
		{
			case Buttons::CLOSE:
				close();
				break;
			default:
				break;
		}

		return Button::State::NORMAL;
	}

	void UIRank::close()
	{
		deactivate();
	}
}