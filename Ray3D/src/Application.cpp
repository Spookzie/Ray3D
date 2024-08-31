#pragma once

#include "libs.h"
#include "Renderer.h"


Vertex vertices[] = {
    //Position                          //Color                         //Texcoords
    glm::vec3(-0.5f,  0.5f,  0.0f),     glm::vec3(1.0f, 0.0f, 0.0f),    glm::vec2(0.0f, 1.0f),      //index = 0 |   top left
    glm::vec3(-0.5f, -0.5f,  0.0f),     glm::vec3(0.0f, 1.0f, 0.0f),    glm::vec2(0.0f, 0.0f),      //        1 |   bottom left
    glm::vec3( 0.5f, -0.5f,  0.0f),     glm::vec3(0.0f, 0.0f, 1.0f),    glm::vec2(1.0f, 0.0f),      //        2 |   bottom right
    glm::vec3( 0.5f,  0.5f,  0.0f),     glm::vec3(0.0f, 1.0f, 0.0f),    glm::vec2(1.0f, 1.0f)       //        3 |   top right
};
unsigned vertexCount = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] = {
    0, 1, 2,    //Bottom Left triangle
    0, 2, 3     //Top right triangle
};
unsigned indexCount = sizeof(indices) / sizeof(GLuint);


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

    
    //  OpenGL Options  //
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



    Renderer renderer;

    //  GAME LOOP   //
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        //  UPDATE  //
        UpdateInput(window);

        
        //  DRAW HERE   //
        glErrorCall( glClearColor(0.0f, 0.0f, 0.0f, 1.0f) );
        renderer.Clear();

        glErrorCall( glUseProgram(coreProgram) );

        //Update uniforms
        glErrorCall( glUniform1i(glGetUniformLocation(coreProgram, "texture0"), 0) );
        glErrorCall( glUniform1i(glGetUniformLocation(coreProgram, "texture1"), 1) );

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
    glErrorCall( glDeleteProgram(coreProgram) );
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}