#include "stdafx.h"
#include "Circle.h"
#include "aie\Gizmos.h"
#include "PhysicsObject.h"
#include "Plane.h"

Circle::Circle()
{
	 oType = CIRCLE; 
}

Circle::Circle(float radius) : m_radius(radius) { oType = CIRCLE; }

void Circle::Update()
{
	RigidBody::Update();
}

void Circle::Draw()
{
	Gizmos::add2DCircle(m_position, m_radius, 10, glm::vec4(1, 0, 0, 1));
}


void Circle::CollideWithBox(Box & other)
{
}

void Circle::CollideWithCircle(Circle& other)
{
	glm::vec2 dirVec = other.m_position - m_position;
	float len = dirVec.length();
	if (len < m_radius + other.m_radius)
	{
		dirVec = dirVec / len;
	}
}

void Circle::CollideWithPlane(Plane & other)
{
	float vperp = glm::dot(m_velocity, other.m_normal);
	float d = glm::dot(m_position - other.m_position, other.m_normal);
	if ((d > 0 && d < m_radius && vperp < 0) || (d<0 && d> -m_radius && vperp > 0))
	{
		ApplyForce(-m_mass * vperp * other.m_normal * 2.f);
}
