#include "RobotRescueGame.h"
#include "SimObject.h"
#include "GameMap.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"
#include "GameSimsPhysics.h"
#include "PlayerRobot.h"
#include "EnemyRobot.h"
#include "CollectableRobot.h"
#include "Flocking.h"
#include "../../Common/Vector2.h"

#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"

using namespace NCL;
using namespace CSC3222;

RobotRescueGame::RobotRescueGame()	{
	renderer	= new GameSimsRenderer();
	texManager	= new TextureManager();
	physics		= new GameSimsPhysics();
	//flock	= new Flocking();
	SimObject::InitObjects(this, texManager);
	InitialiseGame();
}

RobotRescueGame::~RobotRescueGame()	{
	delete currentMap;
	delete texManager;
	delete renderer;
	delete physics;
}

void RobotRescueGame::Update(float dt) {
	for (auto i : newObjects) {
		gameObjects.emplace_back(i);
	}
	newObjects.clear();

	gameTime += dt;

	renderer->Update(dt);

	currentMap->DrawMap(*renderer);

	srand((int)(gameTime * 1000.0f));

	for (auto i = gameObjects.begin(); i != gameObjects.end(); ) {
		
		Vector2 pPos;
		Vector2 ePos;
		//CollisionVolume* pVol;
		
		if ((*i)->getRType() == RigidBody::PLAYER) {
			//pPos = (*i)->GetPosition();
			
			//std::cout << "Please Work " << pPos << std::endl;

		}

		if ((*i)->getRType() == RigidBody::ENEMY) {
			pPos = testRobot->GetPosition();
			//std::cout << "Player Pos: " << pPos << std::endl;
			ePos = (*i)->GetPosition();
			//std::cout << "Enemy Pos: " << ePos << std::endl;

			double range = 60;
			double dBetween = distance(pPos, ePos);
			if (dBetween < range) {
				std::cout << "Distance: " << dBetween << std::endl;
				(*i)->setState(SimObject::ATTACK);

			}
			else {
				Vector2 normal = dVector(pPos, ePos);
				(*i)->SetVelocity(normal * 50);
				(*i)->setState(SimObject::MOVE);
			}
			
		}
		
		
		
		if (!(*i)->UpdateObject(dt, this)) { //object has said its finished with
			physics->RemoveCollider((*i)->GetCollider());
			physics->RemoveRigidBody((*i));
			delete (*i);
			//gameObjects.erase(i);
			i = gameObjects.erase(i);
		}
		else {
			(*i)->DrawObject(*renderer);
			++i;
		}

	}	

	if (Window::GetKeyboard()->KeyPressed(KEYBOARD_P)) {
		//flock->setDirection(Vector2(1, 1));
	} /*if (flocking) {
		for (int i = 0; i < flock->getBoids().size(); i++) {
			//flock->Flock(flock->getBoids()[0],dt);
		}
		
	}*/
	physics->Update(dt);

	renderer->DrawString("Robot Rescue! ", Vector2(380, 700));

	renderer->DrawString("Current Score: " + std::to_string(currentScore), Vector2(10, 10));
	renderer->DrawString("Lives: " + std::to_string(lives), Vector2(850, 10));

	renderer->Render();
}

void RobotRescueGame::InitialiseGame() {
	delete currentMap;
	for (auto o : gameObjects) {
		delete o;
	}
	gameObjects.clear();

	currentMap = new GameMap("GameSimsRobotMap.txt", gameObjects, *texManager, physics);

	renderer->SetScreenProperties(16, currentMap->GetMapWidth(), currentMap->GetMapHeight());

	testRobot = new PlayerRobot();

	AddNewObject(testRobot);

	for (int i = 0; i < 10/*10*/; ++i) {
		float randomX = 32.0f + (rand() % 416);
		float randomY = 32.0f + (rand() % 256);
		AddEnemyRobot(Vector2(randomX, randomY));
		
	}

	for (int i = 0; i < 20/*20*/; ++i) {
		float randomX = 32.0f + (rand() % 416);
		float randomY = 32.0f + (rand() % 256);
		AddCollectableRobot(Vector2(randomX, randomY));
	}

	gameTime		= 0;
	currentScore	= 0;
	lives			= 3;
}

void RobotRescueGame::AddNewObject(SimObject* object) {
	newObjects.emplace_back(object);
	physics->AddRigidBody(object);
	if (object->GetCollider()) {
		physics->AddCollider(object->GetCollider());
	}
}

void RobotRescueGame::AddEnemyRobot(const Vector2& position) {
	std::cout << "Print" << std::endl;
	EnemyRobot* robot = new EnemyRobot(currentMap);

	robot->SetPosition(position);

	AddNewObject(robot);
	std::cout << robot->GetPosition() /16 << std::endl;
	std::cout << "Robot Added" << std::endl;
}

void RobotRescueGame::AddCollectableRobot(const Vector2& position) {
	CollectableRobot* robot = new CollectableRobot();

	robot->SetPosition(position);

	AddNewObject(robot);
	//flock->addBoid(robot);
}

double RobotRescueGame::distance(Vector2 a, Vector2 b) {
	
	double dBetween;
	//Vector2 a;
	//Vector2 b;

	double x1 = a.x;
	double x2 = b.x;
	double y1 = a.y;
	double y2 = b.y;

	dBetween = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

	return dBetween;

}

Vector2 RobotRescueGame::dVector(Vector2 a, Vector2 b) {

	Vector2 dirVector;
	double dBetween;
	double differenceX = a.x - b.x;
	double differenceY = a.y - b.y;

	dBetween = distance(a, b);

	double hyp = sqrt(pow(differenceX, 2) + pow(differenceY, 2));
	if (hyp == 0) {
		return Vector2(0, 0);
	}
	else {

		Vector2 normal = Vector2(
			differenceX / hyp,
			differenceY / hyp
		);

		return normal;
	}
}