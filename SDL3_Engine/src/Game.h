#pragma once
#include <box2d.h>
#include <iostream>
#include <SDL.h>
#include <string>
#include "Player.h"
#include "Sprite.h"

enum Flags {
	GAME_LOG = 1,
	GAME_HELP = 2,
	GAME_FPS_DRAW = 4
};
inline Flags operator|(Flags a, Flags b)
{
	return static_cast<Flags>(static_cast<int>(a) | static_cast<int>(b));
}
inline Flags operator&(Flags a, Flags b)
{
	return static_cast<Flags>(static_cast<int>(a) & static_cast<int>(b));
}
class Game
{
public:

	
	Game(const char title[], const int width, const int height, int flags);
	~Game();

	//we initialise the library for rendering, physics simulation and adding the objects inside the world
	bool InitSDL(const char title[]);
	void InitBox2d();
	void LoadAssets();

	bool getIsRunning() { return bisrunning; }

	void HandleEvents();
	void Update();
	void Render();

	void LOG(std::string text) { if(islogging)std::cout << text << '\n'; }
	void DrawFPS();
	

	void Close();


	//used for cli args
	bool islogging = false;
	bool bisrunning;
	bool bdrawfps;
private:

	bool HandleFlags();

	int GameFlags;


	Uint32 ticks,ontime, fps;

	unsigned int fps_pollrate = 100; //ms

	

	

	int width;
	int height;

	float gravity_force = 9.8f;

	

	//SDL objects

	SDL_Window* window = nullptr;

	SDL_Renderer* renderer = nullptr;

	//box2d objects

	float timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 10;
	int32 positionIterations = 5;

	b2Vec2 gravity;


	b2World* world;

	//world objects

	Player player;

	Sprite floor;



	// only used for easier file loading
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
};

