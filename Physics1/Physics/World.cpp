#include "World.h"
#include "Body.h"
#include "ForceGenerator.h"
#include "Joint.h"

glm::vec2 World::gravity{ 0 , -9.81f };

World::~World()
{
	for (auto body : m_bodies)
	{
		delete body;
	}
	m_bodies.clear();
}

void World::Step(float dt)
{
	if (!m_bodies.empty() && !m_forceGenerators.empty())
	{
		std::vector<Body*> bodies(m_bodies.begin(), m_bodies.end());
		for (auto generator : m_forceGenerators)
		{
			generator->Apply(bodies);
		}
	}

	for (auto body : m_joints)
	{
		body->Step(dt);
	}
	
	for (auto body : m_bodies)
	{
		body->Step(dt);
	}

}

void World::Draw(Graphics* graphics)
{
	for (auto body : m_joints)
	{
		body->Draw(graphics);
	}

	for (auto body : m_forceGenerators)
	{
		body->Draw(graphics);
	}
	
	for (auto body : m_bodies)
	{
		body->Draw(graphics);
	}
}

void World::AddBody(Body* body)
{
	m_bodies.push_back(body);
}

void World::RemoveBody(Body* body)
{
	m_bodies.remove(body);
}

void World::AddForceGenerator(ForceGenerator* generator)
{
	m_forceGenerators.push_back(generator);
}

void World::AddJoint(Joint* joint)
{
	m_joints.push_back(joint);
}

void World::RemoveJoint(Joint* joint)
{
	m_joints.remove(joint);
}
