#include "texture.h"
using namespace nashira;



Texture::Texture(const std::string& filename)
{
	m_tex = AssetManager::get_texture(filename);

	SDL_QueryTexture(m_tex, nullptr, nullptr, &m_width, &m_height);

	m_clipped = false;

	m_render_rect.w = m_width;
	m_render_rect.h = m_height;
}

Texture::Texture(const std::string& filename, const int x, const int y, const int w, const int h)
{
	m_tex = AssetManager::get_texture(filename);

	m_clipped = true;

	m_width = w;
	m_height = h;

	m_render_rect.w = m_width;
	m_render_rect.h = m_height;

	m_clip_rect.x = x;
	m_clip_rect.y = y;
	m_clip_rect.w = m_width;
	m_clip_rect.h = m_height;
}

int Texture::get_width() const {
	return m_width;
}

int Texture::get_height() const {
	return m_height;
}

void Texture::set_alpha(Uint8 alpha) const {
	SDL_SetTextureAlphaMod(m_tex, alpha);
}

float Texture::rotate_point(Vector2 pos, float dist, float dir)
{
	auto* temp = new GameEntity(pos.x, pos.y);
	temp->rotate(dir);
	temp->translate(Vector2(dist, 0.0f));

	const float result = temp->get_position().x;

	delete temp;
	temp = nullptr;

	return result;
}

/// TODO: Move to Equilibrium (future integrated feature?)
void Texture::particle_update(float deltaTime)
{
	particle_tick += 1000 * deltaTime;
	horizontal_particle_tick += 750 * deltaTime;

	if (particle_tick >= particle_move_update)
	{
		particle_tick = 0;

		translate(Vector2(0, 2.5));

		if (get_position().y > 720)
		{
			set_position(Vector2(get_position().x, 0));
		}
	}

	if (horizontal_particle_tick >= horizontal_particle_move_update)
	{
		horizontal_particle_tick = 0;

		const int _x = rand() % 5 + 0;
		translate(Vector2(_x - 2.5, 0));

		if (get_position().x > 1280)
		{
			set_position(Vector2(0, get_position().y));
		}
		else if (get_position().x < 0)
		{
			set_position(Vector2(1280, get_position().y));
		}
	}
}

/// TODO: Move to Equilibrium
float Texture::building_update(float delta_time, float angle, float leftPoint, float rightPoint, int& objective, int& objective_term)
{
	building_idle_tick += 20 * delta_time;

	if (second_texture != nullptr)
	{
		second_texture->building_update(delta_time, angle, leftPoint, rightPoint, objective, objective_term);
	}

	if (abs(rotation()) > 10 && current_building_state != falling && building_idle_tick > building_idle_cooldown)
	{
		float direction = angle > 0 ? 130 : -130;

		translate((RIGHT * (direction * (abs(angle - 10) / 50))) * delta_time);

		if (get_position().x > rightPoint || get_position().x < leftPoint)
		{

			if (current_building_state != falling)
			{
				if (second_texture != nullptr)
				{
					objective -= current_building_state == built ? 2 : 1;
					objective_term++;
				}
				current_building_state = falling;

				Vector2 last_pos = get_position(SPACE::WORLD);

				parent(nullptr);
				set_position(last_pos);
			}
		}
	}

	rise_tick += 120.0f * delta_time;

	if (rise_tick >= rise_cooldown)
	{
		rise_tick = 0.0f;

		switch (current_building_state)
		{

			case (building):

				if (building_idle_tick > building_idle_cooldown)
				{
					rise(5.0f, static_cast<float>(max_height));

					if (m_height < max_height)
					{
						translate(UP * -2.5f);
					}
					else
					{
						if (second_texture != nullptr)
						{
							objective++;
						}

						current_building_state = built;
					}
				}

			break;

			case(built):

				if (second_texture != nullptr)
				{

					if (second_texture->is_demolished())
					{
						objective_term++;
						second_texture = nullptr;
					}
					else
					{
						second_texture->building_demolish();
					}
				}

			break;

			case (deconstruct):

				if (m_height > 0)
				{
					translate(UP * 5.0f);
				}
				else
				{
					current_building_state = built;
				}

			decrease(10.0f);

			break;
			default: ;
		}
	}

	if (current_building_state != falling)
	{
		return m_width * m_height / 50;
	}
	else
	{
		rotate(((get_position().x > Graphics::SCREEN_WIDTH / 2.0f) ? (90.0f * delta_time) : (-90.0f * delta_time)));
		translate(Vector2(get_position().x > Graphics::SCREEN_WIDTH / 2.0f ? 30.0f * delta_time : -30.0f * delta_time, vertical_speed * delta_time));

		vertical_speed += gravity;

		return 0;
	}
}

/// TODO: Move to Equilibrium
bool Texture::is_demolished() const {
	return (current_building_state == demolished);
}

/// TODO: Move to Equilibrium
void Texture::set_building(Texture* frameTexture, int maximumHeight, bool isFrame, float constructionCooldown)
{
	max_height = maximumHeight;

	if (!isFrame)
	{
		second_texture = frameTexture;
		second_texture->set_building(nullptr, maximumHeight, true, constructionCooldown);
	}

	building_idle_cooldown = constructionCooldown;
}

/// TODO: Move to Equilibrium
void Texture::building_demolish()
{
	current_building_state = deconstruct;
}

/// TODO: Move to Equilibrium
void Texture::rise(const int amount, const float cap)
{
	m_clip_rect.h += amount;
	m_height += amount;

	m_clip_rect.h = SDL_clamp(m_clip_rect.h, 0, cap);
	m_height = SDL_clamp(m_height, 0, cap);
}

/// TODO: Move to Equilibrium
void Texture::decrease(const int amount)
{
	m_clip_rect.h -= amount;
	m_height -= amount;

	m_clip_rect.h = SDL_clamp(m_clip_rect.h, 0, 1000);
	m_height = SDL_clamp(m_height, 0, 1000);

	if (m_height <= 0)
	{
		current_building_state = demolished;
	}
}

Texture::Texture(const std::string &text, const std::string &font_path, int size, SDL_Color color)
{
	m_tex = AssetManager::get_text(text, font_path, size, color);

	m_clipped = false;

	SDL_QueryTexture(m_tex, nullptr, nullptr, &m_width, &m_height);

	m_render_rect.w = m_width;
	m_render_rect.h = m_height;
}

Texture::~Texture()
{
	m_tex = nullptr;
}

void Texture::render()
{
	const Vector2 pos = get_position(SPACE::WORLD);
	const Vector2 world_scale = scale(SPACE::WORLD);
	m_render_rect.x = static_cast<int>(pos.x - m_width * world_scale.x * 0.5f);
	m_render_rect.y = static_cast<int>(pos.y - m_height * world_scale.y * 0.5f);
	m_render_rect.w = static_cast<int>(m_width * world_scale.x);
	m_render_rect.h = static_cast<int>(m_height * world_scale.y);

	Graphics::draw_texture(m_tex, m_clipped ? &m_clip_rect : nullptr, &m_render_rect, rotation(SPACE::WORLD));

	if (second_texture != nullptr)
	{
		second_texture->render();
	}
}
