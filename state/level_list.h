#ifndef LEVEL_LIST_H
#define LEVEL_LIST_H

#include "game_state.h"
#include "game_object.h"
#include <vector>
#include "game.h"
class Level_list:public Game_state
{
public:
	Level_list() = default;
	~Level_list() { clean(); }
	void clean();
	virtual void update();
	virtual void render();
	virtual bool on_start();
	virtual bool on_exit();
	virtual std::string get_state_ID() { return m_state_ID; }
private:
	static const std::string m_state_ID;
	std::vector <Game_object*> m_object{};
	static void level_list_to_play();
	static void exit_to_menu();
	bool m_is_running {false};
};

#endif // !LEVEL_LIST_H
