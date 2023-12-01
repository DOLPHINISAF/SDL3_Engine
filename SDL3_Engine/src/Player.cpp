#include "Player.h"

bool Player::Load(const char path[], SDL_Renderer* renderer, b2World* world, bool ISLOGGING = false)
{

	//wchar_t* file;
	
	//Gdiplus::Image* image = new Gdiplus::Image(file);

	player_rect.h = 16;
	player_rect.w = 16;

	//delete image;
	

	islogging = ISLOGGING;
	this->renderer = renderer;
	this->world = world;

	SDL_Surface* tempsurface = nullptr;


	tempsurface = IMG_Load(path);
	if (!tempsurface) {
		LOG("Could not create tempsurface of player from path!! " + std::string(path));
		return false;
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderer, tempsurface);
		
		SDL_FreeSurface(tempsurface);

		LOG("Succesfully loaded texture from path: " + std::string(path));
	}

	return true;
}

void Player::Set(int x, int y, int scale = 1)
{
	//we set the size of the player sprite
	player_rect.x = x;
	player_rect.y = y;
	player_rect.w = player_rect.w * scale;
	player_rect.h = player_rect.h * scale;


	//temporary objects
	b2BodyDef player_body_def;
	b2FixtureDef player_fixture_def;

	player_body_def.fixedRotation = true;
	player_body_def.type = b2_dynamicBody;
	player_body_def.position.Set(float(player_rect.x + player_rect.w / 2), float(-player_rect.y + player_rect.h / 2));

	//creates our body
	player_body = world->CreateBody(&player_body_def);
	//sets size of shape 
	player_shape.SetAsBox(player_rect.w / 2.f, player_rect.h / 2.f);

	player_fixture_def.density = density;
	player_fixture_def.friction = friction;
	player_fixture_def.shape = &player_shape;

	player_fixture = player_body->CreateFixture(&player_fixture_def);

	max_vel.x = 10.f;
	max_vel.y = 10.f;

}

void Player::SetScale(int scale) {
	player_rect.w *= scale;
	player_rect.h *= scale;
	player_shape.SetAsBox(player_rect.w / 2.f, player_rect.h / 2.f);

}

void Player::HandleEvents(SDL_Event& player_events)
{

	//basic movement

	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_D] && current_vel.x <= max_vel.x) {
		current_vel.x = 10.f;
	}
	else if (state[SDL_SCANCODE_A] && current_vel.x >= -max_vel.x) {
		current_vel.x = -10.f;
	}
	else {
		current_vel.x = 0;
	}

	if (state[SDL_SCANCODE_W] && current_vel.y == 0) {
		current_vel.y = 50.f;

	}
	
	player_body->SetLinearVelocity(current_vel);


}

void Player::Update()
{
	//we get the coordinates from the world simulation of box2d and translate them inside sdl for rendering
	player_pos = player_body->GetPosition();
	
	player_rect.x = int(player_pos.x);
	player_rect.y = int(-player_pos.y);

	current_vel = player_body->GetLinearVelocity();
}

void Player::Render()
{
	SDL_RenderCopy(renderer, texture, nullptr, &player_rect);
}

void Player::Close()
{

	SDL_DestroyTexture(texture);
}
