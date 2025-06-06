#include "glad/glad.h"
#include "WindowManager.h"

#include <iostream>

#include "Grid.h"

using namespace std;

unsigned int WindowManager::shaderProgram = 0;
unsigned int WindowManager::VAO, WindowManager::VBO, WindowManager::EBO;

float WindowManager::verticeDistance = 3.0f;

const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec2 aPos; //VERY IMPORTANT, THE GLFW NEEDS THIS TO DRAW
layout (location = 1) in vec2 aTexCoord;

uniform vec2 offset;
uniform float scale;

out vec2 TexCoord;

void main() {
    vec2 pos = aPos * scale + offset;
    
    gl_Position = vec4(pos, 0.0, 1.0); 
    //Built in Variable in GLFW, tells where to draw the vert on screen. 
    //0,0 is Z depth, unused in 2D, 1.0 is making sure you don't go 4D, WHAT IN THE BLACK MAGIC IS THIS

    TexCoord = aTexCoord; //out aTexCoord
}

)";

const char* fragmentShaderSource = R"(
#version 330 core

out vec4 FragColor; //R,G,B,A
in vec2 TexCoord; //U.V

uniform sampler2D texture1; //sampler2D is also what we had in UE5, it takes in an empty black image when created, but has parameter of 0,0,0,0 as well.

void main() {
    FragColor = texture(texture1, TexCoord); //So this would be a black texture with UV wrapped on a triangle.
    //FragColor = vec4(TexCoord, 0.0, 1.0); // U.V to R n G //Test line
}
)";

float vertices[] = {
    // pos          // U.V
    -1.0f,  1.0f,   0.0f, 1.0f,  // top-left
     1.0f,  1.0f,   1.0f, 1.0f,  // top-right
     1.0f, -1.0f,   1.0f, 0.0f,  // bottom-right
    -1.0f, -1.0f,   0.0f, 0.0f   // bottom-left

    // Had a hard time learning what the fuck this is, but thanks to ChatGPT
    // No time to read documentation, maybe it is the way it was set up the vertex shader since it takes up vec4.
};

unsigned int indices[] = {
    //What is this...
    //oh GLFW can only draw triangles like most engines, so 012 for the first and 230 for the second triangle, a square.
    0, 1, 2,
    2, 3, 0
};

//GLenum takes in both Vertex and Fragment Shader, source takes in the Shader Source above
//source is stored in C-String, in another words - char*.

// I'd imagine, char is 'C', and *char can store "String". Because GLFW is written in C, now wonder I had this much of confusion.

unsigned int createShader(GLenum type, const char* source) { 
    unsigned int shader = glCreateShader(type); //Shader object
    
    glShaderSource(shader, 1, &source, nullptr); //nullptr makes sure that the object uses the entire string. char**
    glCompileShader(shader); //GLFW shader object compilation

    // CHECK LINK LOG
    int success;
    char infoLog[512];
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "SHADER CREATE ERROR:\n" << infoLog << std::endl;
    }
    
    return shader;
}

void WindowManager::Update(Player& player, Grid& grid)
{
    glClear(GL_COLOR_BUFFER_BIT); //Clear Screen
    
    grid.Draw();
    
    glfwSwapBuffers(window);
    glfwPollEvents();

    //Handles Mouse Input
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    //Get Window Size
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    //Convert Mouse Position to GLFW World Position, 0,0 to -1,-1, halved, NDC = Normalized Device Coordinates for GLFW window.
    float xNDC = (mouseX / windowWidth) * 2.0f - 1.0f;
    float yNDC = 1.0f - (mouseY / windowHeight) * 2.0f;  // Flip Y

    player.HandlesMouseDown(window, xNDC, yNDC, grid);
    
    cout<< "Mouse X: " << xNDC <<" Mouse Y:  "<< yNDC <<endl; //This is right.
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

    cout <<"Made a new GLFW window." << endl;

    //Load OpenGL functions using GLAD, this is a required step to ensure glad.c is in solution
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    //ORiGINAL LOADER STATEMENT -> (GLADloadproc)glfwGetProcAddress) This causes problem because C++ doesn't know how to cast to .c
    //Answer: reinterpret_cast<GLADloadproc>(glfwGetProcAddress))
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        cerr << "Failed to initialize GLAD\n";
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    glMatrixMode(GL_PROJECTION); //We learned this in Computer Graphics, it "flattens" the camera perspective to orthographics.
    
    glLoadIdentity();
    float aspect = WIDTH / (float)HEIGHT;
    if (aspect >= 1.0f)
        glOrtho(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
    else
        glOrtho(-1.0, 1.0, -1.0f / aspect, 1.0f / aspect, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    //compiling shaders using creatreShader() for cleaner code
    unsigned int vShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    //attach compiled shader to glCreated shader program, assume that we only need to use this once, this is the background.
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram); //Tells GLFW that v,f shader are working together.
    
    // CHECK ERRORS - vShader, fShader and Linker
    int success;
    char infoLog[512];

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        std::cerr << "Vertex Shader Error:\n" << infoLog << endl;
    }

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShader, 512, NULL, infoLog);
        std::cerr << "Fragment Shader Error:\n" << infoLog << endl;
    }
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "SHADER LINK ERROR:\n" << infoLog << endl;
    }
    
    glUseProgram(shaderProgram); //Use the shader program.

    //SO THAT THE GLFW KNOWS WHAT TEXTURE TO USE
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

    //Generate empty array object and vertex/fragment buffers.
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Bind to edit VAO
    glBindVertexArray(VAO);

    //Bind + fill VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Bind + fill EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Tell OpenGL how to interpret vertex data
    // Position attribute (location = 0)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute (location = 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VAO (optional safety)
    glBindVertexArray(0);

    //Enable Opacity
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "Program ID: " << shaderProgram << endl;
}

bool WindowManager::isClosed()
{
    return glfwWindowShouldClose(window);
}