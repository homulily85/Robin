#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"
#include "input_handle.h"

class Player:public Game_object 
{
public:
	//Load texture information into a Player object.
	//Parameters:
	//texture_id: id of texture
	// strength: strength of the player
	//x,y: Initial position of the texture
	//w,h: size of the texture
	//flip: flip type (SDL_FLIP_NONE by default)
	Player(const std::string& texture_id, int strength, int x, int y, int w, int h, SDL_RendererFlip flip = SDL_FLIP_NONE) :Game_object(texture_id, x, y, w, h, flip), m_strength{ strength } {}
	Player():Game_object(){}
	~Player() = default;
	//Update object state
	void update() override;
	//Get strength of the player
	int get_strength() const { return m_strength; }
	void change_strength(int strength, char ope);
	void strength_to_text(int x, int y);
	void set_strength_to_zero() { m_strength = 0; }
	void set_attack(bool attack) { is_attack = attack; }
	bool get_attack() const { return is_attack; }
	double get_x() const { return m_position.get_x(); }
	double get_y() const { return m_position.get_y(); }
private:
	int m_strength{};
	bool is_attack{ false };
};

#endif // !PLAYER_H
