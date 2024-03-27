#include "menu_state.h"
#include <iostream>
#include "game.h"
#include "menu_button.h"
#include "const.h"

using namespace std::string_literals;

const std::string Menu_state::m_state_ID{ "MENU"s };

void Menu_state::clean()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (m_object[i] != nullptr) delete m_object[i];
	}
}

void Menu_state::update()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (!m_exit && m_object[i] != nullptr && m_object.size() < 100)  m_object[i]->update();
		else return;
 	}
}

void Menu_state::render()
{
	for (int i = 0; i < m_object.size(); i++) {
		if (!m_exit && m_object[i] != nullptr)  m_object[i]->draw();
		else return;
	}
}

bool Menu_state::on_start()
{	
	if (!Texture_manager::instance()->load("pic/main_menu_background.png"s, "main_menu"s, game::instance()->get_renderer())) return false;
	if (!Texture_manager::instance()->load("pic/play_button.png"s, "play_button"s, game::instance()->get_renderer())) return false;

	m_object.push_back(new Game_object("main_menu"s, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	m_object.push_back(new Menu_button("play_button"s, WINDOW_WIDTH*0.5-192/2,WINDOW_HEIGHT*0.6-84, 196, 84,menu_to_level_list));
	m_exit=false;
	return true;
}

bool Menu_state::on_exit()
{
	clean();
	m_object.clear();
	Texture_manager::instance()->remove_from_texture_map("main_menu"s);
	Texture_manager::instance()->remove_from_texture_map("play_button"s);
	m_exit = true;	
	return true;
}

void Menu_state::menu_to_level_list()
{
	game::instance()->get_game_state_manager()->replace(new Level_list);
}

void Menu_state::exit_from_menu()
{
	game::instance()->quit();
}



