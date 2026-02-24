//////////////////////////////////////////////////////////////////////////////////
//	This file is part of the continued Journey MMORPG client					//
//	Copyright (C) 2015-2019  Daniel Allendorf, Ryan Payton, lain3d				//
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

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "Audio.h"

#include "../Configuration.h"

#include <nlnx/nx.hpp>
#include <nlnx/audio.hpp>

#include <iostream>
#include <string>

namespace ms
{
	ma_engine* Music::engine = nullptr;
	std::unordered_map<size_t, AudioData> Music::sound_cache;
	std::unordered_map<std::string, AudioData> Music::music_cache;
	bool Music::initialized = false;

	// BGM state: decoder + sound for the currently playing BGM
	static ma_decoder bgm_decoder;
	static ma_sound bgm_sound;
	static bool bgm_active = false;

	Sound::Sound(Name name)
	{
		id = soundids[name];
	}

	Sound::Sound(int32_t itemid)
	{
		auto fitemid = format_id(itemid);

		if (itemids.find(fitemid) != itemids.end())
		{
			id = itemids.at(fitemid);
		} else
		{
			auto pid = (10000 * (itemid / 10000));
			auto fpid = format_id(pid);

			if (itemids.find(fpid) != itemids.end())
				id = itemids.at(fpid);
			else
				id = itemids.at("02000000");
		}
	}

	Sound::Sound(nl::node src)
	{
		id = add_sound(src);
	}

	Sound::Sound()
	{
		id = 0;
	}

	void Sound::play()
	{
		if (!Music::initialized || !Music::engine || id == 0)
			return;

		auto it = Music::sound_cache.find(id);
		if (it == Music::sound_cache.end() || it->second.data.empty())
			return;

		// Fire-and-forget SFX: decode from memory and play inline
		// miniaudio's ma_engine handles cleanup of inline sounds automatically
		auto& audio_data = it->second;

		// Create a temporary decoder from the cached audio data
		ma_decoder* decoder = new ma_decoder;
		ma_decoder_config config = ma_decoder_config_init(ma_format_f32, 0, 0);
		ma_result result = ma_decoder_init_memory(audio_data.data.data(), audio_data.data.size(), &config, decoder);

		if (result != MA_SUCCESS)
		{
			delete decoder;
			return;
		}

		// Create a sound from the decoder
		ma_sound* sound = new ma_sound;
		result = ma_sound_init_from_data_source(Music::engine, decoder,
			MA_SOUND_FLAG_NO_SPATIALIZATION, nullptr, sound);

		if (result != MA_SUCCESS)
		{
			ma_decoder_uninit(decoder);
			delete decoder;
			delete sound;
			return;
		}

		// Set an end callback to clean up the sound and decoder when done
		ma_sound_set_end_callback(sound, [](void* pUserData, ma_sound* pSound) {
			auto* dec = static_cast<ma_decoder*>(pUserData);
			ma_sound_uninit(pSound);
			ma_decoder_uninit(dec);
			delete dec;
			delete pSound;
		}, decoder);

		ma_sound_start(sound);
	}

