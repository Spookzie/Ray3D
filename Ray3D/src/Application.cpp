#pragma once

#include "Game.h"


void UpdateInput(GLFWwindow* window, Mesh& mesh)
{
    //Closing window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, GL_TRUE);

    //  MOVEMENT & ROTATION    //
    //Movement
    if (glfwGetKey(window, GLFW_KEY_W))
        mesh.Move(glm::vec3(0.0f, 0.0f, -0.01f));
    if (glfwGetKey(window, GLFW_KEY_A))
        mesh.Move(glm::vec3(-0.01f, 0.0f, 0.0f));
    if (glfwGetKey(window, GLFW_KEY_S))
        mesh.Move(glm::vec3(0.0f, 0.0f, 0.01f));
    if (glfwGetKey(window, GLFW_KEY_D))
        mesh.Move(glm::vec3(0.01f, 0.0f, 0.0f));

    //Rotation
    if (glfwGetKey(window, GLFW_KEY_Q))
        mesh.Rotate(glm::vec3(0.0f, -1.0f, 0.0f));
    if (glfwGetKey(window, GLFW_KEY_E))
        mesh.Rotate(glm::vec3(0.0f, 1.0f, 0.0f));
    
    //Scaling
    if (glfwGetKey(window, GLFW_KEY_Z))
        mesh.Scale(glm::vec3(0.01f));
    if (glfwGetKey(window, GLFW_KEY_X))
        mesh.Scale(glm::vec3(-0.01f));
}


GLFWwindow* CreateWindow(const char* title, const unsigned int width, const unsigned int height,
    int& fb_width, int& fb_height,
    const int gl_major_version, const int gl_minor_version,
    GLboolean is_resizable)
{
    //Setting up OpenGL Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor_version);
    glfwWindowHint(GLFW_RESIZABLE, is_resizable);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glfwSetFramebufferSizeCallback(window, Game::FramebufferResizeCallback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);    //Enabling v-sync

    return window;
}


int main()
{
    Game game("Ray3D", 640, 480, 3, 3, false);    


    //  GAME LOOP   //
    while (!game.GetWindowShouldClose())
    {
        game.Update();
        game.Render();

        
    }

    return 0;
}