#pragma once

#include <iostream>
#include <string>

#include <GLFW/glfw3.h>
#include <SOIL2.h>

#include "Renderer.h"


class Texture
{
private:
	GLuint id;
	int width, height;
	unsigned int type;
	GLint textureUnit;

public:
	//Constructor & Destructor
	Texture(const char* file_name, GLenum type, GLint texture_unit);
	~Texture();

	inline GLuint GetID() const { return this->id; };

	void Bind();
	inline void Unbind() { glErrorCall(glBindTexture(this->type, 0)); }

	inline GLint GetTextureUnit() const { return this->textureUnit; }
};