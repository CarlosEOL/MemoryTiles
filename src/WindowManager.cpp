#include "WindowManager.h"

#include <iostream>

using namespace std;

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 TexCoord;
void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D texture1;
void main() {
    FragColor = texture(texture1, TexCoord);
}
)";

float vertices[] = {
    // positions   // tex coords
    -1.0f,  1.0f,   0.0f, 1.0f,  // top-left
     1.0f,  1.0f,   1.0f, 1.0f,  // top-right
     1.0f, -1.0f,   1.0f, 0.0f,  // bottom-right
    -1.0f, -1.0f,   0.0f, 0.0f   // bottom-left
};

unsigned int indices[] = {
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
    //glClear(GL_COLOR_BUFFER_BIT);
    
    //glfwSwapBuffers(window);
    //glfwPollEvents();
    cout<<"Updated";
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

    //ORiGINAL LOADER STATEMENT -> (GLADloadproc)glfwGetProcAddress) This causes problem because C++ doesn't know how to cast to .c
    //Answer: reinterpret_cast<GLADloadproc>(glfwGetProcAddress))
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        cerr << "Failed to initialize GLAD\n";
    }

    glViewport(0, 0, WIDTH, HEIGHT);
}

bool WindowManager::isClosed()
{
    return !glfwWindowShouldClose(window);
}


