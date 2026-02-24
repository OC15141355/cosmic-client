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
#include "UICygnusCreation.h"

#include "UICharSelect.h"
#include "UILoginNotice.h"
#include "UIRaceSelect.h"

#include "../UI.h"

#include "../Components/MapleButton.h"

#include "../../Configuration.h"

#include "../../Audio/Audio.h"
#include "../../Data/ItemData.h"

#include "../../Net/Packets/CharCreationPackets.h"

#include <nlnx/nx.hpp>
#include <string>

namespace ms
{
	UICygnusCreation::UICygnusCreation() : UIElement(Point<int16_t>(0, 0), Point<int16_t>(800, 600))
	{
		charSet = false;
		named = false;
		female = false;

		std::string version_text = Configuration::get().get_version();
		version = Text(Text::Font::A11M, Text::Alignment::LEFT, Color::Name::LEMONGRASS, "Ver. " + version_text);

		nl::node Login = nl::nx::ui["Login.img"];
		nl::node Common = Login["Common"];
		// v83: NewCharKnight instead of CustomizeChar/1000
		nl::node NewChar = Login["NewCharKnight"];
		nl::node back = nl::nx::map["Back"]["login.img"]["back"];
		nl::node signboard = nl::nx::map["Obj"]["login.img"]["NewChar"]["signboard"];

		sky = back["2"];
		cloud = back["27"];

		sprites.emplace_back(back["46"], Point<int16_t>(400, 300));
		sprites.emplace_back(signboard["2"], DrawArgument(Point<int16_t>(212, 217), 2.0f));

		// v83: charSet panel background
		sprites_lookboard.emplace_back(NewChar["charSet"], Point<int16_t>(415, 89));

		// v83: avatarSel/0-6 category labels
		for (size_t i = 0; i <= 6; i++)
			sprites_lookboard.emplace_back(NewChar["avatarSel"][i]["normal"],
										   Point<int16_t>(416, 98));

		// v83: Skin, weapon, and hair color L/R for Cygnus
		buttons[Buttons::BT_CHARC_SKINL] = std::make_unique<MapleButton>(NewChar["BtLeft"],
																		 Point<int16_t>(418, 81 + (4 * 18)));
		buttons[Buttons::BT_CHARC_SKINR] = std::make_unique<MapleButton>(NewChar["BtRight"],
																		 Point<int16_t>(415, 81 + (4 * 18)));
		buttons[Buttons::BT_CHARC_WEPL] = std::make_unique<MapleButton>(NewChar["BtLeft"],
																		Point<int16_t>(418, 81 + (8 * 18)));
		buttons[Buttons::BT_CHARC_WEPR] = std::make_unique<MapleButton>(NewChar["BtRight"],
																		Point<int16_t>(415, 81 + (8 * 18)));
		buttons[Buttons::BT_CHARC_HAIRCOLORL] = std::make_unique<MapleButton>(NewChar["BtLeft"],
																			  Point<int16_t>(418, 81 + (2 * 18)));
		buttons[Buttons::BT_CHARC_HAIRCOLORR] = std::make_unique<MapleButton>(NewChar["BtRight"],
																			  Point<int16_t>(415, 81 + (2 * 18)));

		buttons[Buttons::BT_CHARC_OK] = std::make_unique<MapleButton>(NewChar["BtYes"],
																	  Point<int16_t>(502, 381));
		buttons[Buttons::BT_CHARC_CANCEL] = std::make_unique<MapleButton>(NewChar["BtNo"],
																		  Point<int16_t>(607, 381));

		nameboard = NewChar["charName"];
		namechar = Textfield(Text::Font::A13M, Text::Alignment::LEFT, Color::Name::BLACK,
							 Rectangle<int16_t>(Point<int16_t>(539, 209), Point<int16_t>(631, 252)), 12);

		sprites.emplace_back(Common["frame"], Point<int16_t>(400, 300));
		sprites.emplace_back(Common["step"]["3"], Point<int16_t>(40, 0));

		buttons[Buttons::BT_BACK] = std::make_unique<MapleButton>(Common["BtStart"],
																  Point<int16_t>(0, 515));

		namechar.set_state(Textfield::DISABLED);

		namechar.set_enter_callback(
				[&](std::string)
				{
					button_pressed(Buttons::BT_CHARC_OK);
				}
		);

		namechar.set_key_callback(
				KeyAction::Id::ESCAPE,
				[&]()
				{
					button_pressed(Buttons::BT_CHARC_CANCEL);
				}
		);

		facename = Text(Text::Font::A11M, Text::Alignment::CENTER, Color::Name::BLACK);
		hairname = Text(Text::Font::A11M, Text::Alignment::CENTER, Color::Name::BLACK);
		bodyname = Text(Text::Font::A11M, Text::Alignment::CENTER, Color::Name::BLACK);
		topname = Text(Text::Font::A11M, Text::Alignment::CENTER, Color::Name::BLACK);
		botname = Text(Text::Font::A11M, Text::Alignment::CENTER, Color::Name::BLACK);
		shoename = Text(Text::Font::A11M, Text::Alignment::CENTER, Color::Name::BLACK);
		wepname = Text(Text::Font::A11M, Text::Alignment::CENTER, Color::Name::BLACK);

		nl::node mkinfo = nl::nx::etc["MakeCharInfo.img"]["Info"];

		for (size_t i = 0; i < 2; i++)
		{
			bool f;
			nl::node CharGender;

			if (i == 0)
			{
				f = true;
				CharGender = mkinfo["CharFemale"];
			}
			else
			{
				f = false;
				CharGender = mkinfo["CharMale"];
			}

			for (auto node : CharGender)
			{
				int num = stoi(node.name());

				for (auto idnode : node)
				{
					int32_t value = idnode;

					switch (num)
					{
						case 0:
							faces[f].push_back(value);
							break;
						case 1:
							hairs[f].push_back(value);
							break;
						case 2:
							haircolors[f].push_back(static_cast<uint8_t>(value));
							break;
						case 3:
							skins[f].push_back(static_cast<uint8_t>(value));
							break;
						case 4:
							tops[f].push_back(value);
							break;
						case 5:
							bots[f].push_back(value);
							break;
						case 6:
							shoes[f].push_back(value);
							break;
						case 7:
							weapons[f].push_back(value);
							break;
					}
				}
			}
		}

		randomize_look();

		newchar.set_direction(true);

		cloudfx = 200.0f;
	}

