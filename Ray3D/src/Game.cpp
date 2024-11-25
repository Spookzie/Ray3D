/****************************************
            *** NOTE ***
* If there is some type of error in moving the models or camera (or maybe even something else)
* Try de-commenting the viewMatrix & projectionMatrix initialization in Init_Uniforms()
* I did them cuz they felt redundant there.
****************************************/


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

    //Input
    glErrorCall( glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED) );
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

    //Texture 1
    this->textures.push_back(new Texture("res/textures/Basketball.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("res/textures/Basketball_Specular.png", GL_TEXTURE_2D));
    
    //Texture 2
    this->textures.push_back(new Texture("res/textures/Bleach.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("res/textures/Bleach_Specular.png", GL_TEXTURE_2D));
    
    //Texture 3
    this->textures.push_back(new Texture("res/textures/floor.jpg", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("res/textures/floor_Specular.jpg", GL_TEXTURE_2D));
    
    //Texture 4
    this->textures.push_back(new Texture("res/textures/emissive.jpg", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("res/textures/emissive_Specular.jpg", GL_TEXTURE_2D));
}

void Game::Init_Materials()
{
    //Regular Material [Index = 0]
    this->materials.push_back(new Material(
        glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f),  //Ambient, Diffuse, Specular
        0, 1));                                             //DiffuseTex, SpecularTex
    
    //Emissive Material [Index = 1]
    this->materials.push_back(new Material(
        glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(0.5f),  //Ambient, Diffuse, Specular
        0, 1,                                               //DiffuseTex, SpecularTex
        glm::vec3(1.0f), 1.0f));                //Emissive color, intensity
}

void Game::Init_Models()
{
    std::vector<Mesh*> meshes;
    std::vector<Mesh*> meshes2;

    //  Creating Meshes //
    //Pyramids
    meshes.push_back(new Mesh(
        &Pyramid(),
        glm::vec3(0.0f),
        glm::vec3(-1.0f, 0.0f, -2.0f)));
    
    //Floor
    meshes2.push_back(new Mesh(
        &Quad(),
        glm::vec3(0.0f),
        glm::vec3(0.0f),
        glm::vec3(-90.0f, 0.0f, 0.0f),
        glm::vec3(100.0f)));


    //  Creating Models   //
    //Spookzie
    this->models.push_back(new Model(
        glm::vec3(0.0f),
        this->materials[0],
        this->textures[TEX_LOGO],
        this->textures[TEX_LOGO_SPECULAR],
        meshes));

    //Ichigo
    this->models.push_back(new Model(
        glm::vec3(2.0f, 0.0f, 0.0f),
        this->materials[0],
        this->textures[TEX_BLEACH],
        this->textures[TEX_BLEACH_SPECULAR],
        meshes));

    //Emissive
    this->models.push_back(new Model(
        glm::vec3(10.0f, 0.0f, 0.0f),
        this->materials[1],
        this->textures[TEX_EMISSIVE],
        this->textures[TEX_EMISSIVE_SPECULAR],
        meshes));
    
    //Floor
    this->models.push_back(new Model(
        glm::vec3(0.0f, -1.0f, 0.0f),
        this->materials[0],
        this->textures[TEX_FLOOR],
        this->textures[TEX_FLOOR_SPECULAR],
        meshes2));


    //Cleangin mesh after they have been assigned
    for (auto*& i : meshes)
        delete i;

    for (auto*& i : meshes2)
        delete i;
}

void Game::Init_Lights()
{
    this->pointLights.push_back(new PointLight(glm::vec3(0.0f)));
}

void Game::Init_Uniforms()
{
    //this->shaders[SHADER_CORE_PROGRAM]->SetMat4fv(this->viewMatrix, "viewMatrix");
    //this->shaders[SHADER_CORE_PROGRAM]->SetMat4fv(this->projectionMatrix, "projectionMatrix");

    for each (PointLight * pl in this->pointLights)
        pl->SendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
}
//***************************************


Game::Game(const char* title, const unsigned int width, const unsigned int height, const int gl_major_version, const int gl_minor_version, bool is_resizable)
    : windowWidth(width), windowHeight(height), glMajorVersion(gl_major_version), glMinorVersion(gl_minor_version),
        camera(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f))
{
    //  Init Variables  //
    //Window
    this->window = nullptr;
    this->framebufferWidth = this->windowWidth;
    this->framebufferHeight = this->windowHeight;

    //Delta time
    this->deltaTime = 0.0f;
    this->currentTime = 0.0f;
    this->lastTime = 0.0f;

    //Mouse input
    this->lastMouseX = 0.0;
    this->lastMouseY = 0.0;
    this->mouseX = 0.0;
    this->mouseY = 0.0;
    this->mouseOffsetX = 0.0;
    this->mouseOffsetY = 0.0;
    this->firstMouse = true;

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
    this->Init_Models();
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

    for (auto*& i : this->models)
        delete i;

    for (size_t i = 0; i < this->pointLights.size(); i++)
        delete this->pointLights[i];
}


//	PLAYER INPUT    //
//***************************************
void Game::MouseInput()
{
    glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

    if (this->firstMouse)
    {
        /*
        * This checks if it is the first time the mouse is being moved.
        * If it is, it updates the last location with current location and is by-default set to false so as to not execute again.
        * This helps in preventing wrong calculations at the start of the program.
        */
        this->lastMouseX = this->mouseX;
        this->lastMouseY = this->mouseY;
        this->firstMouse = false;
    }

    //Calculate offset
    this->mouseOffsetX = this->mouseX - this->lastMouseX;
    this->mouseOffsetY = this->mouseY - this->lastMouseY;

    //Update last position
    this->lastMouseX = this->mouseX;
    this->lastMouseY = this->mouseY;

    //Move Light
    if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1))
    {
        this->pointLights[0]->SetPosition(this->camera.GetPosition());
    }
}

void Game::KeyboardInput()
{
    //Quit
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(this->window, GL_TRUE);

    //Mesh movement
    if (glfwGetKey(this->window, GLFW_KEY_W))
        this->camera.Move(this->deltaTime, FORWARD);
    if (glfwGetKey(this->window, GLFW_KEY_A))
        this->camera.Move(this->deltaTime, LEFT);
    if (glfwGetKey(this->window, GLFW_KEY_S))
        this->camera.Move(this->deltaTime, BACKWARD);
    if (glfwGetKey(this->window, GLFW_KEY_D))
        this->camera.Move(this->deltaTime, RIGHT);
    if (glfwGetKey(this->window, GLFW_KEY_UP))
        this->camPos.y -= 0.02f;
    if (glfwGetKey(this->window, GLFW_KEY_DOWN))
        this->camPos.y += 0.02f;
}

void Game::UpdateInput()
{
    glfwPollEvents();

    this->KeyboardInput();
    this->MouseInput();

    this->camera.UpdateInput(this->deltaTime, -1, this->mouseOffsetX, this->mouseOffsetY);
}
//***************************************


void Game::Update()
{
    this->UpdateDeltaTime();
    this->UpdateInput();

    //this->models[0]->Rotate(glm::vec3(0.0f, 1.0f, 0.0f));
    //this->models[1]->Rotate(glm::vec3(0.0f, 1.0f, 0.0f));
}


void Game::Render()
{
    //Clear
    glErrorCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    renderer.Clear();

    //Update the uniforms
    this->UpdateUniforms();

    //Render models
    for(auto& i : this->models)
        i->Render(this->shaders[SHADER_CORE_PROGRAM]);

    //End draw
    glfwSwapBuffers(window);
}


void Game::UpdateUniforms()
{
    this->viewMatrix = this->camera.GetViewMatrix();

    //Shader uniforms
    this->shaders[SHADER_CORE_PROGRAM]->SetMat4fv(this->viewMatrix, "viewMatrix");
    this->shaders[SHADER_CORE_PROGRAM]->SetMat4fv(this->projectionMatrix, "projectionMatrix");
    this->shaders[SHADER_CORE_PROGRAM]->SetVec3f(this->camera.GetPosition(), "cameraPos");
    for each (PointLight * pl in this->pointLights)
        pl->SendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

    this->materials[MAT_1]->SendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
}


void Game::UpdateDeltaTime()
{
    this->currentTime = static_cast<float>(glfwGetTime());
    this->deltaTime = this->currentTime - this->lastTime;
    this->lastTime = this->currentTime;
}