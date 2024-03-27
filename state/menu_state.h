#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "game_state.h"
#include "game_object.h"
#include <vector>

class Menu_state :public Game_state
{
public:
	Menu_state()=default;
	~Menu_state() {  }
	void clean();
	virtual void update();
	virtual void render();
	virtual bool on_start();
	virtual bool on_exit();
	virtual std::string get_state_ID() { return m_state_ID; }
private:
	static const std::string m_state_ID;
	std::vector <Game_object*> m_object{};
	static void menu_to_level_list();
	static void exit_from_menu();
};

#endif // !MENU_STATE_H
