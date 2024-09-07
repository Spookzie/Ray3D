#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"


class Shader
{
private:
	GLuint id;

public:
	//Constructor & Destructor
	Shader(char* vertex_file, char* fragment_file, char* geometry_file = (char*)"");
	~Shader();

	inline void Use() { glErrorCall( glUseProgram(this->id) ); };
	inline void Unuse() { glErrorCall( glUseProgram(0) ); };

	//Setting Uniforms
	void Set1i(GLint value, const GLchar* name);
	void Set1f(GLfloat value, const GLchar* name);
	void SetVec2f(glm::fvec2 value, const GLchar* name);
	void SetVec3f(glm::fvec3 value, const GLchar* name);
	void SetVec4f(glm::fvec4 value, const GLchar* name);
	void SetMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	void SetMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);

private:
	//Loading Shaders
	std::string LoadShaderSource(char* file_name);
	GLuint LoadShader(GLenum type, char* file_name);
	void LinkProgram(GLuint vertex_shader, GLuint geometry_shader, GLuint fragment_shader);
};