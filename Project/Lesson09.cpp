#include "Lesson09.h"

Engine::Lesson09::Lesson09(Setting* setting) :Engine::Game(setting)
{

}

Engine::Lesson09::~Lesson09()
{
	//delete texture;
	//delete sprite;
}

void Engine::Lesson09::Init()
{
	// Add a monster player
	texture = new Texture("monster.png");
	sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(6);
	sprite->SetNumYFrames(3);
	sprite->AddAnimation("attack", 13, 14);
	sprite->AddAnimation("idle", 0, 3);
	sprite->AddAnimation("run", 6, 11);
	sprite->PlayAnim("walk");
	sprite->SetScale(3);
	sprite->SetAnimationDuration(90);


	// Add bullets
	bulletTexture = new Texture("bullet.png");
	int bulletNum = 100;
	for (int i = 0; i < bulletNum; i++) {
		Sprite* bulletSprite = new Sprite(bulletTexture, defaultSpriteShader, defaultQuad);
		sprite->SetNumXFrames(1);
		sprite->SetNumYFrames(1);
		sprite->SetScale(1);
		readyBullets.push_back(bulletSprite);
	}


	// Add input mapping 
	inputManager->AddInputMapping("Run Right", SDLK_RIGHT);
	inputManager->AddInputMapping("Run Left", SDLK_LEFT);
	inputManager->AddInputMapping("Jump", SDLK_UP);
	inputManager->AddInputMapping("Attack", SDLK_x);
	inputManager->AddInputMapping("Run Right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	inputManager->AddInputMapping("Run Left", SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	inputManager->AddInputMapping("Jump", SDL_CONTROLLER_BUTTON_A);
	inputManager->AddInputMapping("Attack", SDL_CONTROLLER_BUTTON_X);
	inputManager->AddInputMapping("Quit", SDLK_ESCAPE);
	inputManager->AddInputMapping("Quit", SDL_CONTROLLER_BUTTON_Y);

	SetBackgroundColor(65, 180, 242);

}

void Engine::Lesson09::Update()
{
	// If user press "Quit" key then exit
	if (inputManager->IsKeyReleased("Quit")) {
		state = State::EXIT;
		return;
	}

	sprite->PlayAnim("idle");

	// Move monster sprite using keyboard
	vec2 oldMonsterPos = sprite->GetPosition();
	float x = oldMonsterPos.x, y = oldMonsterPos.y;
	if (inputManager->IsKeyPressed("Run Right")) {
		sprite->PlayAnim("run");
		x += 0.2f * GetGameTime();
		sprite->SetFlipHorizontal(false);
	}

	if (inputManager->IsKeyPressed("Run Left")) {
		sprite->PlayAnim("run");
		x -= 0.2f * GetGameTime();
		sprite->SetFlipHorizontal(true);
	}

	sprite->SetPosition(x, y);

	if (inputManager->IsKeyPressed("Jump") && !jump) {
		//Set gravity and yVelocity
		float ratio = (GetGameTime() / 16.7f);
		gravity = 0.16f * ratio;
		yVelocity = 1.8f;
		jump = true;
	}

	if (y > 0) {
		yVelocity -= gravity;
	}
	else if (y < 0) {
		jump = false;
		yVelocity = 0;
		y = 0;
	}


	y += yVelocity * GetGameTime();
	sprite->SetPosition(x, y);


	if (inputManager->IsKeyPressed("Attack")) {
		sprite->PlayAnim("attack");
		// TODO Spawn Bullets
	}

	// Update monster sprite animation
	sprite->Update(GetGameTime());

}

void Engine::Lesson09::Render()
{
	sprite->Draw();
	for (Sprite* s : inUseBullets) {
		s->Draw();
	}
}

void Engine::Lesson09::SpawnBullets()
{

}


//int main(int argc, char** argv) {
//	Engine::Setting* setting = new Engine::Setting();
//	setting->windowTitle = "Bullets Spawn Demo";
//	setting->screenWidth = 1600;
//	setting->screenHeight = 900;
//	setting->windowFlag = Engine::WindowFlag::WINDOWED;
//	setting->vsync = false;
//	setting->targetFrameRate = 75;
//	Engine::Game* game = new Engine::Lesson09(setting);
//	game->Run();
//	delete setting;
//	delete game;
//
//	return 0;
//}