	void UICygnusCreation::draw(float inter) const
	{
		for (size_t i = 0; i < 2; i++)
			for (size_t k = 0; k < 800; k += sky.width())
				sky.draw(Point<int16_t>(k, (400 * i) - 100));

		int16_t cloudx = static_cast<int16_t>(cloudfx) % 800;
		cloud.draw(Point<int16_t>(cloudx - cloud.width(), 310));
		cloud.draw(Point<int16_t>(cloudx, 310));
		cloud.draw(Point<int16_t>(cloudx + cloud.width(), 310));

		if (!charSet)
		{
			// v83: Customize appearance stage (Cygnus: skin, weapon, hair color)
			UIElement::draw_sprites(inter);

			for (auto &sprite : sprites_lookboard)
				sprite.draw(position, inter);

			facename.draw(Point<int16_t>(620, 218 + (-1 * 18)));
			hairname.draw(Point<int16_t>(620, 218 + (0 * 18)));
			bodyname.draw(Point<int16_t>(620, 218 + (2 * 18)));
			topname.draw(Point<int16_t>(620, 218 + (3 * 18)));
			botname.draw(Point<int16_t>(620, 218 + (4 * 18)));
			shoename.draw(Point<int16_t>(620, 218 + (5 * 18)));
			wepname.draw(Point<int16_t>(620, 218 + (6 * 18)));

			newchar.draw(Point<int16_t>(394, 339), inter);

			UIElement::draw_buttons(inter);
		}
		else if (!named)
		{
			// v83: Name entry stage
			UIElement::draw_sprites(inter);

			nameboard.draw(Point<int16_t>(423, 104));

			namechar.draw(position);
			newchar.draw(Point<int16_t>(394, 339), inter);

			UIElement::draw_buttons(inter);
		}
		else
		{
			// v83: Waiting for server response
			UIElement::draw_sprites(inter);

			nameboard.draw(Point<int16_t>(423, 104));

			UIElement::draw_buttons(inter);
		}

		version.draw(position + Point<int16_t>(707, 1));
	}

