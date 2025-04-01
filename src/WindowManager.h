#pragma once

//CONTEXT: MANAGES GLFW WINDOWS
// I intentionally left out glad so the header won't be included in memoryTiles.Cpp, also then it won't need to compile it again in Tile.h

#include "Player.h"
#include "GLFW/glfw3.h"

class WindowManager
{
public:
    void InitializeGLFW();
    void MakeNewWindow(int, int);
    void Update(Player&, Grid&);
    bool isClosed();

    static unsigned int shaderProgram;
    static unsigned int VAO, VBO, EBO;
    
    //Public Constructor to Call when new window is created
    WindowManager()
    {
        InitializeGLFW();
    }

private:
    GLFWwindow* window;
};
