#include "game.h"
int GetCLIArgs(int argc, char* argv[]);

Game* game = nullptr;

int main(int argc, char* argv[]) {

	

	
	//we instantiate the game obj, init everything
	game = new Game("Joculet", 1280, 720, GetCLIArgs(argc, argv));


	while (game->getIsRunning()) {

		game->HandleEvents();
		game->Update();
		game->Render();

		
	}
	game->Close();
	
	return 0;
}

int GetCLIArgs(int argc, char* argv[]) {
	int flags = 0;
	if (argc > 1)
		for (int i = 0; i < argc; i++) {
			if (*argv[i] == 'h') {
				flags = flags | GAME_HELP;
				return 2;
			}
			if (*argv[i] == 'L') {
				flags = flags |GAME_LOG;
				std::cout << "LOGGING ENABLED !!!!" << "\n\n";
			}
			if (*argv[i] == 'F') {
				flags = flags | GAME_FPS_DRAW;
			}
		}
	return flags;
}
