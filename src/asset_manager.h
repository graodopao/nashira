#pragma once
#include "graphics.h"
#include <SDL_mixer.h>
#include "map"

namespace nashira {
	class AssetManager
	{
	private:
		static std::map<std::string, SDL_Texture*> m_textures;
		static std::map<std::string, SDL_Texture*> m_text;
		static std::map<std::string, TTF_Font*> m_fonts;
		static std::map<std::string, Mix_Music*> m_music;
		static std::map<std::string, Mix_Chunk*> m_sfx;

	public:
		static SDL_Texture* get_texture(const std::string &filename);
		static SDL_Texture* get_text(const std::string &text, const std::string &filename, int size, SDL_Color color);

		static Mix_Music* get_music(const std::string &filename);
		static Mix_Chunk* get_sfx(const std::string &filename);

		static void quit();

	private:
		AssetManager();

		static TTF_Font* get_font(const std::string &filename, int size);
	};
}