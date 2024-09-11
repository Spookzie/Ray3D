#include "Mesh.h"


Mesh::Mesh(Vertex* vertex_array, const unsigned& vertex_count, GLuint* index_array, const unsigned& index_count)
{
	this->Init_VertexData(vertex_array, vertex_count, index_array, index_count);
	this->Init_vao();
	this->Init_ModelMatrix();
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
    this->UpdateUniforms(shader);

    shader->Use();

    glErrorCall( glBindVertexArray(this->vao) );
    glErrorCall( glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0));
}


//	INITIALIZERS	//
//***************************************
void Mesh::Init_VertexData(Vertex* vertex_array, const unsigned& vertex_count, GLuint* index_array, const unsigned& index_count)
{
	for (size_t i = 0; i < vertex_count; i++)
		this->vertices.push_back(vertex_array[i]);
	
	for (size_t i = 0; i < index_count; i++)
		this->indices.push_back(index_array[i]);
}

void Mesh::Init_vao()
{
    glErrorCall( glCreateVertexArrays(1, &this->vao) );
    glErrorCall( glBindVertexArray(this->vao) );

    glErrorCall( glGenBuffers(1, &this->vbo) );
    glErrorCall( glBindBuffer(GL_ARRAY_BUFFER, this->vbo) );
    glErrorCall( glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW) );

    glErrorCall( glGenBuffers(1, &this->ibo) );
    glErrorCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo) );
    glErrorCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW) );


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

void Mesh::Init_ModelMatrix()
{
    this->position = glm::vec3(0.0f);
    this->rotation = glm::vec3(0.0f);
    this->scale = glm::vec3(1.0f);

    this->modelMatrix = glm::mat4(1.0f);
    this->modelMatrix = glm::translate(this->modelMatrix, this->position);
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    this->modelMatrix = glm::scale(this->modelMatrix, this->scale);
}
//***************************************


void Mesh::UpdateUniforms(Shader* shader)
{
    shader->SetMat4fv(this->modelMatrix, "modelMatrix");
}