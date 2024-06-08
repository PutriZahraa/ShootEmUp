#include "Lesson08.h"

Engine::Lesson08::Lesson08(Setting* setting) :Engine::Game(setting)
{

}

Engine::Lesson08::~Lesson08()
{
	//delete texture;
	//delete sprite;
}

void Engine::Lesson08::Init()
{
	texture = new Texture("monster.png");
	sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(6);
	sprite->SetNumYFrames(3);
	sprite->AddAnimation("idle", 0, 3);
	sprite->AddAnimation("walk", 6, 11);
	sprite->PlayAnim("walk");
	sprite->SetScale(3);
	sprite->SetAnimationDuration(10);

	SetBackgroundColor(65, 180, 242);

}

void Engine::Lesson08::Update()
{
	float x = sprite->GetPosition().x;
	float y = sprite->GetPosition().y;
	float velocity = 0.2f;
	// s = v * t;
	float maxX = setting->screenWidth - sprite->GetScaleWidth();
	float minX = 0;
	mul *= (x > maxX || x < minX) ? -1 : 1;
	x += velocity * mul * GetGameTime();
	float rotationSpeed = -0.8f;
	degree += mul * rotationSpeed * GetGameTime();
	sprite->SetFlipHorizontal(mul == 1 ? false : true);
	sprite->SetPosition(x, y);
	sprite->SetRotation(degree);
	sprite->Update(GetGameTime());
}

void Engine::Lesson08::Render()
{
	sprite->Draw();
}

/*
int main(int argc, char** argv) {
	Engine::Setting* setting = new Engine::Setting();
	setting->windowTitle = "Player's Rotation and Movement Demo";
	setting->screenWidth = 1600;
	setting->screenHeight = 900;
	setting->windowFlag = Engine::WindowFlag::WINDOWED;
	setting->vsync = false;
	setting->targetFrameRate = 75;
	Engine::Game* game = new Engine::Lesson08(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}*/

