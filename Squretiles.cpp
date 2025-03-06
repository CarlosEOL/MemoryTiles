
#include "Squretiles.h"

#include <iostream>
#include <thread>   // For sleep_for from GPT
#include <chrono>   // For duration from GPT

using namespace std;

void Squretiles::GenerateSqrTiles()
{
    vector<vector<bool>> grid = vector<vector<bool>>(_sizeX, vector<bool>(_sizeX, false));
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

void Squretiles::DrawStringTiles()
{
    system("cls");
    for (int y = 0; y < _sizeX; y++)
    {
        std::cout << "\n";
        for (int x = 0; x < _sizeX; x++)
        {
            if (_grid[y][x])
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

void Squretiles::DrawInputedTiles(vector<int> tempCoord)
{
    system("cls");
    for (int y = 0; y < _sizeX; y++)
    {
        std::cout << "\n";
        for (int x = 0; x < _sizeX; x++)
        {
            if (y == tempCoord[0] && x == tempCoord[1])
            {
                if (_grid[tempCoord[0]][tempCoord[1]]) 
                {
                    cout << sqr;
                }
                else
                {
                    cout << wrong;
                }
            }
            else
            {
                std::cout << empty;
            }
        }
    }
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

