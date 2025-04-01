#pragma once

#include "Grid.h"
#include "GLFW/glfw3.h"

struct Player
{
    int Health;
    int Level;

    static void HandlesMouseDown(GLFWwindow*, float, float, Grid&);
    
    Player()
    {
        Health = 3;
        Level = 0;
    }
};
