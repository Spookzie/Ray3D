#pragma once

#include "Shader.h"


class Material
{
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 emissiveColor;
	GLint diffuseTex;
	GLint specularTex;
	float emissiveIntensity;

public:
	//Constructor & Destructor
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuse_tex_id, GLint specular_tex_id,
		glm::vec3 emissive_color = glm::vec3(0.0f), float emissive_intensity = 0.0f);
	virtual ~Material();

	void SendToShader(Shader& program_id);
};