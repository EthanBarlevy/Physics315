#include "CollisionTest.h"
#include "Physics/CircleShape.h"
#include "Physics/Body.h"

void CollisionTest::Initialize()
{
	Test::Initialize();
	m_user = new Body(new CircleShape(1, { 0, 0, 1, 1 }), { 0, 0 }, { 0, 0 }, 1, Body::KINEMATIC);
	m_world->AddBody(m_user);

	auto body = new Body(new CircleShape(200, glm::vec4{ 1.0f }), { 0, -207.5 }, { 0, 0 }, 1, Body::STATIC);
	m_world->AddBody(body);

	body = new Body(new CircleShape(200, glm::vec4{ 1.0f }), { 209.7, 0 }, { 0, 0 }, 1, Body::STATIC);
	m_world->AddBody(body);

	body = new Body(new CircleShape(200, glm::vec4{ 1.0f }), { -209.7, 0 }, { 0, 0 }, 1, Body::STATIC);
	m_world->AddBody(body);
}

void CollisionTest::Update()
{
	Test::Update();

	glm::vec2 position = m_graphics->ScreenToWorld(m_input->GetMousePosition());
	m_user->m_velocity = position - m_user->m_position;
	m_user->m_position = position;

	if (m_input->GetMouseButton(0))
	{
		glm::vec2 velocity = { 0, 0 };//randomUnitCircle() * randomf(1, 3);
		float size = randomf(0.1f, 0.6f);

		auto body = new Body(new CircleShape(size, { randomf(), randomf(), randomf(), 1 }), position, velocity, size);
		body->m_damping = 0.4f;
		body->m_gravityScale = 0.5f;
		body->m_restitution = 1;

		m_world->AddBody(body);
	}
}

void CollisionTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void CollisionTest::Render()
{
	m_world->Draw(m_graphics);
}
