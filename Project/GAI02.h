#ifndef GAI02_H
#define GAI02_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Hero.h"
#include "Character.h"
#include "Bullet.h"
#include <random> 

namespace Engine {
	class GAI02 :public Engine::Game
	{
	public:
		GAI02(Setting* setting);
		~GAI02();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Texture* texture = NULL, * texture2 = NULL;
		float spawnTimer;
		vector<Enemy*> enemies;
		Hero* hero;
		vector<Bullet*> inUseBullets;
		vector<Bullet*> readyBullets;
		void UpdateCollisions();
		//void UpdateProjectiles();
		void SpawnBullets();
		bool CheckCollisionB(Character* targetA, Character* targetB);
		bool CheckCollisionA(Bullet* targetA, Character* targetB);
		float timeInterval = 0, xBulletVel = 0, yVelocity = 0;
	};
}
#endif