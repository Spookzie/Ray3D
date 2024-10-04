#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>


class Light
{
private:
	glm::vec3 pos;
	glm::vec3 color;

public:
	//Constructor & Destructor
	Light();
	virtual ~Light();
};