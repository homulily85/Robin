#include "player.h"
#include "texture_manager.h"
#include "game.h"

using namespace std::string_literals;

void Player::update()
{
	//Update something here
	/*Vector2D* target = Input_handle::instance()->get_mouse_position();
	m_velocity = *target - m_position;
	m_position += m_velocity / 50;*/
	//m_current_frame = (SDL_GetTicks() / 100) % 8;
}

void Player::change_strength(int strength, char ope)
{
	switch (ope)
	{
		case '+':
			m_strength += strength;
			break;
		case '-':
			m_strength -= strength;
			break;
		case '*':
			m_strength *= strength;
			break;
		case '/':
			m_strength /= strength;
			break;
		default:
			break;
	}
}

void Player::strength_to_text(int x, int y)
{
	std::string temp = std::to_string(m_strength);
	if (Texture_manager::instance()->is_texture_in_map("player_strength"s))
	{
		Texture_manager::instance()->remove_from_texture_map("player_strength"s);
	}
	if (m_strength==0) 	Texture_manager::instance()->create_texture_from_string(temp, "player_strength"s, 255, 248, 165, 0, 1, game::instance()->get_renderer());
	else Texture_manager::instance()->create_texture_from_string(temp,"player_strength"s, 255,248,165,255,1,game::instance()->get_renderer());
	Texture_manager::instance()->draw("player_strength"s, x, y, Texture_manager::instance()->get_text_width("player_strength"s), Texture_manager::instance()->get_text_height("player_strength"s), game::instance()->get_renderer());
}
