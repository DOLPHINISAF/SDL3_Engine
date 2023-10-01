#include "Sprite.h"

bool Sprite::Load(std::string path, SDL_Renderer* renderer, b2World* world)
{
	this->srenderer = renderer;
	this->world = world;

	SDL_Surface* tempsurface = nullptr;

	tempsurface = IMG_Load(path.c_str());
	if (!tempsurface) {
		LOG("Could not create tempsurface of sprite from path!! " + path);
		return false;
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderer, tempsurface);

		SDL_FreeSurface(tempsurface);

		LOG("Succesfully loaded texture from path: " + path);
	}

	return true;

	
}

void Sprite::Set(int x, int y, int height, int width, int scale = 1)
{
	//we set the size of the sprite sprite
	sprite_rect.x = x;
	sprite_rect.y = y;
	sprite_rect.w = width * scale;
	sprite_rect.h = height * scale;


	//temporary objects
	b2BodyDef sprite_body_def;
	b2FixtureDef sprite_fixture_def;

	sprite_body_def.fixedRotation = true;
	sprite_body_def.type = b2_staticBody;
	sprite_body_def.position.Set(float(sprite_rect.x), float(-sprite_rect.y));

	//creates our body
	sprite_body = world->CreateBody(&sprite_body_def);
	//sets size of shape 
	sprite_shape.SetAsBox(sprite_rect.w / 2.f, sprite_rect.h / 2.f);

	sprite_fixture_def.shape = &sprite_shape;

	sprite_body->CreateFixture(&sprite_fixture_def);

}

void Sprite::Render()
{
	SDL_RenderCopy(srenderer, texture, nullptr, &sprite_rect);
}

void Sprite::Close() {
	SDL_DestroyTexture(texture);
}