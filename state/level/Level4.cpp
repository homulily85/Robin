#include "Level4.h"
#include <iostream>
#include "game.h"
#include "menu_button.h"
#include "const.h"
#include "player.h"
#include "enemy.h"
#include "Vector2D.h"
#include "input_handle.h"
#include "game_over.h"
#include "victory.h"

constexpr int PLAYER_STRENGTH{ 38 };
constexpr int ENEMY0_STRENGTH{ 32 };
constexpr int ENEMY1_STRENGTH{ 3 };
constexpr int ENEMY2_STRENGTH{ 320 };
constexpr int ENEMY3_STRENGTH{ 5 };
constexpr int ENEMY4_STRENGTH{ 400 };
constexpr int ENEMY5_STRENGTH{ 217 };

constexpr int PLAYER_BASE_X{ 296 };
constexpr int PLAYER_BASE_Y{ 460 };
constexpr int ENEMY0_BASE_X{ 700 };
constexpr int ENEMY0_BASE_Y{ 460 };
constexpr int ENEMY1_BASE_X{ 900 };
constexpr int ENEMY1_BASE_Y{ 460 };
constexpr int ENEMY2_BASE_X{ 900 };
constexpr int ENEMY2_BASE_Y{ 332 };
constexpr int ENEMY3_BASE_X{ 900 };
constexpr int ENEMY3_BASE_Y{ 212 };
constexpr int ENEMY4_BASE_X{ 1100 };
constexpr int ENEMY4_BASE_Y{ 460 };
constexpr int ENEMY5_BASE_X{ 1100 };
constexpr int ENEMY5_BASE_Y{ 332 };

using namespace std::string_literals;

const std::string Level4::m_state_ID{ "LEVEL4"s };

void Level4::clean()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (m_object[i] != nullptr)
		{
			delete m_object[i];
			m_object[i] = nullptr;
		}
	}
	if (m_player != nullptr) delete m_player;
	m_player = nullptr;
	for (int i = 0; i < m_enemy.size(); i++) {
		if (m_enemy[i] != nullptr) {
			delete m_enemy[i];
			m_enemy[i] = nullptr;
		}
	}
}

