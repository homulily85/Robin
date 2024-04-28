#include "Level6.h"
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

constexpr int PLAYER_STRENGTH{ 10 };

constexpr int ENEMY0_STRENGTH{ 15 };
constexpr int ENEMY1_STRENGTH{ 50 };
constexpr int ENEMY2_STRENGTH{ 7 };
constexpr int ENEMY3_STRENGTH{ 24 };
constexpr int ENEMY4_STRENGTH{ 2 };
constexpr int ENEMY5_STRENGTH{ 200 };
constexpr int ENEMY6_STRENGTH{ 102 };
constexpr int ENEMY7_STRENGTH{ 2 };
constexpr int ENEMY8_STRENGTH{ 183 };
constexpr int ENEMY9_STRENGTH{ 52 };
constexpr int ENEMY10_STRENGTH{ 368 };

constexpr int PLAYER_BASE_X{ 296 };
constexpr int PLAYER_BASE_Y{ 460 };

constexpr int ENEMY0_BASE_X = PLAYER_BASE_X + BASE_WIDTH * 3.5;
constexpr int ENEMY0_BASE_Y{ PLAYER_BASE_Y };
constexpr int ENEMY1_BASE_X = PLAYER_BASE_X + BASE_WIDTH * 3.5;
constexpr int ENEMY1_BASE_Y{ PLAYER_BASE_Y - BASE_HEIGHT };
constexpr int ENEMY2_BASE_X = PLAYER_BASE_X + BASE_WIDTH * 3.5;
constexpr int ENEMY2_BASE_Y{ PLAYER_BASE_Y - BASE_HEIGHT * 2 };
constexpr int ENEMY3_BASE_X = PLAYER_BASE_X + BASE_WIDTH * 3.5;
constexpr int ENEMY3_BASE_Y{ PLAYER_BASE_Y - BASE_HEIGHT * 3 };
constexpr int ENEMY4_BASE_X = PLAYER_BASE_X + BASE_WIDTH * 5;
constexpr int ENEMY4_BASE_Y{ PLAYER_BASE_Y };
constexpr int ENEMY5_BASE_X = PLAYER_BASE_X + BASE_WIDTH * 5;
constexpr int ENEMY5_BASE_Y{ PLAYER_BASE_Y - BASE_HEIGHT };
constexpr int ENEMY6_BASE_X = PLAYER_BASE_X + BASE_WIDTH * 5;
constexpr int ENEMY6_BASE_Y{ PLAYER_BASE_Y - BASE_HEIGHT * 2 };
constexpr int ENEMY7_BASE_X = PLAYER_BASE_X + BASE_WIDTH * 6.5;
constexpr int ENEMY7_BASE_Y{ PLAYER_BASE_Y };
constexpr int ENEMY8_BASE_X = PLAYER_BASE_X + BASE_WIDTH * 6.5;
constexpr int ENEMY8_BASE_Y{ PLAYER_BASE_Y -BASE_HEIGHT};
constexpr int ENEMY9_BASE_X = PLAYER_BASE_X + BASE_WIDTH * 6.5;
constexpr int ENEMY9_BASE_Y{ PLAYER_BASE_Y - BASE_HEIGHT *2};

constexpr int ENEMY10_BASE_X= PLAYER_BASE_X+BASE_WIDTH*6.5 ;
constexpr int ENEMY10_BASE_Y{ PLAYER_BASE_Y-BASE_HEIGHT*3};

using namespace std::string_literals;

const std::string Level6::m_state_ID{ "LEVEL6"s };

void Level6::clean()
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

