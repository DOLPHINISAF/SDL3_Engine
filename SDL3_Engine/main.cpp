#include "game.h"


Game* game = new Game("Joculet", 1280, 720);

int main(int argc, char* argv[]) {

	while (game->getIsRunning()) {
		game->HandleEvents();
		game->Update();
		game->Render();
		
	}


	return 0;
}