void Level4::update()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (!m_exit && m_object[i] != nullptr)  m_object[i]->update();
		else return;
	}
	if (!m_exit && m_player != nullptr) m_player->update();
	else return;
	for (int i = 0; i < m_enemy.size(); i++) {
		if (!m_exit && m_enemy[i] != nullptr) m_enemy[i]->update();
		else return;
	}
	Vector2D* mouse_pos = Input_handle::instance()->get_mouse_position();
	if (mouse_pos->get_x() > ENEMY0_BASE_X && mouse_pos->get_x() < ENEMY0_BASE_X + 130 && mouse_pos->get_y() > ENEMY0_BASE_Y && mouse_pos->get_y() < ENEMY0_BASE_Y + 130 && Input_handle::instance()->get_mouse_state(LEFT) == true) {
		if (m_enemy[0] != nullptr) {
			m_player->set_position(ENEMY0_BASE_X + 31, ENEMY0_BASE_Y + 62);
			if (m_player->get_strength() > m_enemy[0]->get_strength()) {
				m_player->change_strength(m_enemy[0]->get_strength(), '+');
				m_enemy[0]->set_strength_to_zero();
				m_enemy[0]->set_current_frame(100);
			}
			else m_player->set_strength_to_zero();
		}
	}
	else if (is_tower_destroyed(0,0) && mouse_pos->get_x() > ENEMY1_BASE_X && mouse_pos->get_x() < ENEMY1_BASE_X + 130 && mouse_pos->get_y() > ENEMY1_BASE_Y && mouse_pos->get_y() < ENEMY1_BASE_Y + 130 && Input_handle::instance()->get_mouse_state(LEFT) == true) {
		if (m_enemy[1] != nullptr) {
			m_player->set_position(ENEMY1_BASE_X + 31, ENEMY1_BASE_Y + 62);
			//if (m_player->get_strength() > m_enemy[1]->get_strength()) {
			m_player->change_strength(m_enemy[1]->get_strength(), '/');
			m_enemy[1]->set_strength_to_one();
			m_enemy[1]->set_current_frame(100);
			//}
			//else m_player->set_strength_to_zero();
		}
	}
	else if (is_tower_destroyed(0, 0) && mouse_pos->get_x() > ENEMY2_BASE_X && mouse_pos->get_x() < ENEMY2_BASE_X + 130 && mouse_pos->get_y() > ENEMY2_BASE_Y && mouse_pos->get_y() < ENEMY2_BASE_Y + 130 && Input_handle::instance()->get_mouse_state(LEFT) == true) {
		if (m_enemy[2] != nullptr) {
			m_player->set_position(ENEMY2_BASE_X + 31, ENEMY2_BASE_Y + 62);
			if (m_player->get_strength() > m_enemy[2]->get_strength()) {
				m_player->change_strength(m_enemy[2]->get_strength(), '+');
				m_enemy[2]->set_strength_to_zero();
				m_enemy[2]->set_current_frame(100);
			}
			else m_player->set_strength_to_zero();
		}
	}
	else if (is_tower_destroyed(0, 0)&& mouse_pos->get_x() > ENEMY3_BASE_X && mouse_pos->get_x() < ENEMY3_BASE_X + 130 && mouse_pos->get_y() > ENEMY3_BASE_Y && mouse_pos->get_y() < ENEMY3_BASE_Y + 130 && Input_handle::instance()->get_mouse_state(LEFT) == true) {
		if (m_enemy[3] != nullptr) {
			m_player->set_position(ENEMY3_BASE_X + 31, ENEMY3_BASE_Y + 62);
			//if (m_player->get_strength() > m_enemy[3]->get_strength()) {
				m_player->change_strength(m_enemy[3]->get_strength(), '*');
				m_enemy[3]->set_strength_to_one();
				m_enemy[3]->set_current_frame(100);
			/*}
			else m_player->set_strength_to_zero();*/
		}
	}
	else if (is_tower_destroyed(0, 3) && mouse_pos->get_x() > ENEMY4_BASE_X && mouse_pos->get_x() < ENEMY4_BASE_X + 130 && mouse_pos->get_y() > ENEMY4_BASE_Y && mouse_pos->get_y() < ENEMY4_BASE_Y + 130 && Input_handle::instance()->get_mouse_state(LEFT) == true) {
		if (m_enemy[4] != nullptr) {
			m_player->set_position(ENEMY4_BASE_X + 31, ENEMY4_BASE_Y + 62);
			if (m_player->get_strength() > m_enemy[4]->get_strength()) {
				m_player->change_strength(m_enemy[4]->get_strength(), '+');
				m_enemy[4]->set_strength_to_zero();
				m_enemy[4]->set_current_frame(100);
			}
			else m_player->set_strength_to_zero();
		}
	}
	else if (is_tower_destroyed(0, 3) && mouse_pos->get_x() > ENEMY5_BASE_X && mouse_pos->get_x() < ENEMY5_BASE_X + 130 && mouse_pos->get_y() > ENEMY5_BASE_Y && mouse_pos->get_y() < ENEMY5_BASE_Y + 130 && Input_handle::instance()->get_mouse_state(LEFT) == true) {
		if (m_enemy[5] != nullptr) {
			m_player->set_position(ENEMY5_BASE_X + 31, ENEMY5_BASE_Y + 62);
			if (m_player->get_strength() > m_enemy[5]->get_strength()) {
				m_player->change_strength(m_enemy[5]->get_strength(), '+');
				m_enemy[5]->set_strength_to_zero();
				m_enemy[5]->set_current_frame(100);
			}
			else m_player->set_strength_to_zero();
		}
	}
	if (m_player->get_strength() == 0) game::instance()->get_game_state_manager()->replace(new Game_over);
	else if (enemy_count == count_defeated()) game::instance()->get_game_state_manager()->replace(new Victory);
}

