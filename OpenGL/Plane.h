#pragma once
#include "PhysicsObject.h"

class Circle;

class Plane : public PhysicsObject
{
public:
	Plane();

	virtual void CollideWithBox(Box& other);
	virtual void CollideWithCircle(Circle& other);
	virtual void CollideWithPlane(Plane& other);

	virtual void Update(float deltaTime);
	virtual void Draw();

	glm::vec2 m_normal;
};

