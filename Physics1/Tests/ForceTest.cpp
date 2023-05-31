#include "ForceTest.h"
#include "Physics/Body.h"
#include "Physics/CircleShape.h"
#include "Engine/Random.h"
#include "Physics/GravitationalGenerator.h"
#include "Physics/GravitationalForce.h"
#include "Physics/PointForce.h"
#include "Physics/AreaForce.h"
#include "Physics/DragForce.h"

#define POINT_FORCE
//#define AREA_FORCE
//#define DRAG_FORCE

void ForceTest::Initialize()
{
	Test::Initialize();


#if defined(POINT_FORCE)
	auto body = new Body(new CircleShape(3, { 1, 1, 1, 0.2f }), m_graphics->ScreenToWorld({ 400, 300 }), { 0, 0 }, 0, Body::STATIC)
		;
	ForceGenerator* forceGenerator = new PointForce(body, 20);
	m_world->AddForceGenerator(forceGenerator);
#elif defined(AREA_FORCE)
	auto body = new Body(new CircleShape(3, { 1, 1, 1, 0.2f }), m_graphics->ScreenToWorld({ 400, 300 }), { 0, 0 }, 0, Body::STATIC)
		;
	ForceGenerator* forceGenerator = new AreaForce(body, 20, -45);
	m_world->AddForceGenerator(forceGenerator);
#elif defined(DRAG_FORCE)
	auto body = new Body(new CircleShape(3, { 1, 1, 1, 0.2f }), m_graphics->ScreenToWorld({ 400, 300 }), { 0, 0 }, 0, Body::STATIC)
		;
	ForceGenerator* forceGenerator = new DragForce(body, 0.5f);
	m_world->AddForceGenerator(forceGenerator);
#endif

	//GravitationalForce* force= new GravitationalForce(400);
	//m_world->AddForceGenerator(force);
}

void ForceTest::Update()
{
	Test::Update();
	if (m_input->GetMouseButton(0))
	{
		glm::vec2 velocity = randomUnitCircle() * randomf(0.2f, 0.3f);

		float size = randomf(1, 5);
		auto body = new Body(new CircleShape(size * 5, { randomf(0, 255), randomf(0, 255), randomf(0, 255), randomf(0, 255) }), m_graphics->ScreenToWorld(m_input->GetMousePosition()), velocity);
		body->m_damping = 1;
		body->m_gravityScale = 1;

		m_world->AddBody(body);
	}
}

void ForceTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void ForceTest::Render()
{
	m_world->Draw(m_graphics);
}
