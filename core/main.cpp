#include "game.h"
#include "const.h"
#include <Windows.h>

int WINAPI WinMain(	HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	try {
		if (!game::instance()->init("Robin", WINDOW_WIDTH, WINDOW_HEIGHT)) throw -1;
	}
	catch (int) {
		exit(EXIT_FAILURE);
	}
	while (game::instance()->is_running())
	{
		game::instance()->handle_events();
		game::instance()->render();
		game::instance()->update();
	}
	game::instance()->clean_up();
	return 0;
}