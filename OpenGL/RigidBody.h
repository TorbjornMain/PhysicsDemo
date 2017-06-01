#pragma once
#include "PhysicsObject.h"
#include <glm/glm/glm.hpp>
class RigidBody : public PhysicsObject
{
public:
	RigidBody();
	~RigidBody();
	void ApplyForce(glm::vec2 force);
	void ApplyForce(glm::vec2 force, glm::vec2 pos);
	virtual void Update(float deltaTime);

	float m_resistution = 1;
	float m_mass = 1;
	float m_moment = 1;
	float m_rotation = 0;
	float m_angVel = 0;
	glm::vec2 m_velocity;
	
};

