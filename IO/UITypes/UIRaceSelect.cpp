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
#include "UIRaceSelect.h"
#include "UICharSelect.h"
#include "UIExplorerCreation.h"
#include "UICygnusCreation.h"
#include "UIAranCreation.h"

#include "../UI.h"
#include "../Configuration.h"

#include "../Components/MapleButton.h"
#include "../../Audio/Audio.h"

#include <cctype>

#include <nlnx/nx.hpp>
#include <string>

namespace ms
{
	// v83: Complete rewrite — RaceSelect_new (26-class carousel) replaced with
	// RaceSelect (3 static races: Explorer, Aran, Cygnus Knight)
	UIRaceSelect::UIRaceSelect() : UIElement(Point<int16_t>(0, 0), Point<int16_t>(800, 600)), selected_race(EXPLORER)
	{
		std::string version_text = Configuration::get().get_version();
		version = Text(Text::Font::A11M, Text::Alignment::LEFT, Color::Name::LEMONGRASS, "Ver. " + version_text);

		nl::node Login = nl::nx::ui["Login.img"];
		nl::node Common = Login["Common"];
		nl::node RaceSelect = Login["RaceSelect"];

		// v83: Common frame background
		sprites.emplace_back(Common["frame"], Point<int16_t>(400, 300));

		// v83: 3 race sub-nodes
		nl::node normal_node = RaceSelect["normal"];
		nl::node aran_node = RaceSelect["aran"];
		nl::node knight_node = RaceSelect["knight"];

		// v83: Race selection buttons
		buttons[Buttons::BT_NORMAL] = std::make_unique<MapleButton>(normal_node["BtNormal"]);
		buttons[Buttons::BT_ARAN] = std::make_unique<MapleButton>(aran_node["BtAran"]);
		buttons[Buttons::BT_KNIGHT] = std::make_unique<MapleButton>(knight_node["BtKnight"]);
		buttons[Buttons::BT_SELECT] = std::make_unique<MapleButton>(RaceSelect["BtSelect"]);
		buttons[Buttons::BACK] = std::make_unique<MapleButton>(Common["BtStart"], Point<int16_t>(0, 515));

		// v83: Off/On animations for each race
		off_anims[EXPLORER] = Animation(normal_node["OffAnimation"]);
		on_anims[EXPLORER] = Animation(normal_node["OnAnimation"]);
		off_anims[ARAN] = Animation(aran_node["OffAnimation"]);
		on_anims[ARAN] = Animation(aran_node["OnAnimation"]);
		off_anims[KNIGHT] = Animation(knight_node["OffAnimation"]);
		on_anims[KNIGHT] = Animation(knight_node["OnAnimation"]);

		// v83: Text descriptions for each race
		race_texts[EXPLORER] = Sprite(normal_node["text"]);
		race_texts[ARAN] = Sprite(aran_node["text"]);
		race_texts[KNIGHT] = Sprite(knight_node["text"]);

		Sound(Sound::Name::RACESELECT).play();
	}

	void UIRaceSelect::draw(float inter) const
	{
		UIElement::draw_sprites(inter);

		version.draw(position + Point<int16_t>(707, 1));

		// v83: Draw race animations — selected shows OnAnimation, others show OffAnimation
		for (uint8_t i = 0; i < RACE_COUNT; i++)
		{
			if (i == selected_race)
				on_anims[i].draw(DrawArgument(position), inter);
			else
				off_anims[i].draw(DrawArgument(position), inter);
		}

		// v83: Draw selected race description text
		race_texts[selected_race].draw(position, inter);

		UIElement::draw_buttons(inter);
	}

	void UIRaceSelect::update()
	{
		UIElement::update();

		for (uint8_t i = 0; i < RACE_COUNT; i++)
		{
			if (i == selected_race)
				on_anims[i].update();
			else
				off_anims[i].update();
		}
	}

	Cursor::State UIRaceSelect::send_cursor(bool clicked, Point<int16_t> cursorpos)
	{
		return UIElement::send_cursor(clicked, cursorpos);
	}

	void UIRaceSelect::send_key(int32_t keycode, bool pressed, bool escape)
	{
		if (pressed)
		{
			if (escape)
				show_charselect();
			else if (keycode == KeyAction::Id::RETURN)
				button_pressed(Buttons::BT_SELECT);
		}
	}

	UIElement::Type UIRaceSelect::get_type() const
	{
		return TYPE;
	}

	bool UIRaceSelect::check_name(std::string name) const
	{
		nl::node ForbiddenName = nl::nx::etc["ForbiddenName.img"];

		for (auto forbiddenName : ForbiddenName)
		{
			std::string lName = to_lower(name);
			std::string fName = to_lower(forbiddenName);

			if (lName.find(fName) != std::string::npos)
				return false;
		}

		return true;
	}

	void UIRaceSelect::send_naming_result(bool nameused)
	{
		if (selected_race == EXPLORER)
		{
			if (auto explorercreation = UI::get().get_element<UIExplorerCreation>())
				explorercreation->send_naming_result(nameused);
		}
		else if (selected_race == KNIGHT)
		{
			if (auto cygnuscreation = UI::get().get_element<UICygnusCreation>())
				cygnuscreation->send_naming_result(nameused);
		}
		else if (selected_race == ARAN)
		{
			if (auto arancreation = UI::get().get_element<UIAranCreation>())
				arancreation->send_naming_result(nameused);
		}
	}

	Button::State UIRaceSelect::button_pressed(uint16_t buttonid)
	{
		switch (buttonid)
		{
		case Buttons::BACK:
			show_charselect();
			return Button::State::NORMAL;
		case Buttons::BT_NORMAL:
			selected_race = EXPLORER;
			Sound(Sound::Name::RACESELECT).play();
			return Button::State::NORMAL;
		case Buttons::BT_ARAN:
			selected_race = ARAN;
			Sound(Sound::Name::RACESELECT).play();
			return Button::State::NORMAL;
		case Buttons::BT_KNIGHT:
			selected_race = KNIGHT;
			Sound(Sound::Name::RACESELECT).play();
			return Button::State::NORMAL;
		case Buttons::BT_SELECT:
		{
			Sound(Sound::Name::SCROLLUP).play();
			deactivate();

			if (selected_race == EXPLORER)
				UI::get().emplace<UIExplorerCreation>();
			else if (selected_race == ARAN)
				UI::get().emplace<UIAranCreation>();
			else if (selected_race == KNIGHT)
				UI::get().emplace<UICygnusCreation>();

			return Button::State::NORMAL;
		}
		default:
			return Button::State::NORMAL;
		}
	}

	void UIRaceSelect::show_charselect()
	{
		Sound(Sound::Name::SCROLLUP).play();

		deactivate();

		if (auto charselect = UI::get().get_element<UICharSelect>())
			charselect->makeactive();
	}

	std::string UIRaceSelect::to_lower(std::string value) const
	{
		std::transform(value.begin(), value.end(), value.begin(), ::tolower);

		return value;
	}
}
