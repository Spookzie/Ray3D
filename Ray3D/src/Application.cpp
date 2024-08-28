#pragma once

#include "libs.h"
#include "Renderer.h"


void UpdateInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, GL_TRUE);
}


void FramebufferResizeCallback(GLFWwindow* window, int fbw, int fbh)
{
    glViewport(0, 0, fbw, fbh);
}


bool LoadShaders(GLuint& program)
{
    bool loadSuccess = true;
    char infoLog[512];
    GLint success;

    std::string temp = "";
    std::string src = "";

    std::fstream inFile;

    //  Vertex Shader   //
     //Reading the shader file
    inFile.open("res/shaders/VertexShader.glsl");

    if (inFile.is_open())
    {
        while (std::getline(inFile, temp))
            src += temp + "\n";
    }
    else
    {
        std::cout << "ERROR::Application.cpp::LoadShaders(): Failed to load Vertex Shader" << std::endl;
        loadSuccess = false;
    }

    inFile.close();

    //Compiling the shader file
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* v_src = src.c_str();
    glShaderSource(vertexShader, 1, &v_src, NULL);
    glCompileShader(vertexShader);

    //Checking for errors during compilation
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::Application.cpp::LoadShaders(): Failed to compile the vertex shader" << std::endl;
        std::cout << infoLog << std::endl;
        loadSuccess = false;
    }


    temp = "";
    src = "";

    //  Fragment Shader //
    //Reading the shader file
    inFile.open("res/shaders/FragmentShader.glsl");

    if (inFile.is_open())
    {
        while (std::getline(inFile, temp))
            src += temp + "\n";
    }
    else
        std::cout << "ERROR::Application.cpp::LoadShaders(): Failed to load Fragment Shader" << std::endl;

    inFile.close();

    //Compiling the shader file
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* f_src = src.c_str();
    glShaderSource(fragmentShader, 1, &f_src, NULL);
    glCompileShader(fragmentShader);

    //Checking for errors during compilation
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::Application.cpp::LoadShaders(): Failed to compile the fragment shader" << std::endl;
        std::cout << infoLog << std::endl;
        loadSuccess = false;
    }
    
    //  Linking the Program //
    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    //Error Checking
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::Application.cpp::LoadShaders(): Failed to link the program" << std::endl;
        std::cout << infoLog << std::endl;
        loadSuccess = false;
    }


    glErrorCall( glUseProgram(0) );
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return loadSuccess;
}


int main()
{
    //Initializing GLFW
    if (!glfwInit())
        std::cout << "ERROR::Application.cpp::main(): Failed to initialize GLFW" << std::endl;


    //  CREATING WINDOW //
    const unsigned int windowWidth = 640;
    const unsigned int windowHeight = 480;
    int framebufferWidth = 0;
    int framebufferHeight = 0;

    //Setting up OpenGL Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Ray3D", NULL, NULL);

    glfwSetFramebufferSizeCallback(window, FramebufferResizeCallback);

    glfwMakeContextCurrent(window);


    //Initializing GLEW
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR::Application.cpp::main(): Failed to initialize GLEW" << std::endl;
        glfwTerminate();
    }

    
    //OpenGL Options
    glErrorCall( glEnable(GL_DEPTH_TEST) );

    glErrorCall( glEnable(GL_CULL_FACE) );
    glErrorCall( glCullFace(GL_BACK) );
    glErrorCall( glFrontFace(GL_CCW) );

    glErrorCall( glEnable(GL_BLEND) );
    glErrorCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    glErrorCall( glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) );


    //Initializing the shader
    GLuint coreProgram;
    if (!LoadShaders(coreProgram))
        glfwTerminate();


    Renderer renderer;

    //  GAME LOOP   //
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();   //Polling for Events

        //  UPDATE  //
        UpdateInput(window);

        
        //  DRAW HERE   //
        glErrorCall( glClearColor(0.0f, 0.0f, 0.0f, 1.0f) );
        renderer.Clear();


        glfwSwapBuffers(window);    //Swapping buffers
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    glErrorCall( glDeleteProgram(coreProgram) );

    return 0;
}