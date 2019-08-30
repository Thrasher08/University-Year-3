#pragma once
#include "../../Common/Vector2.h"
#include "RobotRescueGame.h"
#include "RigidBody.h"

namespace NCL {
	using namespace Maths;
	namespace Rendering {
		class TextureBase;
	}
	namespace CSC3222 {
		class GameSimsRenderer;
		class TextureManager;
		class RobotRescueGame;
		class RigidBody;
		class CollisionVolume;

		class SimObject	: public RigidBody {
		public:
			SimObject();
			~SimObject();

			enum States {ATTACK, HIDE, MOVE};			

			void SetCollider(CollisionVolume * c) {
				collider = c;
			}

			CollisionVolume* GetCollider() const {
				return collider;
			}

			virtual bool UpdateObject(float dt, RobotRescueGame* game) = 0;

			virtual void DrawObject(GameSimsRenderer &r) = 0;

			static void InitObjects(RobotRescueGame* game, TextureManager* manager);

			void UpdateCollider();

			void setState(States state) {
				this->state = state;
			}

		protected:
			CollisionVolume*		collider;
			RigidBody*				rb;
			States state;
			Rendering::TextureBase* texture;
			static TextureManager*  texManager;
			static RobotRescueGame* game;
		};
	}
}

