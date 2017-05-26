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

void RigidBody::Update()
{
	m_position += m_velocity;
	ApplyForce(glm::vec2(0, -9.8) * m_mass * 1.f / 60.f);
}
