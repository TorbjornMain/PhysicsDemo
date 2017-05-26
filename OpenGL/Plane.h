#pragma once
#include "PhysicsObject.h"

class Circle;

class Plane : PhysicsObject
{
public:
	Plane();

	virtual void CollideWithBox(Box& other);
	virtual void CollideWithCircle(Circle& other);
	virtual void CollideWithPlane(Plane& other);

	virtual void Update();
	virtual void Draw();

	glm::vec2 m_normal;
};

