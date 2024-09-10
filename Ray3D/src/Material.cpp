#include "Material.h"


Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->diffuseTex = diffuseTex;
	this->specularTex = specularTex;
}

Material::~Material()
{
}


void Material::SendToShader(Shader& program_id)
{
	program_id.SetVec3f(this->ambient, "material.ambient");
	program_id.SetVec3f(this->diffuse, "material.diffuse");
	program_id.SetVec3f(this->specular, "material.specular");
	program_id.Set1i(this->diffuseTex, "material.diffuseTex");
	program_id.Set1i(this->specularTex, "material.specularTex");
}