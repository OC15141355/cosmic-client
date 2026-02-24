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

#include "../Components/Slider.h"

#include "../../Data/ItemData.h"
#include "../../Graphics/Text.h"

namespace ms
{
	class UICashShop : public UIElement
	{
	public:
		static constexpr Type TYPE = UIElement::Type::CASHSHOP;
		static constexpr bool FOCUSED = true;
		static constexpr bool TOGGLED = false;

		UICashShop();

		void draw(float inter) const;
		void update() override;

		Button::State button_pressed(uint16_t buttonid);

		Cursor::State send_cursor(bool clicked, Point<int16_t> cursorpos) override;

		UIElement::Type get_type() const override;

		void exit_cashshop();

	private:
		void update_items();

		static constexpr uint8_t MAX_ITEMS = 7u * 2u + 1u;

		class Item
		{
		public:
			enum Label : uint8_t
			{
				ACTION,
				BOMB_SALE,
				BONUS,
				EVENT = 4,
				HOT,
				LIMITED,
				LIMITED_BRONZE,
				LIMITED_GOLD,
				LIMITED_SILVER,
				LUNA_CRYSTAL,
				MASTER = 12,
				MUST,
				NEW,
				SALE = 17,
				SPEICAL,
				SPECIAL_PRICE,
				TIME,
				TODAY,
				WEEKLY,
				WONDER_BERRY,
				WORLD_SALE,
				NONE
			};

			Item(int32_t itemid, Label label, int32_t discount, uint16_t count) : label(label), discount_price(discount), count(count), data(ItemData::get(itemid)) {}

			Label label;
			int32_t discount_price;
			uint16_t count;

			void draw(const DrawArgument& args) const
			{
				data.get_icon(false).draw(args);
			}

			const std::string get_name() const
			{
				return data.get_name();
			}

			const int32_t get_price() const
			{
				return data.get_price();
			}

		private:
			const ItemData& data;
		};

		// v83: Removed buttons that don't exist in v83 CashShop.img:
		// BtChargeNX, BtChargeRefresh (CSGLChargeNX doesn't exist)
		// BtWish, BtMileage, BtHelp (CSStatus only has BtCharge/BtCheck/BtCoupon/BtExit)
		// BtNext, BtPrev (CSPromotionBanner doesn't exist)
		// BtDetailPackage, BtNonGrade (CSMVPBanner doesn't exist)
		// BtInventory, BtSaveAvatar (CSChar only has BtBuyAvatar/BtDefaultAvatar/BtTakeoffAvatar)
		enum Buttons : uint16_t
		{
			BtPreview1,
			BtPreview2,
			BtPreview3,
			BtExit,
			BtCharge,
			BtCheck,
			BtCoupon,
			BtBuyAvatar,
			BtDefaultAvatar,
			BtTakeoffAvatar,
			BtBuy
		};

		Sprite preview_sprites[3];
		uint8_t preview_index;

		Sprite menu_tabs[9];
		uint8_t menu_index;

		Text job_label;
		Text name_label;

		// v83: Removed promotion_sprites/pos/index (CSPromotionBanner doesn't exist)
		// v83: Removed mvp_sprites/pos/grade/gauge/exp (CSMVPBanner doesn't exist)
		// v83: Removed charge_charset (CSGLChargeNX doesn't exist)
		// v83: Removed BestNew_dim (Base/BestNew doesn't exist)
		// v83: Removed item_line, item_none (Base/line, Base/noItem don't exist)

		Sprite item_base;
		std::vector<Sprite> item_labels;
		std::vector<Item> items;
		Text item_name[MAX_ITEMS];
		Text item_price[MAX_ITEMS];
		Text item_discount[MAX_ITEMS];
		Text item_percent[MAX_ITEMS];

		Slider list_slider;
		int16_t list_offset;
	};
}
