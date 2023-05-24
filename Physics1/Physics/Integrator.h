#pragma once
#include "Body.h"

namespace Integrator
{
	void ExplicitEuler(Body& body, float dt)
	{
		body.m_position += body.m_velocity * dt;
		body.m_velocity += (body.m_force * body.m_invMass) * dt;
	}
	void SemiImplicitEuler(Body& body, float dt)
	{
		body.m_velocity += (body.m_force * body.m_invMass) * dt;
		body.m_position += body.m_velocity * dt;
	}
}