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

#include "../../Graphics/Animation.h"
#include "../../Graphics/Text.h"

namespace ms
{
	// v83: Race selection screen — 3 races: Explorer, Aran, Cygnus Knight
	// (v167+ had a 26-class carousel via RaceSelect_new; v83 uses simple RaceSelect)
	class UIRaceSelect : public UIElement
	{
	public:
		static constexpr Type TYPE = UIElement::Type::RACESELECT;
		static constexpr bool FOCUSED = false;
		static constexpr bool TOGGLED = false;

		UIRaceSelect();

		void draw(float inter) const override;

		void update() override;

		Cursor::State send_cursor(bool clicked, Point<int16_t> cursorpos) override;

		void send_key(int32_t keycode, bool pressed, bool escape) override;

		UIElement::Type get_type() const override;

		bool check_name(std::string name) const;

		void send_naming_result(bool nameused);

	protected:
		Button::State button_pressed(uint16_t buttonid) override;

	private:
		void show_charselect();

		std::string to_lower(std::string value) const;

		// v83: 3 races only
		static constexpr uint8_t RACE_COUNT = 3;

		enum Buttons : uint16_t
		{
			BACK,
			BT_NORMAL,
			BT_ARAN,
			BT_KNIGHT,
			BT_SELECT
		};

		enum Race : uint8_t
		{
			EXPLORER = 0,
			ARAN = 1,
			KNIGHT = 2
		};

		Text version;

		// v83: Each race has off/on animations and descriptive text
		Animation off_anims[RACE_COUNT];
		Animation on_anims[RACE_COUNT];
		Sprite race_texts[RACE_COUNT];

		uint8_t selected_race;
	};
}
