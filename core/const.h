#ifndef CONST_H
#define CONST_H	

inline const int WINDOW_WIDTH{ 1280 };
inline const int WINDOW_HEIGHT{ 720 };

constexpr int BASE_WIDTH{ 130 };
constexpr int BASE_HEIGHT{ 130 };

constexpr int PLAYER_WIDTH{ 78 };
constexpr int PLAYER_HEIGHT{ 58 };

constexpr int ENEMY_WIDTH{ 80 };
constexpr int ENEMY_HEIGHT{ 64 };

constexpr int BUFF_WIDTH{ 19 };
constexpr int BUFF_HEIGHT{ 67 };

constexpr int DEBUFF_WIDTH{ 32 };
constexpr int DEBUFF_HEIGHT{ 32 };

constexpr int REPLAY_WIDTH{ 84 };
constexpr int REPLAY_HEIGHT{ 84 };

constexpr int TO_LEVEL_LIST_WIDTH{ 84 };
constexpr int TO_LEVEL_LIST_HEIGHT{ 84 };

constexpr int PLAYER_Y_SCALE{ 68 };
constexpr int ENEMY_Y_SCALE{ 68 };
constexpr int BUFF_Y_SCALE{ 45 };
constexpr int DEBUFF_Y_SCALE{ 85 };

constexpr int ENEMY_DEFAULT_MAX_FRAME{ 4 };
constexpr int ENEMY_ATTACK_MAX_FRAME{ 8 };
constexpr int ENEMY_DEATH_MAX_FRAME{ 5 };

constexpr int PLAYER_IDLE_MAX_FRAME{ 11 };
constexpr int PLAYER_ATTACK_MAX_FRAME{ 3 };
constexpr int PLAYER_DEATH_MAX_FRAME{ 4 };
#endif // !CONST_H
