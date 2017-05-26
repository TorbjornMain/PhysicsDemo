#include "stdafx.h"
#include "PhysicsObject.h"


PhysicsObject::PhysicsObject()
{
}


PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::CheckCollision(PhysicsObject & other)
{
	switch (other.oType)
	{
	case CIRCLE:
		CollideWithCircle();
		break;
	case BOX:
		CollideWithBox();
		break;
	case PLANE:
		CollideWithPlane();
		break;
	default:
		break;
	}
}
