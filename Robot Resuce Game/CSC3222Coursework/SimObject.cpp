#include "SimObject.h"
#include "CollisionVolume.h"

using namespace NCL;
using namespace CSC3222;

TextureManager*  SimObject::texManager = nullptr;
RobotRescueGame* SimObject::game = nullptr;

SimObject::SimObject()	{
	texture		= nullptr;
	collider	= new CollisionVolume(CollisionVolume::bSphere, this);
	//collider->setPos(Vector2(0, 0));
}

SimObject::~SimObject()	{
	delete collider;
}

void SimObject::InitObjects(RobotRescueGame* game, TextureManager* texManager) {
	SimObject::game			= game;
	SimObject::texManager	= texManager;
}

void SimObject::UpdateCollider() {
	Vector2 offset(8, 8);
	this->collider->setPos(this->GetPosition() + offset);
}