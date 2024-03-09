#include "game_over.h"
#include "texture_manager.h"
#include "game.h"
#include "menu_button.h"
#include "game_state_manager.h"
#include "const.h"

using namespace std::string_literals;

const std::string Game_over::m_state_ID{ "GAME_OVER"s };

void Game_over::clean()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (m_object[i] != nullptr)
		{
			delete m_object[i];
			m_object[i] = nullptr;
		}
	}
}

void Game_over::update()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (!m_exit && m_object.size() < 100 && m_object[i] != nullptr)  m_object[i]->update();
		else return;
	}
}

void Game_over::render()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (!m_exit && m_object[i] != nullptr)  m_object[i]->draw();
		else return;
	}
}

bool Game_over::on_start()
{
	m_exit = false;
	Texture_manager::instance()->load("pic/game_over_background.png"s, "game_over_background"s,game::instance()->get_renderer());
	Texture_manager::instance()->load("pic/to_level_list.png"s, "to_level_list"s, game::instance()->get_renderer());
	Texture_manager::instance()->create_texture_from_string("GAME OVER"s, "game_over"s, 224, 103, 66,255, 2, game::instance()->get_renderer());
	m_object.push_back(new Game_object("game_over_background"s, 0, 0, 1280, 720));
	m_object.push_back(new Menu_button("to_level_list"s, WINDOW_WIDTH*0.45, WINDOW_HEIGHT*0.45, 84, 84, to_level_list));
	m_object.push_back(new Game_object("game_over"s, 410, 150, Texture_manager::instance()->get_text_width("game_over"s), Texture_manager::instance()->get_text_height("game_over"s)));
	return true;
}

bool Game_over::on_exit()
{
	m_exit = true;
	clean();
	m_object.clear();
	Texture_manager::instance()->remove_from_texture_map("game_over_background"s);
	Texture_manager::instance()->remove_from_texture_map("to_level_list"s);
	Texture_manager::instance()->remove_from_texture_map("game_over"s);
	return true;
}

void Game_over::to_level_list()
{
	game::instance()->get_game_state_manager()->replace(new Level_list);
}
