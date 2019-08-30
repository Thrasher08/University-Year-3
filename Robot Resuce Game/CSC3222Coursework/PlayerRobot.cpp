#include "PlayerRobot.h"
#include "Laser.h"
#include "TextureManager.h"
#include "RobotRescueGame.h"
#include "../../Common/Window.h"

using namespace NCL;
using namespace CSC3222;
using namespace Rendering;

PlayerRobot::PlayerRobot() : Robot()	{
	texture = texManager->GetTexture("Turret Bot.png");

	rType = PLAYER;
	position = Vector2(32, 32);
}

PlayerRobot::~PlayerRobot()	{

}

bool PlayerRobot::UpdateObject(float dt, RobotRescueGame* game) {
	
	//float testSpeed = 64;
	float speed = 50;


	if (Window::GetKeyboard()->KeyDown(KEYBOARD_LEFT)) {
		currentAnimDir = MovementDir::Left;
		UpdateAnimFrame(dt);
		force.x = -speed;
		//laserDir(0, 0);
		//newVelocity.x = -testSpeed * dt;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_RIGHT)) {
		currentAnimDir = MovementDir::Right;
		UpdateAnimFrame(dt);

		force.x = speed;
		//newVelocity.x = testSpeed * dt;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_UP)) {
		currentAnimDir = MovementDir::Up;
		UpdateAnimFrame(dt);

		force.y = -speed;
		//newVelocity.y = -testSpeed * dt;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_DOWN)) {
		currentAnimDir = MovementDir::Down;
		UpdateAnimFrame(dt);
		
		force.y = speed;
		//newVelocity.y = -testSpeed * dt;
	}
	
	this->UpdateCollider();

	Vector2 newVelocity = velocity.Normalised();
	float velocityCutOff = 0.0001;	//Cut off velocity if below this value
	Vector2 laserDir(0, 0);

	if (velocity.Length() < velocityCutOff){

		if (currentAnimDir == MovementDir::Left) {
			//Window::GetKeyboard()->KeyPressed(KEYBOARD_LEFT);
			laserDir.x = -1;
			laserDir.y = -0;
		}
		if (currentAnimDir == MovementDir::Right) {
			//laserDir(1, 0);
			laserDir.x = 1;
			laserDir.y = 0;
		}
		if (currentAnimDir == MovementDir::Up) {
			//laserDir(0, 1);
			laserDir.x = 0;
			laserDir.y = 1;
		}
		if (currentAnimDir == MovementDir::Down) {
			//laserDir(0, 1);
			laserDir.x = 0;
			laserDir.y = -1;
		}
	}
	else{

		newVelocity = velocity.Normalised();
	}
	AddForce(force);
	//position += newVelocity;

	if (Window::GetKeyboard()->KeyPressed(KEYBOARD_SPACE)) {
		Vector2 laserSpeed = newVelocity * 500.0f;				//Initial Speed 150.0f try to make laser take 1 second to cross screen
		Laser* shot = new Laser(laserSpeed);
		shot->SetPosition(position + Vector2(8,16));

		game->AddNewObject(shot);
	}

	return true;
}