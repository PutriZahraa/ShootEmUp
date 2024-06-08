#include "Character.h"

Engine::Character::Character(Texture* texture, Shader* shader, Quad* quad)
{
	this->sprite = new Sprite(texture, shader, quad);
	state = Engine::CharacterState::ALIVE;
}

Engine::Character::~Character()
{
	delete sprite;
}

void Engine::Character::Update(float deltaTime)
{
	sprite->Update(deltaTime);
}

void Engine::Character::Draw()
{
	if (Engine::CharacterState::ALIVE == state) {
		sprite->Draw();
	}
}

void Engine::Character::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
}

vec2 Engine::Character::GetPosition()
{
	return sprite->GetPosition();
}

Engine::Sprite* Engine::Character::GetSprite()
{
	return sprite;
}

vec2 Engine::Character::GetVelocity()
{
	return velocity;
}







