#ifndef VICTORY_H
#define VICTORY_H

#include "game_state.h"
#include "game_object.h"
#include <vector>
#include "game.h"
class Victory : public Game_state
{
public:
	Victory() :Game_state() { game::instance()->get_log_file() << "Entered Victory\n"; }
	~Victory() { game::instance()->get_log_file() << "Exited Victory\n"; }
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

#endif // !VICTORY_H
