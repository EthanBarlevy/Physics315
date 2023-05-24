#pragma once
#include <glm/glm.hpp>

class Body
{
public: 
	enum Type
	{
		STATIC,
		KINEMATIC,
		DYNAMIC
	};
public:
	Body(class Shape* shape, const glm::vec2& position, const glm::vec2& velocity = {0, 0}, float mass = 1, Type type = Type::DYNAMIC) :
		m_shape{ shape },
		m_position{ position },
		m_velocity{ velocity },
		m_mass{ mass },
		type { type }
	{
		m_invMass = (mass == 0) ? 0 : 1 / mass;
	}

	void ApplyForce(const glm::vec2& force);
	void Step(float dt);
	void Draw(class Graphics* m_graphics);

	bool Intersects(Body* body);

	void ClearForce() { m_force = glm::vec2{ 0, 0 }; }

public:
	class Shape* m_shape{ nullptr };

	Type type{ Type::DYNAMIC };

	glm::vec2 m_position{ 0, 0 };
	glm::vec2 m_velocity{ 0, 0 };
	glm::vec2 m_force{ 0, 0 };

	float m_mass{ 1 };
	float m_invMass{ 1 };
	float m_damping{ 1 };
	float m_gravityScale{ 1 };
};