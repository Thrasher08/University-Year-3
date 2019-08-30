#pragma once
#include "../../Common/Vector2.h"

namespace NCL {
	using namespace Maths;
	namespace CSC3222 {
		class RigidBody	{
			friend class GameSimsPhysics;
		public:
			RigidBody();
			~RigidBody();

			enum RigidTypes { PLAYER, ENEMY, LASER, COLLECTABLE };

			Vector2 GetPosition() const {
				return position;
			}

			void SetPosition(const Vector2& newPosition) {
				position = newPosition;
			}

			Vector2 GetVelocity() const {
				return velocity;
			}

			void SetVelocity(const Vector2& newVelocity) {
				velocity = newVelocity;
			}

			void AddForce(const Vector2& newForce) {
				force += newForce;
			}

			float getIMass() {
				return inverseMass;
			}

			RigidTypes getRType() {
				return rType;
			}

			void setIMass(float inverseMass) {
				this->inverseMass = inverseMass;
			}


		protected:
			Vector2 position;
			Vector2 velocity;
			Vector2 force;

			RigidTypes rType;

			float inverseMass;
			float elasticity;


		};
	}
}