	void UICygnusCreation::update()
	{
		if (!charSet)
		{
			for (auto& sprite : sprites_lookboard)
				sprite.update();

			newchar.update(Constants::TIMESTEP);
		}
		else if (!named)
		{
			namechar.update(position);
			newchar.update(Constants::TIMESTEP);
		}

		UIElement::update();

		cloudfx += 0.25f;
	}

	Cursor::State UICygnusCreation::send_cursor(bool clicked, Point<int16_t> cursorpos)
	{
		if (namechar.get_state() == Textfield::State::NORMAL)
		{
			if (namechar.get_bounds().contains(cursorpos))
			{
				if (clicked)
				{
					namechar.set_state(Textfield::State::FOCUSED);

					return Cursor::State::CLICKING;
				}
				else
				{
					return Cursor::State::IDLE;
				}
			}
		}

		return UIElement::send_cursor(clicked, cursorpos);
	}

	void UICygnusCreation::send_key(int32_t keycode, bool pressed, bool escape)
	{
		if (pressed)
		{
			if (escape)
				button_pressed(Buttons::BT_CHARC_CANCEL);
			else if (keycode == KeyAction::Id::RETURN)
				button_pressed(Buttons::BT_CHARC_OK);
		}
	}

	UIElement::Type UICygnusCreation::get_type() const
	{
		return TYPE;
	}

	void UICygnusCreation::send_naming_result(bool nameused)
	{
		if (!named)
		{
			if (!nameused)
			{
				named = true;

				std::string cname = namechar.get_text();
				int32_t cface = faces[female][face];
				int32_t chair = hairs[female][hair];
				uint8_t chairc = haircolors[female][haircolor];
				uint8_t cskin = skins[female][skin];
				int32_t ctop = tops[female][top];
				int32_t cbot = bots[female][bot];
				int32_t cshoe = shoes[female][shoe];
				int32_t cwep = weapons[female][weapon];

				CreateCharPacket(cname, 0, cface, chair, chairc, cskin, ctop, cbot, cshoe, cwep, female).dispatch();

				auto onok = [&](bool alternate)
				{
					Sound(Sound::Name::SCROLLUP).play();

					UI::get().remove(UIElement::Type::LOGINNOTICE_CONFIRM);
					UI::get().remove(UIElement::Type::LOGINNOTICE);
					UI::get().remove(UIElement::Type::CLASSCREATION);
					UI::get().remove(UIElement::Type::RACESELECT);

					if (auto charselect = UI::get().get_element<UICharSelect>())
						charselect->post_add_character();
				};

				UI::get().emplace<UIKeySelect>(onok, true);
			}
			else
			{
				auto onok = [&]()
				{
					namechar.set_state(Textfield::State::FOCUSED);

					buttons[Buttons::BT_CHARC_OK]->set_state(Button::State::NORMAL);
					buttons[Buttons::BT_CHARC_CANCEL]->set_state(Button::State::NORMAL);
				};

				UI::get().emplace<UILoginNotice>(UILoginNotice::Message::NAME_IN_USE, onok);
			}
		}
	}

