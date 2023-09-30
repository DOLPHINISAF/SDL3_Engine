#include "game.h"

Game* game = nullptr;


int main(int argc, char* argv[]) {

	game = new Game("Joculet", 1280, 720);

	while (game->getIsRunning()) {
		game->HandleEvents();
		game->Update();
		game->Render();
		
	}
	game->Close();

	return 0;
}