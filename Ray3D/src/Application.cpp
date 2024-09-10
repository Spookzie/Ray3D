#pragma once

#include "libs.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"


Vertex vertices[] = {
    //Position                          //Color                         //Texcoords                 //Normal      
    glm::vec3(-0.5f,  0.5f,  0.0f),     glm::vec3(1.0f, 0.0f, 0.0f),    glm::vec2(0.0f, 1.0f),      glm::vec3(0.0f, 0.0f, -1.0f),    //index = 0 |   top left
    glm::vec3(-0.5f, -0.5f,  0.0f),     glm::vec3(0.0f, 1.0f, 0.0f),    glm::vec2(0.0f, 0.0f),      glm::vec3(0.0f, 0.0f, -1.0f),    //        1 |   bottom left
    glm::vec3( 0.5f, -0.5f,  0.0f),     glm::vec3(0.0f, 0.0f, 1.0f),    glm::vec2(1.0f, 0.0f),      glm::vec3(0.0f, 0.0f, -1.0f),    //        2 |   bottom right
    glm::vec3( 0.5f,  0.5f,  0.0f),     glm::vec3(0.0f, 1.0f, 0.0f),    glm::vec2(1.0f, 1.0f),      glm::vec3(0.0f, 0.0f, -1.0f)     //        3 |   top right
};
unsigned vertexCount = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] = {
    0, 1, 2,    //Bottom Left triangle
    0, 2, 3     //Top right triangle
};
unsigned indexCount = sizeof(indices) / sizeof(GLuint);


void FramebufferResizeCallback(GLFWwindow* window, int fbw, int fbh)
{
    glViewport(0, 0, fbw, fbh);
}


void UpdateInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
{
    //Closing window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, GL_TRUE);

    //  MOVEMENT & ROTATION    //
    //Movement
    if (glfwGetKey(window, GLFW_KEY_W))
        position.z -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_A))
        position.x -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_S))
        position.z += 0.01f;
    if (glfwGetKey(window, GLFW_KEY_D))
        position.x += 0.01f;

    //Rotation
    if (glfwGetKey(window, GLFW_KEY_Q))
        rotation.y -= 1.0f;
    if (glfwGetKey(window, GLFW_KEY_E))
        rotation.y += 1.0f;
    
    //Scaling
    if (glfwGetKey(window, GLFW_KEY_Z))
        scale += 0.01f;
    if (glfwGetKey(window, GLFW_KEY_X))
        scale -= 0.01f;
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

    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glfwSetFramebufferSizeCallback(window, FramebufferResizeCallback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);    //Enabling v-sync


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
    Shader shader("res/shaders/VertexShader.glsl", "res/shaders/FragmentShader.glsl");

    
    GLuint vao;
    glErrorCall( glCreateVertexArrays(1, &vao) );
    glErrorCall( glBindVertexArray(vao) );

    GLuint vbo;
    glErrorCall( glGenBuffers(1, &vbo) );
    glErrorCall( glBindBuffer(GL_ARRAY_BUFFER, vbo) );
    glErrorCall( glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW) );

    GLuint ibo;
    glErrorCall( glGenBuffers(1, &ibo) );
    glErrorCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo) );
    glErrorCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW) );


    //  Setting up vertex attribute pointers   //
    //Position
    glErrorCall( glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position)) );
    glErrorCall( glEnableVertexAttribArray(0) );

    //Color
    glErrorCall( glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color)) );
    glErrorCall( glEnableVertexAttribArray(1) );

    //Texcoord
    glErrorCall( glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord)) );
    glErrorCall( glEnableVertexAttribArray(2) );
    
    //Normal
    glErrorCall( glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal)) );
    glErrorCall( glEnableVertexAttribArray(3) );


    //Initialzing Textures
    Texture texture0("res/textures/Spookzie_Logo.png", GL_TEXTURE_2D, 0);
    Texture texture1("res/textures/Basketball.png", GL_TEXTURE_2D, 1);

    //Initializing the material
    Material material0(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), texture0.GetTextureUnit(), texture1.GetTextureUnit());


    //  MVP //
    //Init model matrix
    glm::vec3 position(0.0f);
    glm::vec3 rotation(0.0f);
    glm::vec3 scale(1.0f);
    glm::mat4 modelMatrix(1.0f);

    //Init view matrix
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
    shader.SetMat4fv(modelMatrix, "modelMatrix");
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
        UpdateInput(window, position, rotation, scale);

        glErrorCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        renderer.Clear();


        //Update matrices
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position); // Moving
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotating around y
        modelMatrix = glm::scale(modelMatrix, scale); // Scaling

        //  Update uniforms  //
        //Shader uniforms
        shader.SetMat4fv(modelMatrix, "modelMatrix");
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

        //Draw
        glErrorCall( glBindVertexArray(vao) );
        glErrorCall( glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0) );


        glfwSwapBuffers(window);
    }



    // Cleanup
    glErrorCall( glDeleteVertexArrays(1, &vao) );
    glErrorCall( glDeleteBuffers(1, &vbo) );
    glErrorCall( glDeleteBuffers(1, &ibo) );
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}