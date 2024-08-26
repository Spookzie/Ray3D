#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


#include <iostream>


int main(void)
{
    GLFWwindow* window;

    //Initializing GLFW
    if (!glfwInit())
        return -1;

    //Creating Windows
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {

        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    //Initializing GLEW
    if (glewInit != GLEW_OK)
        std::cout << "ERROR::Application.cpp: Failed to initialize GLEW" << std::endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}