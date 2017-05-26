#include "stdafx.h"
#include "Plane.h"
#include "Circle.h"
#include "aie\Gizmos.h"

Plane::Plane()
{
	oType = PLANE;
}

void Plane::CollideWithBox(Box & other)
{
}

void Plane::CollideWithCircle(Circle & other)
{
	float vperp = glm::dot(other.m_velocity, m_normal);
	float d = glm::dot(other.m_position - m_position, m_normal);
	if ((d > 0 && d < other.m_radius && vperp < 0) || (d<0 && d> -other.m_radius && vperp > 0))
	{
		other.ApplyForce(-other.m_mass * vperp * m_normal * 2.f);
	}
}

void Plane::CollideWithPlane(Plane & other)
{
}

void Plane::Update()
{
}

void Plane::Draw()
{
	Gizmos::add2DLine(m_position - glm::vec2(m_normal.y, -m_normal.x) * 100.f, m_position + glm::vec2(m_normal.y, -m_normal.x) * 100.f, glm::vec4(0, 1, 0, 1));
}
