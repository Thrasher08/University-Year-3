#include "EnemyRobot.h"
#include "TextureManager.h"
#include "../../Common/TextureLoader.h"
#include "GameMap.h"
using namespace NCL;
using namespace CSC3222;
using namespace Rendering;

EnemyRobot::EnemyRobot(GameMap* map) : Robot()	{
	texture = texManager->GetTexture("Turret Bot overgrown.png");
	moving = false;
	rType = ENEMY;
	state = ATTACK;
	this->map = map;
	std::cout << "Path Find Occurs" << std::endl;
	map->PathFinding(Vector2(10*16, 8*16), Vector2(64,64), nodePath);
	
	//map->GeneratePath()
}

EnemyRobot::~EnemyRobot()	{
}

bool EnemyRobot::UpdateObject(float dt, RobotRescueGame* game) {
	thinkTime -= dt;
	this->UpdateCollider();
	if (moving) {
		position += velocity * dt;
		UpdateAnimFrame(dt);
	}

	switch (state) {

		case ATTACK: AttackPlayer(); break;
		case HIDE: HideFromPlayer(); break;
		case MOVE: MoveTowardsPlayer(); break;
	}

	if (thinkTime < 0) {
		moving = false;
		velocity = Vector2();

		thinkTime += 0.5f;

		float testSpeed = 16;

		int choice = rand() % 5;

		if (choice == 1) {
			moving = true;
			velocity.x = -testSpeed;
			currentAnimDir = MovementDir::Left;
		}

		if (choice == 2) {
			moving = true;
			velocity.x = testSpeed;
			currentAnimDir = MovementDir::Right;
		}

		if (choice == 3) {
			moving = true;
			velocity.y = -testSpeed;
			currentAnimDir = MovementDir::Up;
		}

		if (choice == 4) {
			moving = true;
			velocity.y = testSpeed;
			currentAnimDir = MovementDir::Down;
		}
	}
	return true;
}

void EnemyRobot::AttackPlayer() {
	std::cout << "ATTACK" << std::endl;
	//state = HIDE;
}

void EnemyRobot::HideFromPlayer() {

	std::cout << "HIDE" << std::endl;
	//state = MOVE;
}

void EnemyRobot::MoveTowardsPlayer() {

	std::cout << "MOVE" << std::endl;
	//state = ATTACK;
}

void EnemyRobot::DrawObject(GameSimsRenderer &r) {
	Robot::DrawObject(r);

	if (!nodePath.empty()) {
		//std::cout << "There's a node path" << std::endl;
		for (int i = 0; i <(nodePath.size() -1 ); i++) {
			//std::cout << "Hi there" << std::endl;
			r.DrawLine(Vector2(nodePath[i]->posX, nodePath[i]->posY), Vector2(nodePath[i + 1]->posX, nodePath[i + 1]->posY));
			//std::cout << "Line has been drawn" << std::endl;
		}
		//for (auto& i : nodePath) {}
		//for (auto it = nodePath.begin(); it != nodePath.end(); it++) {(*i)}
	}
}