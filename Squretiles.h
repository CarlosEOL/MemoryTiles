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
    std::vector <std::vector<int>> _tempCoord;

    //Constructor for Functions//
    Squretiles()
    {
        //Properly initialize an nested vector by filling it with data
        _grid = std::vector<std::vector<bool>>(_sizeX, std::vector<bool>(_sizeX, false));

        //Create a new grid, filled with randomized true and false//
        GenerateSqrTiles(_grid);

        //Draw to Console//
        DrawStringTiles(_grid);

        //HideTiles();


        //All the code below helps me to learn what a nested vector can do.// 

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

    void GenerateSqrTiles(std::vector <std::vector<bool>>);
    void DrawStringTiles(std::vector <std::vector<bool>>);
    void HideTiles();
    void CheckTiles(int, int);
    void IncreaseSize();
};
