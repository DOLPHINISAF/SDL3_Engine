#include "game.h"

Game::Game(const char title[], const int width, const int height, int flags) {

	GameFlags = flags;

	if (HandleFlags()) {

		//inits gdi for img loading
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		ticks = 0;
		ontime = 0;
		this->width = width;
		this->height = height;
		
		if (InitSDL(title))
			bisrunning = true;
		else
			bisrunning = false;

		InitBox2d();
		LoadAssets();

	}
	else {
		std::cout << "START FLAGS:\n";
		std::cout << "L - used to turn on logging in console\n";
		std::cout << "H - shows this menu\n";
	}
}
Game::~Game() {

	Close();
	
}

bool Game::HandleFlags() {
	islogging = GAME_LOG & GameFlags;

	bdrawfps = GAME_FPS_DRAW & GameFlags;

	return !(GAME_HELP & GameFlags);
}

bool Game::InitSDL(const char title[]) {


	//SDL getting intialised 100% correct
	if (!SDL_Init(SDL_INIT_EVERYTHING)) {
		
		LOG("SDL Initialised");

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);

		if (window) {
			LOG("Window initialised");

			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer) {
				LOG("Renderer Initialised");
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}
			else {
				LOG("Renderer failed to initialised!");
				return false;
			}

		}
		else {
			LOG("Window failed to initialise!");
			return false;
		}
	}
	else {
		LOG("SDL Failed to initialise!");
		return false;
	}
	
	
	
	return true;
}

void Game::InitBox2d() {

	gravity.Set(0.f, -gravity_force);

	world = new b2World(gravity);

}

void Game::LoadAssets() {

	player.Load("images/player.png", renderer, world, islogging);
	player.Set(10, 10, 4);

	floor.Load("images/floor.png", renderer, world, islogging);
	floor.Set(0, 400, 16, 16, 50, 1);
}

void Game::DrawFPS() {
	if (!bdrawfps) return;

	ticks++;
	if (SDL_GetTicks() - ontime >= 100) {
		fps = ticks * 10;

		std::cout << fps << '\n';
		ticks = 0;
		ontime = SDL_GetTicks();
	}

}

// MAIN GAME FUNCTIONALITY 
void Game::HandleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {

		//if esc key is pressed game quits
		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {

			bisrunning = false;
			
		}
		player.HandleEvents(event);

	}

}

void Game::Update()
{
	
	player.Update();

	world->Step(timeStep, velocityIterations, positionIterations);
}

void Game::Render()
{
	//sets the background color
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//clears what is on the screen
	SDL_RenderClear(renderer);
	//adds stuff to the screen
	player.Render();
	floor.Render();

	//redraws the screen
	SDL_RenderPresent(renderer);

	DrawFPS();
}

void Game::Close()
{
	player.Close();
	floor.Close();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	Gdiplus::GdiplusShutdown(gdiplusToken);
}
