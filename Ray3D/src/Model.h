#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"


class Model
{
private:
	Material* material;
	Texture* overrideTexDiffuse;
	Texture* overrideTexSpecular;
	std::vector<Mesh*> meshes;
	glm::vec3 pos;

public:
	//Constructor & Destructor
	Model(glm::vec3 position, Material* material, Texture* orTex_dif, Texture* orTex_spec, std::vector<Mesh*> meshes);
	virtual ~Model();

	void Rotate(const glm::vec3 rotation);

	void Update();
	void Render(Shader* shader);

private:
	void UpdateUniforms();
};