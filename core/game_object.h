#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "texture_manager.h"
#include "vector2D.h"

class Game_object
{
public:
	//Load texture information into a game object.
	//Parameters:
	//texture_id: id of texture
	//x,y: Initial position of the texture
	//w,h: size of the texture
	//flip: flip type (SDL_FLIP_NONE by default)
	Game_object(std::string texture_id, int x, int y, int w, int h, SDL_RendererFlip flip = SDL_FLIP_NONE) : m_position{ static_cast<double>(x),static_cast<double>(y)}, m_texture_id{texture_id}, m_w{w}, m_h{h}, m_flip{flip} {}
	Game_object() = default;
	virtual ~Game_object() = default;
	//Load texture information into a game object.
	//Parameters:
	//texture_id: id of texture
	//x,y: Initial position of the texture
	//w,h: size of the texture
	//flip: flip type (SDL_FLIP_NONE by default)
	void load(std::string texture_id, int x, int y, int w, int h, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//Draw texture using texture_manager
	void draw();
	//Update object state
	virtual void update() {}
	virtual void clean()  {}
	void set_current_frame(int frame) { m_current_frame = frame; }
	void set_position(int x, int y) { m_position.set_x(x); m_position.set_y(y); }
protected:
	std::string m_texture_id{};
	SDL_RendererFlip m_flip{ SDL_FLIP_NONE };
	
	int m_current_row{ 1 };
	int m_current_frame{ 0 };

	Vector2D m_position{};
	Vector2D m_velocity{};
	Vector2D m_acceleration{};

	int m_w{};
	int m_h{};
};

#endif // !GAME_OBJECT_H
