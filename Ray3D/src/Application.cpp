#pragma once

#include "libs.h"
#include "Renderer.h"


void FramebufferResizeCallback(GLFWwindow* window, int fbw, int fbh)
{
    glViewport(0, 0, fbw, fbh);
}


int main()
{
    //Initializing GLFW
    if (!glfwInit())
        std::cout << "ERROR::Application.cpp: Failed to initialize GLFW" << std::endl;


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
        std::cout << "ERROR::Application.cpp: Failed to initialize GLEW" << std::endl;
        glfwTerminate();
    }


    Renderer renderer;

    //  GAME LOOP   //
    while (!glfwWindowShouldClose(window))
    {
        //Polling for Events
        glfwPollEvents();

        //  DRAW HERE   //
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        renderer.Clear();

        //Swapping buffers
        glfwSwapBuffers(window);
    }


    glfwTerminate();

    return 0;
}