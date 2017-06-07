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

void RigidBody::ResolveCollision(RigidBody & other, glm::vec2 contact, glm::vec2 * direction)
{
	glm::vec2 unitDisp = direction != nullptr ? *direction : glm::normalize(other.m_position - m_position);
	// get the component along this axis for each object
	glm::vec2 unitParallel(unitDisp.y, -unitDisp.x);
	// determine the total velocity of the contact points, boith linear and rotational
	float r1 = glm::dot(contact - m_position, -unitParallel);
	float r2 = glm::dot(contact - other.m_position, unitParallel);
	float v1 = glm::dot(m_velocity, unitDisp) - r1*m_angVel;
	float v2 = glm::dot(other.m_velocity, unitDisp) + r2*other.m_angVel;
	if (v1 > v2) // they're moving closer
	{
		// calculate the effective mass at contact point for each object
		// ie how much the contact point will move due to the force applied.
		float mass1 = 1.0f / (1.0f / m_mass + (r1*r1) / m_moment);
		float mass2 = 1.0f / (1.0f / other.m_mass + (r2*r2) / other.m_moment);
		glm::vec2 force = (1.0f + m_resistution)*mass1*mass2 / (mass1 + mass2)*(v1 - v2)*unitDisp;
		//apply equal and opposite forces
		ApplyForce(-force, contact - m_position);
		other.ApplyForce(force, contact - other.m_position);
	}
}

void RigidBody::Update(float deltaTime)
{
	m_position += m_velocity * deltaTime;
	m_rotation += m_angVel * deltaTime;
	m_velocity *= 0.99f;
	m_angVel *= 0.99f;
	ApplyForce(glm::vec2(0, -9.8) * m_mass * deltaTime);
}
