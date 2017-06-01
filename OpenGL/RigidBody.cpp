#include "stdafx.h"
#include "RigidBody.h"


RigidBody::RigidBody()
{
}


RigidBody::~RigidBody()
{
}

void RigidBody::ApplyForce(glm::vec2 force)
{
	m_velocity += force / m_mass;
}

void RigidBody::ApplyForce(glm::vec2 force, glm::vec2 pos)
{
	ApplyForce(force);
	m_angVel += (force.y * pos.x - force.x * pos.y) / (m_moment);
}

void RigidBody::Update(float deltaTime)
{
	m_position += m_velocity * deltaTime;
	m_rotation += m_angVel * deltaTime;
	m_velocity *= 0.99f;
	m_angVel *= 0.99f;
	ApplyForce(glm::vec2(0, -9.8) * m_mass * deltaTime);
}
