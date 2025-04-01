#pragma once

#include <glad/glad.h>

enum TileState
{
    Hidden,
    RevealedWrong,
    RevealedRight
};

class Tile
{
public:
    
    Tile(float x, float y, float size, GLuint hiddenTex, GLuint rightTex, GLuint wrongTex);

    void Draw();
    void Reveal(bool isCorrect);
    void Reset();
    bool Contains(float mouseX, float mouseY) const;
    TileState GetState() const;

private:
    
    float x, y, size;
    TileState state = TileState::Hidden;

    GLuint hiddenTexture;
    GLuint rightTexture;
    GLuint wrongTexture;
};
