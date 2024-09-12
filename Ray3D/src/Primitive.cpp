#include "Primitive.h"


//**************************************************
//	PRIMITIVE CLASS	//
Primitive::Primitive()
{
}

Primitive::~Primitive()
{
}


void Primitive::Set(const Vertex* vertices, const unsigned int vertexCount, const GLuint* indices, const unsigned int indexCount)
{
	for (size_t i = 0; i < vertexCount; i++)
		this->vertices.push_back(vertices[i]);
	
	for (size_t i = 0; i < indexCount; i++)
		this->indices.push_back(indices[i]);
}
//**************************************************


//**************************************************
//	QUAD CLASS	//
Quad::Quad()
{
    Vertex vertices[] = {
        //Position                          //Color                         //Texcoords                 //Normal      
        glm::vec3(-0.5f,  0.5f,  0.0f),     glm::vec3(1.0f, 0.0f, 0.0f),    glm::vec2(0.0f, 1.0f),      glm::vec3(0.0f, 0.0f, 1.0f),    //index = 0 |   top left
        glm::vec3(-0.5f, -0.5f,  0.0f),     glm::vec3(0.0f, 1.0f, 0.0f),    glm::vec2(0.0f, 0.0f),      glm::vec3(0.0f, 0.0f, 1.0f),    //        1 |   bottom left
        glm::vec3( 0.5f, -0.5f,  0.0f),     glm::vec3(0.0f, 0.0f, 1.0f),    glm::vec2(1.0f, 0.0f),      glm::vec3(0.0f, 0.0f, 1.0f),    //        2 |   bottom right
        glm::vec3( 0.5f,  0.5f,  0.0f),     glm::vec3(0.0f, 1.0f, 0.0f),    glm::vec2(1.0f, 1.0f),      glm::vec3(0.0f, 0.0f, 1.0f)     //        3 |   top right
    };
    unsigned int vertexCount = sizeof(vertices) / sizeof(Vertex);

    GLuint indices[] = {
        0, 1, 2,    //Bottom Left triangle
        0, 2, 3     //Top right triangle
    };
    unsigned int indexCount = sizeof(indices) / sizeof(GLuint);


    this->Set(vertices, vertexCount, indices, indexCount);
}
//**************************************************


//**************************************************
//	TRIANGLE CLASS	//
Triangle::Triangle()
{
    Vertex vertices[] = {
        //Position                          //Color                         //Texcoords                 //Normal      
        glm::vec3(-0.5f,  0.5f,  0.0f),     glm::vec3(1.0f, 0.0f, 0.0f),    glm::vec2(0.0f, 1.0f),      glm::vec3(0.0f, 0.0f, 1.0f),    //index = 0 |   top left
        glm::vec3(-0.5f, -0.5f,  0.0f),     glm::vec3(0.0f, 1.0f, 0.0f),    glm::vec2(0.0f, 0.0f),      glm::vec3(0.0f, 0.0f, 1.0f),    //        1 |   bottom left
        glm::vec3(0.5f, -0.5f,  0.0f),     glm::vec3(0.0f, 0.0f, 1.0f),    glm::vec2(1.0f, 0.0f),      glm::vec3(0.0f, 0.0f, 1.0f),    //        2 |   bottom right
        glm::vec3(0.5f,  0.5f,  0.0f),     glm::vec3(0.0f, 1.0f, 0.0f),    glm::vec2(1.0f, 1.0f),      glm::vec3(0.0f, 0.0f, 1.0f)     //        3 |   top right
    };
    unsigned int vertexCount = sizeof(vertices) / sizeof(Vertex);

    GLuint indices[] = {
        0, 1, 2,    //Bottom Left triangle
    };
    unsigned int indexCount = sizeof(indices) / sizeof(GLuint);


    this->Set(vertices, vertexCount, indices, indexCount);
}
//**************************************************