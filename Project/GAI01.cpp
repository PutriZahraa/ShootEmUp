#include "GAI01.h"

Engine::GAI01::GAI01(Setting* setting) :Engine::Game(setting)
{
}

Engine::GAI01::~GAI01()
{
}

void Engine::GAI01::Init()
{
	texture = new Texture("s8dchars.png");
	CreatePlayerSprite();
	CreateBotSprite();
	SetBackgroundColor(145, 235, 84);
}

void Engine::GAI01::Update()
{

	if (inputManager->IsKeyPressed("quit")) {
		state = Engine::State::EXIT;
	}

	ControlPlayerSprite();
	ControBotSprite();
}

void Engine::GAI01::Render()
{
	botSprite->Draw();
	playerSprite->Draw();
}

void Engine::GAI01::CreatePlayerSprite()
{
	playerSprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	playerSprite->SetNumXFrames(96);
	playerSprite->SetNumYFrames(1);
	playerSprite->AddAnimation("up", 0, 2);
	playerSprite->AddAnimation("upright", 12, 14);
	playerSprite->AddAnimation("right", 24, 26);
	playerSprite->AddAnimation("downright", 36, 38);
	playerSprite->AddAnimation("down", 48, 50);
	playerSprite->AddAnimation("downleft", 60, 62);
	playerSprite->AddAnimation("left", 72, 74);
	playerSprite->AddAnimation("upleft", 84, 86);
	playerSprite->PlayAnim("down");
	playerSprite->SetScale(3);
	playerSprite->SetAnimationDuration(90);
	//playerSprite->SetPosition((setting->screenWidth / 2) - 20, setting->screenHeight/2);
	playerSprite->SetPosition(0, 0);


	inputManager->AddInputMapping("walk-left", SDLK_LEFT);
	inputManager->AddInputMapping("walk-left", SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	inputManager->AddInputMapping("walk-left", SDL_CONTROLLER_AXIS_LEFTX);

	inputManager->AddInputMapping("walk-right", SDLK_RIGHT);
	inputManager->AddInputMapping("walk-right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	inputManager->AddInputMapping("walk-right", SDL_CONTROLLER_AXIS_RIGHTX);

	inputManager->AddInputMapping("walk-up", SDLK_UP);
	inputManager->AddInputMapping("walk-up", SDL_CONTROLLER_BUTTON_DPAD_UP);
	inputManager->AddInputMapping("walk-up", SDL_CONTROLLER_AXIS_RIGHTY);

	inputManager->AddInputMapping("walk-down", SDLK_DOWN);
	inputManager->AddInputMapping("walk-down", SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	inputManager->AddInputMapping("walk-down", SDL_CONTROLLER_AXIS_LEFTY);

	inputManager->AddInputMapping("quit", SDLK_ESCAPE);

}

void Engine::GAI01::ControlPlayerSprite()
{
	// Get Current Player's Position
	float speed = 0.07f;
	// s = v * t;
	// Control player's movement using keyboard or gamepad
	playerVelocity = vec2(0, 0);
	if (inputManager->IsKeyPressed("walk-up")) {
		playerVelocity += vec2(0.0f, speed);
	}

	if (inputManager->IsKeyPressed("walk-down")) {
		playerVelocity += vec2(0.0f, -speed);
	}

	if (inputManager->IsKeyPressed("walk-right")) {
		playerVelocity += vec2(speed, 0.0f);
	}

	if (inputManager->IsKeyPressed("walk-left")) {
		playerVelocity += vec2(-speed, 0.0f);
	}

	vec2 playerPosition = playerSprite->GetPosition();
	vec2 oldPosition = vec2(playerPosition);
	playerPosition += playerVelocity * GetGameTime();
	// Update new player's position
	playerSprite->SetPosition(playerPosition.x, playerPosition.y);
	// Update player's animation
	string anim = FacingSprite(oldPosition, playerPosition);
	playerSprite->PlayAnim(anim);
	playerSprite->Update(GetGameTime());
}

void Engine::GAI01::CreateBotSprite()
{
	botSprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	botSprite->SetNumXFrames(96);
	botSprite->SetNumYFrames(1);
	botSprite->AddAnimation("bot-up", 4, 6);
	botSprite->AddAnimation("bot-upright", 16, 18);
	botSprite->AddAnimation("bot-right", 28, 30);
	botSprite->AddAnimation("bot-downright", 40, 42);
	botSprite->AddAnimation("bot-down", 52, 54);
	botSprite->AddAnimation("bot-downleft", 64, 66);
	botSprite->AddAnimation("bot-left", 76, 78);
	botSprite->AddAnimation("bot-upleft", 88, 90);
	botSprite->PlayAnim("bot-down");
	botSprite->SetScale(3);
	botSprite->SetAnimationDuration(90);
	botSprite->SetPosition(setting->screenWidth / 2, setting->screenHeight / 2);
}

void Engine::GAI01::ControBotSprite()
{
	// Apply steering behavior
	// vec2 steering = Arrival(botSprite->GetPosition(), playerSprite->GetPosition(), botVelocity, 0.15f, 400.0f);
	// vec2 steering = Seek(botSprite->GetPosition(), botVelocity, playerSprite->GetPosition(), 0.06f);
	// vec2 steering = Flee(botSprite->GetPosition(), botVelocity, playerSprite->GetPosition(), 0.06f);
	vec2 steering = Pursue(botSprite->GetPosition(), botVelocity, playerSprite->GetPosition(), playerVelocity, 0.06f);
	// Update Bot Position based on steering behavior
	botVelocity += steering;
	vec2 botPosition = botSprite->GetPosition();
	vec2 oldPosition = vec2(botPosition);
	botPosition += botVelocity * GetGameTime();
	botSprite->SetPosition(botPosition.x, botPosition.y);
	// Update Sprite Animation
	string anim = FacingSprite(oldPosition, botPosition);
	botSprite->PlayAnim("bot-" + anim);
	botSprite->Update(GetGameTime());
}

string Engine::GAI01::FacingSprite(vec2 position, vec2 target)
{
	if (target == position) {
		return "";
	}

	vec2 direction = normalize(target - position);

	float angle = degrees(atan2(direction.y, direction.x));
	if (angle < 0) {
		angle += 360;
	}

	float range = 22.5f;

	if (angle >= (0.0f + range) && angle < (45.0f + range)) {
		return "upright";
	}
	else if (angle >= (45.0f + range) && angle < (90.0f + range)) {
		return "up";
	}
	else if (angle >= (90.0f + range) && angle < (135.0f + range)) {
		return "upleft";
	}
	else if (angle >= (135.0f + range) && angle < (180.0f + range)) {
		return "left";
	}
	else if (angle >= (180.0f + range) && angle < (235.5f + range)) {
		return "downleft";
	}
	else if (angle >= (235.5f + range) && angle < (270.0f + range)) {
		return "down";
	}
	else if (angle >= (270.0f + range) && angle < (315.0f + range)) {
		return "downright";
	}
	else {
		return "right";
	}
}

vec2 Engine::GAI01::Seek(vec2 position, vec2 velocity, vec2 target, float maxSpeed) {
	vec2 desiredVelocity = normalize(target - position) * maxSpeed;
	vec2 steering = desiredVelocity - velocity;
	return steering;
}

vec2 Engine::GAI01::Flee(vec2 position, vec2 velocity, vec2 target, float maxSpeed) {
	vec2 desiredVelocity = normalize(position - target) * maxSpeed;
	vec2 steering = desiredVelocity - velocity;
	return steering;
}

vec2 Engine::GAI01::Arrival(vec2 position, vec2 target, vec2 botVelocity, float maxSpeed, float slowRadius) {
	vec2 desiredVelocity = target - position;
	float distance = length(desiredVelocity);

	if (distance < slowRadius) {
		desiredVelocity = normalize(desiredVelocity);
		desiredVelocity = desiredVelocity * maxSpeed * (distance / slowRadius);
	}
	else {
		desiredVelocity = normalize(desiredVelocity);
		desiredVelocity = desiredVelocity * maxSpeed;
	}

	vec2 steering = desiredVelocity - botVelocity;
	return steering;
}

vec2 Engine::GAI01::Pursue(vec2 position, vec2 velocity, vec2 targetPosition, vec2 targetVelocity, float maxSpeed) {
	float distance = length(targetPosition - position);
	float T = distance / maxSpeed;
	float maxPredictionTime = 0.5f;
	if (maxSpeed <= distance / maxPredictionTime) {
		T = maxPredictionTime;
	}
	vec2 targetFuturePos = targetPosition + targetVelocity * T;
	return Seek(position, botVelocity, targetFuturePos, maxSpeed);
}

/*int main(int argc, char** argv) {
	Engine::Setting* setting = new Engine::Setting();
	setting->windowTitle = "Steering Behavior : Seek, Flee, Arrival, Pursue, and Evade";
	setting->screenWidth = 1600;
	setting->screenHeight = 900;
	setting->windowFlag = Engine::WindowFlag::WINDOWED;
	setting->vsync = false;
	setting->targetFrameRate = 0;
	Engine::Game* game = new Engine::GAI01(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}*/
