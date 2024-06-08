#include "Enemy.h"

Engine::Enemy::Enemy(Texture* texture, Shader* shader, Quad* quad) :Character(texture, shader, quad)
{
	sprite->SetNumXFrames(10);
	sprite->SetNumYFrames(1);
	sprite->AddAnimation("bot-up", 0, 0);
	sprite->AddAnimation("bot-upright", 1, 1);
	sprite->AddAnimation("bot-right", 2, 2);
	sprite->AddAnimation("bot-downright", 3, 3);
	sprite->AddAnimation("bot-down", 4, 4);
	sprite->AddAnimation("bot-downleft", 5, 5);
	sprite->AddAnimation("bot-left", 6, 6);
	sprite->AddAnimation("bot-upleft", 7, 7);
	sprite->PlayAnim("bot-down");
	sprite->SetScale(2);
	sprite->SetAnimationDuration(90);

	maxSpeed = 0.0f;
	target = NULL;
}

Engine::Enemy::~Enemy()
{
}

void Engine::Enemy::Update(float deltaTime)
{
	if (Engine::CharacterState::ALIVE == state) {
		Move(deltaTime);
	}

}

void Engine::Enemy::SetTarget(Character* target)
{
	this->target = target;
}

void Engine::Enemy::SetMaxSpeed(float maxSpeed)
{
	this->maxSpeed = maxSpeed;
}

void Engine::Enemy::Move(float deltaTime)
{
	vec2 steering = Seek();
	// Update Bot Position based on steering behavior
	velocity += steering;
	vec2 position = GetPosition();
	vec2 oldPosition = vec2(position);
	position += velocity * deltaTime;
	SetPosition(position.x, position.y);
	// Update Sprite Animation
	string anim = FacingSprite(oldPosition, position);
	sprite->PlayAnim("bot-"+anim);
	sprite->Update(deltaTime);
}

vec2 Engine::Enemy::Seek() {
	vec2 targetPosition = target->GetPosition();
	vec2 position = GetPosition();
	vec2 desiredVelocity = normalize(targetPosition - position) * maxSpeed;
	vec2 steering = desiredVelocity - velocity;
	return steering;
}

string Engine::Enemy::FacingSprite(vec2 position, vec2 target)
{
	if (target == position) {
		return "";
	}

	vec2 direction = normalize(target - position);

	float angle = degrees(atan2(direction.y, direction.x));
	if (angle < 0) {
		angle += 360;
	}

	float range = 22.5f;

	if (angle >= (0.0f + range) && angle < (45.0f + range)) {
		return "upright";
	}
	else if (angle >= (45.0f + range) && angle < (90.0f + range)) {
		return "up";
	}
	else if (angle >= (90.0f + range) && angle < (135.0f + range)) {
		return "upleft";
	}
	else if (angle >= (135.0f + range) && angle < (180.0f + range)) {
		return "left";
	}
	else if (angle >= (180.0f + range) && angle < (235.5f + range)) {
		return "downleft";
	}
	else if (angle >= (235.5f + range) && angle < (270.0f + range)) {
		return "down";
	}
	else if (angle >= (270.0f + range) && angle < (315.0f + range)) {
		return "downright";
	}
	else {
		return "right";
	}
}