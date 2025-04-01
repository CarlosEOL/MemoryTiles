#include "Tile.h"

Tile::Tile(float x, float y, float size, GLuint hiddenTex, GLuint rightTex, GLuint wrongTex)
    : x(x), y(y), size(size),
      hiddenTexture(hiddenTex),
      rightTexture(rightTex),
      wrongTexture(wrongTex) {}

void Tile::Draw() {
    float half = size / 2.0f;

    float vertices[] = {
        x - half, y + half, 0.0f, 1.0f,
        x + half, y + half, 1.0f, 1.0f,
        x + half, y - half, 1.0f, 0.0f,
        x - half, y - half, 0.0f, 0.0f
    };

    GLuint textureToUse = hiddenTexture;
    if (state == TileState::RevealedRight)
        textureToUse = rightTexture;
    else if (state == TileState::RevealedWrong)
        textureToUse = wrongTexture;

    glBindTexture(GL_TEXTURE_2D, textureToUse);
    // Bind VAO/VBO once before this outside loop
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Tile::Reveal(bool isCorrect) {
    state = isCorrect ? RevealedRight : RevealedWrong;
}

void Tile::Reset() {
    state = Hidden;
}

bool Tile::Contains(float mouseX, float mouseY) const {
    return mouseX > x - size / 2 && mouseX < x + size / 2 &&
           mouseY > y - size / 2 && mouseY < y + size / 2;
}

TileState Tile::GetState() const {
    return state;
}