#pragma once
#include "Test.h"

class ParticleTest : public Test
{
public:
	void Initialize() override;
	
	void Update() override;
	void FixedUpdate() override;
	void Render() override;

};