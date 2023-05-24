#include "Joint.h"
#include "Body.h"
#include "Engine/Graphics.h"

Joint::Joint(Body* bodyA, Body* bodyB, float constant, float restLength) :
	m_bodyA{ bodyA },
	m_bodyB{ bodyB },
	m_springConstant{ constant },
	m_restLength{ restLength }
{
	if (!m_restLength) glm::distance(bodyA->m_position, bodyB->m_position);
}

void Joint::Step(float dt)
{
	glm::vec2 direction = m_bodyA->m_position - m_bodyB->m_position;
	if (direction == glm::vec2{ 0, 0 }) return;

	float length = glm::length(direction);

	float x = length - m_restLength;
	//if (x < 0) return;
	float f = -m_springConstant * x;

	m_bodyA->ApplyForce(glm::normalize(direction) * f);
	m_bodyB->ApplyForce(-glm::normalize(direction) * f);
}

void Joint::Draw(Graphics* graphics)
{
	graphics->DrawLine(graphics->WorldToScreen(m_bodyA->m_position), graphics->WorldToScreen(m_bodyB->m_position), glm::vec4{1});
}
