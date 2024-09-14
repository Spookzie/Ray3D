#pragma once

#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Primitive.h"


class Game
{
private:
	//Window
	GLFWwindow* window;
	const unsigned int windowWidth, windowHeight;
	int framebufferWidth, framebufferHeight;

	//OpenGL Context
	const int glMajorVersion, glMinorVersion;


public:
	//Constructor & Destructor
	Game(const char* title, const unsigned int width, const unsigned int height, const int gl_major_version, const int gl_minor_version, GLboolean is_resizable);
	virtual ~Game();

	//Accessors
	inline int GetWindowShouldClose() { return glfwWindowShouldClose(this->window); }

	//Modifiers
	inline void SetWindowShouldClose() { glfwSetWindowShouldClose(window, GL_TRUE); }

	void Update();
	void Render();
	
	inline static void FramebufferResizeCallback(GLFWwindow* window, int fbw, int fbh) { glViewport(0, 0, fbw, fbh); };


private:
	//Initializers
	void Init_GLFW();
	void Init_Window(const char* title, GLboolean is_resizable);
	void Init_GLEW();
	void Init_OpenGLOptions();
};