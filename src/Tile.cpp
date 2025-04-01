#include "Tile.h"
#include "WindowManager.h"

#include <iostream>

using namespace std;

Tile::Tile(float x, float y, float size, GLuint hiddenTex, GLuint rightTex, GLuint wrongTex, bool isRight)
    : x(x), y(y), size(size),
      hiddenTexture(hiddenTex),
      rightTexture(rightTex),
      wrongTexture(wrongTex),
      isRight(isRight){}

void Tile::Draw()
{
    //Use Shader Program made in WindowsManager
    glUseProgram(WindowManager::shaderProgram);
    
    GLuint currentTexture = hiddenTexture; //Default Texture
    if (state == RevealedRight)
        currentTexture = rightTexture;
    else if (state == RevealedWrong)
        currentTexture = wrongTexture;

    //Bind texture to texture2D, texture edit.
    glBindTexture(GL_TEXTURE_2D, currentTexture);

    glUniform2f(glGetUniformLocation(WindowManager::shaderProgram, "offset"), 0, 0);

    //Bind the shared VAO
    glBindVertexArray(WindowManager::VAO);
    
    //Draw triangles on top on the shader program.
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //Unbind for safety
    glBindVertexArray(0);

    cout << "Drawing Tile at: " << x << ", " << y << endl;
}

void Tile::Reveal()
{
    state = isRight ? RevealedRight : RevealedWrong;
}

void Tile::Reset()
{
    state = Hidden;
}

bool Tile::Contains(float mouseX, float mouseY) const
{
    return mouseX > x - size / 2 && mouseX < x + size / 2 &&
           mouseY > y - size / 2 && mouseY < y + size / 2;
}

TileState Tile::GetState() const
{
    return state;
}