	Button::State UICygnusCreation::button_pressed(uint16_t buttonid)
	{
		switch (buttonid)
		{
			case Buttons::BT_CHARC_OK:
				if (!charSet)
				{
					// v83: Transition from customize to name entry
					charSet = true;

					buttons[Buttons::BT_CHARC_SKINL]->set_active(false);
					buttons[Buttons::BT_CHARC_SKINR]->set_active(false);
					buttons[Buttons::BT_CHARC_WEPL]->set_active(false);
					buttons[Buttons::BT_CHARC_WEPR]->set_active(false);
					buttons[Buttons::BT_CHARC_HAIRCOLORL]->set_active(false);
					buttons[Buttons::BT_CHARC_HAIRCOLORR]->set_active(false);

					buttons[Buttons::BT_CHARC_OK]->set_position(Point<int16_t>(510, 289));
					buttons[Buttons::BT_CHARC_CANCEL]->set_position(Point<int16_t>(615, 289));

					namechar.set_state(Textfield::State::FOCUSED);

					return Button::State::NORMAL;
				}
				else
				{
					if (!named)
					{
						std::string name = namechar.get_text();

						if (name.size() <= 0)
						{
							return Button::State::NORMAL;
						}
						else if (name.size() >= 4)
						{
							namechar.set_state(Textfield::State::DISABLED);

							buttons[Buttons::BT_CHARC_OK]->set_state(Button::State::DISABLED);
							buttons[Buttons::BT_CHARC_CANCEL]->set_state(Button::State::DISABLED);

							if (auto raceselect = UI::get().get_element<UIRaceSelect>())
							{
								if (raceselect->check_name(name))
								{
									NameCharPacket(name).dispatch();

									return Button::State::IDENTITY;
								}
							}

							std::function<void()> okhandler = [&]()
							{
								namechar.set_state(Textfield::State::FOCUSED);

								buttons[Buttons::BT_CHARC_OK]->set_state(Button::State::NORMAL);
								buttons[Buttons::BT_CHARC_CANCEL]->set_state(Button::State::NORMAL);
							};

							UI::get().emplace<UILoginNotice>(UILoginNotice::Message::ILLEGAL_NAME, okhandler);

							return Button::State::NORMAL;
						}
						else
						{
							namechar.set_state(Textfield::State::DISABLED);

							buttons[Buttons::BT_CHARC_OK]->set_state(Button::State::DISABLED);
							buttons[Buttons::BT_CHARC_CANCEL]->set_state(Button::State::DISABLED);

							std::function<void()> okhandler = [&]()
							{
								namechar.set_state(Textfield::State::FOCUSED);

								buttons[Buttons::BT_CHARC_OK]->set_state(Button::State::NORMAL);
								buttons[Buttons::BT_CHARC_CANCEL]->set_state(Button::State::NORMAL);
							};

							UI::get().emplace<UILoginNotice>(UILoginNotice::Message::ILLEGAL_NAME, okhandler);

							return Button::State::IDENTITY;
						}
					}
					else
					{
						return Button::State::NORMAL;
					}
				}
			case BT_BACK:
				Sound(Sound::Name::SCROLLUP).play();

				UI::get().remove(UIElement::Type::CLASSCREATION);
				UI::get().emplace<UIRaceSelect>();

				return Button::State::NORMAL;
			case Buttons::BT_CHARC_CANCEL:
				if (charSet)
				{
					// v83: Go back from name entry to customize
					charSet = false;

					buttons[Buttons::BT_CHARC_SKINL]->set_active(true);
					buttons[Buttons::BT_CHARC_SKINR]->set_active(true);
					buttons[Buttons::BT_CHARC_WEPL]->set_active(true);
					buttons[Buttons::BT_CHARC_WEPR]->set_active(true);
					buttons[Buttons::BT_CHARC_HAIRCOLORL]->set_active(true);
					buttons[Buttons::BT_CHARC_HAIRCOLORR]->set_active(true);

					buttons[Buttons::BT_CHARC_OK]->set_position(Point<int16_t>(502, 381));
					buttons[Buttons::BT_CHARC_CANCEL]->set_position(Point<int16_t>(607, 381));

					namechar.set_state(Textfield::State::DISABLED);

					return Button::State::NORMAL;
				}
				else
				{
					button_pressed(Buttons::BT_BACK);

					return Button::State::NORMAL;
				}
			case Buttons::BT_CHARC_HAIRCOLORL:
				haircolor = (haircolor > 0) ? haircolor - 1 : haircolors[female].size() - 1;
				newchar.set_hair(hairs[female][hair] + haircolors[female][haircolor]);
				hairname.change_text(newchar.get_hair()->get_name());

				return Button::State::NORMAL;
			case Buttons::BT_CHARC_HAIRCOLORR:
				haircolor = (haircolor < haircolors[female].size() - 1) ? haircolor + 1 : 0;
				newchar.set_hair(hairs[female][hair] + haircolors[female][haircolor]);
				hairname.change_text(newchar.get_hair()->get_name());

				return Button::State::NORMAL;
			case Buttons::BT_CHARC_SKINL:
				skin = (skin > 0) ? skin - 1 : skins[female].size() - 1;
				newchar.set_body(skins[female][skin]);
				bodyname.change_text(newchar.get_body()->get_name());

				return Button::State::NORMAL;
			case Buttons::BT_CHARC_SKINR:
				skin = (skin < skins[female].size() - 1) ? skin + 1 : 0;
				newchar.set_body(skins[female][skin]);
				bodyname.change_text(newchar.get_body()->get_name());

				return Button::State::NORMAL;
			case Buttons::BT_CHARC_WEPL:
				weapon = (weapon > 0) ? weapon - 1 : weapons[female].size() - 1;
				newchar.add_equip(weapons[female][weapon]);
				wepname.change_text(get_equipname(EquipSlot::Id::WEAPON));

				return Button::State::NORMAL;
			case Buttons::BT_CHARC_WEPR:
				weapon = (weapon < weapons[female].size() - 1) ? weapon + 1 : 0;
				newchar.add_equip(weapons[female][weapon]);
				wepname.change_text(get_equipname(EquipSlot::Id::WEAPON));

				return Button::State::NORMAL;
		}

		return Button::State::PRESSED;
	}

