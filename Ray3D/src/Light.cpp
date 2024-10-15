#include "Light.h"


//	BASE LIGHT CLASS	//
//***********************************
Light::Light(float intensity, glm::vec3 color)
	: intensity(intensity), color(color)
{
}

Light::~Light()
{
}
//***********************************


//	POINT LIGHT CLASS	//
//***********************************
PointLight::PointLight(glm::vec3 position, float intensity, glm::vec3 color, float constant, float linear, float quadratic)
	: position(position), Light(intensity, color), constant(constant), linear(linear), quadratic(quadratic)
{
}

PointLight::~PointLight()
{
}


void PointLight::SendToShader(Shader& program_id)
{
	program_id.SetVec3f(this->position, "pointLight.position");
	program_id.SetVec3f(this->color, "pointLight.color");

	program_id.Set1f(this->intensity, "pointLight.intensity");
	program_id.Set1f(this->constant, "pointLight.constant");
	program_id.Set1f(this->linear, "pointLight.linear");
	program_id.Set1f(this->quadratic, "pointLight.quadratic");
}
//***********************************