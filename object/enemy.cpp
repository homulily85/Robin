#include "enemy.h"
#include "texture_manager.h"
#include "game.h"
#include <string>

using namespace std::string_literals;

int Enemy::enemy_id{ 0 };

void Enemy::update()
{
	/*_current_frame = (SDL_GetTicks() / 100) % 6;
	m_velocity.set_x(1);
	m_position -= m_velocity;*/
}

void Enemy::strength_to_text(int x, int y)
{
	std::string temp = std::to_string(m_strength);
	if (Texture_manager::instance()->is_texture_in_map("enemy"s+std::to_string(m_enemy_id)))
	{
		Texture_manager::instance()->remove_from_texture_map("enemy"s + std::to_string(m_enemy_id));
	}
	if (m_strength == 0) {
		Texture_manager::instance()->remove_from_texture_map("enemy"s + std::to_string(m_enemy_id));
		return;
	}
	else if (m_strength == 1) {
		Texture_manager::instance()->remove_from_texture_map("enemy"s + std::to_string(m_enemy_id));
		/*Texture_manager::instance()->remove_from_texture_map("mul"s);
		Texture_manager::instance()->remove_from_texture_map("sub"s);
		Texture_manager::instance()->remove_from_texture_map("plus"s);
		Texture_manager::instance()->remove_from_texture_map("div"s);*/
	}
	else Texture_manager::instance()->create_texture_from_string(temp, "enemy"s + std::to_string(m_enemy_id), 255, 248, 165, 255, 1, game::instance()->get_renderer());
	Texture_manager::instance()->draw("enemy"s + std::to_string(m_enemy_id), x, y, Texture_manager::instance()->get_text_width("enemy"s + std::to_string(m_enemy_id)), Texture_manager::instance()->get_text_height("enemy"s + std::to_string(m_enemy_id)), game::instance()->get_renderer());
}

