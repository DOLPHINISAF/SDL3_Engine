#pragma once

#include <SDL.h>
#include <box2d.h>

class Player
{
public:
	void HandleEvents();
	void Update();
	void Render();

	void Close();


private:

	SDL_Rect body;


	


};

