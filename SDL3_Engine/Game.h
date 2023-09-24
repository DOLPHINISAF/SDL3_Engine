#pragma once
#include "Player.h"
#include <iostream>
#include <SDL.h>
#include <string>
#include <box2d.h>
class Game
{
public:

	
	Game(const char title[], const int width, const int height);
	~Game();

	bool InitSDL(const char title[]);

	void InitBox2d();

	bool getIsRunning() { return bisrunning; }

	void HandleEvents();
	void Update();
	void Render();

	void LOG(std::string text) { std::cout << text << '\n'; }

	void Close();

private:

	bool bisrunning;

	int width;
	int height;

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
};

