#pragma once

#include "math_helper.h"

namespace nashira {
	class GameEntity
	{
	public:

		enum class SPACE
		{
			LOCAL = 0,
			WORLD = 1
		};

		float m_rotation;

	private:

		Vector2 m_pos;
		Vector2 m_scale;

		bool mActive;
		GameEntity* m_parent;

	public:

		GameEntity(float x = 0.0f, float y = 0.0f);

		virtual ~GameEntity();

		void set_position(Vector2 position);
		[[nodiscard]] Vector2 get_position(SPACE space = SPACE::WORLD) const;

		void rotation(float degree_angle);
		[[nodiscard]] float rotation(SPACE space = SPACE::WORLD) const;

		void scale(Vector2 scale);
		Vector2 scale(SPACE space = SPACE::WORLD);

		void active(bool active);
		bool active();

		void parent(GameEntity* parent);
		GameEntity* parent();

		void translate(Vector2 vec);
		void rotate(float amount);

		virtual void update();
		virtual void render();
	};
}