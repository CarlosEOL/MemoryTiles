#pragma once

#include "Grid.h"
#include "GLFW/glfw3.h"

struct Player
{
    int Health;
    int Level;

    void TakeDamage();

    Grid* grid;

    static void HandlesMouseDown(GLFWwindow*, float, float, Grid&);
    
    Player()
    {
        grid = nullptr;
        Health = 3;
        Level = 0;
    }
};

extern Player playerInstance;
