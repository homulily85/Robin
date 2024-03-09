#include "menu_button.h"
#include "vector2D.h"
#include "input_handle.h"

using namespace std::string_literals;

void Menu_button::update()
{
	std::string temp = ""s;
	Vector2D* mouse_pos = Input_handle::instance()->get_mouse_position();
	if (mouse_pos->get_x() < m_position.get_x() || mouse_pos->get_x() > m_position.get_x() + m_w
		|| mouse_pos->get_y() < m_position.get_y() || mouse_pos->get_y() > m_position.get_y() + m_h) m_current_frame = MOVE_OUT;
	else {
		if (Input_handle::instance()->get_mouse_state(LEFT)&& m_is_released) {
			m_current_frame = CLICK;
			m_callback();
			m_is_released = false;
		}
		else if (!Input_handle::instance()->get_mouse_state(LEFT)) {
			m_is_released = true;
			m_current_frame = MOVE_OVER;
		}
	}
}