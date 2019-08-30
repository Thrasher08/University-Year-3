#pragma once
#include "SimObject.h"

namespace NCL {
	namespace CSC3222 {
		class CollisionVolume {
		public:
			enum collType { bBox, bSphere };		//Collision types of bounding box and bounding sphere
			CollisionVolume(collType coll, RigidBody *rb);
			~CollisionVolume();

			
			collType getColl() {
				return coll;
			}
			
			int getRadius() {
				return radius;
			}

			void setSize(int size) {
				this->size = size;
			}

			void setRadius(int radius) {
				this->radius = radius;
			}

			int getSize() {
				return size;
			}

			void setPos(Vector2 position) {
				this->position = position;
			}

			Vector2 getPos() {
				return position;
			}

			bool hasCollided(CollisionVolume *coll1, CollisionVolume *coll2) {
				return collided;
			}

			void setStatic(bool staticObject) {
				this->staticObject = staticObject;
			}

			bool isStatic() {
				return staticObject;
			}

			double getXCord() {
				return xCoordinate;
			}
			double getYCord() {
				return yCoordinate;
			}

			void setRBParent(RigidBody *rbParent) {
				this->rbParent = rbParent;
			}

			RigidBody* getRBParent() {
				return rbParent;
			}

		protected:
			Vector2 position;
			int size;
			int radius;
			double xCoordinate;
			double yCoordinate;
			collType coll;
			bool collided;
			bool staticObject;
			RigidBody *rbParent;
		};
	}
}
