#include "GameSimsPhysics.h"
#include "RigidBody.h"
#include "CollisionVolume.h"
#include "PlayerRobot.h"
#include "../../Common/Vector2.h"

using namespace NCL;
using namespace CSC3222;
using namespace std;

GameSimsPhysics::GameSimsPhysics()	{

}

GameSimsPhysics::~GameSimsPhysics()	{

}

void GameSimsPhysics::Update(float dt) {
	Integration(dt);
	CollisionDetection(dt);
}

void GameSimsPhysics::AddRigidBody(RigidBody* b) {
	allBodies.emplace_back(b);
}

void GameSimsPhysics::RemoveRigidBody(RigidBody* b) {
	auto at = std::find(allBodies.begin(), allBodies.end(), b);

	if (at != allBodies.end()) {
		//maybe delete too?
		allBodies.erase(at);
	}
}

void GameSimsPhysics::AddCollider(CollisionVolume* c) {
	allColliders.emplace_back(c);
}

void GameSimsPhysics::RemoveCollider(CollisionVolume* c) {
	auto at = std::find(allColliders.begin(), allColliders.end(), c);

	if (at != allColliders.end()) {
		//maybe delete too?
		allColliders.erase(at);
	}
}

void GameSimsPhysics::Integration(float dt) {
	for (int i = 0; i < allBodies.size(); i++)
	{
		Vector2 acceleration = (allBodies[i]->force * allBodies[i]->inverseMass);

		allBodies[i]->velocity = allBodies[i]->velocity + (acceleration * dt);
		allBodies[i]->velocity *= 0.975f;	//friction
		allBodies[i]->position = allBodies[i]->position + (allBodies[i]->velocity * dt);
		allBodies[i]->force = Vector2(0, 0);
	}

}

void GameSimsPhysics::CollisionDetection(float dt) {
	//cout << allColliders.size() << endl;
	for (int i = 0; i <= allColliders.size(); i++) {

		for (int j = i + 1; j < allColliders.size(); j++) {

			double collDist = distance(allColliders[i], allColliders[j]);
			int collRange = 8;

			if (collDist < collRange) {

				if (hasCollided(allColliders[i], allColliders[j]) == true) {


					double pDist = (allColliders[i]->getRadius() + allColliders[2]->getRadius()) - collDist;
					Vector2 normal = dVector(allColliders[i], allColliders[j]);

					//cout << "normal: " << normal << "penetration: " << pDist << "\n\n";

					double totalmass = allColliders[i]->getRBParent()->getIMass() + allColliders[j]->getRBParent()->getIMass();
					double rImpulse = impulse(allColliders[i], allColliders[j]);


					Vector2 posA = (normal * pDist * (allColliders[j]->getRBParent()->getIMass()) / totalmass);
					Vector2 posB = (normal * pDist * (allColliders[i]->getRBParent()->getIMass()) / totalmass);


					allColliders[j]->getRBParent()->SetPosition(allColliders[j]->getRBParent()->GetPosition() - posA);
					allColliders[i]->getRBParent()->SetPosition(allColliders[i]->getRBParent()->GetPosition() + posB);

					Vector2 velA = allColliders[j]->getRBParent()->GetVelocity() - (normal * allColliders[j]->getRBParent()->getIMass() * rImpulse);
					Vector2 velB = allColliders[i]->getRBParent()->GetVelocity() - (normal * allColliders[i]->getRBParent()->getIMass() * rImpulse);
					
					allColliders[j]->getRBParent()->SetVelocity(velA);
					allColliders[i]->getRBParent()->SetVelocity(velB);
				}
			}


		}
	}
}

double GameSimsPhysics::distance(CollisionVolume *coll1, CollisionVolume *coll2) {
	
	double dBetween;

	double x1 = coll1->getPos().x;
	double x2 = coll2->getPos().x;
	double y1 = coll1->getPos().y;
	double y2 = coll2->getPos().y;

	dBetween = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	return dBetween;
}

Vector2 GameSimsPhysics::dVector(CollisionVolume *coll1, CollisionVolume *coll2) {
	
	Vector2 dirVector;
	double dBetween;
	Vector2 difference = coll1->getPos() - coll2->getPos();

	dBetween = distance(coll1, coll2);

	double hyp = sqrt(pow(difference.x, 2) + pow(difference.y, 2));
	if (hyp == 0) {
		return Vector2(0, 0);
	}
	else {

		Vector2 normal = Vector2(
			difference.x / hyp,
			difference.y / hyp
		);

		return normal;
	}
}

double GameSimsPhysics::impulse(CollisionVolume *coll1, CollisionVolume *coll2) {
	
	double rImpulse;
	double rImpulseX;
	double rImpulseY;

	Vector2 velA = coll1->getRBParent()->GetVelocity();
	Vector2 velB = coll2->getRBParent()->GetVelocity();

	Vector2 normal = dVector(coll1, coll2);

	double elasticity = 1;

	Vector2 rVel = velB - velA;
	double totalmass = coll1->getRBParent()->getIMass() + coll2->getRBParent()->getIMass();

	rImpulseX = (-(1 + elasticity) * rVel.x * normal.x);
	rImpulseY = (-(1 + elasticity) * rVel.y * normal.y);

	rImpulse = rImpulseX + rImpulseY / totalmass;
	
	return rImpulse;

}

bool GameSimsPhysics::hasCollided(CollisionVolume *coll1, CollisionVolume *coll2) {

	double collDist = distance(coll1, coll2);
	//Vector2 normal = dVector(coll1, coll2);

	int collRange = 5;

	if (collDist > collRange) {
		//Don't print anything further than this range
	}
	else {
		//cout << collDist << endl;
	}

	if (coll1->getColl() == CollisionVolume::bSphere && coll2->getColl() == CollisionVolume::bSphere) {

		if (collDist < (coll1->getRadius() + coll2->getRadius())) {

			double pDist = (coll1->getRadius() + coll2->getRadius()) - collDist;
			return true;
		}
	}
	else if (coll1->getColl() == CollisionVolume::bBox && coll2->getColl() == CollisionVolume::bBox) {

		if (collDist < ((coll1->getSize() / 2) + (coll2->getSize() / 2))) {
			return true;
		}
	}
	else if (coll1->getColl() == CollisionVolume::bBox && coll2->getColl() == CollisionVolume::bSphere) {

		if (coll1->getRadius() > collDist) {

			if (coll1->isStatic() == true) {
				return true;
			}
			else {
				return true;
			}

		}

	}
	else {		//bBox & bSphere
		return false;
	}
}