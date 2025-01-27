#include "time_server.h"
using namespace nashira;

Uint64 Time::m_start_ticks{SDL_GetTicks()};
Uint64 Time::m_elapsed_ticks{0};
float Time::m_delta_time{0.0f};
float Time::m_time_scale{0.0f};

Time::Time() = default;

void Time::reset()
{
	m_start_ticks = SDL_GetTicks();
}

float Time::delta_time() {
	return m_delta_time;
}

void Time::time_scale(const float scale)
{
	m_time_scale = scale;
}

float Time::time_scale() {
	return m_time_scale;
}

void Time::update()
{
	m_elapsed_ticks = SDL_GetTicks() - m_start_ticks;
	m_delta_time = static_cast<float>(m_elapsed_ticks) * 0.001f;
}