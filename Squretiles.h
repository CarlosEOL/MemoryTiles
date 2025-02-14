#pragma once
//#include <string>
#include <vector>

struct Squretiles
{
private:

    //Size of Grid//
    int _sizeX = 3;

    //Initialize an empty vector that stores bools *I asked a friend about how to make an dynamic array*//
    std::vector <std::vector<bool>> _grid;
    
public:

    //Record Coord so game can rememeber when checking for correct tiles/duplicate coord
    std::vector <std::vector<int>> _SavedCoords;

    //Constructor for Functions//
    Squretiles()
    {
        //Properly initialize an nested vectors by filling it with data//
        _SavedCoords = std::vector<std::vector<int>>(3, std::vector<int>(3, 0));
        _grid = std::vector<std::vector<bool>>(_sizeX, std::vector<bool>(_sizeX, false));

        //Create a new grid, filled with randomized true and false//
        GenerateSqrTiles(_grid);

        //Draw to Console//
        DrawStringTiles(_grid);


        //Hide Tiles By Drawing Bunch of Os
        HideTiles();


        //All the code below helped me learn how to initiate a nested vector.// 

        /* 
        //Saves memory allocation for this specific vector.
        _grid.reserve(_sizeX);

        for (int y = 0; y <= _sizeX; y++)
        {
            _grid[y].reserve(_sizeX);
        }
        */
    }

    char empty = 'O';
    char sqr = 'X';

    // These are pretty straightforward, most of them have O2 algorithm that checks the _grid for grid randomization or checking tile true & false.
    void GenerateSqrTiles(std::vector <std::vector<bool>>);
    void DrawStringTiles(std::vector <std::vector<bool>>);
    void HideTiles(); // Simple Draw Grid of Os//
    bool CheckTiles(int, int); // Checks if the tile is true, returns tile bool. Input y,x coord and save it to _SavedCoords //
    void DrawInputedTiles(); // Draws all guessed tiles //
    void IncreaseSize(); // Increase grid size //
};