	void UICygnusCreation::randomize_look()
	{
		hair = 0;
		face = 0;
		skin = randomizer.next_int(skins[female].size());
		haircolor = randomizer.next_int(haircolors[female].size());
		top = 0;
		bot = 0;
		shoe = 0;
		weapon = randomizer.next_int(weapons[female].size());

		newchar.set_body(skins[female][skin]);
		newchar.set_face(faces[female][face]);
		newchar.set_hair(hairs[female][hair] + haircolors[female][haircolor]);
		newchar.add_equip(tops[female][top]);
		newchar.add_equip(bots[female][bot]);
		newchar.add_equip(shoes[female][shoe]);
		newchar.add_equip(weapons[female][weapon]);

		bodyname.change_text(newchar.get_body()->get_name());
		facename.change_text(newchar.get_face()->get_name());
		hairname.change_text(newchar.get_hair()->get_name());
		topname.change_text(get_equipname(EquipSlot::Id::TOP));
		botname.change_text(get_equipname(EquipSlot::Id::BOTTOM));
		shoename.change_text(get_equipname(EquipSlot::Id::SHOES));
		wepname.change_text(get_equipname(EquipSlot::Id::WEAPON));
	}

	const std::string& UICygnusCreation::get_equipname(EquipSlot::Id slot) const
	{
		if (int32_t item_id = newchar.get_equips().get_equip(slot))
		{
			return ItemData::get(item_id).get_name();
		}
		else
		{
			static const std::string& nullstr = "Missing name.";

			return nullstr;
		}
	}
}
