#pragma once

#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Primitive.h"


void FramebufferResizeCallback(GLFWwindow* window, int fbw, int fbh)
{
    glViewport(0, 0, fbw, fbh);
}


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
    glfwSetFramebufferSizeCallback(window, FramebufferResizeCallback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);    //Enabling v-sync

    return window;
}


int main()
{
    //Initializing GLFW
    if (!glfwInit())
        std::cout << "ERROR::Application.cpp::main(): Failed to initialize GLFW" << std::endl;


    //  CREATING WINDOW //
    const int glMajorVersion = 4;
    const int glMinorVersion = 5;
    const unsigned int windowWidth = 640;
    const unsigned int windowHeight = 480;
    int framebufferWidth = windowWidth;
    int framebufferHeight = windowHeight;

    GLFWwindow* window = CreateWindow("Ray3D", windowWidth, windowHeight, framebufferWidth, framebufferHeight, glMajorVersion, glMinorVersion, GL_TRUE);


    //Initializing GLEW
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR::Application.cpp::main(): Failed to initialize GLEW" << std::endl;
        glfwTerminate();
    }

    
    //  OpenGL Options  //
    glErrorCall( glEnable(GL_DEPTH_TEST) );

    glErrorCall( glEnable(GL_CULL_FACE) );
    glErrorCall( glCullFace(GL_BACK) );
    glErrorCall( glFrontFace(GL_CCW) );

    glErrorCall( glEnable(GL_BLEND) );
    glErrorCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    glErrorCall( glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) );


    //Initializing the shader
    Shader shader(glMajorVersion, glMinorVersion, "res/shaders/VertexShader.glsl", "res/shaders/FragmentShader.glsl");

    //Initializing the mesh
    Mesh mesh(&Quad());


    //Initialzing Textures
    Texture texture0("res/textures/Spookzie_Logo.png", GL_TEXTURE_2D, 0);
    Texture texture1("res/textures/Basketball.png", GL_TEXTURE_2D, 1);

    //Initializing the material
    Material material0(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), texture0.GetTextureUnit(), texture1.GetTextureUnit());


    //Camera
    glm::vec3 camPos(0.0f, 0.0f, 1.0f);
    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
    glm::vec3 camFront(0.0f, 0.0f, -1.0f);
    glm::mat4 viewMatrix(1.0f);
    viewMatrix = glm::lookAt(camPos, camPos + camFront, worldUp);

    //Init projection matrix
    float fov = 90.0f;
    float nearPlane = 0.1f;
    float farPlane = 1000.0f;
    glm::mat4 projectionMatrix(1.0f);
    float aspectRatio = static_cast<float>(framebufferWidth) / framebufferHeight;
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);


    //  LIGHTING    //
    glm::vec3 lightPos0(1.0f, 1.0f, 1.0f);


    //Init Uniforms
    shader.SetMat4fv(viewMatrix, "viewMatrix");
    shader.SetMat4fv(projectionMatrix, "projectionMatrix");
    
    shader.SetVec3f(lightPos0, "lightPos0");
    shader.SetVec3f(camPos, "cameraPos");
    

    Renderer renderer;

    //  GAME LOOP   //
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        //  UPDATE  //
        UpdateInput(window, mesh);

        glErrorCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        renderer.Clear();


        //  Update uniforms  //
        //Shader uniforms
        shader.SetMat4fv(viewMatrix, "viewMatrix");
        shader.SetMat4fv(projectionMatrix, "projectionMatrix");

        //Texture uniforms
        shader.Set1i(texture0.GetTextureUnit(), "texture0");
        shader.Set1i(texture1.GetTextureUnit(), "texture1");

        material0.SendToShader(shader);

        shader.Use();

        //Bind textures
        texture0.Bind();
        texture1.Bind();

        mesh.Render(&shader);


        glfwSwapBuffers(window);
    }


    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}