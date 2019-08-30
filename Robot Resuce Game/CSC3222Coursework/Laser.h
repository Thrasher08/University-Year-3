#pragma once
#include "SimObject.h"
#include "RobotRescueGame.h"

namespace NCL {
	namespace CSC3222 {
		class Laser : public SimObject {
		public:
			Laser(Vector2& direction);
			~Laser();

			void DrawObject(GameSimsRenderer &r) override;
			bool UpdateObject(float dt, RobotRescueGame* game) override;
			RigidTypes getRType() {
				return rType;
			}
		};
	}
}

