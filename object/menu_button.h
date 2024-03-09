#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "game_object.h"

class Menu_button:public Game_object
{
public:
	//Load texture. See Game_object for more information
	Menu_button(std::string texture_id, int x, int y, int w, int h, void (*callback)(),SDL_RendererFlip flip = SDL_FLIP_NONE) :Game_object(texture_id, x, y, w, h, flip), m_callback{ callback } {}
	~Menu_button() = default;
	void update();
private:
	enum button_state
	{
		MOVE_OUT,
		MOVE_OVER,
		CLICK,
	};
	//Using function pointer for function call back
	void(*m_callback)();
	bool m_is_released{ false };

};


#endif // !MENU_BUTTON_H
