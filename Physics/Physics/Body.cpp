#include "Body.h"
#include "Integrator.h"
#include "World.h"
#include "CircleShape.h"

void Body::ApplyForce(const glm::vec2& force)
{
	m_force += force;
}

void Body::Step(float dt)
{
	if (type != DYNAMIC) return;

	// gravity
	ApplyForce(World::gravity * m_gravityScale * m_mass);

	Integrator::SemiImplicitEuler(*this, dt);
	ClearForce();

	// damping
	m_velocity *= 1.0f / (1.0f + dt * m_damping);
}

void Body::Draw(Graphics* m_graphics)
{
	m_shape->Draw(m_graphics, m_position);
}

bool Body::Intersects(Body* body)
{
	glm::vec2 direction = body->m_position - m_position;
	float distance = glm::length(direction);
	float radius = dynamic_cast<CircleShape*>(this->m_shape)->radius + dynamic_cast<CircleShape*>(body->m_shape)->radius;
	return distance <= radius;
}
