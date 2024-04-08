#include "level_list.h"
#include <iostream>
#include "game.h"
#include "menu_button.h"
#include "level.h"
#include "input_handle.h"
#include "const.h"

using namespace std::string_literals;

const std::string Level_list::m_state_ID{ "LEVEL_LIST"s };

void Level_list::clean()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (m_object[i] != nullptr) {
			delete m_object[i];
			m_object[i] = nullptr;
		}
	}
}

void Level_list::update()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (!m_exit &&m_object.size()<100 && m_object[i] != nullptr)  m_object[i]->update();
		else return;
	}

}

void Level_list::render()
{
	{
		for (int i = 0; i < m_object.size(); i++) {
			if (!m_exit && m_object[i] != nullptr)  m_object[i]->draw();
			else return;
		}
	}
}

bool Level_list::on_start()
{
	if (!Texture_manager::instance()->load("pic/level_list_background.png"s, "background"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/back_button.png"s, "back_button"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/level_icon.png"s, "level_icon"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/level_lock.png"s, "level_lock"s, game::instance()->get_renderer())) return false;

	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= 5; j++) {
			if ((i - 1) * 5 + j <= 9) {
				if (!Texture_manager::instance()->create_texture_from_string(std::to_string(j + 5 * (i - 1)), "level"s + std::to_string(j + 5 * (i - 1)), 255, 248, 165, 255, 0, game::instance()->get_renderer())) return false;
			}
		}
	}
	m_object.push_back(new Game_object("background"s, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	m_object.push_back(new Menu_button("back_button"s, WINDOW_WIDTH * 0.05, WINDOW_HEIGHT * 0.88, 84, 84, exit_to_menu));
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 5; j++) {
			if ((i - 1) * 5 + j <= 9)
			{
				m_object.push_back(new Menu_button("level_icon"s, WINDOW_WIDTH * 0.22 + WINDOW_WIDTH * 0.12 * (j - 1), WINDOW_HEIGHT * 0.1 + WINDOW_HEIGHT * 0.2 * (i - 1), 90, 105, level_list_to_play));
				if (j + 5 * (i - 1) < 10) m_object.push_back(new Game_object("level"s + std::to_string(j + 5 * (i - 1)), WINDOW_WIDTH * 0.24 + WINDOW_WIDTH * 0.12 * (j - 1), WINDOW_HEIGHT * 0.11 + WINDOW_HEIGHT * 0.2 * (i - 1), Texture_manager::instance()->get_text_width("level"s + std::to_string(j + 5 * (i - 1))), Texture_manager::instance()->get_text_height("level"s + std::to_string(j + 5 * (i - 1)))));
				else m_object.push_back(new Game_object("level"s + std::to_string(j + 5 * (i - 1)), WINDOW_WIDTH * 0.23 + WINDOW_WIDTH * 0.12 * (j - 1), WINDOW_HEIGHT * 0.11 + WINDOW_HEIGHT * 0.2 * (i - 1), Texture_manager::instance()->get_text_width("level"s + std::to_string(j + 5 * (i - 1))), Texture_manager::instance()->get_text_height("level"s + std::to_string(j + 5 * (i - 1)))));
			}
			else {
				m_object.push_back(new Menu_button("level_lock"s, WINDOW_WIDTH * 0.22 + WINDOW_WIDTH * 0.12 * (j - 1), WINDOW_HEIGHT * 0.1 + WINDOW_HEIGHT * 0.2 * (i - 1), 90, 105, level_list_to_play));
			}
		}
	}
	m_exit = false;
	return true;
}

bool Level_list::on_exit()
{
	m_exit = true;
	clean();
	m_object.clear();
	Texture_manager::instance()->remove_from_texture_map("background"s);
	Texture_manager::instance()->remove_from_texture_map("back_button"s);
	Texture_manager::instance()->remove_from_texture_map("level_icon"s);
	Texture_manager::instance()->remove_from_texture_map("level_lock"s);
	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= 5; j++) {
			Texture_manager::instance()->remove_from_texture_map("level"s + std::to_string(j + 8 * (i - 1)));
		}
	}
	return true;
}

void Level_list::level_list_to_play()
{
	int level_number{};

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 5; j++) {
			if (Input_handle::instance()->get_mouse_position()->get_x() > WINDOW_WIDTH * 0.22 + WINDOW_WIDTH * 0.12 * (j - 1) && Input_handle::instance()->get_mouse_position()->get_x() < WINDOW_WIDTH * 0.22 + WINDOW_WIDTH * 0.12 * (j - 1) + 90
				&& Input_handle::instance()->get_mouse_position()->get_y() > WINDOW_HEIGHT * 0.1 + WINDOW_HEIGHT * 0.2 * (i - 1) && Input_handle::instance()->get_mouse_position()->get_y() < WINDOW_HEIGHT * 0.1 + WINDOW_HEIGHT * 0.2 * (i - 1) + 105)
			{
				level_number = j + 5 * (i - 1);
				break;
			}
		}
	}

	switch (level_number)
	{
	case 1:
		game::instance()->get_game_state_manager()->replace(new Level1);
		break;
	case 2:
		game::instance()->get_game_state_manager()->replace(new Level2);
		break;
	case 3:
		game::instance()->get_game_state_manager()->replace(new Level3);
		break;
	case 4:
		game::instance()->get_game_state_manager()->replace(new Level4);
		break;
	case 5:
		game::instance()->get_game_state_manager()->replace(new Level5);
		break;
	case 6:
		game::instance()->get_game_state_manager()->replace(new Level6);
		break;
	case 7:
		game::instance()->get_game_state_manager()->replace(new Level7);
		break;
	case 8:
		game::instance()->get_game_state_manager()->replace(new Level8);
		break;
	case 9:
		game::instance()->get_game_state_manager()->replace(new Level9);
		break;
	/*case 10:
		game::instance()->get_game_state_manager()->replace(new Level10);
		break;*/
	/*case 11:
		game::instance()->get_game_state_manager()->replace(new Level11);
		break;*/
	/*case 12:
		game::instance()->get_game_state_manager()->replace(new Level12);
		break;*/
	/*case 13:
		game::instance()->get_game_state_manager()->replace(new Level13);
		break;*/
	/*case 14:
		game::instance()->get_game_state_manager()->replace(new Level14);
		break;*/
	/*case 15:
		game::instance()->get_game_state_manager()->replace(new Level15);
		break;*/
	/*case 16:
		game::instance()->get_game_state_manager()->replace(new Level16);
		break;*/
	/*case 17:
		game::instance()->get_game_state_manager()->replace(new Level17);
		break;*/
	/*case 18:
		game::instance()->get_game_state_manager()->replace(new Level18);
		break;*/
	/*case 19:
		game::instance()->get_game_state_manager()->replace(new Level19);
		break;*/
	/*case 20:
		game::instance()->get_game_state_manager()->replace(new Level20);
		break;*/
	default:
		break;
	}
}

void Level_list::exit_to_menu()
{
	game::instance()->get_game_state_manager()->replace(new Menu_state);
}
