#include "ParticleTest.h"
#include "Physics/CircleShape.h"
#include "Physics/Body.h"
#include "Engine/Random.h"

void ParticleTest::Initialize()
{
	Test::Initialize();

}

void ParticleTest::Update()
{
	Test::Update();
	if (m_input->GetMouseButton(0))
	{
		glm::vec2 velocity = randomUnitCircle() * randomf(2, 3);
		auto body = new Body(new CircleShape(randomf(0.5f, 2), { randomf(0, 255), randomf(0, 255), randomf(0, 255), randomf(0, 255) }), m_graphics->ScreenToWorld(m_input->GetMousePosition()), velocity);
		body->m_damping = 1;
		m_world->AddBody(body);
	}
}

void ParticleTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void ParticleTest::Render()
{
	m_world->Draw(m_graphics);
}
