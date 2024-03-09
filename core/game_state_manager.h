#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "game_state.h"
#include <vector>

class Game_state_manager
{
public:
	Game_state_manager()=default;
	~Game_state_manager();
	//Add new state on top of current one
	void push(Game_state* state);
	//Replace current state
	void replace(Game_state* state);
	//Reset current state
	void pop();
	//Render current state
	void render();
	//Update current state
	void update();
	Game_state* get_current_game_state() { return m_game_state.back(); }
private:
	std::vector<Game_state*> m_game_state{};
};

#endif // !GAME_STATE_MANAGER_H
