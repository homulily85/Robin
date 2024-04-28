#ifndef ENEMY_H
#define ENEMY_H

#include "game_object.h"

class Enemy :public Game_object 
{
public:
	//Load texture information into a Enemy object.
	//Parameters:
	//texture_id: id of texture
	//x,y: Initial position of the texture
	//w,h: size of the texture
	//flip: flip type (SDL_FLIP_NONE by default)
	Enemy(const std::string& texture_id, int strength, int x, int y, int w, int h, SDL_RendererFlip flip = SDL_FLIP_NONE) :Game_object(texture_id, x, y, w, h, flip), m_strength{ strength },m_enemy_id{ enemy_id++ } { }
	Enemy() :Game_object(), m_enemy_id{enemy_id++} {}
	~Enemy() {m_enemy_id = 0; }
	//Update object state
	void update() override;
	int get_strength() const { return m_strength; }
	void strength_to_text(int x, int y,std::string ope,bool is_buff=false);
	void set_strength_to_zero() { m_strength = 0; }
	void set_strength_to_one() { m_strength = 1; }
	bool get_attack() const { return m_attack; }
	void set_attack(bool attack) { m_attack = attack; }
private:
	static int enemy_id;
	int m_enemy_id{ 0 };
	int m_strength{0};
	bool m_attack{ false };
};

#endif // !ENEMY_H
