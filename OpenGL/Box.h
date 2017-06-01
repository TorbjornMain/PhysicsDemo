#pragma once
#include "RigidBody.h"
class Box : public RigidBody
{
public:
	Box();
	~Box();

	virtual void Update(float deltaTime);
	virtual void Draw();

	virtual void CollideWithBox(Box& other);
	virtual void CollideWithCircle(Circle& other);
	virtual void CollideWithPlane(Plane& other);
};

