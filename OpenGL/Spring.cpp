#include "stdafx.h"
#include "Spring.h"
#include "aie\Gizmos.h"



Spring::~Spring()
{
}

void Spring::Update(float deltaTime)
{
	glm::vec2 p2 = body2->ToWorld(contact2);
	glm::vec2 p1 = body1->ToWorld(contact1);
	glm::vec2 dist = p2 - p1;
	float len = sqrtf(dist.x*dist.x + dist.y* dist.y);
	// apply damping
	glm::vec2 dv = body2->m_velocity - body1->m_velocity;
	float damping = 0.1f; // make this a member
	glm::vec2 force = dist * restoringForce * (restLength - len) - damping * dv;
	body1->ApplyForce(-force*deltaTime, p1 - body1->m_position);
	body2->ApplyForce(force*deltaTime, p2 - body2->m_position);
}

void Spring::Draw()
{
	glm::vec2 p2 = body2->ToWorld(contact2);
	glm::vec2 p1 = body1->ToWorld(contact1);
	Gizmos::add2DLine(p1, p2, glm::vec4(0, 1, 1, 1));

}
