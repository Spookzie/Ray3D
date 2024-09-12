#include "Mesh.h"


Mesh::Mesh(Vertex* vertex_array, const unsigned int& vertex_count, GLuint* index_array, const unsigned int& index_count, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;

	this->Init_vao(vertex_array, vertex_count, index_array, index_count);
    this->UpdateModelMatrix();
}

Mesh::Mesh(Primitive* primitive, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;

    this->Init_vao(primitive);
    this->UpdateModelMatrix();
}

Mesh::~Mesh()
{
    glErrorCall( glDeleteVertexArrays(1, &this->vao) );
    glErrorCall( glDeleteBuffers(1, &this->vbo) );
    glErrorCall( glDeleteBuffers(1, &this->ibo) );
}


void Mesh::Update()
{
    
}


void Mesh::Render(Shader* shader)
{
    this->UpdateModelMatrix();
    this->UpdateUniforms(shader);

    shader->Use();

    glErrorCall( glBindVertexArray(this->vao) );
    glErrorCall( glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 0));
}


//	INITIALIZERS	//
//***************************************
void Mesh::Init_vao(Vertex* vertex_array, const unsigned int& vertex_count, GLuint* index_array, const unsigned int& index_count)
{
    this->vertexCount = vertex_count;
    this->indexCount = index_count;

    //Creating VAO, VBO, & IBO
    glErrorCall( glCreateVertexArrays(1, &this->vao) );
    glErrorCall( glBindVertexArray(this->vao) );

    glErrorCall( glGenBuffers(1, &this->vbo) );
    glErrorCall( glBindBuffer(GL_ARRAY_BUFFER, this->vbo) );
    glErrorCall( glBufferData(GL_ARRAY_BUFFER, this->vertexCount * sizeof(Vertex), vertex_array, GL_STATIC_DRAW) );

    glErrorCall( glGenBuffers(1, &this->ibo) );
    glErrorCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo) );
    glErrorCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indexCount * sizeof(GLuint), index_array, GL_STATIC_DRAW) );


    //  Setting up vertex attribute pointers   //
    //Position
    glErrorCall( glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position)));
    glErrorCall( glEnableVertexAttribArray(0));

    //Color
    glErrorCall( glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color)));
    glErrorCall( glEnableVertexAttribArray(1));

    //Texcoord
    glErrorCall( glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord)));
    glErrorCall( glEnableVertexAttribArray(2));

    //Normal
    glErrorCall( glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal)));
    glErrorCall( glEnableVertexAttribArray(3));
}


void Mesh::Init_vao(Primitive* primitive)
{
    this->vertexCount = primitive->GetVertexCount();
    this->indexCount = primitive->GetIndexCount();

    //Creating VAO, VBO, & IBO
    glErrorCall( glCreateVertexArrays(1, &this->vao) );
    glErrorCall( glBindVertexArray(this->vao) );

    glErrorCall( glGenBuffers(1, &this->vbo) );
    glErrorCall( glBindBuffer(GL_ARRAY_BUFFER, this->vbo) ) ;
    glErrorCall( glBufferData(GL_ARRAY_BUFFER, this->vertexCount * sizeof(Vertex), primitive->GetVertices(), GL_STATIC_DRAW) );

    glErrorCall( glGenBuffers(1, &this->ibo) );
    glErrorCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo) );
    glErrorCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indexCount * sizeof(GLuint), primitive->GetIndices(), GL_STATIC_DRAW) );


    //  Setting up vertex attribute pointers   //
    //Position
    glErrorCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position)));
    glErrorCall(glEnableVertexAttribArray(0));

    //Color
    glErrorCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color)));
    glErrorCall(glEnableVertexAttribArray(1));

    //Texcoord
    glErrorCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord)));
    glErrorCall(glEnableVertexAttribArray(2));

    //Normal
    glErrorCall(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal)));
    glErrorCall(glEnableVertexAttribArray(3));
}
//***************************************


void Mesh::UpdateUniforms(Shader* shader)
{
    shader->SetMat4fv(this->modelMatrix, "modelMatrix");
}


void Mesh::UpdateModelMatrix()
{
    this->modelMatrix = glm::mat4(1.0f);
    this->modelMatrix = glm::translate(this->modelMatrix, this->position);
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    this->modelMatrix = glm::scale(this->modelMatrix, this->scale);
}