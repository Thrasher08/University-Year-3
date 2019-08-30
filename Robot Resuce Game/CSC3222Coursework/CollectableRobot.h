#pragma once
#include "SimObject.h"
#include "RobotRescueGame.h"

namespace NCL {
	namespace CSC3222 {
		enum RobotType {
			Score,
			Speed,
			Armour,
			Freeze,
			Special
		};

		class CollectableRobot : public SimObject {
		public:
			CollectableRobot();
			CollectableRobot(RobotType type);
			~CollectableRobot();

			void DrawObject(GameSimsRenderer &r) override;
			bool UpdateObject(float dt, RobotRescueGame* game) override;
			RigidTypes getRType() {
				return rType;
			}

		protected:
			RobotType type;

			bool	collected;
			Vector2 spawnPoint;
		};
	}
}

