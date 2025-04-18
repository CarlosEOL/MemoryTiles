#pragma once

#include <glad/glad.h>

enum TileState // TO BE FAIR, THIS IS A LOT BETTER THAN ARRAYS.
{
    Hidden,
    RevealedWrong,
    RevealedRight
};

class Tile
{
public:

    // x, y is draw location on window, size of the square, 3 loaded textures.
    Tile(float x, float y, float size, GLuint hiddenTex, GLuint rightTex, GLuint wrongTex, bool isRight);

    void Draw();
    void Reveal();
    void Reset();
    bool Contains(float mouseX, float mouseY) const;
    
    TileState GetState() const;

private:
    
    float x, y, size;
    bool isRight;
    TileState state = Hidden;

    GLuint hiddenTexture;
    GLuint rightTexture;
    GLuint wrongTexture;
};
