#pragma once

//CONTEXT: MANAGES GLFW WINDOWS

#include "glad/glad.h"
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
