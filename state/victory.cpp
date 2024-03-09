#include "victory.h"
#include "texture_manager.h"
#include "game.h"
#include "menu_button.h"
#include "game_state_manager.h"
#include "const.h"

using namespace std::string_literals;

const std::string Victory::m_state_ID{ "VICTORY"s };

void Victory::clean()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (m_object[i] != nullptr)
		{
			delete m_object[i];
			m_object[i] = nullptr;
		}
	}
}

void Victory::update()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (!m_exit && m_object.size() < 100 && m_object[i] != nullptr)  m_object[i]->update();
		else return;
	}
}

void Victory::render()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (!m_exit && m_object[i] != nullptr)  m_object[i]->draw();
		else return;
	}
}

bool Victory::on_start()
{
	m_exit = false;
	Texture_manager::instance()->load("pic/victory_background.png"s, "victory_background"s, game::instance()->get_renderer());
	Texture_manager::instance()->load("pic/to_level_list.png"s, "to_level_list"s, game::instance()->get_renderer());
	Texture_manager::instance()->create_texture_from_string("VICTORY"s, "victory"s, 230, 240, 72,255, 2, game::instance()->get_renderer());
	m_object.push_back(new Game_object("victory_background"s, 0, 0, 1280, 720));
	m_object.push_back(new Menu_button("to_level_list"s, WINDOW_WIDTH*0.45, WINDOW_HEIGHT*0.45, 84, 84, to_level_list));
	m_object.push_back(new Game_object("victory"s, 470, 150, Texture_manager::instance()->get_text_width("victory"s), Texture_manager::instance()->get_text_height("victory"s)));
	return true;
}	

bool Victory::on_exit()
{
	m_exit = true;
	clean();
	m_object.clear();
	Texture_manager::instance()->remove_from_texture_map("victory_background"s);
	Texture_manager::instance()->remove_from_texture_map("to_level_list"s);
	Texture_manager::instance()->remove_from_texture_map("victory"s);
	return true;
}

void Victory::to_level_list()
{
	game::instance()->get_game_state_manager()->replace(new Level_list);
}