#include "Sprite.h"
#include "Character.h"
#include "Input.h"
#include "GAI02.h"

#ifndef HERO_H
#define HERO_H

namespace Engine {
	class Hero :public Engine::Character
	{
	public:
		Hero(Texture* texture, Shader* shader, Quad* quad);
		~Hero();
		void Update(float deltaTime);
		void Move(float deltaTime);
		void Init(Input* inputManager);
	private:
		Input* inputManager;
		float width = 0, height = 0;
	};
}
#endif