	Error Sound::init()
	{
		nl::node uisrc = nl::nx::sound["UI.img"];

		add_sound(Sound::Name::BUTTONCLICK, uisrc["BtMouseClick"]);
		add_sound(Sound::Name::BUTTONOVER, uisrc["BtMouseOver"]);
		add_sound(Sound::Name::CHARSELECT, uisrc["CharSelect"]);
		add_sound(Sound::Name::DLGNOTICE, uisrc["DlgNotice"]);
		add_sound(Sound::Name::MENUDOWN, uisrc["MenuDown"]);
		add_sound(Sound::Name::MENUUP, uisrc["MenuUp"]);
		add_sound(Sound::Name::RACESELECT, uisrc["RaceSelect"]);
		add_sound(Sound::Name::SCROLLUP, uisrc["ScrollUp"]);
		add_sound(Sound::Name::SELECTMAP, uisrc["SelectMap"]);
		add_sound(Sound::Name::TAB, uisrc["Tab"]);
		add_sound(Sound::Name::WORLDSELECT, uisrc["WorldSelect"]);
		add_sound(Sound::Name::DRAGSTART, uisrc["DragStart"]);
		add_sound(Sound::Name::DRAGEND, uisrc["DragEnd"]);
		add_sound(Sound::Name::WORLDMAPOPEN, uisrc["WorldmapOpen"]);
		add_sound(Sound::Name::WORLDMAPCLOSE, uisrc["WorldmapClose"]);

		nl::node gamesrc = nl::nx::sound["Game.img"];

		add_sound(Sound::Name::GAMESTART, gamesrc["GameIn"]);
		add_sound(Sound::Name::JUMP, gamesrc["Jump"]);
		add_sound(Sound::Name::DROP, gamesrc["DropItem"]);
		add_sound(Sound::Name::PICKUP, gamesrc["PickUpItem"]);
		add_sound(Sound::Name::PORTAL, gamesrc["Portal"]);
		add_sound(Sound::Name::LEVELUP, gamesrc["LevelUp"]);
		add_sound(Sound::Name::TOMBSTONE, gamesrc["Tombstone"]);

		nl::node itemsrc = nl::nx::sound["Item.img"];

		for (auto node : itemsrc)
			add_sound(node.name(), node["Use"]);

		return Error::Code::NONE;
	}

	void Sound::close()
	{
		// Stop BGM if playing
		if (bgm_active)
		{
			ma_sound_stop(&bgm_sound);
			ma_sound_uninit(&bgm_sound);
			ma_decoder_uninit(&bgm_decoder);
			bgm_active = false;
		}

		if (Music::engine)
		{
			ma_engine_uninit(Music::engine);
			delete Music::engine;
			Music::engine = nullptr;
		}

		Music::sound_cache.clear();
		Music::music_cache.clear();
		Music::initialized = false;
	}

	bool Sound::set_sfxvolume(uint8_t vol)
	{
		if (!Music::engine)
			return false;

		ma_engine_set_volume(Music::engine, static_cast<float>(vol) / 100.0f);
		return true;
	}

	size_t Sound::add_sound(nl::node src)
	{
		nl::audio ad = src;

		auto data = reinterpret_cast<const uint8_t*>(ad.data());

		if (data)
		{
			size_t id = ad.id();

			// Cache the full audio data (including the WAV header)
			AudioData audio_data;
			audio_data.data.assign(data, data + ad.length());
			Music::sound_cache[id] = std::move(audio_data);

			return id;
		} else
		{
			return 0;
		}
	}

	void Sound::add_sound(Name name, nl::node src)
	{
		size_t id = add_sound(src);

		if (id)
			soundids[name] = id;
	}

	void Sound::add_sound(std::string itemid, nl::node src)
	{
		size_t id = add_sound(src);

		if (id)
			itemids[itemid] = id;
	}

	std::string Sound::format_id(int32_t itemid)
	{
		std::string strid = std::to_string(itemid);
		strid.insert(0, 8 - strid.size(), '0');

		return strid;
	}

	EnumMap<Sound::Name, size_t> Sound::soundids;
	std::unordered_map<std::string, size_t> Sound::itemids;

	Music::Music(std::string p)
	{
		path = p;
	}

