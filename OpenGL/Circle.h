#pragma once
#include "RigidBody.h"

class Box;

class Circle : public RigidBody
{
public:
	Circle();
	Circle(float radius); 

	virtual void Update();
	virtual void Draw();

	virtual void CollideWithBox(Box& other);
	virtual void CollideWithCircle(Circle& other);
	virtual void CollideWithPlane(Plane& other);

	float m_radius = 0;
};

