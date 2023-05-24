#include "GravitationalForce.h"
#include "Body.h"

void GravitationalForce::Apply(std::vector<class Body*> bodies)
{
	for (size_t i = 0; i < bodies.size() - 1; i++)
	{
		for (size_t j = i + 1; j < bodies.size(); j++)
		{
			Body* bodyA = bodies[i];
			Body* bodyB = bodies[j];
			
			float mass = bodyA->m_mass * bodyB->m_mass;

			glm::vec2 direction = bodyA->m_position - bodyB->m_position;
			float distance = glm::length(direction);
			if (!distance) continue;
			distance = glm::max(1.0f, distance);

			float force = m_strength * (mass / (distance));

			glm::vec2 nDirection = glm::normalize(direction);
			bodyA->ApplyForce(-nDirection * force);
			bodyB->ApplyForce(nDirection * force);
		}
	}
}