	void Music::play() const
	{
		if (!initialized || !engine)
			return;

		static std::string bgmpath = "";

		if (path == bgmpath)
			return;

		// Stop current BGM if playing
		if (bgm_active)
		{
			ma_sound_stop(&bgm_sound);
			ma_sound_uninit(&bgm_sound);
			ma_decoder_uninit(&bgm_decoder);
			bgm_active = false;
		}

		// Extract audio data from NX if not cached
		if (music_cache.find(path) == music_cache.end())
		{
			nl::audio ad = nl::nx::sound.resolve(path);
			auto data = reinterpret_cast<const uint8_t*>(ad.data());

			if (data)
			{
				AudioData audio_data;
				audio_data.data.assign(data, data + ad.length());
				music_cache[path] = std::move(audio_data);
			}
		}

		auto it = music_cache.find(path);
		if (it == music_cache.end() || it->second.data.empty())
		{
			bgmpath = path;
			return;
		}

		// Decode BGM from memory
		ma_decoder_config config = ma_decoder_config_init(ma_format_f32, 0, 0);
		ma_result result = ma_decoder_init_memory(
			it->second.data.data(), it->second.data.size(), &config, &bgm_decoder);

		if (result != MA_SUCCESS)
		{
			bgmpath = path;
			return;
		}

		// Create a looping sound from the decoder
		result = ma_sound_init_from_data_source(engine, &bgm_decoder,
			MA_SOUND_FLAG_NO_SPATIALIZATION, nullptr, &bgm_sound);

		if (result != MA_SUCCESS)
		{
			ma_decoder_uninit(&bgm_decoder);
			bgmpath = path;
			return;
		}

		ma_sound_set_looping(&bgm_sound, MA_TRUE);
		ma_sound_start(&bgm_sound);
		bgm_active = true;
		bgmpath = path;
	}

	void Music::play_once() const
	{
		if (!initialized || !engine)
			return;

		static std::string bgmpath = "";

		if (path == bgmpath)
			return;

		// Stop current BGM if playing
		if (bgm_active)
		{
			ma_sound_stop(&bgm_sound);
			ma_sound_uninit(&bgm_sound);
			ma_decoder_uninit(&bgm_decoder);
			bgm_active = false;
		}

		// Extract audio data from NX if not cached
		if (music_cache.find(path) == music_cache.end())
		{
			nl::audio ad = nl::nx::sound.resolve(path);
			auto data = reinterpret_cast<const uint8_t*>(ad.data());

			if (data)
			{
				AudioData audio_data;
				audio_data.data.assign(data, data + ad.length());
				music_cache[path] = std::move(audio_data);
			}
		}

		auto it = music_cache.find(path);
		if (it == music_cache.end() || it->second.data.empty())
		{
			bgmpath = path;
			return;
		}

		// Decode BGM from memory (no loop)
		ma_decoder_config config = ma_decoder_config_init(ma_format_f32, 0, 0);
		ma_result result = ma_decoder_init_memory(
			it->second.data.data(), it->second.data.size(), &config, &bgm_decoder);

		if (result != MA_SUCCESS)
		{
			bgmpath = path;
			return;
		}

		result = ma_sound_init_from_data_source(engine, &bgm_decoder,
			MA_SOUND_FLAG_NO_SPATIALIZATION, nullptr, &bgm_sound);

		if (result != MA_SUCCESS)
		{
			ma_decoder_uninit(&bgm_decoder);
			bgmpath = path;
			return;
		}

		ma_sound_set_looping(&bgm_sound, MA_FALSE);
		ma_sound_start(&bgm_sound);
		bgm_active = true;
		bgmpath = path;
	}

	Error Music::init()
	{
		// Initialize the miniaudio engine for audio playback
		engine = new ma_engine;
		ma_engine_config engineConfig = ma_engine_config_init();

		ma_result result = ma_engine_init(&engineConfig, engine);

		if (result != MA_SUCCESS)
		{
			std::cout << "Audio: failed to initialize engine (error " << result << ")" << std::endl;
			delete engine;
			engine = nullptr;
			initialized = false;
			return Error::Code::NONE; // Non-fatal: game works without audio
		}

		initialized = true;
		std::cout << "Audio: engine initialized successfully" << std::endl;

		return Error::Code::NONE;
	}

	bool Music::set_bgmvolume(uint8_t vol)
	{
		if (!engine)
			return false;

		// Set volume on BGM sound if active
		if (bgm_active)
			ma_sound_set_volume(&bgm_sound, static_cast<float>(vol) / 100.0f);

		return true;
	}

	void Music::update_context()
	{
		// miniaudio handles its own threading, no manual pumping needed
	}
}
