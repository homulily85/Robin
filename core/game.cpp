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
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << SDL_GetError() << '\n';
        return false;
    }
    if (is_full_screen) {
        flags = flags | SDL_WINDOW_FULLSCREEN;
    }
    m_window = SDL_CreateWindow(name, xpos, ypos, width, height, flags);
    if (m_window == nullptr) {
        std::cout << SDL_GetError() << '\n';
        return false;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr) {
        std::cout << SDL_GetError() << '\n';
        return false;
    }
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
    if (TTF_Init() == -1) {
        std::cout << TTF_GetError() << '\n';
        return false;
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
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    TTF_Quit();
}
