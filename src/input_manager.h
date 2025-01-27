#pragma once
#include <SDL.h>
#include <string.h>
#include "math_helper.h"

namespace nashira {
	class Input
	{

	public:

		enum MOUSE_BUTTONS
		{
			LEFT = SDL_BUTTON_LEFT,
			MIDDLE = SDL_BUTTON_MMASK,
			RIGHT = SDL_BUTTON_RIGHT,
			BACK = SDL_BUTTON_X1MASK,
			FORWARD = SDL_BUTTON_X2MASK,
		};

	private:
		static Uint8* m_prev_keyboard_state;
		static const Uint8* m_keyboard_state;
		static int m_key_length;

		static Uint32 m_prev_mouse_state;
		static Uint32 m_mouse_state;

		static int m_mouse_x;
		static int m_mouse_y;
	public:
		static void initialize();

		[[nodiscard]] static bool key_down(SDL_Scancode scan_code);
		[[nodiscard]] static bool key_pressed(SDL_Scancode scan_code);
		[[nodiscard]] static bool key_released(SDL_Scancode scan_code);

		[[nodiscard]] static bool mouse_button_down(MOUSE_BUTTONS button);
		[[nodiscard]] static bool mouse_button_pressed(MOUSE_BUTTONS button);
		[[nodiscard]] static bool mouse_button_released(MOUSE_BUTTONS button);

		[[nodiscard]] static bool mouse_is_in_area(const Vector2 &rect_start, const Vector2 &rect_end);

		[[nodiscard]] static Vector2 mouse_get_pos();

		static void update_previous_input();

		static void update();

	private:
		Input() {}; // You're not meant to instantiate this
	};
}

