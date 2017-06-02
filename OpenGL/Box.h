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

	glm::vec2 m_localX;
	glm::vec2 m_localY;
	float m_width = 1;
	float m_height = 1;
};

