#pragma once

#include <box2d.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
class Player
{
public:

	bool Load(std::string path, SDL_Renderer* renderer, b2World* world);

	void Set(int x, int y, int height, int width, int scale);
	void SetScale(int scale);

	void HandleEvents(SDL_Event& player_events);
	void Update();
	void Render();

	void Close();

	void LOG(std::string text) { std::cout << text << '\n'; }
private:



	SDL_Rect player_rect;

	SDL_Texture* texture = nullptr;

	SDL_Renderer* renderer = nullptr;


	//player phisics proprieties

	b2World* world = nullptr;

	float density = 0.1f;
	float friction = 0.0f;


	
	b2Body* player_body;
	b2PolygonShape player_shape;
	b2Fixture* player_fixture; //only needed to change density/fricion. not used currently

	
	b2Vec2 player_pos;
};