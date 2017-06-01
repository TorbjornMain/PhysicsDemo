#include "stdafx.h"
#include "PhysicsObject.h"
#include "Circle.h"
#include "Plane.h"
#include "Box.h"

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
		CollideWithCircle(*(Circle*)(void*)&other);
		break;
	case BOX:
		CollideWithBox(*(Box*)(void*)&other);
		break;
	case PLANE:
		CollideWithPlane(*(Plane*)(void*)&other);
		break;
	default:
		break;
	}
}
