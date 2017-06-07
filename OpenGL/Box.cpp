#include "stdafx.h"
#include "Box.h"
#include "aie\Gizmos.h"
#include <glm\glm\ext.hpp>
#include "Plane.h"
#include "Circle.h"
Box::Box()
{
	oType = BOX;
	m_moment = (1.0f / 12.0f) * m_mass * m_width * m_height;
}


Box::~Box()
{
}

void Box::Update(float deltaTime)
{
	RigidBody::Update(deltaTime);
	float c = std::cos(m_rotation);
	float s = std::sin(m_rotation);
	m_localX = glm::vec2(c, s);
	m_localY = glm::vec2(-s, c);
}

void Box::Draw()
{
	glm::mat4 m = glm::eulerAngleZ(m_rotation);
	Gizmos::add2DAABBFilled(m_position, glm::vec2(m_width/2, m_height/2), glm::vec4(0, 0, 1, 1), &m);
}

void Box::CollideWithBox(Box & other)
{
	
}

void Box::CollideWithCircle(Circle & other)
{
	glm::vec2 circlePos = other.m_position - m_position;
	float w2 = m_width / 2, h2 = m_height / 2;
	int numContacts = 0;
	// contact is in our box coordinates
	glm::vec2 contact(0, 0);
	// check the four corners to see if any of them are inside the circle
	for (float x = -w2; x < m_width; x += m_width)
	{
		for (float y = -h2; y < m_height; y += m_height)
		{
			glm::vec2 p = x*m_localX + y*m_localY;
			glm::vec2 dp = p - circlePos;
			if (dp.x*dp.x + dp.y*dp.y < other.m_radius*other.m_radius)
			{
				numContacts++;
				contact += glm::vec2(x, y);
			}
		}
	}


	glm::vec2* direction = NULL;
	// get the local position of the circle centre
	glm::vec2 localPos(glm::dot(m_localX, circlePos), glm::dot(m_localY, circlePos));
	if (localPos.y < h2 && localPos.y > -h2)
	{
		if (localPos.x > 0 && localPos.x < w2 + other.m_radius)
		{
			numContacts++;
			contact += glm::vec2(w2, localPos.y);
			direction = new glm::vec2(m_localX);
		}
		if (localPos.x < 0 && localPos.x > -(w2 + other.m_radius))
		{
			numContacts++;
			contact += glm::vec2(-w2, localPos.y);
			direction = new glm::vec2(-m_localX);
		}
	}
	if (localPos.x < w2 && localPos.x > -w2)
	{
		if (localPos.y > 0 && localPos.y < h2 + other.m_radius)
		{
			numContacts++;
			contact += glm::vec2(localPos.x, h2);
			direction = new glm::vec2(m_localY);
		}
		if (localPos.y < 0 && localPos.y > -(h2 + other.m_radius))
		{
			numContacts++;
			contact += glm::vec2(localPos.x, -h2);
			direction = new glm::vec2(-m_localY);
		}
	}


	if (numContacts > 0)
	{
		// average, and convert back into world coords
		contact = m_position + (1.0f / numContacts) * (m_localX*contact.x + m_localY*contact.y);
		ResolveCollision(other, contact, direction);
	}
	delete direction;
}

void Box::CollideWithPlane(Plane & other)
{
	int numContacts = 0;
	glm::vec2 contact;
	float contactV = 0;
	float radius = 0.5f * std::fminf(m_width, m_height);

	float comFromPlane = glm::dot(m_position - other.m_position, other.m_normal);
	float penetration = 0;

	for (float x = -m_width / 2; x < m_width; x += m_width)
	{
		for (float y = -m_height / 2; y < m_height; y += m_height)
		{
			// get the position of the corner in world space
			glm::vec2 p = m_position + x*m_localX + y*m_localY;
			float distFromPlane = glm::dot(p - other.m_position, other.m_normal);
			// this is the total velocity of the point
			float velocityIntoPlane = glm::dot(m_velocity + m_angVel*(-y*m_localX + x*m_localY), other.m_normal);
			// if this corner is on the opposite side from the COM,
			// and moving further in, we need to resolve the collision
			if ((distFromPlane > 0 && comFromPlane < 0 && velocityIntoPlane > 0)
				|| (distFromPlane < 0 && comFromPlane > 0 && velocityIntoPlane < 0))
			{
				numContacts++;
				contact += p;
				contactV += velocityIntoPlane;
				if (comFromPlane >= 0)
				{
					if (penetration > distFromPlane)
						penetration = distFromPlane;
				}
				else
				{
					if (penetration < distFromPlane)
						penetration = distFromPlane;
				}
			}
		}
	}

	if (numContacts > 0)
	{
		// get the average collision velocity into the plane
		// (covers linear and rotational velocity of all corners involved)
		float collisionV = contactV / (float)numContacts;
		// get the acceleration required to stop (restitution = 0) or reverse (restitution = 1) the average velocity into the plane
		glm::vec2 acceleration = -other.m_normal * ((1.0f + m_resistution) * collisionV);

		glm::vec2 localContact = (contact / (float)numContacts) - m_position;
		// this is the perpendicular distance we apply the force at relative to the COM, so Torque = F*r
		float r = glm::dot(localContact, glm::vec2(other.m_normal.y, -other.m_normal.x));
		// work out the "effective mass" - this is a combination of moment of
		// inertia and mass, and tells us how much the contact point velocity
		// will change with the force we're applying
		float mass0 = 1.0f / (1.0f / m_mass + (r*r) / m_moment);
		// and apply the force
		ApplyForce(acceleration*mass0, localContact);
		m_position -= other.m_normal * penetration;
	}
}
