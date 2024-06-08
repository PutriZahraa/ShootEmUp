#include "Sprite.h"

#ifndef CHARACTER_H
#define CHARACTER_H

namespace Engine {
	enum class CharacterState {
		ALIVE,
		DEAD
	};
	class Character
	{
	public:
		Character(Texture* texture, Shader* shader, Quad* quad);
		~Character();
		void Update(float deltaTime);
		void Draw();
		void SetPosition(float x, float y);
		vec2 GetPosition();
		Sprite* GetSprite();
		vec2 GetVelocity();
	protected:
		Sprite* sprite;
		CharacterState state;
		vec2 velocity;
	};
}
#endif
