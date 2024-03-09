#ifndef INPUT_HANDLE_H
#define	INPUT_HANDLE_H

#include <SDL.h>
#include <array>
#include "vector2D.h"

enum mouse_button
{
	LEFT,
	MIDDLE,
	RIGHT,
};

class Input_handle
{
public:
	static Input_handle* instance();
	~Input_handle() { if (m_instance != nullptr) delete m_instance; }
	void update();
	bool get_mouse_state(int button) { return m_mouse_state[button]; }
	Vector2D* get_mouse_position() { return m_mouse_position; }
	
private:
	//Make Input_handle singleton
	Input_handle() {}
	static Input_handle* m_instance;

	//Handling mouse input
	void on_mouse_move();
	void on_mouse_button_up();
	void on_mouse_button_down();
	SDL_Event m_event;

	std::array<bool, 3> m_mouse_state{};
	Vector2D* m_mouse_position{ new Vector2D };
};

#endif // !INPUT_HANDLE_H
