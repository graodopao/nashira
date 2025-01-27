#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace nashira {
	class Graphics
	{
	public:
		static constexpr int SCREEN_WIDTH{1280};
		static constexpr int SCREEN_HEIGHT{720};

	private:
		static SDL_Window* m_window;
		static SDL_Surface* m_back_buffer;
		static SDL_Renderer* mRenderer;
	public:
		static bool initialize();

		static SDL_Texture* load_texture(const std::string &path);
		static SDL_Texture* create_text_texture(TTF_Font* font, const std::string &text, SDL_Color color);

		static void clear_back_buffer();

		static void draw_texture(SDL_Texture* tex, const SDL_Rect* clip = nullptr, const SDL_Rect* rend = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

		static void render();

		static void quit();
	private:
		Graphics(); // You're not meant to instantiate this
	};
}
