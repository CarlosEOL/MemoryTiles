#pragma once

//CONTEXT: MANAGES GLFW WINDOWS
// I intentionally left out glad so the header won't be included in memoryTiles.Cpp, also then it won't need to compile it again in Tile.h

#include "GLFW/glfw3.h"

class WindowManager
{
public:
    void InitializeGLFW();
    void MakeNewWindow(int, int);
    void Update();
    bool isClosed();
    
    //Public Constructor to Call when new window is created
    WindowManager()
    {
        InitializeGLFW();
    }

private:
    GLFWwindow* window;
};
