#pragma once

#include "Renderer.h"

#include <iostream>
#include <string>

#include <GLFW/glfw3.h>
#include <SOIL2.h>


class Texture
{
private:
	GLuint id;
	int width, height;
	unsigned int type;

public:
	//Constructor & Destructor
	Texture(const char* file_name, GLenum type);
	virtual ~Texture();

	inline GLuint GetID() const { return this->id; };

	void Bind(const GLint texture_unit);
	inline void Unbind() { glErrorCall(glBindTexture(this->type, 0)); }
};