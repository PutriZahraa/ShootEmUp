#include "Sprite.h"
#include "Character.h"

#ifndef ENEMY_H
#define ENEMY_H

namespace Engine {
	class Enemy:public Engine::Character
	{
	public:
		Enemy(Texture* texture, Shader* shader, Quad* quad);
		~Enemy();
		void Update(float deltaTime);
		void SetTarget(Character* target);
		void SetMaxSpeed(float maxSpeed);
		void Move(float deltaTime);
	private:
		vec2 Engine::Enemy::Seek();
		string Engine::Enemy::FacingSprite(vec2 position, vec2 target);
		Character *target;
		float maxSpeed;
	};
}
#endif
