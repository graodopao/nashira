#pragma once
#include <SDL.h>

namespace nashira {
	class Time
	{
	private:
		static Uint64 m_start_ticks;
		static Uint64 m_elapsed_ticks;

		static float m_delta_time;
		static float m_time_scale;

	public:
		static void reset();
		[[nodiscard]] static float delta_time();

		static void time_scale(float scale);
		[[nodiscard]] static float time_scale();

		static void update();
	private:
		Time();
	};
}