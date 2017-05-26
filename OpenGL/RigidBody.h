#pragma once
#include "PhysicsObject.h"
#include <glm/glm/glm.hpp>
class RigidBody : public PhysicsObject
{
public:
	RigidBody();
	~RigidBody();
	void ApplyForce(glm::vec2 force);
	virtual void Update();

	float m_mass;
	glm::vec2 m_velocity;
};

