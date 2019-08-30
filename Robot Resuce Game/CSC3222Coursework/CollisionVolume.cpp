#include "CollisionVolume.h"

using namespace NCL;
using namespace CSC3222;

CollisionVolume::CollisionVolume(collType col, RigidBody *rb)
{

	coll = col;
	//size = 1;
	radius = 16;
	isStatic();
	setRBParent(rb);
}


CollisionVolume::~CollisionVolume()
{
}

