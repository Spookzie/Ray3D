#pragma once

#include "Vertex.h"

#include <vector>

#include <gl/glew.h>
#include <GLFW/glfw3.h>


class Primitive
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

public:
	//Constructor & Destructor
	Primitive();
	virtual ~Primitive();

	void Set(const Vertex* vertices, const unsigned int vertexCount, const GLuint* indices, const unsigned int indexCount);

	inline Vertex* GetVertices() { return this->vertices.data(); }
	inline GLuint* GetIndices() { return this->indices.data(); }
	inline const unsigned int GetVertexCount() { return this->vertices.size(); }
	inline const unsigned int GetIndexCount() { return this->indices.size(); }
};


class Quad : public Primitive
{
public:
	//Constructor & Destructor
	Quad();
};


class Triangle : public Primitive
{
public:
	//Constructor & Destructor
	Triangle();
};


class Pyramid : public Primitive
{
public:
	//Constructor & Destructor
	Pyramid();
};


class Cube : public Primitive
{
public:
	//Constructor & Destructor
	Cube();
};