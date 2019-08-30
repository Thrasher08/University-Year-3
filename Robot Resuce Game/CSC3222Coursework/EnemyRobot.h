#pragma once
#include "Robot.h"
#include "GameMap.h"

namespace NCL {
	namespace CSC3222 {
		class EnemyRobot : public Robot {

		public:
			EnemyRobot(GameMap* map);
			~EnemyRobot();

			bool UpdateObject(float dt, RobotRescueGame* game) override;

			void AttackPlayer();
			void HideFromPlayer();
			void MoveTowardsPlayer();

			RigidTypes getRType() {
				return rType;
			}
			void DrawObject(GameSimsRenderer &r) override;

			void setEPos(Vector2 position) {
				this->position = position;
			}

			Vector2 getEPos() {
				return position;
			}

		protected:
			float	thinkTime;
			bool	moving;
			bool hello;
			std::vector<MapNode*> nodePath;
			Vector2 position;
			GameMap* map;
		};
	}
}

