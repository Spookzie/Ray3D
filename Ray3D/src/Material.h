#pragma once

#include "Shader.h"


class Material
{
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLint diffuseTex;
	GLint specularTex;

public:
	//Constructor & Destructor
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuse_tex_id, GLint specular_tex_id);
	virtual ~Material();

	void SendToShader(Shader& program_id);
};