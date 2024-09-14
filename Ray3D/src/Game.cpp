#include "Game.h"


//	INITIALIZERS    //
//***************************************
void Game::Init_GLFW()
{
    if (!glfwInit())
        std::cout << "ERROR::Game.cpp::Init_GLFW(): Failed to initialize GLFW" << std::endl;
}

void Game::Init_Window(const char* title, GLboolean is_resizable)
{
    //Setting up OpenGL Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->glMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->glMinorVersion);
    glfwWindowHint(GLFW_RESIZABLE, is_resizable);

    this->window = glfwCreateWindow(this->windowWidth, this->windowHeight, title, NULL, NULL);
    if (this->window == nullptr)
    {
        std::cout << "ERROR::Game.cpp::Init_Window(): Failed to initialize window" << std::endl;
        glfwTerminate();
    }

    glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
    glfwSetFramebufferSizeCallback(this->window, this->FramebufferResizeCallback);

    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);    //Enabling v-sync
}

void Game::Init_GLEW()
{
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR::Game.cpp::Init_GLEW(): Failed to initialize GLEW" << std::endl;
        glfwTerminate();
    }
}

void Game::Init_OpenGLOptions()
{
    glErrorCall( glEnable(GL_DEPTH_TEST) );
                 
    glErrorCall( glEnable(GL_CULL_FACE) );
    glErrorCall( glCullFace(GL_BACK) );
    glErrorCall( glFrontFace(GL_CCW) );
                 
    glErrorCall( glEnable(GL_BLEND) );
    glErrorCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
                 
    glErrorCall( glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) );
}
//***************************************


Game::Game(const char* title, const unsigned int width, const unsigned int height, const int gl_major_version, const int gl_minor_version, GLboolean is_resizable)
    :   windowWidth(width), windowHeight(windowHeight), glMajorVersion(gl_major_version), glMinorVersion(gl_minor_version)
{
    this->window = nullptr;
    this->framebufferWidth = this->windowWidth;
    this->framebufferHeight = this->windowHeight;

    this->Init_GLFW();
	this->Init_Window(title, is_resizable);
    this->Init_GLEW();
    this->Init_OpenGLOptions();
}

Game::~Game()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();
}


void Game::Update()
{
}

void Game::Render()
{
}