#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "game_state.h"
#include "game_object.h"
#include <vector>

class Game_over: public Game_state
{
public:
	Game_over()=default;
	~Game_over() { clean(); }
	void clean();
	virtual void update();
	virtual void render();
	virtual bool on_start();
	virtual bool on_exit();
	virtual std::string get_state_ID() { return m_state_ID; }

private:
	static const std::string m_state_ID;
	std::vector <Game_object*> m_object{};
	static void to_level_list();
};

#endif // !GAME_OVER_H
