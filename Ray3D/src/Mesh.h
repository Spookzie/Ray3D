#pragma once

#include <iostream>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Vertex.h"


class Mesh
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	GLuint vao, vbo, ibo;
	
	glm::vec3 position, rotation, scale;

	glm::mat4 modelMatrix;

public:
	//Constructor & Destructor
	Mesh(Vertex* vertex_array, const unsigned& vertex_count, GLuint* index_array, const unsigned& index_count);
	~Mesh();

	void Update();
	void Render(Shader* shader);

private:
	void Init_VertexData(Vertex* vertex_array, const unsigned& vertex_count, GLuint* index_array, const unsigned& index_count);
	void Init_vao();
	void Init_ModelMatrix();

	void UpdateUniforms(Shader* shader);
};