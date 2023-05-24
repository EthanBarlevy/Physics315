#include "JointTest.h"
#include "CircleShape.h"
#include "World.h"
#include "Body.h"
#include "Joint.h"

#define STRING_CONSTANT 200;

void JointTest::Initialize()
{
	Test::Initialize();

	m_anchor = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 400, 100 }, { 0, 0 }, 0, Body::KINEMATIC);
	m_world->AddBody(m_anchor);

	auto bodyB = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 400, 200 }, { 0, 0 }, 1, Body::DYNAMIC);
	bodyB->m_gravityScale = 250;
	bodyB->m_damping = 0.75f;
	m_world->AddBody(bodyB);

	auto joint = new Joint(m_anchor, bodyB, STRING_CONSTANT, 1);
	m_world->AddJoint(joint);
}

void JointTest::Update()
{
	Test::Update();
	m_anchor->m_position = m_input->GetMousePosition();
}

void JointTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void JointTest::Render()
{
	m_world->Draw(m_graphics);
	m_graphics->DrawCircle(m_input->GetMousePosition(), 10, { randomf(), randomf(), randomf(), 1 });
}

