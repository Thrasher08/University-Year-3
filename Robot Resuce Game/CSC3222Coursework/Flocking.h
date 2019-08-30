/*#pragma once
#include "../../Common/Vector2.h"
#include "SimObject.h"
#include "PlayerRobot.h"

namespace NCL {
	namespace CSC3222 {
		using namespace Maths;

			class Flocking : public SimObject
			{
			public:
				Flocking();
				~Flocking();

				void addBoid(SimObject* o) {
					boids.emplace_back();
				}

				std::vector<SimObject*> getBoids() {
					return boids;
				}

				void setDirection(Vector2 direction) {
					this->direction = direction;
				}
				void Flock(SimObject* o, float dt);
				bool UpdateObject(float dt, RobotRescueGame* game) override;
				void DrawObject(GameSimsRenderer &r) override;

				Vector2 Seperate(SimObject* o);
				Vector2 Allign(SimObject* o);
				Vector2 Cohesion(SimObject* o);
				Vector2 Avoid(SimObject* o);
				

			protected:

				Vector2 direction;
				std::vector<SimObject*> boids;

				float avoidThresh;
				float cohThresh;
				float sepThresh;
				float alignThresh;

			};

		}
	}
}*/