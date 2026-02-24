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
#include "UIEvent.h"

#include "../UI.h"

#include "../Components/MapleButton.h"
#include "../Data/ItemData.h"

#include <nlnx/nx.hpp>
#include <string>

namespace ms
{
	UIEvent::UIEvent() : UIDragElement<PosEVENT>()
	{
		offset = 0;
		event_count = 0; // v83: no active events to display

		// v83: EventList doesn't exist, use MapleEvent instead (simple: BtClose, Loading, backgrnd)
		nl::node MapleEvent = nl::nx::ui["UIWindow.img"]["MapleEvent"];
		nl::node close = nl::nx::ui["Basic.img"]["BtClose3"];

		nl::node backgrnd = MapleEvent["backgrnd"];
		Point<int16_t> bg_dimensions = Texture(backgrnd).get_dimensions();

		sprites.emplace_back(backgrnd);

		buttons[Buttons::CLOSE] = std::make_unique<MapleButton>(close, Point<int16_t>(bg_dimensions.x() - 19, 6));

		// v83: MapleEvent is minimal — no event list, no item_reward, no label_on/label_next
		// event_title, event_date, item_reward, text_reward, next, label_on, label_next left as default (empty)
		for (size_t i = 0; i < 3; i++)
			event_title[i] = ShadowText(Text::Font::A18M, Text::Alignment::LEFT, Color::Name::HALFANDHALF, Color::Name::ENDEAVOUR);

		for (size_t i = 0; i < 3; i++)
			event_date[i] = Text(Text::Font::A12B, Text::Alignment::LEFT, Color::Name::WHITE);

		dimension = bg_dimensions;
		dragarea = Point<int16_t>(dimension.x(), 20);
	}

	void UIEvent::draw(float inter) const
	{
		// v83: simple MapleEvent window — just background + close button
		UIElement::draw(inter);
	}

	void UIEvent::update()
	{
		UIElement::update();

		for (size_t i = 0; i < 3; i++)
		{
			int16_t slot = i + offset;

			if (slot >= event_count)
				break;

			std::string title = get_event_title(slot);

			if (title.length() > 35)
				title = title.substr(0, 35) + "..";

			event_title[i].change_text(title);
			event_date[i].change_text(get_event_date(slot));
		}
	}

	void UIEvent::remove_cursor()
	{
		UIDragElement::remove_cursor();

		UI::get().clear_tooltip(Tooltip::Parent::EVENT);

		slider.remove_cursor();
	}

	Cursor::State UIEvent::send_cursor(bool clicked, Point<int16_t> cursorpos)
	{
		Point<int16_t> cursoroffset = cursorpos - position;

		if (slider.isenabled())
			if (Cursor::State new_state = slider.send_cursor(cursoroffset, clicked))
				return new_state;

		int16_t yoff = cursoroffset.y();
		int16_t xoff = cursoroffset.x();
		int16_t row = row_by_position(yoff);
		int16_t col = col_by_position(xoff);

		if (row > 0 && row < 4 && col > 0 && col < 6)
			show_item(row, col);

		return UIDragElement::send_cursor(clicked, cursorpos);
	}

	void UIEvent::send_key(int32_t keycode, bool pressed, bool escape)
	{
		if (pressed && escape)
			close();
	}

	UIElement::Type UIEvent::get_type() const
	{
		return TYPE;
	}

	Button::State UIEvent::button_pressed(uint16_t buttonid)
	{
		switch (buttonid)
		{
			case Buttons::CLOSE:
				close();
			default:
				break;
		}

		return Button::State::NORMAL;
	}

	void UIEvent::close()
	{
		deactivate();
	}

	std::string UIEvent::get_event_title(uint8_t id)
	{
		switch (id)
		{
			case 0:
				return "LINE FRIENDS";
			case 1:
				return "LINE FRIENDS Coin Shop";
			case 2:
				return "[14th Street] Big Bang Store";
			case 3:
				return "[14th Street] Override Fashion Marketing";
			case 4:
				return "[14th Street] Dance Battle V";
			case 5:
				return "MapleStory 14th Anniversary Appre..";
			case 6:
				return "[14th Street] Big Bang Store Season..";
			case 7:
				return "[14th Street] Maplelin Star Grub!";
			case 8:
				return "[14th Street] Sub-Zero Hunt";
			case 9:
				return "[14th Street] The Legends Return!";
			case 10:
				return "[14th Street] Renegade Personal Training";
			case 11:
				return "[14th Street] Round-We-Go Cafe Rising Heroes!";
			case 12:
				return "[14th Street] Big Bang Attack!";
			case 13:
				return "[14th Street] Spiegelmann's Art Retrieval";
			case 14:
				return "[14th Street] 14th Street Sky";
			case 15:
				return "[Sunny Sunday] Perks Abound!";
			default:
				return "";
		}
	}

	std::string UIEvent::get_event_date(uint8_t id)
	{
		switch (id)
		{
			case 0:
			case 1:
			case 2:
				return "04/24/2019 - 05/21/2019, 23:59";
			case 3:
				return "04/24/2019 - 05/07/2019, 23:59";
			case 4:
				return "04/24/2019 - 06/11/2019, 23:59";
			case 5:
				return "05/11/2019 - 05/11/2019, 23:59";
			case 6:
			case 10:
			case 11:
			case 12:
				return "05/22/2019 - 06/11/2019, 23:59";
			case 7:
			case 8:
				return "05/08/2019 - 05/21/2019, 23:59";
			case 9:
				return "05/08/2019 - 06/11/2019, 23:59";
			case 13:
			case 14:
				return "05/29/2019 - 06/11/2019, 23:59";
			case 15:
				return "05/05/2019 - 05/05/2019, 23:59";
			default:
				return "";
		}
	}

	int16_t UIEvent::row_by_position(int16_t y)
	{
		int16_t item_height = 43;

		if (y >= 148 && y <= 148 + item_height)
			return 1;
		else if (y >= 273 && y <= 273 + item_height)
			return 2;
		else if (y >= 398 && y <= 398 + item_height)
			return 3;
		else
			return -1;
	}

	int16_t UIEvent::col_by_position(int16_t x)
	{
		int16_t item_width = 43;

		if (x >= 25 && x <= 25 + item_width)
			return 1;
		else if (x >= 71 && x <= 71 + item_width)
			return 2;
		else if (x >= 117 && x <= 117 + item_width)
			return 3;
		else if (x >= 163 && x <= 163 + item_width)
			return 4;
		else if (x >= 209 && x <= 209 + item_width)
			return 5;
		else
			return -1;
	}

	void UIEvent::show_item(int16_t row, int16_t col)
	{
		UI::get().show_item(Tooltip::Parent::EVENT, 2000000 + col - 1);
	}
}