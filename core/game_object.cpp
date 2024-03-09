#include "game_object.h"
#include "game.h"
void Game_object::load(std::string texture_id, int x, int y, int w, int h, SDL_RendererFlip flip)
{
	m_texture_id = texture_id;
	m_position.set_x(x);
	m_position.set_y(y);
	m_w = w;
	m_h = h;
	m_flip = flip;
}

void Game_object::draw()
{
	Texture_manager::instance()->draw_frame(m_texture_id, static_cast<double>(m_position.get_x()), static_cast<double>(m_position.get_y()), m_w, m_h, m_current_row, m_current_frame, game::instance()->get_renderer(), m_flip);
}

