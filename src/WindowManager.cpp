#include "WindowManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

using namespace std;

const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec2 aPos; //VERY IMPORTANT, THE GLFW NEEDS THIS TO DRAW
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0); 
    //Built in Variable in GLFW, tells where to draw the vert on screen. 
    //0,0 is Z depth, unused in 2D, 1.0 is making sure you don't go 4D, WHAT IN THE BLACK MAGIC IS THIS

    TexCoord = aTexCoord; //out aTexCoord
}

)";

const char* fragmentShaderSource = R"(
#version 330 core

out vec4 FragColor; //R,G,B,A
in vec2 TexCoord; //U.V

uniform sampler2D texture1;  //sampler2D is also what we had in UE5, it takes in an empty image when created, but has parameter of 0,0,0,0 as well.

void main() {
    FragColor = texture(texture1, TexCoord); //So this would be a black texture with UV wrapped on a triangle.
}
)";

float vertices[] = {
    // pos   // U.V
    -1.0f,  1.0f,   0.0f, 1.0f,  // top-left
     1.0f,  1.0f,   1.0f, 1.0f,  // top-right
     1.0f, -1.0f,   1.0f, 0.0f,  // bottom-right
    -1.0f, -1.0f,   0.0f, 0.0f   // bottom-left

    // Had a hard time learning what the fuck this is, but thanks to ChatGPT
    // No time to read documentation, maybe it is the way it was set up the vertex shader since it takes up vec4.
};

unsigned int indices[] = { //What is this... oh GLFW can only draw triangles like most engines, so 012 for the first and 230 for the second triangle, a square.
    0, 1, 2,
    2, 3, 0
};

unsigned int createShader(GLenum type, const char* source) {
    unsigned int shader = glCreateShader(type);
    
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    return shader;
}

void WindowManager::Update()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    //cout<<"Updated"; this works.
}


void WindowManager::InitializeGLFW()
{
    //Load GLFW
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW\n";
    }
}


void WindowManager::MakeNewWindow(int WIDTH, int HEIGHT)
{
    //Create a window
    window = glfwCreateWindow(WIDTH, HEIGHT, "glfwSquareTiles", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    //Load OpenGL functions using GLAD, this is a required step to ensure glad.c is in solution
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    //ORiGINAL LOADER STATEMENT -> (GLADloadproc)glfwGetProcAddress) This causes problem because C++ doesn't know how to cast to .c
    //Answer: reinterpret_cast<GLADloadproc>(glfwGetProcAddress))
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        cerr << "Failed to initialize GLAD\n";
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    // Compile shaders
    unsigned int vShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram);
}

bool WindowManager::isClosed()
{
    return glfwWindowShouldClose(window);
}


