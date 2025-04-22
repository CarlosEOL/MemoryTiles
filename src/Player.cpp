#include "Player.h"

#include <iostream>
#include <ostream>
#include <thread>

Player playerInstance;

void Player::HandlesMouseDown(GLFWwindow* window, float xNDC, float yNDC, Grid& grid)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && playerInstance.Health > 0) {
        for (Tile& tile : grid.GetGrid()) {
            if (tile.Contains(xNDC, yNDC)) {
                tile.Reveal([](bool isRight)
                {
                    if (!isRight)
                    {
                        playerInstance.TakeDamage();
                        cout << "Revealed a Tile!" << endl;
                    }
                });
                
                break;
            }
        }
    }
}

void Player::TakeDamage() {
    
    if (Health > 0)
    {
        Health--;
        cout << "Player health: " << Health << endl;

        if (Health == 0)
        {
            cout << "Player Death!" << endl;
        
            this_thread::sleep_for(chrono::milliseconds(80));
            
            if (grid != nullptr)
            {
                cout << "REGENERATING GRID!" << endl;
                grid->GenerateGrid(3);
            }
            else
            {
                cout << "Grid is a nullptr" << endl;
            }

            Health = 3;
        }
    }
}