#pragma once
#include <glm/glm/glm.hpp>
enum ObjectType
{
	CIRCLE,
	BOX,
	PLANE,
	SPRING
};

class Plane;
class Circle;
class Box;

class PhysicsObject
{
public:
	PhysicsObject();
	~PhysicsObject();
	

	virtual void CollideWithBox(Box& other) = 0;
	virtual void CollideWithCircle(Circle& other) = 0;
	virtual void CollideWithPlane(Plane& other) = 0;

	void CheckCollision(PhysicsObject& other);

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	ObjectType oType;
	glm::vec2 m_position;
};

