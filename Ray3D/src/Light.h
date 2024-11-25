#pragma once

#include "Shader.h"


class Light
{
protected:
	glm::vec3 color;
	float intensity;

public:
	//Constructor & Destructor
	Light(float intensity, glm::vec3 color);
	virtual ~Light();

	virtual void SendToShader(Shader& program_id) = 0;
};


class PointLight : public Light
{
protected:
	glm::vec3 position;
	float constant, linear, quadratic;

public:
	//Constructor & Destructor
	PointLight(glm::vec3 position, float intensity = 1.0f, glm::vec3 color = glm::vec3(1.0f),
		float constant = 1.0f, float linear = 0.045f, float quadratic = 0.0075f);
	virtual ~PointLight();

	inline void SetPosition(const glm::vec3 position) { this->position = position; }

	void SendToShader(Shader& program_id);
};