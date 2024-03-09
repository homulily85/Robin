#include "game.h"
#include "const.h"

#undef main
int main(int argc, char* args[]) {
	Uint32 start_time{};
	Uint32 frame_time{};
	if (!game::instance()->init("Robin", WINDOW_WIDTH, WINDOW_HEIGHT)) return 0;
	while (game::instance()->is_running())
	{
		start_time = SDL_GetTicks();
		game::instance()->handle_events();
		game::instance()->render();
		game::instance()->update();
		
		//Create fixed FPS
		frame_time = SDL_GetTicks() - start_time;
		if (frame_time < DELAY_TIME) {
			SDL_Delay(DELAY_TIME - frame_time);
		}
	}
	game::instance()->clean_up();
	return 0;
}