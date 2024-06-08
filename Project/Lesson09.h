#ifndef LESSON09_H
#define LESSON09_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"

namespace Engine {
	class Lesson09 :public Engine::Game
	{
	public:
		Lesson09(Setting* setting);
		~Lesson09();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Engine::Texture* texture = NULL, *bulletTexture = NULL;
		Engine::Sprite* sprite = NULL;
		vector<Sprite*> inUseBullets;
		vector<Sprite*> readyBullets;
		float yVelocity = 0, gravity = 0;
		bool jump = false;
		void SpawnBullets();

	};
}

#endif

