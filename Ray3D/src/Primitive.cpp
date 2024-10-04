#include "Primitive.h"


//	PRIMITIVE CLASS	//
//***********************************
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
//***********************************


//	QUAD CLASS	//
//***********************************
Quad::Quad()
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
        0, 2, 3     //Top right triangle
    };
    unsigned int indexCount = sizeof(indices) / sizeof(GLuint);


    this->Set(vertices, vertexCount, indices, indexCount);
}
//***********************************


//	TRIANGLE CLASS	//
//***********************************
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
//***********************************


//	PYRAMID CLASS	//
//***********************************
Pyramid::Pyramid()
{
    Vertex vertices[] = {
        //Position								//Color							//Texcoords					//Normals
        //Triangle front 
        //Normal here is z = 1 because the triangle facing us
        glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, 1.f),   //Top
        glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),   //Front Bottom Left
        glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),   //Front Bottom Right

        //Triangle left
        //Normal here is x = -1 because the triangle facing left
        glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),  //Top
        glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),  //Back Bottom Left
        glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),  //Front Bottom Left

        //Triangle back
        //Normal here is z = -1 because the triangle facing back
        glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, -1.f),  //Top
        glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),  //Back Bottom Right
        glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),  //Back Bottom Left

        //Triangles right
        //Normal here is x = 1 because the triangle facing right
        glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(1.f, 0.f, 0.f),   //Top
        glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),   //Front Bottom Right
        glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),   //Back Bottom Right
    };
    unsigned vertexCount = sizeof(vertices) / sizeof(Vertex);

    this->Set(vertices, vertexCount, nullptr, 0);
}
//***********************************


//	PYRAMID CLASS	//
//***********************************
Cube::Cube()
{
    Vertex vertices[] =
    {
        //Position								//Color							//Texcoords					//Normals
        glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

        glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
        glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
        glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
        glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, -1.f)
    };
    unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3,

        7, 6, 1,
        7, 1, 0,

        4, 5, 6,
        4, 6, 7,

        3, 2, 5,
        3, 5, 4
    };
    unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

    this->Set(vertices, nrOfVertices, indices, nrOfIndices);
}
//***********************************