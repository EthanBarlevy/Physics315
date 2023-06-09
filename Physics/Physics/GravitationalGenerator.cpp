#include "GravitationalGenerator.h"
#include "Body.h"

void GravitationalGenerator::Apply(std::vector<class Body*> bodies)
{
	for (auto body : bodies)
	{
		body->ApplyForce({ 0, -m_strength });
	}
}
