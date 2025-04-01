#include "Player.h"

void Player::HandlesMouseDown(GLFWwindow* window, float xNDC, float yNDC, Grid& grid)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        for (Tile& tile : grid.GetGrid()) {
            if (tile.Contains(xNDC, yNDC)) {
                tile.Reveal();  // Or use your own logic
                break;
            }
        }
    }
}