void Level6::update()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (!m_exit && m_object[i] != nullptr && m_object.size() < 100)  m_object[i]->update();
		else return;
	}
	if (!m_exit && m_player != nullptr) m_player->update();
	else return;
	for (int i = 0; i < m_enemy.size(); i++) {
		if (!m_exit && m_enemy[i] != nullptr) m_enemy[i]->update();
		else return;
	}
	Vector2D* mouse_pos = Input_handle::instance()->get_mouse_position();
	if (mouse_pos->get_x() > ENEMY0_BASE_X && mouse_pos->get_x() < ENEMY0_BASE_X + BASE_WIDTH && mouse_pos->get_y() > ENEMY0_BASE_Y && mouse_pos->get_y() < ENEMY0_BASE_Y + BASE_HEIGHT && Input_handle::instance()->get_mouse_state(LEFT) == true && m_enemy[0]->get_strength() > 0 && m_player->get_strength() > 0) {
		if (m_enemy[0] != nullptr) {
			m_player->set_position(ENEMY0_BASE_X + 0.25 * (BASE_WIDTH - PLAYER_WIDTH), ENEMY0_BASE_Y + ENEMY_Y_SCALE);
			if (m_player->get_strength() > m_enemy[0]->get_strength()) {
				m_player->change_strength(m_enemy[0]->get_strength(), '+');
				m_enemy[0]->set_strength_to_zero();
				m_enemy[0]->change_texture("enemy_death"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_player->change_texture("player_attack"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_player->set_attack(true);
			}
			else {
				m_player->set_strength_to_zero();
				m_player->change_texture("player_death"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_enemy[0]->change_texture("enemy_attack"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_enemy[0]->set_attack(true);
			}
		}
	}
	else if (mouse_pos->get_x() > ENEMY1_BASE_X && mouse_pos->get_x() < ENEMY1_BASE_X + BASE_WIDTH && mouse_pos->get_y() > ENEMY1_BASE_Y && mouse_pos->get_y() < ENEMY1_BASE_Y + BASE_HEIGHT && Input_handle::instance()->get_mouse_state(LEFT) == true && m_player->get_strength() > 0 && m_enemy[1]->get_strength() > 0) {
		if (m_enemy[1] != nullptr) {
			m_player->set_position(ENEMY1_BASE_X + 0.25 * (BASE_WIDTH - PLAYER_WIDTH), ENEMY1_BASE_Y + ENEMY_Y_SCALE);
			m_player->change_strength(m_enemy[1]->get_strength(), '+');
			m_enemy[1]->set_strength_to_zero();
			m_enemy[1]->set_current_frame(100);
		}
	}
	else if (mouse_pos->get_x() > ENEMY2_BASE_X && mouse_pos->get_x() < ENEMY2_BASE_X + BASE_WIDTH && mouse_pos->get_y() > ENEMY2_BASE_Y && mouse_pos->get_y() < ENEMY2_BASE_Y + BASE_HEIGHT && Input_handle::instance()->get_mouse_state(LEFT) == true && m_enemy[2]->get_strength() > 0 && m_player->get_strength() > 0) {
		if (m_enemy[2] != nullptr) {
			m_player->set_position(ENEMY2_BASE_X + 0.25 * (BASE_WIDTH - PLAYER_WIDTH), ENEMY2_BASE_Y + ENEMY_Y_SCALE);
			if (m_player->get_strength() > m_enemy[2]->get_strength()) {
				m_player->change_strength(m_enemy[2]->get_strength(), '+');
				m_enemy[2]->set_strength_to_zero();
				m_enemy[2]->change_texture("enemy_death"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_player->change_texture("player_attack"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_player->set_attack(true);
			}
			else {
				m_player->set_strength_to_zero();
				m_player->change_texture("player_death"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_enemy[2]->change_texture("enemy_attack"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_enemy[2]->set_attack(true);
			}
		}
	}
	else if (mouse_pos->get_x() > ENEMY3_BASE_X && mouse_pos->get_x() < ENEMY3_BASE_X + BASE_WIDTH && mouse_pos->get_y() > ENEMY3_BASE_Y && mouse_pos->get_y() < ENEMY3_BASE_Y + BASE_HEIGHT && Input_handle::instance()->get_mouse_state(LEFT) == true && m_enemy[3]->get_strength() > 0 && m_player->get_strength() > 0) {
		if (m_enemy[3] != nullptr) {
			m_player->set_position(ENEMY3_BASE_X + 0.25 * (BASE_WIDTH - PLAYER_WIDTH), ENEMY3_BASE_Y + ENEMY_Y_SCALE);
			if (m_player->get_strength() > m_enemy[3]->get_strength()) {
				m_player->change_strength(m_enemy[3]->get_strength(), '+');
				m_enemy[3]->set_strength_to_zero();
				m_enemy[3]->change_texture("enemy_death"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_player->change_texture("player_attack"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_player->set_attack(true);
			}
			else {
				m_player->set_strength_to_zero();
				m_player->change_texture("player_death"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_enemy[3]->change_texture("enemy_attack"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_enemy[3]->set_attack(true);
			}
		}
	}
	else if (is_tower_destroyed(0, 3) && mouse_pos->get_x() > ENEMY4_BASE_X && mouse_pos->get_x() < ENEMY4_BASE_X + BASE_WIDTH && mouse_pos->get_y() > ENEMY4_BASE_Y && mouse_pos->get_y() < ENEMY4_BASE_Y + BASE_HEIGHT && Input_handle::instance()->get_mouse_state(LEFT) == true && m_player->get_strength() > 0 && m_enemy[4]->get_strength() > 1) {
		if (m_enemy[4] != nullptr) {
			m_player->set_position(ENEMY4_BASE_X + 0.25 * (BASE_WIDTH - PLAYER_WIDTH), ENEMY4_BASE_Y + ENEMY_Y_SCALE);
			m_player->change_strength(m_enemy[4]->get_strength(), '/');
			m_enemy[4]->set_strength_to_one();
			m_enemy[4]->set_current_frame(100);
		}
	}
	else if (is_tower_destroyed(0, 3) && mouse_pos->get_x() > ENEMY5_BASE_X && mouse_pos->get_x() < ENEMY5_BASE_X + BASE_WIDTH && mouse_pos->get_y() > ENEMY5_BASE_Y && mouse_pos->get_y() < ENEMY5_BASE_Y + BASE_HEIGHT && Input_handle::instance()->get_mouse_state(LEFT) == true && m_enemy[5]->get_strength() > 0 && m_player->get_strength() > 0) {
		if (m_enemy[5] != nullptr) {
			m_player->set_position(ENEMY5_BASE_X + 0.25 * (BASE_WIDTH - PLAYER_WIDTH), ENEMY5_BASE_Y + ENEMY_Y_SCALE);
			if (m_player->get_strength() > m_enemy[5]->get_strength()) {
				m_player->change_strength(m_enemy[5]->get_strength(), '+');
				m_enemy[5]->set_strength_to_zero();
				m_enemy[5]->change_texture("enemy_death"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_player->change_texture("player_attack"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_player->set_attack(true);
			}
			else {
				m_player->set_strength_to_zero();
				m_player->change_texture("player_death"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_enemy[5]->change_texture("enemy_attack"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_enemy[5]->set_attack(true);
			}
		}
	}
	else if (is_tower_destroyed(0, 3) && mouse_pos->get_x() > ENEMY6_BASE_X && mouse_pos->get_x() < ENEMY6_BASE_X + BASE_WIDTH && mouse_pos->get_y() > ENEMY6_BASE_Y && mouse_pos->get_y() < ENEMY6_BASE_Y + BASE_HEIGHT && Input_handle::instance()->get_mouse_state(LEFT) == true && m_enemy[6]->get_strength() > 0 && m_player->get_strength() > 0) {
		if (m_enemy[6] != nullptr) {
			m_player->set_position(ENEMY6_BASE_X + 0.25 * (BASE_WIDTH - PLAYER_WIDTH), ENEMY6_BASE_Y + ENEMY_Y_SCALE);
			if (m_player->get_strength() > m_enemy[6]->get_strength()) {
				m_player->change_strength(m_enemy[6]->get_strength(), '+');
				m_enemy[6]->set_strength_to_zero();
				m_enemy[6]->change_texture("enemy_death"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_player->change_texture("player_attack"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_player->set_attack(true);
			}
			else {
				m_player->set_strength_to_zero();
				m_player->change_texture("player_death"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_enemy[6]->change_texture("enemy_attack"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_enemy[6]->set_attack(true);
			}
		}
	}
	else if (is_tower_destroyed(0, 6) && mouse_pos->get_x() > ENEMY7_BASE_X && mouse_pos->get_x() < ENEMY7_BASE_X + BASE_WIDTH && mouse_pos->get_y() > ENEMY7_BASE_Y && mouse_pos->get_y() < ENEMY7_BASE_Y + BASE_HEIGHT && Input_handle::instance()->get_mouse_state(LEFT) == true && m_player->get_strength() > 0 && m_enemy[7]->get_strength() > 1) {
		if (m_enemy[7] != nullptr) {
			m_player->set_position(ENEMY7_BASE_X + 0.25 * (BASE_WIDTH - PLAYER_WIDTH), ENEMY7_BASE_Y + ENEMY_Y_SCALE);
			m_player->change_strength(m_enemy[7]->get_strength(), '/');
			m_enemy[7]->set_strength_to_one();
			m_enemy[7]->set_current_frame(100);
		}
	}
	else if (is_tower_destroyed(0, 6) && mouse_pos->get_x() > ENEMY8_BASE_X && mouse_pos->get_x() < ENEMY8_BASE_X + BASE_WIDTH && mouse_pos->get_y() > ENEMY8_BASE_Y && mouse_pos->get_y() < ENEMY8_BASE_Y + BASE_HEIGHT && Input_handle::instance()->get_mouse_state(LEFT) == true && m_player->get_strength() > 0 && m_enemy[8]->get_strength() > 0) {
		if (m_enemy[8] != nullptr) {
			m_player->set_position(ENEMY8_BASE_X + 0.25 * (BASE_WIDTH - PLAYER_WIDTH), ENEMY8_BASE_Y + ENEMY_Y_SCALE);
			if (m_player->get_strength() > m_enemy[8]->get_strength()) {
				m_player->change_strength(m_enemy[8]->get_strength(), '+');
				m_enemy[8]->set_strength_to_zero();
				m_enemy[8]->change_texture("enemy_death"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_player->change_texture("player_attack"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_player->set_attack(true);
			}
			else {
				m_player->set_strength_to_zero();
				m_player->change_texture("player_death"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_enemy[8]->change_texture("enemy_attack"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_enemy[8]->set_attack(true);
			}
		}
	}
	else if (is_tower_destroyed(0, 6) && mouse_pos->get_x() > ENEMY9_BASE_X && mouse_pos->get_x() < ENEMY9_BASE_X + BASE_WIDTH && mouse_pos->get_y() > ENEMY9_BASE_Y && mouse_pos->get_y() < ENEMY9_BASE_Y + BASE_HEIGHT && Input_handle::instance()->get_mouse_state(LEFT) == true && m_player->get_strength() > 0 && m_enemy[9]->get_strength() > 0) {
		if (m_enemy[9] != nullptr) {
			m_player->set_position(ENEMY9_BASE_X + 0.25 * (BASE_WIDTH - PLAYER_WIDTH), ENEMY9_BASE_Y + ENEMY_Y_SCALE);
			if (m_player->get_strength() > m_enemy[9]->get_strength()) {
				m_player->change_strength(m_enemy[9]->get_strength(), '+');
				m_enemy[9]->set_strength_to_zero();
				m_enemy[9]->change_texture("enemy_death"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_player->change_texture("player_attack"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_player->set_attack(true);
			}
			else {
				m_player->set_strength_to_zero();
				m_player->change_texture("player_death"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_enemy[9]->change_texture("enemy_attack"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_enemy[9]->set_attack(true);
			}
		}
	}
	else if (is_tower_destroyed(0, 6) && mouse_pos->get_x() > ENEMY10_BASE_X && mouse_pos->get_x() < ENEMY10_BASE_X + BASE_WIDTH && mouse_pos->get_y() > ENEMY10_BASE_Y && mouse_pos->get_y() < ENEMY10_BASE_Y + BASE_HEIGHT && Input_handle::instance()->get_mouse_state(LEFT) == true && m_player->get_strength() > 0 && m_enemy[10]->get_strength() > 0) {
		if (m_enemy[10] != nullptr) {
			m_player->set_position(ENEMY10_BASE_X + 0.25 * (BASE_WIDTH - PLAYER_WIDTH), ENEMY10_BASE_Y + ENEMY_Y_SCALE);
			if (m_player->get_strength() > m_enemy[10]->get_strength()) {
				m_player->change_strength(m_enemy[10]->get_strength(), '+');
				m_enemy[10]->set_strength_to_zero();
				m_enemy[10]->change_texture("enemy_death"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_player->change_texture("player_attack"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_player->set_attack(true);
			}
			else {
				m_player->set_strength_to_zero();
				m_player->change_texture("player_death"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
				m_enemy[10]->change_texture("enemy_attack"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
				m_enemy[10]->set_attack(true);
			}
		}
	}
	if (m_player->get_strength() == 0 && frame_check_defeat()) {
		SDL_Delay(500);
		game::instance()->get_game_state_manager()->replace(new Game_over);
	}
	else if (enemy_count == count_defeated() && frame_check_victory()) {
		SDL_Delay(500);
		game::instance()->get_game_state_manager()->replace(new Victory);
	}
}

void Level6::render()
{
	Uint32 start_time{};
	Uint32 frame_time{};
	for (int i = 0; i < m_object.size(); i++) {
		if (!m_exit && m_object[i] != nullptr)  m_object[i]->draw();
		else return;
	}
	if (!m_exit && m_player != nullptr)
	{
		m_player->draw();
		m_player->strength_to_text(m_player->get_x() + 15, m_player->get_y() - 53);
		if (m_player->get_strength() != 0 && !m_player->get_attack()) {
			m_player->set_current_frame((int)((SDL_GetTicks() / 100) % (PLAYER_IDLE_MAX_FRAME - 1)));
		}
		else if (m_player->get_strength() != 0 && m_player->get_attack()) {
			if (m_player->get_current_frame() < PLAYER_ATTACK_MAX_FRAME - 1) {
				int frame = m_player->get_current_frame();
				frame_time = SDL_GetTicks() - start_time;
				if (frame_time > 100) {
					frame++;
					m_player->set_current_frame(frame);
					SDL_Delay(100);
				}
			}
			else {
				m_player->set_attack(false);
				m_player->change_texture("player_idle"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
			}
		}
		else if (m_player->get_strength() == 0 && m_player->get_current_frame() < PLAYER_DEATH_MAX_FRAME - 1 && !check_enemy_attack()) {
			int frame = m_player->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_player->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
	}
	else return;
	if (!m_exit && m_enemy[0] != nullptr) {
		m_enemy[0]->draw();
		m_enemy[0]->strength_to_text(ENEMY0_BASE_X + 50, ENEMY0_BASE_Y + 15);
		if (m_enemy[0]->get_strength() != 0 && !m_enemy[0]->get_attack()) {
			m_enemy[0]->set_current_frame((int)((SDL_GetTicks() / 100) % (ENEMY_DEFAULT_MAX_FRAME - 1)));
		}
		if (m_enemy[0]->get_strength() == 0 && m_enemy[0]->get_current_frame() < ENEMY_DEATH_MAX_FRAME - 1 && !m_player->get_attack()) {
			int frame = m_enemy[0]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[0]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else if (m_enemy[0]->get_attack() && m_enemy[0]->get_current_frame() < ENEMY_ATTACK_MAX_FRAME - 1) {
			int frame = m_enemy[0]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[0]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else m_enemy[0]->set_attack(false);
	}
	else return;
	if (!m_exit && m_enemy[1] != nullptr) {
		m_enemy[1]->draw();
		m_enemy[1]->strength_to_text(ENEMY1_BASE_X + 70, ENEMY1_BASE_Y + 15);
		if (m_enemy[1]->get_strength() == 0) Texture_manager::instance()->remove_from_texture_map("plus"s);

	}
	else return;
	if (!m_exit && m_enemy[2] != nullptr) {
		m_enemy[2]->draw();
		m_enemy[2]->strength_to_text(ENEMY2_BASE_X + 50, ENEMY2_BASE_Y + 15);
		if (m_enemy[2]->get_strength() != 0 && !m_enemy[2]->get_attack()) {
			m_enemy[2]->set_current_frame((int)((SDL_GetTicks() / 100) % (ENEMY_DEFAULT_MAX_FRAME - 1)));
		}
		if (m_enemy[2]->get_strength() == 0 && m_enemy[2]->get_current_frame() < ENEMY_DEATH_MAX_FRAME - 1 && !m_player->get_attack()) {
			int frame = m_enemy[2]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[2]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else if (m_enemy[2]->get_attack() && m_enemy[2]->get_current_frame() < ENEMY_ATTACK_MAX_FRAME - 1) {
			int frame = m_enemy[2]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[2]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else m_enemy[2]->set_attack(false);
	}
	else return;
	if (!m_exit && m_enemy[3] != nullptr) {
		m_enemy[3]->draw();
		m_enemy[3]->strength_to_text(ENEMY3_BASE_X + 50, ENEMY3_BASE_Y + 15);
		if (m_enemy[3]->get_strength() != 0 && !m_enemy[3]->get_attack()) {
			m_enemy[3]->set_current_frame((int)((SDL_GetTicks() / 100) % (ENEMY_DEFAULT_MAX_FRAME - 1)));
		}
		if (m_enemy[3]->get_strength() == 0 && m_enemy[3]->get_current_frame() < ENEMY_DEATH_MAX_FRAME - 1 && !m_player->get_attack()) {
			int frame = m_enemy[3]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[3]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else if (m_enemy[3]->get_attack() && m_enemy[3]->get_current_frame() < ENEMY_ATTACK_MAX_FRAME - 1) {
			int frame = m_enemy[3]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[3]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else m_enemy[3]->set_attack(false);
	}
	else return;
	if (!m_exit && m_enemy[4] != nullptr) {
		m_enemy[4]->draw();
		m_enemy[4]->strength_to_text(ENEMY4_BASE_X + 70, ENEMY4_BASE_Y + 15);
		if (m_enemy[4]->get_strength() == 1) Texture_manager::instance()->remove_from_texture_map("div1"s);
	}
	else return;
	if (!m_exit && m_enemy[5] != nullptr) {
		m_enemy[5]->draw();
		m_enemy[5]->strength_to_text(ENEMY5_BASE_X + 50, ENEMY5_BASE_Y + 15);
		if (m_enemy[5]->get_strength() != 0 && !m_enemy[5]->get_attack()) {
			m_enemy[5]->set_current_frame((int)((SDL_GetTicks() / 100) % (ENEMY_DEFAULT_MAX_FRAME - 1)));
		}
		if (m_enemy[5]->get_strength() == 0 && m_enemy[5]->get_current_frame() < ENEMY_DEATH_MAX_FRAME - 1 && !m_player->get_attack()) {
			int frame = m_enemy[5]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[5]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else if (m_enemy[5]->get_attack() && m_enemy[5]->get_current_frame() < ENEMY_ATTACK_MAX_FRAME - 1) {
			int frame = m_enemy[5]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[5]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else m_enemy[5]->set_attack(false);
	}
	else return;
	if (!m_exit && m_enemy[6] != nullptr) {
		m_enemy[6]->draw();
		m_enemy[6]->strength_to_text(ENEMY6_BASE_X + 50, ENEMY6_BASE_Y + 15);
		if (m_enemy[6]->get_strength() != 0 && !m_enemy[6]->get_attack()) {
			m_enemy[6]->set_current_frame((int)((SDL_GetTicks() / 100) % (ENEMY_DEFAULT_MAX_FRAME - 1)));
		}
		if (m_enemy[6]->get_strength() == 0 && m_enemy[6]->get_current_frame() < ENEMY_DEATH_MAX_FRAME - 1 && !m_player->get_attack()) {
			int frame = m_enemy[6]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[6]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else if (m_enemy[6]->get_attack() && m_enemy[6]->get_current_frame() < ENEMY_ATTACK_MAX_FRAME - 1) {
			int frame = m_enemy[6]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[6]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else m_enemy[6]->set_attack(false);
	}
	else return;
	if (!m_exit && m_enemy[7] != nullptr) {
		m_enemy[7]->draw();
		m_enemy[7]->strength_to_text(ENEMY7_BASE_X + 70, ENEMY7_BASE_Y + 15);
		if (m_enemy[7]->get_strength() == 1) Texture_manager::instance()->remove_from_texture_map("div2"s);
	}
	else return;
	if (!m_exit && m_enemy[8] != nullptr) {
		m_enemy[8]->draw();
		m_enemy[8]->strength_to_text(ENEMY8_BASE_X + 50, ENEMY8_BASE_Y + 15);
		if (m_enemy[8]->get_strength() != 0 && !m_enemy[8]->get_attack()) {
			m_enemy[8]->set_current_frame((int)((SDL_GetTicks() / 100) % (ENEMY_DEFAULT_MAX_FRAME - 1)));
		}
		if (m_enemy[8]->get_strength() == 0 && m_enemy[8]->get_current_frame() < ENEMY_DEATH_MAX_FRAME - 1 && !m_player->get_attack()) {
			int frame = m_enemy[8]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[8]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else if (m_enemy[8]->get_attack() && m_enemy[8]->get_current_frame() < ENEMY_ATTACK_MAX_FRAME - 1) {
			int frame = m_enemy[8]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[8]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else m_enemy[8]->set_attack(false);
	}
	else return;
	if (!m_exit && m_enemy[9] != nullptr) {
		m_enemy[9]->draw();
		m_enemy[9]->strength_to_text(ENEMY9_BASE_X + 50, ENEMY9_BASE_Y + 15);
		if (m_enemy[9]->get_strength() != 0 && !m_enemy[9]->get_attack()) {
			m_enemy[9]->set_current_frame((int)((SDL_GetTicks() / 100) % (ENEMY_DEFAULT_MAX_FRAME - 1)));
		}
		if (m_enemy[9]->get_strength() == 0 && m_enemy[9]->get_current_frame() < ENEMY_DEATH_MAX_FRAME - 1 && !m_player->get_attack()) {
			int frame = m_enemy[9]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[9]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else if (m_enemy[9]->get_attack() && m_enemy[9]->get_current_frame() < ENEMY_ATTACK_MAX_FRAME - 1) {
			int frame = m_enemy[9]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[9]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else m_enemy[9]->set_attack(false);
	}
	else return;
	if (!m_exit && m_enemy[10] != nullptr) {
		m_enemy[10]->draw();
		m_enemy[10]->strength_to_text(ENEMY10_BASE_X + 50, ENEMY10_BASE_Y + 15);
		if (m_enemy[10]->get_strength() != 0 && !m_enemy[10]->get_attack()) {
			m_enemy[10]->set_current_frame((int)((SDL_GetTicks() / 100) % (ENEMY_DEFAULT_MAX_FRAME - 1)));
		}
		if (m_enemy[10]->get_strength() == 0 && m_enemy[10]->get_current_frame() < ENEMY_DEATH_MAX_FRAME - 1 && !m_player->get_attack()) {
			int frame = m_enemy[10]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[10]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else if (m_enemy[10]->get_attack() && m_enemy[10]->get_current_frame() < ENEMY_ATTACK_MAX_FRAME - 1) {
			int frame = m_enemy[10]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[10]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else m_enemy[10]->set_attack(false);
	}
	else return;
}

bool Level6::on_start()
{
	if (!Texture_manager::instance()->load("pic/game_play_background.png"s, "game_play_background"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/replay.png"s, "replay"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/to_level_list.png"s, "to_level_list"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/base.png"s, "base"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/roof.png"s, "roof"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/player_idle.png"s, "player_idle"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/player_attack.png"s, "player_attack"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/player_death.png"s, "player_death"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/enemy_default.png"s, "enemy_default"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/enemy_death.png"s, "enemy_death"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/enemy_attack.png"s, "enemy_attack"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/buff.png"s, "buff"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/debuff.png"s, "debuff"s, game::instance()->get_renderer())) return false;

	if (!Texture_manager::instance()->create_texture_from_string("/"s, "div1"s, 255, 248, 165, 255, 1, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->create_texture_from_string("/"s, "div2"s, 255, 248, 165, 255, 1, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->create_texture_from_string("+"s, "plus"s, 255, 248, 165, 255, 1, game::instance()->get_renderer())) return false;

	m_object.push_back(new Game_object("game_play_background"s, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	m_object.push_back(new Menu_button("replay"s, WINDOW_WIDTH * 0.02, WINDOW_HEIGHT * 0.02, 84, 84, replay));
	m_object.push_back(new Menu_button("to_level_list"s, WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.02, 84, 84, to_level_list));

	m_object.push_back(new Game_object("roof"s, PLAYER_BASE_X, PLAYER_BASE_Y, BASE_WIDTH, BASE_HEIGHT));//player' s base
	m_object.push_back(new Game_object("base"s, ENEMY0_BASE_X, ENEMY0_BASE_Y, BASE_WIDTH, BASE_HEIGHT));//enemy0's base
	m_object.push_back(new Game_object("base"s, ENEMY1_BASE_X, ENEMY1_BASE_Y, BASE_WIDTH, BASE_HEIGHT));//enemy1's base
	m_object.push_back(new Game_object("base"s, ENEMY2_BASE_X, ENEMY2_BASE_Y, BASE_WIDTH, BASE_HEIGHT));//enemy2's base
	m_object.push_back(new Game_object("base"s, ENEMY3_BASE_X, ENEMY3_BASE_Y, BASE_WIDTH, BASE_HEIGHT));//enemy3's base
	m_object.push_back(new Game_object("base"s, ENEMY4_BASE_X, ENEMY4_BASE_Y, BASE_WIDTH, BASE_HEIGHT));//enemy4's base
	m_object.push_back(new Game_object("base"s, ENEMY5_BASE_X, ENEMY5_BASE_Y, BASE_WIDTH, BASE_HEIGHT));//enemy5's base
	m_object.push_back(new Game_object("base"s, ENEMY6_BASE_X, ENEMY6_BASE_Y, BASE_WIDTH, BASE_HEIGHT));//enemy6's base
	m_object.push_back(new Game_object("base"s, ENEMY7_BASE_X, ENEMY7_BASE_Y, BASE_WIDTH, BASE_HEIGHT));//enemy7's base
	m_object.push_back(new Game_object("base"s, ENEMY8_BASE_X, ENEMY8_BASE_Y, BASE_WIDTH, BASE_HEIGHT));//enemy8's base
	m_object.push_back(new Game_object("base"s, ENEMY9_BASE_X, ENEMY9_BASE_Y, BASE_WIDTH, BASE_HEIGHT));//enemy9's base
	m_object.push_back(new Game_object("base"s, ENEMY10_BASE_X, ENEMY10_BASE_Y, BASE_WIDTH, BASE_HEIGHT));//enemy10's base

	m_object.push_back(new Game_object("div1"s, ENEMY4_BASE_X + 50, ENEMY4_BASE_Y + 15, Texture_manager::instance()->get_text_width("div1"s),Texture_manager::instance()->get_text_height("div1")));
	m_object.push_back(new Game_object("div2"s, ENEMY7_BASE_X + 50, ENEMY7_BASE_Y + 15, Texture_manager::instance()->get_text_width("div2"s), Texture_manager::instance()->get_text_height("div2")));
	m_object.push_back(new Game_object("plus"s, ENEMY1_BASE_X + 50, ENEMY1_BASE_Y + 15, Texture_manager::instance()->get_text_width("plus"s), Texture_manager::instance()->get_text_height("plus")));

	m_player = new Player("player_idle"s, PLAYER_STRENGTH, PLAYER_BASE_X + 0.5 * (BASE_WIDTH - PLAYER_WIDTH), PLAYER_BASE_Y + PLAYER_Y_SCALE, PLAYER_WIDTH, PLAYER_HEIGHT);//player

	m_enemy.push_back(new Enemy("enemy_default"s, ENEMY0_STRENGTH, ENEMY0_BASE_X + 0.5 * (BASE_WIDTH - ENEMY_WIDTH), ENEMY0_BASE_Y + ENEMY_Y_SCALE, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy0
	m_enemy.push_back(new Enemy("buff"s, ENEMY1_STRENGTH, ENEMY1_BASE_X + 0.5 * (BASE_WIDTH - BUFF_WIDTH), ENEMY1_BASE_Y + BUFF_Y_SCALE, BUFF_WIDTH, BUFF_HEIGHT, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy1
	m_enemy.push_back(new Enemy("enemy_default"s, ENEMY2_STRENGTH, ENEMY2_BASE_X + 0.5 * (BASE_WIDTH - ENEMY_WIDTH), ENEMY2_BASE_Y + ENEMY_Y_SCALE, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy2
	m_enemy.push_back(new Enemy("enemy_default"s, ENEMY3_STRENGTH, ENEMY3_BASE_X + 0.5 * (BASE_WIDTH - ENEMY_WIDTH), ENEMY3_BASE_Y + ENEMY_Y_SCALE, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy3
	m_enemy.push_back(new Enemy("debuff"s, ENEMY4_STRENGTH, ENEMY4_BASE_X + 0.5 * (BASE_WIDTH - DEBUFF_WIDTH), ENEMY4_BASE_Y + DEBUFF_Y_SCALE, DEBUFF_WIDTH, DEBUFF_HEIGHT, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy4
	m_enemy.push_back(new Enemy("enemy_default"s, ENEMY5_STRENGTH, ENEMY5_BASE_X + 0.5 * (BASE_WIDTH - ENEMY_WIDTH), ENEMY5_BASE_Y + ENEMY_Y_SCALE, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy5
	m_enemy.push_back(new Enemy("enemy_default"s, ENEMY6_STRENGTH, ENEMY6_BASE_X + 0.5 * (BASE_WIDTH - ENEMY_WIDTH), ENEMY6_BASE_Y + ENEMY_Y_SCALE, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy6
	m_enemy.push_back(new Enemy("debuff"s, ENEMY7_STRENGTH, ENEMY7_BASE_X + 0.5 * (BASE_WIDTH - DEBUFF_WIDTH), ENEMY7_BASE_Y + DEBUFF_Y_SCALE, DEBUFF_WIDTH, DEBUFF_HEIGHT, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy7
	m_enemy.push_back(new Enemy("enemy_default"s, ENEMY8_STRENGTH, ENEMY8_BASE_X + 0.5 * (BASE_WIDTH - ENEMY_WIDTH), ENEMY8_BASE_Y + ENEMY_Y_SCALE, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy8
	m_enemy.push_back(new Enemy("enemy_default"s, ENEMY9_STRENGTH, ENEMY9_BASE_X + 0.5 * (BASE_WIDTH - ENEMY_WIDTH), ENEMY9_BASE_Y + ENEMY_Y_SCALE, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy9
	m_enemy.push_back(new Enemy("enemy_default"s, ENEMY10_STRENGTH, ENEMY10_BASE_X + 0.5 * (BASE_WIDTH - ENEMY_WIDTH), ENEMY10_BASE_Y + ENEMY_Y_SCALE, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy10
	m_exit = false;
	return true;
}

bool Level6::on_exit()
{
	clean();
	m_object.clear();

	Texture_manager::instance()->remove_from_texture_map("game_play_background"s);
	Texture_manager::instance()->remove_from_texture_map("replay"s);
	Texture_manager::instance()->remove_from_texture_map("to_level_list"s);
	Texture_manager::instance()->remove_from_texture_map("base"s);
	Texture_manager::instance()->remove_from_texture_map("roof"s);
	Texture_manager::instance()->remove_from_texture_map("player_idle"s);
	Texture_manager::instance()->remove_from_texture_map("player_attack"s);
	Texture_manager::instance()->remove_from_texture_map("player_death"s);
	Texture_manager::instance()->remove_from_texture_map("enemy_default"s);
	Texture_manager::instance()->remove_from_texture_map("enemy_death"s);
	Texture_manager::instance()->remove_from_texture_map("enemy_attack"s);
	Texture_manager::instance()->remove_from_texture_map("buff"s);
	Texture_manager::instance()->remove_from_texture_map("debuff"s);
	Texture_manager::instance()->remove_from_texture_map("div1"s);
	Texture_manager::instance()->remove_from_texture_map("div2"s);
	Texture_manager::instance()->remove_from_texture_map("plus"s);


	m_exit = true;
	return true;
}

void Level6::replay()
{
	game::instance()->get_game_state_manager()->replace(new Level6);
}

void Level6::to_level_list()
{
	game::instance()->get_game_state_manager()->replace(new Level_list);
}

int Level6::count_defeated()
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

bool Level6::is_tower_destroyed(int start_enemy_index, int end_enemy_index)
{
	for (int i = start_enemy_index; i <= end_enemy_index; i++) {
		if (!m_exit && m_enemy[i] != nullptr) {
			if (!((m_enemy[i]->get_strength() == 0) || (m_enemy[i]->get_strength()) == 1)) return false;
		}
	}
	return true;
}

bool Level6::frame_check_defeat()
{
	if (m_player->get_strength() == 0 && m_player->get_current_frame() >= PLAYER_DEATH_MAX_FRAME - 1) return true;
	else return false;
}

bool Level6::check_enemy_attack()
{
	for (auto p : m_enemy) {
		if (p->get_attack()) return true;
	}
	return false;
}
bool Level6::frame_check_victory()
{
	if (count_defeated() == enemy_count) {
		for (auto p : m_enemy) {
			if (p->get_current_frame() < ENEMY_DEATH_MAX_FRAME - 1) return false;
		}
		return true;
	}
}
