#include "enemy.h"
#include "texture_manager.h"
#include "game.h"
#include <string>

using namespace std::string_literals;

int Enemy::enemy_id{ 0 };

void Enemy::update()
{

}

void Enemy::strength_to_text(int x, int y,std::string ope,bool is_buff)
{
	std::string temp{};
	if (ope == "+"s&&!is_buff) {
		temp = std::to_string(m_strength);
	}
	else temp = ope + std::to_string(m_strength);
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
		return;
	}
	else Texture_manager::instance()->create_texture_from_string(temp, "enemy"s + std::to_string(m_enemy_id), 255, 248, 165, 255, 1, game::instance()->get_renderer());
	Texture_manager::instance()->draw("enemy"s + std::to_string(m_enemy_id), x, y, Texture_manager::instance()->get_text_width("enemy"s + std::to_string(m_enemy_id)), Texture_manager::instance()->get_text_height("enemy"s + std::to_string(m_enemy_id)), game::instance()->get_renderer());
}