void Level4::render()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (!m_exit && m_object[i] != nullptr)  m_object[i]->draw();
		else return;
	}
	if (!m_exit && m_player != nullptr)
	{
		m_player->draw();
		m_player->strength_to_text(PLAYER_BASE_X + 50, PLAYER_BASE_Y + 15);
	}
	else return;
	if (!m_exit && m_enemy[0] != nullptr) {
		m_enemy[0]->draw();
		m_enemy[0]->strength_to_text(ENEMY0_BASE_X + 50, ENEMY0_BASE_Y + 15);
	}
	else return;
	if (!m_exit && m_enemy[1] != nullptr) {
		m_enemy[1]->draw();
		m_enemy[1]->strength_to_text(ENEMY1_BASE_X + 70, ENEMY1_BASE_Y + 15);
		if (m_enemy[1]->get_strength() == 1) Texture_manager::instance()->remove_from_texture_map("div"s);

	}
	if (!m_exit && m_enemy[2] != nullptr) {
		m_enemy[2]->draw();
		m_enemy[2]->strength_to_text(ENEMY2_BASE_X + 50, ENEMY2_BASE_Y + 15);
	}
	else return;
	if (!m_exit && m_enemy[3] != nullptr) {
		m_enemy[3]->draw();
		m_enemy[3]->strength_to_text(ENEMY3_BASE_X + 70, ENEMY3_BASE_Y + 15);
		if (m_enemy[3]->get_strength() == 1) Texture_manager::instance()->remove_from_texture_map("mul"s);
	}
	else return;
	if (!m_exit && m_enemy[4] != nullptr) {
		m_enemy[4]->draw();
		m_enemy[4]->strength_to_text(ENEMY4_BASE_X + 50, ENEMY4_BASE_Y + 15);
	}
	else return;
	if (!m_exit && m_enemy[5] != nullptr) {
		m_enemy[5]->draw();
		m_enemy[5]->strength_to_text(ENEMY5_BASE_X + 50, ENEMY5_BASE_Y + 15);
	}
	else return;
}

