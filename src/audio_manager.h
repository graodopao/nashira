#pragma once
#include "asset_manager.h"

namespace nashira {
	class AudioManager
	{
	public:
		static void initialize();

		static void play_music(const std::string &filename, int loops = -1);

		static void pause_music();

		static void resume_music();

		static void play_sfx(const std::string &filename, int loops = false, int channel = 0);

		static void quit();
	private:
		AudioManager();
	};
}