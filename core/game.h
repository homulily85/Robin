#ifndef GAME_H
#define GAME_H

#include "game_state_manager.h"
#include "input_handle.h"
#include "menu_state.h"
#include "texture_manager.h"
#include "level_list.h"
#include <array>
#include <SDL.h>
#include <SDL_ttf.h>
#include <fstream>
using namespace std::string_literals;

class game
{
public:
	//This function is used to initialize game object.
	//You need to call this function whenever you want to access game member function.
	static game* instance();	
	~game() { clean_up(); }
	//Initialize SDL and create a window.
	//Parameters:
	//name: window's name
	//width, height: width, height of the window
	//is_full_screen: true to make window full_screen, false for not (false by default).
	//xpos, ypos: position of window (SDL_WINDOWPOS_UNDEFINED by default)
	//flag: SDL window flag (SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE by default) 
	bool init(const char* name, int width, int heigth,bool is_full_sceen=false, int xpos=SDL_WINDOWPOS_UNDEFINED, int ypos=SDL_WINDOWPOS_UNDEFINED, int flags=SDL_WINDOW_SHOWN);
	//Render texture to screen
	void render();
	//Update game status
	void update();
	//Handle event
	void handle_events();
	//Clean up resource
	void clean_up();
	//Check if game is running
	bool is_running() const { return m_is_running; }
	//Get SDL_Render
	SDL_Renderer* get_renderer() { return m_renderer; }
	void quit() { m_is_running = false; }
	Game_state_manager* get_game_state_manager() { return m_game_state_machine; }
	bool m_is_paused{ false };
	std::ofstream& get_log_file() { return m_log_file; }
	bool is_all_level_before_cleared(int level);
	bool is_level_cleared(int level) { return m_level_cleared[level - 1]; }
	void set_level_cleared(int level) { m_level_cleared[level-1] = true; }
private:
	//Ensure that game object can be initialized only once
	game() {}
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{};
	int m_current_frame{};
	bool m_is_running{ false };
	static game* m_instance;
	Game_state_manager* m_game_state_machine{ nullptr };
	std::ofstream m_log_file{"log.txt"};
	std::array<bool, 10> m_level_cleared{};
	SDL_RWops* m_file{ nullptr };
};

#endif // !GAME_H
