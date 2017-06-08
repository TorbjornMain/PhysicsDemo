#pragma once
#include "PhysicsObject.h"
#include "RigidBody.h"
class Spring : public PhysicsObject
{
public:
	Spring() { oType = SPRING; }
	~Spring();

	virtual void Update(float deltaTime);
	virtual void Draw();

	virtual void CollideWithBox(Box& other) {};
	virtual void CollideWithCircle(Circle& other) {};
	virtual void CollideWithPlane(Plane& other) {};

	RigidBody* body1;
	RigidBody* body2;
	glm::vec2 contact1 = glm::vec2(0,0);
	glm::vec2 contact2 = glm::vec2(0,0);
	float restLength = 1;
	float restoringForce = 1;
};

