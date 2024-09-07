#pragma once

#include "libs.h"
#include "Renderer.h"
#include "Shader.h"


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
        scale -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_X))
        scale += 0.01f;
}


void FramebufferResizeCallback(GLFWwindow* window, int fbw, int fbh)
{
    glViewport(0, 0, fbw, fbh);
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
    Shader coreProgram((char*)"res/shaders/VertexShader.glsl", (char*)"res/shaders/FragmentShader.glsl");

    
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


    // **********************************
    //  Texture 1   //
    int imgWidth = 0;
    int imgHeight = 0;
    unsigned char* img = SOIL_load_image("res/textures/Spookzie_Logo.png", &imgWidth, &imgHeight, NULL, SOIL_LOAD_RGBA);

    GLuint texture0;
    glErrorCall( glGenTextures(1, &texture0) );
    glErrorCall( glBindTexture(GL_TEXTURE_2D, texture0) );

    //Setting texture parameters
    glErrorCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT) );                    //Resampling texture down if it needs to be rendered small
    glErrorCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) );                    //Resampling texture up if it needs to be rendered large
    glErrorCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );                //Clamping horizontally
    glErrorCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) );  //Clamping vertically

    //Uploading texture data
    if (img)
    {
        glErrorCall( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, img) );
        glErrorCall( glGenerateMipmap(GL_TEXTURE_2D) );
        SOIL_free_image_data(img);
    }
    else
        std::cout << "ERROR::Application.cpp::main(): Failed to load texture 0" << std::endl;
    
    //  Texture 2   //
    int imgWidth1 = 0;
    int imgHeight1 = 0;
    unsigned char* img1 = SOIL_load_image("res/textures/Basketball.png", &imgWidth1, &imgHeight1, NULL, SOIL_LOAD_RGBA);

    GLuint texture1;
    glErrorCall( glGenTextures(1, &texture1) );
    glErrorCall( glBindTexture(GL_TEXTURE_2D, texture1) );

    //Setting texture parameters
    glErrorCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT) );                    //Resampling texture down if it needs to be rendered small
    glErrorCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) );                    //Resampling texture up if it needs to be rendered large
    glErrorCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );                //Clamping horizontally
    glErrorCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) );  //Clamping vertically

    //Uploading texture data
    if (img1)
    {
        glErrorCall( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth1, imgHeight1, 0, GL_RGBA, GL_UNSIGNED_BYTE, img1) );
        glErrorCall( glGenerateMipmap(GL_TEXTURE_2D) );
        SOIL_free_image_data(img1);
    }
    else
        std::cout << "ERROR::Application.cpp::main(): Failed to load texture 1" << std::endl;
    // **********************************


    //  MVP //
    //Init model matrix
    glm::vec3 position(0.0f);
    glm::vec3 rotation(0.0f);
    glm::vec3 scale(1.0f);

    glm::mat4 modelMatrix(1.0f);

    /**
    * Functions to alter the texture differently during runtime
    * 
    * modelMatrix = glm::translate(modelMatrix, position);                     //Moving
    * modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));    //Rotate around x
    * modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));    //              y
    * modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));    //              z
    * modelMatrix = glm::scale(modelMatrix, scale);                                     //Scaling
    ***************************************/

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
    float aspectRatio = static_cast<float>(framebufferWidth) / framebufferHeight;
    glm::mat4 projectionMatrix(1.0f);
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

    //  LIGHTING    //
    glm::vec3 lightPos0(0.0f, 0.0f, 1.0f);

    //Init Uniforms
    coreProgram.SetMat4fv(modelMatrix, "modelMatrix");
    coreProgram.SetMat4fv(viewMatrix, "viewMatrix");
    coreProgram.SetMat4fv(projectionMatrix, "projectionMatrix");
    
    coreProgram.SetVec3f(lightPos0, "lightPos0");
    coreProgram.SetVec3f(camPos, "cameraPos");
    

    Renderer renderer;

    //  GAME LOOP   //
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        //  UPDATE  //
        UpdateInput(window, position, rotation, scale);

        
        glErrorCall( glClearColor(0.0f, 0.0f, 0.0f, 1.0f) );
        renderer.Clear();


        //  Update uniforms   //
        //Textures
        coreProgram.Set1i(0, "texture0");
        coreProgram.Set1i(1, "texture1");

        //Movement, rotation, scaling
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);    //Moving
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));  //Rotating around y
        modelMatrix = glm::scale(modelMatrix, scale);   //Scaling
        coreProgram.SetMat4fv(modelMatrix, "modelMatrix");

        //Handling texture rendering on change in aspect ratio
        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
        float aspectRatio = static_cast<float>(framebufferWidth) / framebufferHeight;
        projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
        coreProgram.SetMat4fv(modelMatrix, "projectionMatrix");

        coreProgram.Use();

        //Activate texture unit 0 and bind the texture
        glErrorCall( glActiveTexture(GL_TEXTURE0) );
        glErrorCall( glBindTexture(GL_TEXTURE_2D, texture0) );
        glErrorCall( glActiveTexture(GL_TEXTURE1) );
        glErrorCall( glBindTexture(GL_TEXTURE_2D, texture1) );

        glErrorCall( glBindVertexArray(vao) );
        glErrorCall( glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0) );


        glfwSwapBuffers(window);


        // Unbinding (if needed)
        // glErrorCall( glBindVertexArray(0) ); // Only needed if switching VAOs
        // glErrorCall( glBindBuffer(GL_ARRAY_BUFFER, 0) ); // Only needed if switching VBOs
        // glErrorCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) ); // Only needed if switching IBOs
        // glErrorCall( glUseProgram(0) ); // Only needed if switching programs
        // glErrorCall( glBindTexture(GL_TEXTURE_2D, 0) ); // Only needed if switching textures
    }


    // Cleanup
    glErrorCall( glDeleteTextures(1, &texture0) );
    glErrorCall( glDeleteVertexArrays(1, &vao) );
    glErrorCall( glDeleteBuffers(1, &vbo) );
    glErrorCall( glDeleteBuffers(1, &ibo) );
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}