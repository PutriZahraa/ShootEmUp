#include "Bullet.h"

Engine::Bullet::Bullet(Sprite* sprite)
{
	this->sprite = sprite;
}

Engine::Bullet::~Bullet()
{
}

void Engine::Bullet::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
}

vec2 Engine::Bullet::GetPosition()
{
	return sprite->GetPosition();
}

void Engine::Bullet::Update(float deltaTime)
{
	float x = GetPosition().x;
	float y = GetPosition().y;
	y += yVelocity * deltaTime;
	//x += xVelocity * deltaTime;
	//SetPosition(x, GetPosition().y);
	SetPosition(GetPosition().x, y);
	sprite->Update(deltaTime);
}

void Engine::Bullet::Draw()
{
	sprite->Draw();
}
