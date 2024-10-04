#pragma once

#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Primitive.h"
#include "Camera.h"
#include "Model.h"
#include "Light.h"


//	ENUMS	//
enum shader_enum{ SHADER_CORE_PROGRAM = 0};
enum texture_enum { TEX_LOGO = 0, TEX_LOGO_SPECULAR, TEX_BALL, TEX_BALL_SPECULAR, TEX_BLEACH, TEX_BLEACH_SPECULAR, TEX_FLOOR, TEX_FLOOR_SPECULAR };
enum material_enum{ MAT_1 = 0};
enum mesh_enum{MESH_QUAD = 0};


class Game
{
private:
	//Renderer
	Renderer renderer;

	//Window
	GLFWwindow* window;
	const unsigned int windowWidth, windowHeight;
	int framebufferWidth, framebufferHeight;

	//OpenGL Context
	const int glMajorVersion, glMinorVersion;

	//Delta time
	float deltaTime, currentTime, lastTime;

	//Mouse input
	double lastMouseX, lastMouseY, mouseX, mouseY, mouseOffsetX, mouseOffsetY;
	bool firstMouse;

	//Camera
	Camera camera;

	//Matrices
	glm::mat4 viewMatrix;
	glm::vec3 camPos, worldUp, camFront;
	glm::mat4 projectionMatrix;
	float fov, nearPlane, farPlane;

	//Drawing
	std::vector<Shader*> shaders;
	std::vector<Texture*> textures;
	std::vector<Material*> materials;
	std::vector < Model*> models;

	//Lighting
	std::vector<glm::vec3> lights;


public:
	//Constructor & Destructor
	Game(const char* title, const unsigned int width, const unsigned int height, const int gl_major_version, const int gl_minor_version, bool is_resizable);
	virtual ~Game();

	//Accessors
	inline int GetWindowShouldClose() { return glfwWindowShouldClose(this->window); }

	//Modifiers
	inline void SetWindowShouldClose() { glfwSetWindowShouldClose(this->window, GL_TRUE); }

	//	UPDATE	//
	//Player Input
	void MouseInput();
	void KeyboardInput();
	void UpdateInput();

	void Update();

	//	RENDER	//
	void Render();
	

private:
	//Initializers
	void Init_GLFW();
	void Init_Window(const char* title, GLboolean is_resizable);
	void Init_GLEW();
	void Init_OpenGLOptions();
	void Init_Matrices();
	void Init_Shaders();
	void Init_Textures();
	void Init_Materials();
	void Init_Models();
	void Init_Lights();
	void Init_Uniforms();

	//Update
	void UpdateDeltaTime();
	void UpdateUniforms();
	
	inline static void FramebufferResizeCallback(GLFWwindow* window, int fbw, int fbh) { glViewport(0, 0, fbw, fbh); }
};