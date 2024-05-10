#include "game.h"
#include "SDL_ttf.h"
game* game::m_instance{};
game* game::instance()
{
    if (m_instance == nullptr) {
        m_instance = new game();
    }
    return m_instance;
}

bool game::init(const char* name, int width, int height, bool is_full_screen, int xpos, int ypos, int flags)
{
    try
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			throw std::exception();
		}
    }
    catch (const std::exception)
    {
        m_log_file << "Error: " <<SDL_GetError() << '\n';
		return false;
    }
    
    if (is_full_screen) {
        flags = flags | SDL_WINDOW_FULLSCREEN;
    }
    try {
		m_window = SDL_CreateWindow(name, xpos, ypos, width, height, flags);
		if (m_window == nullptr) {
			throw std::exception();
		}
	}
	catch (const std::exception)
	{
		m_log_file << "Error: " <<SDL_GetError() << '\n';
		return false;
	}
    
    try {
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (m_renderer == nullptr) {
			throw std::exception();
		}
    }
    catch (const std::exception)
    {
        m_log_file << "Error: " << SDL_GetError() << '\n';
        return false;
    }

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
    try
    {
        if (TTF_Init() == -1) {
			throw std::exception();
		}
    }
    catch (const std::exception&)
    {
        m_log_file << TTF_GetError() << '\n';
        return false;
    }
    try
    {
		m_file = SDL_RWFromFile("level.dat", "r+b");
        if (m_file == nullptr) throw - 1;
        for (int i = 0; i < 10; i++) {
			SDL_RWread(m_file, &m_level_cleared[i], sizeof(bool), 1);
        }
		SDL_RWclose(m_file);
		for (int i = 0; i < 10; i++) {
			m_log_file << "Level " << i+1 << " cleared: " << m_level_cleared[i] << '\n';
		}
    }
    catch (int)
    {
		m_file = SDL_RWFromFile("level.dat", "w+b");
		if (m_file == nullptr) {
			m_log_file << "Error: " << SDL_GetError() << '\n';
			return false;
		}
        for (int i = 0; i < 10; i++) {
			m_level_cleared[i] = false;
			SDL_RWwrite(m_file, &m_level_cleared[i], sizeof(bool), 1);
        }
		SDL_RWclose(m_file);
    }
    //Initialize something here
    m_game_state_machine = new Game_state_manager;
    m_game_state_machine->push(new Menu_state);
    m_is_running = true;
    return true;
}

void game::render()
{
    SDL_RenderClear(m_renderer);
    m_game_state_machine->render();
    SDL_RenderPresent(m_renderer);
}

void game::update()
{
    m_game_state_machine->update();
}

void game::handle_events()
{
    Input_handle::instance()->update();
}

void game::clean_up()
{
	m_file = SDL_RWFromFile("level.dat", "w+b");
    for (int i = 0; i < 10; i++) {
        SDL_RWwrite(m_file, &m_level_cleared[i], sizeof(bool), 1);
    }
	SDL_RWclose(m_file);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    TTF_Quit();
    m_log_file << "Game cleaned up successfully\n";
    m_log_file.close();
}

bool game::is_all_level_before_cleared(int level)
{
   /* level--;
	for (int i = 0; i < level; i++) {
		if (!m_level_cleared[i]) return false;
	}*/
    return true;
}
