/*#include "Flocking.h"
using namespace NCL;
using namespace CSC3222;
using namespace Rendering;
Flocking::Flocking()
{

}


Flocking::~Flocking()
{

}

Vector2 Flocking::Allign(SimObject* o) {

	for (int i = 0; i<boids.size(); i++) {
		if (boids[i]->GetPosition().x== o->GetPosition().x){
			continue;
		}

		float distance = sqrt(pow(o->GetPosition().x - boids[i]->GetPosition().x, 2) + pow(o->GetPosition().y - boids[i]->GetPosition().y, 2));

		if (distance > alignThresh) {
			continue;
		}
		direction += boids[i]->GetPosition();
	}
	return direction.Normalised();
}

Vector2 Flocking::Seperate(SimObject* o) {
	
	for (int i = 0; i<boids.size(); i++) {
		if (boids[i]->GetPosition().x == o->GetPosition().x) {
			continue;
		}

		float distance = sqrt(pow(o->GetPosition().x - boids[i]->GetPosition().x, 2) + pow(o->GetPosition().y - boids[i]->GetPosition().y, 2));

		if (distance > sepThresh) {
			continue;
		}

		float strength = 1.0f - (distance / sepThresh);
		direction += (o->GetPosition() - boids[i]->GetPosition().Normalised() * strength);
			return direction.Normalised();
	}
}


Vector2 Flocking::Cohesion(SimObject* o) {
	Vector2 avgPos = o->GetPosition();
	float count = 1;
	
	for (int i = 0; i<boids.size(); i++) {
		if (boids[i] == o) {
			continue;
	}
	float distance = sqrt(pow(o->GetPosition().x - boids[i]->GetPosition().x, 2) + pow(o->GetPosition().y - boids[i]->GetPosition().y, 2));
		if (distance > cohThresh) {
		continue;
		
	}
	avgPos += boids[i]->GetPosition();
	count++;
	
	}
	avgPos /= count;
	direction = avgPos - o->GetPosition();
	return direction.Normalised();
}

/*Vector2 Flocking::Avoid(SimObject* o) {
		
			for (int i = 0; i<boids.size(); i++) {
				if (boids[i]->GetPosition().x == o->GetPosition().x) {	//type
					continue;
				
			}
			float distance = sqrt(pow(o->GetPosition().x - boids[i]->GetPosition().x, 2) + pow(o->GetPosition().y - boids[i]->GetPosition().y, 2));
			
				if (distance > avoidThresh) {
					continue;
				
			}
			direction += (o->GetPosition - boids[i]->GetPosition().Normalised();
			
		}
		return direction.Normalised();
		}

void Flocking::Flock(SimObject *o,float dt) {
	
	Vector2 dir;
	dir = dir+Allign(o);
	dir += Seperate(o);
	dir += Cohesion(o);
	dir += Avoid(o);
		o->GetPosition += direction * dt;
	
}*/