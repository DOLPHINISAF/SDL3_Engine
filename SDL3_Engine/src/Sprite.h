#pragma once
#include <box2d.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

class Sprite
{
public:

	bool Load(std::string path, SDL_Renderer* renderer, b2World* world, bool ISLOGGING);

	void Set(int x, int y, int height, int width, int scaleX, int scaleY);
	
	void Render();

	void Close();

	

private:


	void LOG(std::string text) { if(islogging)std::cout << text << '\n'; }

	bool islogging;

	//SDL2 objects
	SDL_Rect sprite_rect;

	SDL_Texture* texture = nullptr;
	SDL_Renderer* srenderer = nullptr;

	//BOX2D objects
	b2World* world = nullptr;

	b2Body* sprite_body;
	b2PolygonShape sprite_shape;
};

