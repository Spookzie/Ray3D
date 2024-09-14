#include "Shader.h"


Shader::Shader(const int version_major, const int version_minor, char* vertex_file, char* fragment_file, char* geometry_file)
    : versionMajor(version_major), versionMinor(version_minor)
{
    GLuint vertexShader = 0;
    GLuint geometryShader = 0;
    GLuint fragmentShader = 0;

    vertexShader = this->LoadShader(GL_VERTEX_SHADER, vertex_file);

    if (geometry_file != "")
        geometryShader = this->LoadShader(GL_GEOMETRY_SHADER, geometry_file);
    
    fragmentShader = this->LoadShader(GL_FRAGMENT_SHADER, fragment_file);

    this->LinkProgram(vertexShader, geometryShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(geometryShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glErrorCall( glDeleteProgram(this->id) );
}


//  UNIFORMS    //
//***************************************
void Shader::Set1i(GLint value, const GLchar* name)
{
    this->Use();

    glErrorCall( glUniform1i(glGetUniformLocation(this->id, name), value) );

    this->Unuse();
}

void Shader::Set1f(GLfloat value, const GLchar* name)
{
    this->Use();

    glErrorCall( glUniform1f(glGetUniformLocation(this->id, name), value) );

    this->Unuse();
}

void Shader::SetVec2f(glm::fvec2 value, const GLchar* name)
{
    this->Use();

    glErrorCall( glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value)) );

    this->Unuse();
}

void Shader::SetVec3f(glm::fvec3 value, const GLchar* name)
{
    this->Use();

    glErrorCall( glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value)) );

    this->Unuse();
}

void Shader::SetVec4f(glm::fvec4 value, const GLchar* name)
{
    this->Use();

    glErrorCall( glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value)) );

    this->Unuse();
}

void Shader::SetMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose)
{
    this->Use();

    glErrorCall( glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value)) );

    this->Unuse();
}

void Shader::SetMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose)
{
    this->Use();

    glErrorCall( glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value)) );

    this->Unuse();
}
//***************************************


std::string Shader::LoadShaderSource(char* file_name)
{
    std::string temp = "";
    std::string src = "";

    std::fstream inFile;

    inFile.open(file_name);

    //Reading the shader file
    if (inFile.is_open())
    {
        while (std::getline(inFile, temp))
            src += temp + "\n";
    }
    else
        std::cout << "ERROR::Shader.cpp::LoadShaderSource(): Failed to load file: " << file_name << std::endl;

    inFile.close();

    std::string version = std::to_string(this->versionMajor) + std::to_string(this->versionMinor) + "0";
    src.replace(src.find("#version"), 12, ("#version " + version));
    //std::cout << src << std::endl;

    return src;
}


GLuint Shader::LoadShader(GLenum type, char* file_name)
{
    char infoLog[512];
    GLint success;

    //Compiling the shader file
    GLuint shader = glCreateShader(type);
    std::string str_src = this->LoadShaderSource(file_name);
    const GLchar* src = str_src.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    //Checking for errors during compilation
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::Shader.cpp::LoadShader(): Failed to compile the shader: " << file_name << std::endl;
        std::cout << infoLog << std::endl;
    }

    return shader;
}


void Shader::LinkProgram(GLuint vertex_shader, GLuint geometry_shader, GLuint fragment_shader)
{
    char infoLog[512];
    GLint success;

    this->id = glCreateProgram();

    glAttachShader(this->id, vertex_shader);

    if (geometry_shader)
        glAttachShader(this->id, geometry_shader);

    glAttachShader(this->id, fragment_shader);

    glLinkProgram(this->id);

    //Error Checking
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->id, 512, NULL, infoLog);
        std::cout << "ERROR::Shader.cpp::LinkProgram(): Failed to link the program" << std::endl;
        std::cout << infoLog << std::endl;
    }

    glErrorCall( glUseProgram(0) );
}