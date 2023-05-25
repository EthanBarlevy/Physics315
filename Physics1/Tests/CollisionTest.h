#pragma once
#pragma once
#include "Test.h"

class CollisionTest : public Test
{
public:
	void Initialize() override;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;

private:
	class Body* m_user{ nullptr };
};