#include "stdafx.h"
#include "Circle.h"
#include "aie\Gizmos.h"
#include "PhysicsObject.h"
#include "Plane.h"
#include "Box.h"

Circle::Circle()
{
	 oType = CIRCLE; 
}

Circle::Circle(float radius) : m_radius(radius) { oType = CIRCLE; }

void Circle::Update(float deltaTime)
{
	m_moment = 0.5f* m_mass * m_radius*m_radius;
	RigidBody::Update(deltaTime);
}

void Circle::Draw()
{
	Gizmos::add2DCircle(m_position, m_radius, 10, glm::vec4(1, 0, 0, 1));
	Gizmos::add2DLine(m_position, m_position + (m_radius * glm::vec2(std::cos(m_rotation), std::sin(m_rotation))), glm::vec4(0, 0, 0, 1));
}


void Circle::CollideWithBox(Box & other)
{
	other.CollideWithCircle(*this);
}

void Circle::CollideWithCircle(Circle& other)
{
	if (glm::length(other.m_position - m_position) < other.m_radius + m_radius)
	{
		glm::vec2 unitDisp = glm::normalize(other.m_position - m_position);
		glm::vec2 contact = m_position + (unitDisp * m_radius);
		ResolveCollision(other, contact);
	}
}

void Circle::CollideWithPlane(Plane & other)
{
		glm::normalize(other.m_normal);

		float vperp = glm::dot(m_velocity, other.m_normal);
		float d = glm::dot(m_position - other.m_position, other.m_normal);
		if ((d > 0 && d < m_radius && vperp < 0) || (d < 0 && d > -m_radius && vperp > 0))
		{
			ApplyForce(-m_mass * vperp * other.m_normal * (1 + m_resistution));
			m_position += other.m_normal * (m_radius - d);
		}
}

