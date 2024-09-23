#include "Model.h"


Model::Model(glm::vec3 position, Material* material, Texture* orTex_dif, Texture* orTex_spec, std::vector<Mesh*> meshes)
	: pos(position), material(material), overrideTexDiffuse(orTex_dif), overrideTexSpecular(orTex_spec)
{
	for (auto* i : meshes)
		this->meshes.push_back(new Mesh(*i));

    for (auto& i : this->meshes)
    {
        i->Move(this->pos);
        i->SetOrigin(this->pos);
    }
}

Model::~Model()
{
	for (auto* i : this->meshes)
		delete i;
}


void Model::Rotate(const glm::vec3 rotation)
{
    for (auto& i : this->meshes)
        i->Rotate(rotation);
}


void Model::Update()
{
}


void Model::Render(Shader* shader)
{
    //Update the uniforms
    this->UpdateUniforms();

    this->material->SendToShader(*shader);

    //Use a program
    shader->Use();

    //Bind textures
    this->overrideTexDiffuse->Bind(0);
    this->overrideTexSpecular->Bind(1);

    //Draw
    for(auto* i : this->meshes)
        i->Render(shader);
}


void Model::UpdateUniforms()
{
}