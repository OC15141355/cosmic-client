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
#include "UIQuit.h"

#include "Timer.h"
#include "../UI.h"
#include "../Window.h"

#include "../Components/MapleButton.h"

#include "../../Character/ExpTable.h"
#include "../../Gameplay/Stage.h"
#include "../../Net/Session.h"

#include <nlnx/nx.hpp>
#include <string>

namespace ms
{
	// v83: Rewritten to use UIWindow.img/GameMenu instead of UIWindow6.img/askReward
	// v83 GameMenu has: BtQuit, BtChannel, BtGameOpt, BtSysOpt, BtSkin, backgrnd
	UIQuit::UIQuit(const CharStats &st) : stats(st)
	{
		nl::node GameMenu = nl::nx::ui["UIWindow.img"]["GameMenu"];
		nl::node backgrnd = GameMenu["backgrnd"];

		sprites.emplace_back(backgrnd);

		buttons[Buttons::BT_QUIT] = std::make_unique<MapleButton>(GameMenu["BtQuit"]);
		buttons[Buttons::BT_CHANNEL] = std::make_unique<MapleButton>(GameMenu["BtChannel"]);
		buttons[Buttons::BT_GAMEOPT] = std::make_unique<MapleButton>(GameMenu["BtGameOpt"]);
		buttons[Buttons::BT_SYSOPT] = std::make_unique<MapleButton>(GameMenu["BtSysOpt"]);
		buttons[Buttons::BT_SKIN] = std::make_unique<MapleButton>(GameMenu["BtSkin"]);

		int16_t width = Constants::Constants::get().get_viewwidth();
		int16_t height = Constants::Constants::get().get_viewheight();

		background = ColorBox(width, height, Color::Name::BLACK, 0.5f);

		Point<int16_t> bg_dimensions = Texture(backgrnd).get_dimensions();
		position = Point<int16_t>((width - bg_dimensions.x()) / 2, (height - bg_dimensions.y()) / 2);
		dimension = bg_dimensions;
	}

	void UIQuit::draw(float inter) const
	{
		background.draw(Point<int16_t>(0, 0));

		UIElement::draw(inter);
	}

	void UIQuit::update()
	{
		UIElement::update();
	}

	Cursor::State UIQuit::send_cursor(bool clicked, Point<int16_t> cursorpos)
	{
		return UIElement::send_cursor(clicked, cursorpos);
	}

	void UIQuit::send_key(int32_t keycode, bool pressed, bool escape)
	{
		if (pressed)
		{
			if (escape)
				close();
			else if (keycode == KeyAction::Id::RETURN)
				button_pressed(Buttons::BT_QUIT);
		}
	}

	UIElement::Type UIQuit::get_type() const
	{
		return TYPE;
	}

	Button::State UIQuit::button_pressed(uint16_t buttonid)
	{
		switch (buttonid)
		{
			case Buttons::BT_QUIT:
			{
				Constants::Constants::get().set_viewwidth(800);
				Constants::Constants::get().set_viewheight(600);

				float fadestep = 0.025f;

				Window::get().fadeout(
						fadestep,
						[]()
						{
							GraphicsGL::get().clear();

							UI::get().change_state(UI::State::LOGIN);
							UI::get().set_scrollnotice("");
							Session::get().reconnect();

							UI::get().enable();
							Timer::get().start();
							GraphicsGL::get().unlock();
						}
				);

				GraphicsGL::get().lock();
				Stage::get().clear();
				Timer::get().start();
			}
				break;
			case Buttons::BT_CHANNEL:
			case Buttons::BT_GAMEOPT:
			case Buttons::BT_SYSOPT:
			case Buttons::BT_SKIN:
				// v83: stub — these buttons are not yet implemented
				close();
				break;
			default:
				break;
		}

		return Button::State::NORMAL;
	}

	void UIQuit::close()
	{
		deactivate();

		UI::get().clear_tooltip(Tooltip::Parent::TEXT);
	}
}
