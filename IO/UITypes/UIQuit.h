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
#include <string>

#include "../UIElement.h"

#include "../Components/Charset.h"
#include "Character/CharStats.h"
#include "../Graphics/Text.h"
#include "../Graphics/Geometry.h"

namespace ms
{
	// v83: Rewritten to use UIWindow.img/GameMenu (simple menu with quit/channel/options buttons)
	// v167+ used UIWindow6.img/askReward with play time/level/exp tracking
	class UIQuit : public UIElement
	{
	public:
		static constexpr Type TYPE = UIElement::Type::QUIT;
		static constexpr bool FOCUSED = true;
		static constexpr bool TOGGLED = false;

		UIQuit(const CharStats &stats);

		void draw(float inter) const override;

		void update() override;

		Cursor::State send_cursor(bool clicked, Point<int16_t> cursorpos) override;

		void send_key(int32_t keycode, bool pressed, bool escape) override;

		UIElement::Type get_type() const override;

	protected:
		Button::State button_pressed(uint16_t buttonid) override;

	private:
		const CharStats &stats;

		void close();

		enum Buttons : uint16_t
		{
			BT_QUIT,
			BT_CHANNEL,
			BT_GAMEOPT,
			BT_SYSOPT,
			BT_SKIN
		};

		ColorBox background;
	};
}
