#pragma once
#include <vector>
#include "../../Common/Vector2.h"
#include <iostream>
#include <String>

namespace NCL {
	using namespace Maths;
	namespace CSC3222 {
		class RigidBody;
		class CollisionVolume;

		class GameSimsPhysics	{
		public:
			GameSimsPhysics();
			~GameSimsPhysics();

			void Update(float dt);

			void AddRigidBody(RigidBody* b);
			void RemoveRigidBody(RigidBody* b);

			void AddCollider(CollisionVolume* c);
			void RemoveCollider(CollisionVolume* c);

			double distance(CollisionVolume *coll1, CollisionVolume *coll2);
			Vector2 dVector(CollisionVolume *coll1, CollisionVolume *coll2);

			double impulse(CollisionVolume *coll1, CollisionVolume *coll2);

			bool hasCollided(CollisionVolume *coll1, CollisionVolume *coll2);

		protected:
			void Integration(float dt);
			void CollisionDetection(float dt);

			std::vector<RigidBody*>			allBodies;
			std::vector<CollisionVolume*>	allColliders;
		};
	}
}

