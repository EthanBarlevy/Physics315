#include "ForceTest.h"
#include "Body.h"
#include "CircleShape.h"
#include "Random.h"
#include "GravitationalGenerator.h"
#include "GravitationalForce.h"
#include "PointForce.h"
#include "AreaForce.h"
#include "DragForce.h"

//#define POINT_FORCE
//#define AREA_FORCE
//#define DRAG_FORCE

void ForceTest::Initialize()
{
	Test::Initialize();


#if defined(POINT_FORCE)
	auto body = new Body(new CircleShape(200, { 1, 1, 1, 0.2f }), { 400, 300 }, { 0, 0 }, 0, Body::STATIC)
		;
	ForceGenerator* forceGenerator = new PointForce(body, 2000);
	m_world->AddForceGenerator(forceGenerator);
#elif defined(AREA_FORCE)
	auto body = new Body(new CircleShape(200, { 1, 1, 1, 0.2f }), { 400, 300 }, { 0, 0 }, 0, Body::STATIC)
		;
	ForceGenerator* forceGenerator = new AreaForce(body, 2000, -45);
	m_world->AddForceGenerator(forceGenerator);
#elif defined(DRAG_FORCE)
	auto body = new Body(new CircleShape(200, { 1, 1, 1, 0.2f }), { 400, 300 }, { 0, 0 }, 0, Body::STATIC)
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
		glm::vec2 velocity = randomUnitCircle() * randomf(200, 300);

		float size = randomf(1, 5);
		auto body = new Body(new CircleShape(size * 5, { randomf(0, 255), randomf(0, 255), randomf(0, 255), randomf(0, 255) }), m_input->GetMousePosition(), velocity);
		body->m_damping = 1;
		body->m_gravityScale = 30;

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
