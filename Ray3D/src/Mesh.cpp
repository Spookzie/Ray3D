#include "Mesh.h"


void Mesh::Init_vao()
{
    //Creating VAO, VBO, & IBO
    glErrorCall( glCreateVertexArrays(1, &this->vao) );
    glErrorCall( glBindVertexArray(this->vao) );

    glErrorCall( glGenBuffers(1, &this->vbo) );
    glErrorCall( glBindBuffer(GL_ARRAY_BUFFER, this->vbo) ) ;
    glErrorCall( glBufferData(GL_ARRAY_BUFFER, this->vertexCount * sizeof(Vertex), this->vertexArray, GL_STATIC_DRAW) );

    if (this->indexCount > 0)
    {
        glErrorCall( glGenBuffers(1, &this->ibo) );
        glErrorCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo) );
        glErrorCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indexCount * sizeof(GLuint), this->indexArray, GL_STATIC_DRAW) );
    }


    //  Setting up vertex attribute pointers   //
    //Position
    glErrorCall( glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position)) );
    glErrorCall( glEnableVertexAttribArray(0) );
                 
    //Color      
    glErrorCall( glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color)) );
    glErrorCall( glEnableVertexAttribArray(1) );
                 
    //Texcoord   
    glErrorCall( glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord)) );
    glErrorCall( glEnableVertexAttribArray(2) );
                 
    //Normal     
    glErrorCall( glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal)) );
    glErrorCall( glEnableVertexAttribArray(3) );
}


//	Constructor & Destructor    //
//***************************************
Mesh::Mesh(Vertex* vertex_array, const unsigned int& vertex_count, GLuint* index_array, const unsigned int& index_count, glm::vec3 origin, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : vertexCount(vertex_count), indexCount(index_count), origin(origin), position(position), rotation(rotation), scale(scale)
{
    //Initializing vertex & index arrays
    this->vertexArray = new Vertex[this->vertexCount];
    for (size_t i = 0; i < vertex_count; i++)
        this->vertexArray[i] = vertex_array[i];
    
    this->indexArray = new GLuint[this->indexCount];
    for (size_t i = 0; i < index_count; i++)
        this->indexArray[i] = index_array[i];


	this->Init_vao();
    this->UpdateModelMatrix();
}

Mesh::Mesh(Primitive* primitive, glm::vec3 origin, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : origin(origin), position(position), rotation(rotation), scale(scale)
{
    //Initializing vertex & index arrays
    this->vertexCount = primitive->GetVertexCount();
    this->vertexArray = new Vertex[this->vertexCount];
    for (size_t i = 0; i < primitive->GetVertexCount(); i++)
        this->vertexArray[i] = primitive->GetVertices()[i];

    this->indexCount = primitive->GetIndexCount();
    this->indexArray = new GLuint[this->indexCount];
    for (size_t i = 0; i < primitive->GetIndexCount(); i++)
        this->indexArray[i] = primitive->GetIndices()[i];


    this->Init_vao();
    this->UpdateModelMatrix();
}

Mesh::Mesh(const Mesh& obj, glm::vec3 origin)
    : origin(origin)
{
    this->position = obj.position;
    this->rotation = obj.rotation;
    this->scale = obj.scale;
    this->vertexCount = obj.vertexCount;
    this->indexCount = obj.indexCount;


    //Initializing vertex & index arrays
    this->vertexArray = new Vertex[this->vertexCount];
    for (size_t i = 0; i < obj.vertexCount; i++)
        this->vertexArray[i] = obj.vertexArray[i];

    this->indexArray = new GLuint[this->indexCount];
    for (size_t i = 0; i < obj.indexCount; i++)
        this->indexArray[i] = obj.indexArray[i];


    this->Init_vao();
    this->UpdateModelMatrix();
}

Mesh::~Mesh()
{
    glErrorCall( glDeleteVertexArrays(1, &this->vao) );
    glErrorCall( glDeleteBuffers(1, &this->vbo) );
    
    if (this->indexCount > 0)
        glErrorCall( glDeleteBuffers(1, &this->ibo) );

    delete[] this->vertexArray;
    delete[] this->indexArray;
}
//***************************************


void Mesh::Update()
{    
}


void Mesh::Render(Shader* shader)
{
    this->UpdateModelMatrix();
    this->UpdateUniforms(shader);

    shader->Use();

    glErrorCall( glBindVertexArray(this->vao) );

    if (this->indexCount == 0)
    {
        glErrorCall( glDrawArrays(GL_TRIANGLES, 0, this->vertexCount) );
    }
    else
        glErrorCall( glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 0));

    //Unbind
    glErrorCall( glBindVertexArray(0) );
    glErrorCall( glUseProgram(0) );
    glErrorCall( glBindTexture(GL_TEXTURE_2D, 0) );
}


void Mesh::UpdateUniforms(Shader* shader)
{
    shader->SetMat4fv(this->modelMatrix, "modelMatrix");
}


void Mesh::UpdateModelMatrix()
{
    this->modelMatrix = glm::mat4(1.0f);
    this->modelMatrix = glm::translate(this->modelMatrix, this->origin);
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    this->modelMatrix = glm::translate(this->modelMatrix, this->position - this->origin);
    this->modelMatrix = glm::scale(this->modelMatrix, this->scale);
}