bool Level4::on_start()
{
	if (!Texture_manager::instance()->load("pic/game_play_background.png"s, "game_play_background"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/replay.png"s, "replay"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/to_level_list.png"s, "to_level_list"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/base.png"s, "base"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/roof.png"s, "roof"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/player_default.png"s, "player_default"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/enemy_default.png"s, "enemy_default"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/multiple_buff.png"s, "multiple_buff"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/debuff.png"s, "debuff"s, game::instance()->get_renderer())) return false;

	if (!Texture_manager::instance()->create_texture_from_string("/"s, "div"s, 255, 248, 165, 255, 1, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->create_texture_from_string("x"s, "mul"s, 255, 248, 165, 255, 1, game::instance()->get_renderer())) return false;

	m_object.push_back(new Game_object("game_play_background"s, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	m_object.push_back(new Menu_button("replay"s, WINDOW_WIDTH * 0.02, WINDOW_HEIGHT * 0.02, 84, 84, replay));
	m_object.push_back(new Menu_button("to_level_list"s, WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.02, 84, 84, to_level_list));

	m_object.push_back(new Game_object("roof"s, PLAYER_BASE_X, PLAYER_BASE_Y, 130, 130));//player' s base
	m_object.push_back(new Game_object("roof"s, ENEMY0_BASE_X, ENEMY0_BASE_Y, 130, 130));//enemy0's base, tower 1
	m_object.push_back(new Game_object("base"s, ENEMY1_BASE_X, ENEMY1_BASE_Y, 130, 130));//enemy1's base, tower 2
	m_object.push_back(new Game_object("base"s, ENEMY2_BASE_X, ENEMY2_BASE_Y, 130, 130));//enemy2's base, tower 2
	m_object.push_back(new Game_object("roof"s, ENEMY3_BASE_X, ENEMY3_BASE_Y, 130, 130));//enemy3's base, tower 2
	m_object.push_back(new Game_object("base"s, ENEMY4_BASE_X, ENEMY4_BASE_Y, 130, 130));//enemy4's base, tower 3
	m_object.push_back(new Game_object("roof"s, ENEMY5_BASE_X, ENEMY5_BASE_Y, 130, 130));//enemy5's base, tower 3

	m_object.push_back(new Game_object("div"s, ENEMY1_BASE_X + 50, ENEMY1_BASE_Y + 15, Texture_manager::instance()->get_text_width("mul"s), Texture_manager::instance()->get_text_height("mul"s)));
	m_object.push_back(new Game_object("mul"s, ENEMY3_BASE_X + 50, ENEMY3_BASE_Y + 15, Texture_manager::instance()->get_text_width("mul"s), Texture_manager::instance()->get_text_height("mul"s)));

	m_player = new Player("player_default"s, PLAYER_STRENGTH, PLAYER_BASE_X + 50, PLAYER_BASE_Y + 65, 37, 51);//player

	m_enemy.push_back(new Enemy("enemy_default"s, ENEMY0_STRENGTH, ENEMY0_BASE_X + 50, ENEMY0_BASE_Y + 68, 80, 64, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy0
	m_enemy.push_back(new Enemy("debuff"s, ENEMY1_STRENGTH, ENEMY1_BASE_X + 50, ENEMY1_BASE_Y + 85, 32, 32, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy1
	m_enemy.push_back(new Enemy("enemy_default"s, ENEMY2_STRENGTH, ENEMY2_BASE_X + 50, ENEMY2_BASE_Y + 68, 80, 64, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy2
	m_enemy.push_back(new Enemy("multiple_buff"s, ENEMY3_STRENGTH, ENEMY3_BASE_X + 65, ENEMY3_BASE_Y + 40, 19, 76, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy3
	m_enemy.push_back(new Enemy("enemy_default"s, ENEMY4_STRENGTH, ENEMY4_BASE_X + 50, ENEMY4_BASE_Y + 68, 80, 64, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy4
	m_enemy.push_back(new Enemy("enemy_default"s, ENEMY5_STRENGTH, ENEMY5_BASE_X + 50, ENEMY5_BASE_Y + 68, 80, 64, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy5

	m_exit = false;
	return true;
	return true;
}

bool Level4::on_exit()
{
	clean();
	m_object.clear();

	Texture_manager::instance()->remove_from_texture_map("game_play_background"s);
	Texture_manager::instance()->remove_from_texture_map("replay"s);
	Texture_manager::instance()->remove_from_texture_map("to_level_list"s);
	Texture_manager::instance()->remove_from_texture_map("base"s);
	Texture_manager::instance()->remove_from_texture_map("roof"s);
	Texture_manager::instance()->remove_from_texture_map("player_default"s);
	Texture_manager::instance()->remove_from_texture_map("enemy_default"s);
	Texture_manager::instance()->remove_from_texture_map("multiple_buff"s);
	Texture_manager::instance()->remove_from_texture_map("mul"s);
	Texture_manager::instance()->remove_from_texture_map("div"s);
	Texture_manager::instance()->remove_from_texture_map("debuff"s);

	m_exit = true;
	return true;
}

void Level4::replay()
{
	game::instance()->get_game_state_manager()->replace(new Level4);
	std::cout << "replay" << std::endl;
}

void Level4::to_level_list()
{
	game::instance()->get_game_state_manager()->replace(new Level_list);
}

int Level4::count_defeated()
{
	int count{ 0 };
	for (int i = 0; i < m_enemy.size(); i++) {
		if (!m_exit && m_enemy[i] != nullptr) {
			if (m_enemy[i]->get_strength() == 0 || m_enemy[i]->get_strength() == 1) count++;
		}
		else return -1;
	}
	return count;
}

bool Level4::is_tower_destroyed(int start_enemy_index, int end_enemy_index)
{
	for (int i = start_enemy_index; i <= end_enemy_index; i++) {
		if (!m_exit && m_enemy[i] != nullptr) {
			if (!((m_enemy[i]->get_strength() == 0) || (m_enemy[i]->get_strength()) == 1)) return false;
		}
	}
	return true;
}
