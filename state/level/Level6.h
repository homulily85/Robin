#ifndef LEVEL6_H
#define LEVEL6_H

#include "game_state.h"
#include "game_object.h"
#include "player.h"
#include "enemy.h"
#include <vector>
#include "game.h"
class Level6 :public Game_state
{
public:
	Level6() :Game_state() { game::instance()->get_log_file() << "Entered Level 6\n"; }
	~Level6() {  game::instance()->get_log_file() << "Exited Level 6\n"; }
	void clean();
	virtual void update();
	virtual void render();
	virtual bool on_start();
	virtual bool on_exit();
	virtual std::string get_state_ID() { return m_state_ID; }
private:
	static const std::string m_state_ID;
	std::vector <Game_object*> m_object{};
	static void replay();
	static void to_level_list();
	Player* m_player{};
	std::vector <Enemy*> m_enemy{};
	int enemy_count{ 0 };
	int count_defeated();
	bool is_tower_destroyed(int start_enemy_index, int end_enemy_index);
};

#endif // !LEVEL6_H
