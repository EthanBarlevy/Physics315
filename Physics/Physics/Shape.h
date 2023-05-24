#pragma once
#include <glm/glm.hpp>

class Shape
{
public:
	Shape() {}
	Shape(const glm::vec4& color) : color{ color } {}

	virtual void Draw(class Graphics* graphics, const glm::vec2& position) = 0;
public:
	glm::vec4 color{ 1, 1, 1, 1 };
};