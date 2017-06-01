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
	other.CollideWithPlane(*this);
}

void Plane::CollideWithPlane(Plane & other)
{
}

void Plane::Update(float deltaTime)
{
}

void Plane::Draw()
{
	Gizmos::add2DLine(m_position - glm::vec2(m_normal.y, -m_normal.x) * 100.f, m_position + glm::vec2(m_normal.y, -m_normal.x) * 100.f, glm::vec4(0, 1, 0, 1));
}
