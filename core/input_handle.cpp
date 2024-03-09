#include "input_handle.h"
#include "game.h"

Input_handle* Input_handle::m_instance{ nullptr };

Input_handle* Input_handle::instance()
{
    if (m_instance == nullptr) {
        m_instance = new Input_handle;
    }
    return m_instance;
}

void Input_handle::update()
{
    while (SDL_PollEvent(&m_event)>0) {
        switch (m_event.type)
        {
        case SDL_QUIT:
            game::instance()->quit();
            break;
        case SDL_MOUSEMOTION:
            on_mouse_move();
            break;
        case SDL_MOUSEBUTTONDOWN:
            on_mouse_button_down();
            break;
        case SDL_MOUSEBUTTONUP:
            on_mouse_button_up();
            break;
        }
    }

}
void Input_handle::on_mouse_move()
{
    if (m_event.type == SDL_MOUSEMOTION) {
        //get mouse x,y
        int x, y;
        SDL_GetMouseState(&x, &y);
        m_mouse_position->set_x(x);
        m_mouse_position->set_y(y);
    }
}

void Input_handle::on_mouse_button_up()
{
    switch (m_event.button.button)
    {
    case SDL_BUTTON_LEFT:
        m_mouse_state[LEFT] = false;
        break;
    case SDL_BUTTON_MIDDLE:
        m_mouse_state[MIDDLE] = false;
        break;
    case SDL_BUTTON_RIGHT:
        m_mouse_state[RIGHT] = false;
        break;
    default:
        break;
    }
    SDL_PumpEvents();
}

void Input_handle::on_mouse_button_down()
{
    switch (m_event.button.button)
    {
    case SDL_BUTTON_LEFT:
        m_mouse_state[LEFT] = true;
        break;
    case SDL_BUTTON_MIDDLE:
        m_mouse_state[MIDDLE] = true;
        break;
    case SDL_BUTTON_RIGHT:
        m_mouse_state[RIGHT] = true;
        break;
    default:
        break;
    }
}