#include "Game.h"


//	INITIALIZERS    //
//***************************************
void Game::Init_GLFW()
{
    if (glfwInit() == GLFW_FALSE)
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
    if (!this->window)
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

void Game::Init_Matrices()
{
    this->viewMatrix = glm::mat4(1.0f);
    this->viewMatrix = glm::lookAt(this->camPos, this->camPos + this->camFront, this->worldUp);

    this->projectionMatrix = glm::mat4(1.0f);
    float aspectRatio = static_cast<float>(this->framebufferWidth) / this->framebufferHeight;
    this->projectionMatrix = glm::perspective(glm::radians(this->fov),
        aspectRatio,
        this->nearPlane, this->farPlane);

}

void Game::Init_Shaders()
{
    this->shaders.push_back(new Shader(this->glMajorVersion, this->glMinorVersion, 
        "res/shaders/VertexShader.glsl", "res/shaders/FragmentShader.glsl"));
}

void Game::Init_Textures()
{
    //Texture 0
    this->textures.push_back(new Texture("res/textures/Spookzie_Logo.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("res/textures/Spookzie_Logo_Specular.png", GL_TEXTURE_2D));

    //Texture 0
    this->textures.push_back(new Texture("res/textures/Basketball.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("res/textures/Basketball_Specular.png", GL_TEXTURE_2D));
}

void Game::Init_Materials()
{
    this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 0, 1));
}

void Game::Init_Meshes()
{
    this->meshes.push_back( new Mesh(&Pyramid()) );
}

void Game::Init_Lights()
{
    this->lights.push_back(new glm::vec3(1.0f, 1.0f, 1.0f));
}

void Game::Init_Uniforms()
{
    this->shaders[SHADER_CORE_PROGRAM]->SetMat4fv(this->viewMatrix, "viewMatrix");
    this->shaders[SHADER_CORE_PROGRAM]->SetMat4fv(this->projectionMatrix, "projectionMatrix");

    this->shaders[SHADER_CORE_PROGRAM]->SetVec3f(*this->lights[0], "lightPos0");
    this->shaders[SHADER_CORE_PROGRAM]->SetVec3f(this->camPos, "cameraPos");
}
//***************************************


Game::Game(const char* title, const unsigned int width, const unsigned int height, const int gl_major_version, const int gl_minor_version, bool is_resizable)
    : windowWidth(width), windowHeight(height), glMajorVersion(gl_major_version), glMinorVersion(gl_minor_version)
{
    //  Init Variables  //
    //Window
    this->window = nullptr;
    this->framebufferWidth = this->windowWidth;
    this->framebufferHeight = this->windowHeight;

    //Matrices
    this->camPos = glm::vec3(0.0f, 0.0f, 1.0f);
    this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->camFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->fov = 90.0f;
    this->nearPlane = 0.1f;
    this->farPlane = 1000.0f;


    //  Init Functions  //
    this->Init_GLFW();
    this->Init_Window(title, is_resizable);
    this->Init_GLEW();
    this->Init_OpenGLOptions();
    this->Init_Matrices();
    this->Init_Shaders();
    this->Init_Textures();
    this->Init_Materials();
    this->Init_Meshes();
    this->Init_Lights();
    this->Init_Uniforms();
}

Game::~Game()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();

    for (size_t i = 0; i < this->shaders.size(); i++)
        delete this->shaders[i];
    
    for (size_t i = 0; i < this->textures.size(); i++)
        delete this->textures[i];

    for (size_t i = 0; i < this->materials.size(); i++)
        delete this->materials[i];

    for (size_t i = 0; i < this->meshes.size(); i++)
        delete this->meshes[i];
    
    for (size_t i = 0; i < this->lights.size(); i++)
        delete this->lights[i];
}


void Game::UpdateInput()
{
    //Quit
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(this->window, GL_TRUE);

    //Mesh movement
    if (glfwGetKey(this->window, GLFW_KEY_W))
        this->camPos.z += 0.03f;
    if (glfwGetKey(this->window, GLFW_KEY_A))
        this->camPos.x += 0.03f;
    if (glfwGetKey(this->window, GLFW_KEY_S))
        this->camPos.z -= 0.03f;
    if (glfwGetKey(this->window, GLFW_KEY_D))
        this->camPos.x -= 0.03f;
    if (glfwGetKey(this->window, GLFW_KEY_UP))
        this->camPos.y -= 0.03f;
    if (glfwGetKey(this->window, GLFW_KEY_DOWN))
        this->camPos.y += 0.03f;
}


void Game::Update()
{
    glfwPollEvents();
    this->UpdateInput();
}


void Game::Render()
{
    //Clear
    glErrorCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    renderer.Clear();

    //Update the uniforms
    this->UpdateUniforms();

    //Use a program
    this->shaders[SHADER_CORE_PROGRAM]->Use();

    //Bind textures
    this->textures[TEX_LOGO]->Bind(0);
    this->textures[TEX_LOGO_SPECULAR]->Bind(1);

    //Draw
    this->meshes[MESH_QUAD]->Render(this->shaders[SHADER_CORE_PROGRAM]);

    //End draw
    glfwSwapBuffers(window);
}


void Game::UpdateUniforms()
{
    this->viewMatrix = glm::lookAt(this->camPos, this->camPos + this->camFront, this->worldUp);

    //Shader uniforms
    this->shaders[SHADER_CORE_PROGRAM]->SetMat4fv(this->viewMatrix, "viewMatrix");
    this->shaders[SHADER_CORE_PROGRAM]->SetMat4fv(this->projectionMatrix, "projectionMatrix");

    this->materials[MAT_1]->SendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
}