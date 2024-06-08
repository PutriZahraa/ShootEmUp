#include "GAI02.h"
#include <random>


Engine::GAI02::GAI02(Setting* setting) :Engine::Game(setting)
{
	spawnTimer = 0.0f;
	hero = NULL;
}

random_device rd;
mt19937 gen(rd());
const float minX = 100.0f;
const float maxX = 900.0f;
std::uniform_real_distribution<float> disX(minX, maxX);

Engine::GAI02::~GAI02()
{
	delete hero;
	delete texture2;
}

void Engine::GAI02::Init()
{
	texture = new Texture("ships.png");
	texture2 = new Texture("rockets.png");
	SetBackgroundColor(33, 116, 185);
	hero = new Hero(texture, defaultSpriteShader, defaultQuad);
	hero->Init(inputManager);
	hero->SetPosition(setting->screenWidth / 2 - hero->GetSprite()->GetScaleWidth(), setting->screenHeight / 2);
	inputManager->AddInputMapping("quit", SDLK_ESCAPE);
	inputManager->AddInputMapping("shoots", SDLK_SPACE);
	
	int bulletNum = 50;
	for (int i = 0; i < bulletNum; i++) {
		Sprite* bs = (new Sprite(texture2, defaultSpriteShader, defaultQuad));
		bs->SetNumXFrames(3);
		bs->SetNumYFrames(1);
		bs->SetScale(2);
		readyBullets.push_back(new Bullet(bs));
	}
}

void Engine::GAI02::Update()
{
	timeInterval += GetGameTime();
	vec2 oldMonsterPos = hero->GetPosition();
	float x = oldMonsterPos.x, y = oldMonsterPos.y;
	if (inputManager->IsKeyPressed("quit")) {
		state = Engine::State::EXIT;
	}

	if (inputManager->IsKeyPressed("shoots")) {
		SpawnBullets();
	}
	y += yVelocity * GetGameTime();

	for (Bullet* b : inUseBullets) {
		// If bullet off screen then remove a bullet from in-use container, and insert into ready-to-use container
		if (b->GetPosition().x < -b->sprite->GetScaleWidth() || b->GetPosition().x > setting->screenWidth) {
			readyBullets.push_back(b);
			inUseBullets.erase(remove(inUseBullets.begin(), inUseBullets.end(), b), inUseBullets.end());
		}

		b->Update(GetGameTime());
	}
	// Spawn Enemies
	spawnTimer += GetGameTime();
	if (spawnTimer >= 1000) {
		// create a new enemy
		Enemy* enemy = new Enemy(texture, defaultSpriteShader, defaultQuad);
		// Set random enemy's position
		uniform_real_distribution<float> disX(0, setting->screenHeight);
		float x = disX(gen);
		uniform_real_distribution<float> disY(0, setting->screenWidth);
		float y = disY(gen);
		uniform_int_distribution<> disBorder(2, 2);
		int border = disBorder(gen);
		// 0 = spawn from bottom, 1 = left, 2 = top, 3 = right
		if (0 == border) {
			y = -enemy->GetSprite()->GetScaleHeight();
		}
		else if (1 == border) {
			x = -enemy->GetSprite()->GetScaleWidth();
		}
		else if (2 == border) {
			y = setting->screenHeight;
		}
		else {
			x = setting->screenWidth;
		}
		enemy->SetPosition(x, y);
		enemy->SetMaxSpeed(0.06f);
		enemy->SetTarget(hero);
		enemies.push_back(enemy);
		spawnTimer = 0;
	}

	for (Enemy* e : enemies) {
		e->Update(GetGameTime());
	}

	hero->Update(GetGameTime());
	
}

void Engine::GAI02::SpawnBullets()
{
	if (timeInterval >= 150) {
		Bullet* b = readyBullets.back();
		readyBullets.pop_back();
		b->SetPosition(hero->GetPosition().x, hero->GetPosition().y);
		b->yVelocity = 0.6f;
		inUseBullets.push_back(b);
		timeInterval = 0;
		cout << "spawn" << endl;
	}

}

bool Engine::GAI02::CheckCollisionB(Character* targetA, Character* targetB) {
	// Get the positions of the projectile and the bot
	vec2 PosA = targetA->GetPosition();
	vec2 PosB = targetB->GetPosition();

	// Calculate the distance between the projectile and the bot
	float distance = length(PosA - PosB);

	float collisionThreshold = 20.0f;

	if (distance < collisionThreshold) {
		return true;
	}
	else {
		return false;
	}
}

bool Engine::GAI02::CheckCollisionA(Bullet* targetA, Character* targetB) {
	// Get the positions of the projectile and the bot
	vec2 PosA = targetA->GetPosition();
	vec2 PosB = targetB->GetPosition();

	// Calculate the distance between the projectile and the bot
	float distance = length(PosA - PosB);

	float collisionThreshold = 20.0f;

	if (distance < collisionThreshold) {
		return true;
	}
	else {
		return false;
	}
}

void Engine::GAI02::UpdateCollisions() {
	for (auto its = enemies.begin(); its != enemies.end();) {
		Enemy* enemy = *its;
		for (auto it = inUseBullets.begin(); it != inUseBullets.end();) {
			Bullet* b = *it;
			vec2 velocity = vec2(0, 1); // Velocity pointing upwards
			vec2 position = b->GetPosition();
			vec2 newPosition = position + (velocity * 1.f);

			b->SetPosition(newPosition.x, newPosition.y);
			b->Update(GetGameTime());

			if (CheckCollisionA(b, enemy)) {
				float newX = disX(gen);
				delete b;
				it = inUseBullets.erase(it);
				enemy->SetPosition(newX / 2, setting->screenHeight);
			}
			else if (CheckCollisionB(enemy, hero)) {
				state = Engine::State::EXIT;
			}
			else {
				++it;
			}
		}
	}
	
}

void Engine::GAI02::Render()
{
	for (Enemy* enemy : enemies) {
		enemy->Draw();
	}
	for (Bullet* b : inUseBullets) {
		b->Draw();
	}
	hero->Draw();
}

int main(int argc, char** argv) {
	Engine::Setting* setting = new Engine::Setting();
	setting->windowTitle = "Shoot 'em up!!!";
	setting->screenWidth = 1600;
	setting->screenHeight = 900;
	setting->windowFlag = Engine::WindowFlag::WINDOWED;
	setting->vsync = false;
	setting->targetFrameRate = 0;
	Engine::Game* game = new Engine::GAI02(setting);
	game->Run();
	delete setting;
	delete game;

    return 0;
}