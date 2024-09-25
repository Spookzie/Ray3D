#include "Material.h"


Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuse_tex_id, GLint specular_tex_id)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->diffuseTex = diffuse_tex_id;
	this->specularTex = specular_tex_id;
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