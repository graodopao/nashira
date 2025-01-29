#include "input_manager.h"
using namespace nashira;

int Input::m_key_length{0};
const Uint8* Input::m_keyboard_state{SDL_GetKeyboardState(&Input::m_key_length)};
Uint8* Input::m_prev_keyboard_state{};

int Input::m_mouse_x{0};
int Input::m_mouse_y{0};

Uint32 Input::m_prev_mouse_state{0};
Uint32 Input::m_mouse_state{0};

void Input::initialize()
{
	m_keyboard_state = SDL_GetKeyboardState(&m_key_length);
	m_prev_keyboard_state = new Uint8[m_key_length];
	memcpy(m_prev_keyboard_state, m_keyboard_state, m_key_length);
}

bool Input::key_down(const SDL_Scancode scan_code) {
	return m_keyboard_state[scan_code];
}

bool Input::key_pressed(const SDL_Scancode scan_code) {
	return !m_prev_keyboard_state[scan_code] && m_keyboard_state[scan_code];
}

bool Input::key_released(const SDL_Scancode scan_code) {
	return m_prev_keyboard_state[scan_code] && !m_keyboard_state[scan_code];
}

Vector2 Input::mouse_get_pos() {
	return {static_cast<float>(m_mouse_x), static_cast<float>(m_mouse_y)};
}

bool Input::mouse_button_down(const MOUSE_BUTTONS button) {
	return (m_mouse_state & button);
}

bool Input::mouse_button_pressed(const MOUSE_BUTTONS button) {
	return !(m_prev_mouse_state & button) && (m_mouse_state & button);
}

bool Input::mouse_button_released(const MOUSE_BUTTONS button) {
	return (m_prev_mouse_state & button) && !(m_mouse_state & button);
}

bool Input::mouse_is_in_area(const Vector2 &rect_start, const Vector2 &rect_end) {
	const Vector2 pos = mouse_get_pos();
	return (pos.x >= rect_start.x && pos.y >= rect_start.y && pos.x <= rect_end.x && pos.y <= rect_end.y);
}

void Input::update()
{
	m_mouse_state = SDL_GetMouseState(&m_mouse_x, &m_mouse_y);
}

void Input::update_previous_input()
{
	memcpy(m_prev_keyboard_state, m_keyboard_state, m_key_length);
	m_prev_mouse_state = m_mouse_state;
}
