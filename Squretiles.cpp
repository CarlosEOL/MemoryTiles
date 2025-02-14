
#include "Squretiles.h"

#include <iostream>
#include <thread>   // For sleep_for from GPT
#include <chrono>   // For duration from GPT

void Squretiles::GenerateSqrTiles(std::vector <std::vector<bool>> grid)
{
    for (int y = 0; y < _sizeX; y++)
    {
        for (int x = 0; x < _sizeX; x++)
        {
            grid[y][x] = rand()%2;

            //std::cout << grid[y][x]; //Debug
        }
        //std::cout << "\n"; //Debug
    }

    //std::cout << "Max Size Initiated: " << grid.size(); //Debug

    //Override local grid with generated grid//
    _grid = grid;

    //Then clean up the memories afterwards, I've heard it's a good practice.
    grid.clear();
    grid.shrink_to_fit();
    
}

void Squretiles::DrawStringTiles(std::vector <std::vector<bool>> grid)
{
    for (int y = 0; y < _sizeX; y++)
    {
        std::cout << "\n";
        for (int x = 0; x < _sizeX; x++)
        {
            if (grid[y][x])
            {
                std::cout << sqr;
            }
            else 
            {
                std::cout << empty;
            }
        }
    }

    this_thread::sleep_for(std::chrono::seconds(3));
}

void Squretiles::DrawInputedTiles() 
{
    
}

void Squretiles::HideTiles() 
{
    system("cls"); //GeeksForGeeks//
    for (int y = 0; y < _sizeX; y++)
    {
        std::cout << "\n";
        for (int x = 0; x < _sizeX; x++)
        {
            std::cout << "O";
        }
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

bool Squretiles::CheckTiles(int row, int col) 
{
    return _grid[col][row]; //y,x

    //Then Save Row and Col to _SavedCoords
}

void Squretiles::IncreaseSize() 
{
    _sizeX++;
}

