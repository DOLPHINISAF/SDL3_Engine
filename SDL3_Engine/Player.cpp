#include "Player.h"

bool Player::Load(std::string path, SDL_Renderer* renderer, b2World* world)
{

	this->renderer = renderer;
	this->world = world;

	SDL_Surface* tempsurface = nullptr;

	tempsurface = IMG_Load(path.c_str());
	if (!tempsurface) {
		LOG("Could not create tempsurface of player from path!! " + path);
		return false;
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderer, tempsurface);
		
		SDL_FreeSurface(tempsurface);

		LOG("Succesfully loaded texture from path: " + path);
	}

	return true;
}

void Player::Set(int x, int y, int height, int width, int scale = 1)
{
	//we set the size of the player sprite
	player_rect.x = x;
	player_rect.y = y;
	player_rect.w = width * scale;
	player_rect.h = height * scale;


	//temporary objects
	b2BodyDef player_body_def;
	b2FixtureDef player_fixture_def;

	player_body_def.fixedRotation = true;
	player_body_def.type = b2_dynamicBody;
	player_body_def.position.Set(float(player_rect.x), float(-player_rect.y));

	//creates our body
	player_body = world->CreateBody(&player_body_def);
	//sets size of shape 
	player_shape.SetAsBox(player_rect.w / 2.f, player_rect.h / 2.f);

	player_fixture_def.density = density;
	player_fixture_def.friction = friction;
	player_fixture_def.shape = &player_shape;

	player_fixture = player_body->CreateFixture(&player_fixture_def);

}

void Player::SetScale(int scale) {
	player_rect.w *= scale;
	player_rect.h *= scale;
	player_shape.SetAsBox(player_rect.w / 2.f, player_rect.h / 2.f);

}

void Player::HandleEvents()
{

}

void Player::Update()
{
	//we get the coordinates from the world simulation of box2d and translate them inside sdl for rendering
	player_pos = player_body->GetPosition();

	player_rect.x = int(player_pos.x);
	player_rect.y = int(-player_pos.y);
}

void Player::Render()
{
	SDL_RenderCopy(renderer, texture, nullptr, &player_rect);
}

void Player::Close()
{

	SDL_DestroyTexture(texture);
}
