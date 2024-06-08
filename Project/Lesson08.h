#ifndef LESSON08_H
#define LESSON08_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"

namespace Engine {
	class Lesson08 :public Engine::Game
	{
	public:
		Lesson08(Setting* setting);
		~Lesson08();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Engine::Texture* texture = NULL;
		Engine::Sprite* sprite = NULL;
		float mul = 1, degree = 0;

	};
}

#endif

