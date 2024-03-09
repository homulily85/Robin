#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>

class Game_state
{
public:
	Game_state() = default;
	virtual ~Game_state() = default;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool on_start() = 0;
	virtual bool on_exit() = 0;
	virtual std::string get_state_ID() = 0;
protected:
	bool m_exit{ false };

};

#endif // !GAME_STATE_H
