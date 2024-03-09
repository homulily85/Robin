#ifndef LEVEL2_H
#define LEVEL2_H

#include "game_state.h"
#include "game_object.h"
#include "player.h"
#include "enemy.h"
#include <vector>

class Level2 :public Game_state
{
public:
	Level2() = default;
	~Level2() { clean(); }
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

#endif // !LEVEL2_H
