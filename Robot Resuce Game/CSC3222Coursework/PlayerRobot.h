#pragma once
#include "Robot.h"
#include "RobotRescueGame.h"

namespace NCL {
	namespace CSC3222 {
		class PlayerRobot : public Robot	{
		public:
			PlayerRobot();
			~PlayerRobot();

			bool UpdateObject(float dt, RobotRescueGame* game) override;
			RigidTypes getRType() {
				return rType;
			}

			Vector2 getPPos() {
				return position;
			}

		protected:
			Vector2 position;
		};
	}
}

