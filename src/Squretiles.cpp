
#include "Squretiles.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void Squretiles::GenerateSqrTiles()
{
    srand(time(NULL)); //From https://stackoverflow.com/questions/14849866/c-rand-is-not-really-random, so that rand() is truly random
    //Properly initialize an nested vectors by filling it with data, if the saved coords are -1 they are ignored. 
    _SavedCoords = vector<vector<int>>(maxSaveIndex, vector<int>(2, -1));
    
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

void Squretiles::DrawInputedTiles(vector<int> tempCoord) // IM ACTUALLY GOING INSANE TRYING TO FIGURE THIS OUT PLEASE HELP.
{
    system("cls");
    
    if (tempCoord == PreviousCoord)
        currentSaveIndex--;
    
    _SavedCoords[currentSaveIndex] = tempCoord;
    
    PreviousCoord = tempCoord;

    // CHECK TILE GRID USING SAVED COORDS //
    
    for (int y = 0; y < _sizeX; y++) //Column
    {
        cout << "\n";
        for (int x = 0; x < _sizeX; x++) //Row
        {
            bool hasGon = false;
            
            for (int i = 0; i < maxSaveIndex; i++) //Check Saved indexes, Im like, JESUS CHRIST THERE IS 2 NESTED FOR LOOP OH NO
            {
                //Check if its double -1, and the savecoord's xy is current xy
                if (_SavedCoords[i][1] == y && _SavedCoords[i][0] == x) //if x,y corespond to savecoords, in this case, x = y y = x
                {
                    if (_grid[y][x])
                    {
                        cout << sqr;
                    }
                    else
                    {
                        cout << wrong;
                    }
                    hasGon = true;
                }
            }

            //This part of the project just gave me brain fart
            if (!hasGon)
                cout << empty;
        }
    }

    currentSaveIndex++;
    
    if (currentSaveIndex > maxSaveIndex - 1)
    {
        currentSaveIndex = 0;
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

    //std::this_thread::sleep_for(std::chrono::seconds(1));
}

bool Squretiles::CheckTiles(int row, int col) 
{
    cout << _grid[col][row];
    return _grid[col][row]; //y,x
}

void Squretiles::IncreaseSize() 
{
    _sizeX++;
    currentSaveIndex = 0;
    maxSaveIndex = _sizeX * _sizeX;
    _SavedCoords = vector<vector<int>>(maxSaveIndex, vector<int>(2, -1));
}

