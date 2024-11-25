#include "Material.h"


Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuse_tex_id, GLint specular_tex_id, glm::vec3 emissive_color, float emissive_intensity)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->emissiveColor = emissive_color;
	this->diffuseTex = diffuse_tex_id;
	this->specularTex = specular_tex_id;
	this->emissiveIntensity = emissive_intensity;
}


Material::~Material()
{
}


void Material::SendToShader(Shader& program_id)
{
	program_id.SetVec3f(this->ambient, "material.ambient");
	program_id.SetVec3f(this->diffuse, "material.diffuse");
	program_id.SetVec3f(this->specular, "material.specular");
	program_id.SetVec3f(this->emissiveColor, "material.emissiveColor");

	program_id.Set1i(this->diffuseTex, "material.diffuseTex");
	program_id.Set1i(this->specularTex, "material.specularTex");

	program_id.Set1f(this->emissiveIntensity, "material.emissiveIntensity");
}