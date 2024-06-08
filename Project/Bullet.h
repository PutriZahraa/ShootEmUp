#ifndef BULLET_H
#define BULLET_H

#include "Sprite.h"

namespace Engine {
	class Bullet
	{
	public:
		BoundingBox boundingBox;
		Bullet(Sprite* sprite);
		~Bullet();
		float xVelocity, yVelocity = 0;
		Sprite* sprite;
		void SetPosition(float x, float y);
		vec2 GetPosition();
		void Update(float deltaTime);
		void Draw();
	};
}
#endif

