#pragma once

#include "Renderer.h"
#include "Primitive.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Vertex.h"

#include <glm/gtc/matrix_transform.hpp>


class Mesh
{
private:
	unsigned int vertexCount;
	unsigned int indexCount;

	GLuint vao, vbo, ibo;
	
	glm::vec3 position, rotation, scale;
	glm::mat4 modelMatrix;

public:
	//Constructor & Destructor
	Mesh(Vertex* vertex_array, const unsigned int& vertex_count, GLuint* index_array, const unsigned int& index_count,
		glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation= glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));

	Mesh(Primitive* primitive, glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation= glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
	~Mesh();

	void Update();
	void Render(Shader* shader);

	inline void SetPosition(const glm::vec3 position) { this->position = position; }
	inline void SetRotation(const glm::vec3 rotation) { this->rotation = rotation; }
	inline void SetScale(const glm::vec3 scale) { this->scale = scale; }

	inline void Move(const glm::vec3 position) { this->position += position; }
	inline void Rotate(const glm::vec3 rotation) { this->rotation += rotation; }
	inline void Scale(const glm::vec3 scale) { this->scale += scale; }

private:
	void Init_vao(Vertex* vertex_array, const unsigned int& vertex_count, GLuint* index_array, const unsigned int& index_count);
	void Init_vao(Primitive* primitive);

	void UpdateUniforms(Shader* shader);
	void UpdateModelMatrix();
};