#pragma once
#include <string>
#include <vector>

struct Squretiles
{
private:

    //Size of Grid//
    int _sizeX = 3;

    //Initialize an empty vector that stores bools *I asked a friend about how to make an dynamic array*//
    std::vector <std::vector<bool>> _grid;

    
public:

    //Constructor for Functions//
    Squretiles()
    {
        _grid = std::vector<std::vector<bool>>(_sizeX, std::vector<bool>(_sizeX, false));

        //Create a new grid, filled with randomized true and false//
        GenerateSqrTiles(_grid);

        //Draw to Console//
        DrawStringTiles(_grid);


        //All this code is to learn what a nested vector can do.// 
        /*
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
    void IncreaseSize();
};
