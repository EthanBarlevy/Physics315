#pragma once
#include "Test.h"

class JointTest : public Test
{
public:
	void Initialize() override;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;

private:
	class Body* m_anchor{ nullptr };
};