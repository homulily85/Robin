#include "level1.h"
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

constexpr int PLAYER_STRENGTH{ 22 };
constexpr int ENEMY0_STRENGTH{ 15 };
constexpr int ENEMY1_STRENGTH{ 30 };

constexpr int PLAYER_BASE_X{ 296 };
constexpr int PLAYER_BASE_Y{ 460 };
constexpr int ENEMY0_BASE_X{ PLAYER_BASE_X+BASE_WIDTH*4 };
constexpr int ENEMY0_BASE_Y{ 460 };
constexpr int ENEMY1_BASE_X{ PLAYER_BASE_X+BASE_WIDTH*4 };
constexpr int ENEMY1_BASE_Y{ ENEMY0_BASE_Y-BASE_HEIGHT};

using namespace std::string_literals;

const std::string Level1::m_state_ID{ "LEVEL1"s };

void Level1::clean()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (m_object[i] != nullptr)
		{
			delete m_object[i];
			m_object[i] = nullptr;
		}
	}
	if (m_player != nullptr) delete m_player;
	m_player=nullptr;
	for (int i = 0; i < m_enemy.size(); i++) {
		if (m_enemy[i] != nullptr) {
			delete m_enemy[i];
			m_enemy[i] = nullptr;
		}
	}
}

void Level1::update()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (!m_exit && m_object[i] != nullptr&&m_object.size()<100)  m_object[i]->update();
		else return;
	}
	if (!m_exit && m_player != nullptr) m_player->update();
	else return;
	for (int i = 0; i < m_enemy.size(); i++) {
		if (!m_exit && m_enemy[i] != nullptr) m_enemy[i]->update();
		else return;
	}
	Vector2D* mouse_pos = Input_handle::instance()->get_mouse_position();
	if (mouse_pos->get_x() > ENEMY0_BASE_X && mouse_pos->get_x() < ENEMY0_BASE_X+ BASE_WIDTH && mouse_pos->get_y() > ENEMY0_BASE_Y&& mouse_pos->get_y() < ENEMY0_BASE_Y+ BASE_HEIGHT &&Input_handle::instance()->get_mouse_state(LEFT)==true&&m_enemy[0]->get_strength()>0&&m_player->get_strength()!=0) {
		if (m_enemy[0] != nullptr) {
			m_player->set_position(ENEMY0_BASE_X + 0.25*(BASE_WIDTH-PLAYER_WIDTH), ENEMY0_BASE_Y + 65);
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
	else if (mouse_pos->get_x() > ENEMY1_BASE_X && mouse_pos->get_x() < ENEMY1_BASE_X+ BASE_WIDTH && mouse_pos->get_y() > ENEMY1_BASE_Y&& mouse_pos->get_y() < ENEMY1_BASE_Y+ BASE_HEIGHT && Input_handle::instance()->get_mouse_state(LEFT) == true&&m_enemy[1]->get_strength()>0&&m_player->get_strength()!=0) {
			if (m_enemy[1] != nullptr) {
				m_player->set_position(ENEMY1_BASE_X+ 0.25 * (BASE_WIDTH - PLAYER_WIDTH), ENEMY1_BASE_Y+65);
				if (m_player->get_strength() > m_enemy[1]->get_strength()) {
					m_player->change_strength(m_enemy[1]->get_strength(), '+');
					m_enemy[1]->set_strength_to_zero();
					m_enemy[1]->change_texture("enemy_death"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
					m_player->change_texture("player_attack"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
					m_player->set_attack(true);
				}
				else {
					m_player->set_strength_to_zero();
					m_player->change_texture("player_death"s, PLAYER_WIDTH, PLAYER_HEIGHT, SDL_FLIP_NONE);
					m_enemy[1]->change_texture("enemy_attack"s, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL);
					m_enemy[1]->set_attack(true);
				}
			}
		}
	if (m_player->get_strength() == 0&& frame_check_defeat()) {
		SDL_Delay(500);
		game::instance()->get_game_state_manager()->replace(new Game_over);
	}
	else if (enemy_count == count_defeated() && frame_check_victory()) {
		SDL_Delay(500);
		game::instance()->get_game_state_manager()->replace(new Victory);
	}
}

void Level1::render()
{
	Uint32 start_time{};
	Uint32 frame_time{};
	for (int i = 0; i < m_object.size(); i++) {
		if (!m_exit && m_object[i] != nullptr)  m_object[i]->draw();
		else return;
	}
	if (!m_exit&&m_player != nullptr)
	{
		m_player->draw();
		m_player->strength_to_text(PLAYER_BASE_X+50, PLAYER_BASE_Y+15);
		if (m_player->get_strength() != 0&&!m_player->get_attack()) {
			m_player->set_current_frame((int)((SDL_GetTicks() / 100) % (PLAYER_IDLE_MAX_FRAME-1)));
		}
		else if (m_player->get_strength() != 0 && m_player->get_attack()){
			if (m_player->get_current_frame() < PLAYER_ATTACK_MAX_FRAME-1) {
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
		else if (m_player->get_strength() == 0 && m_player->get_current_frame() <PLAYER_DEATH_MAX_FRAME-1 && !m_enemy[0]->get_attack() && !m_enemy[1]->get_attack()) {
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
		m_enemy[0]->strength_to_text(ENEMY0_BASE_X+50, ENEMY0_BASE_Y+15);
		if (m_enemy[0]->get_strength() != 0 && !m_enemy[0]->get_attack()) {
			m_enemy[0]->set_current_frame((int)((SDL_GetTicks() / 100) % (ENEMY_DEFAULT_MAX_FRAME-1)));
		}
		if (m_enemy[0]->get_strength() == 0 && m_enemy[0]->get_current_frame() < ENEMY_DEATH_MAX_FRAME-1&&!m_player->get_attack()) {
			int frame = m_enemy[0]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[0]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else if (m_enemy[0]->get_attack() && m_enemy[0]->get_current_frame() < ENEMY_ATTACK_MAX_FRAME-1) {
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
		m_enemy[1]->strength_to_text(ENEMY1_BASE_X+50, ENEMY1_BASE_Y+15);
		if (m_enemy[1]->get_strength() != 0 && !m_enemy[1]->get_attack()) {
			m_enemy[1]->set_current_frame((int)((SDL_GetTicks() / 100) % (ENEMY_DEFAULT_MAX_FRAME-1)));
		}
		if (m_enemy[1]->get_strength() == 0&&m_enemy[1]->get_current_frame()<ENEMY_DEATH_MAX_FRAME-1&&!m_player->get_attack()) {
			int frame = m_enemy[1]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time >100) {
				frame++;
				m_enemy[1]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else if (m_enemy[1]->get_attack() && m_enemy[1]->get_current_frame() < ENEMY_ATTACK_MAX_FRAME-1) {
			int frame = m_enemy[1]->get_current_frame();
			frame_time = SDL_GetTicks() - start_time;
			start_time = SDL_GetTicks();
			if (frame_time > 100) {
				frame++;
				m_enemy[1]->set_current_frame(frame);
				SDL_Delay(100);
			}
		}
		else m_enemy[1]->set_attack(false);
	}
	else return;
}

bool Level1::on_start()
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

	m_object.push_back(new Game_object("game_play_background"s, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	m_object.push_back(new Menu_button("replay"s, WINDOW_WIDTH*0.02, WINDOW_HEIGHT*0.02, REPLAY_WIDTH, REPLAY_HEIGHT, replay));
	m_object.push_back(new Menu_button("to_level_list"s, WINDOW_WIDTH*0.1, WINDOW_HEIGHT*0.02, TO_LEVEL_LIST_WIDTH, TO_LEVEL_LIST_HEIGHT, to_level_list));
	m_object.push_back(new Game_object("roof"s, PLAYER_BASE_X, PLAYER_BASE_Y, BASE_WIDTH,BASE_HEIGHT));//player's base
	m_object.push_back(new Game_object("base"s, ENEMY0_BASE_X, ENEMY0_BASE_Y, BASE_WIDTH,BASE_HEIGHT));//enemy0's base
	m_object.push_back(new Game_object("base"s, ENEMY1_BASE_X, ENEMY1_BASE_Y, BASE_WIDTH,BASE_HEIGHT));//enemy1's base
	m_player=new Player("player_idle"s,PLAYER_STRENGTH, PLAYER_BASE_X+0.5*(BASE_WIDTH - PLAYER_WIDTH), PLAYER_BASE_Y + 68, PLAYER_WIDTH, PLAYER_HEIGHT);
	m_enemy.push_back(new Enemy("enemy_default"s, ENEMY0_STRENGTH, ENEMY0_BASE_X+0.5*(BASE_WIDTH-ENEMY_WIDTH), ENEMY0_BASE_Y + 68, ENEMY_WIDTH, ENEMY_HEIGHT, SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy0
	m_enemy.push_back(new Enemy("enemy_default"s, ENEMY1_STRENGTH, ENEMY1_BASE_X+ 0.5 * (BASE_WIDTH - ENEMY_WIDTH), ENEMY1_BASE_Y+68, ENEMY_WIDTH, ENEMY_HEIGHT,SDL_FLIP_HORIZONTAL)); enemy_count++;//enemy1
	m_exit= false;
	return true;
}

bool Level1::on_exit()
{
	clean();
	m_object.clear();

	Texture_manager::instance()->remove_from_texture_map("game_play_background"s);
	Texture_manager::instance()->remove_from_texture_map("replay"s);
	Texture_manager::instance()->remove_from_texture_map("to_level_list"s);
	Texture_manager::instance()->remove_from_texture_map("base"s);
	Texture_manager::instance()->remove_from_texture_map("roof"s);
	Texture_manager::instance()->remove_from_texture_map("player_idle"s);
	Texture_manager::instance()->remove_from_texture_map("enemy_default"s);
	Texture_manager::instance()->remove_from_texture_map("enemy_death"s);
	Texture_manager::instance()->remove_from_texture_map("player_attack"s);
	Texture_manager::instance()->remove_from_texture_map("player_death"s);
	Texture_manager::instance()->remove_from_texture_map("enemy_attack"s);
	m_exit = true;
	return true;
}

void Level1::replay()
{
	game::instance()->get_game_state_manager()->replace(new Level1);
}

void Level1::to_level_list()
{
	game::instance()->get_game_state_manager()->replace(new Level_list);
}

int Level1::count_defeated()
{
	int count{ 0 };
	for (int i = 0; i < m_enemy.size(); i++) {
		if (!m_exit && m_enemy[i] != nullptr) {
			if (m_enemy[i]->get_strength() == 0) count++;
		}
		else return -1;
	}
	return count;
}

bool Level1::frame_check_victory()
{
	if (count_defeated() == enemy_count) {
		for (auto p : m_enemy) {
			if (p->get_current_frame() != ENEMY_DEATH_MAX_FRAME-1) return false;
		}
		return true;
	}
}

bool Level1::frame_check_defeat()
{
	if (m_player->get_strength() == 0 && m_player->get_current_frame() >= PLAYER_DEATH_MAX_FRAME-1) return true;
	else return false;
}
