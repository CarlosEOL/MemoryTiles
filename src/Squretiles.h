#pragma once
//#include <string>
#include <vector>

// Summery //
// 
// Since I'm making this game alone, and wants to see it into fruition.
// I'm going to add enough UXR such as actual graphics using an graphic library like GLFW instead of a simple console in the later stages.
// I'll have a link to Github and update it every single day untill the game is fully flushed out.
//
// Reference: https://humanbenchmark.com/tests/memory
// 

using namespace std;

struct Squretiles
{
private:

    //Size of Grid//
    int _sizeX = 3;

    //TempSaveCoord//
    int totalCoordSize = 0;

    //Initialize an empty vector that stores bools *I asked a friend about how to make an dynamic array*//
    vector <vector<bool>> _grid;

    vector<int> PreviousCoord;
    int maxSaveIndex = _sizeX * _sizeX;
    
public:
    //Record Coord so game can rememeber when checking for correct tiles/duplicate coord
    int currentSaveIndex = 0;
    vector <vector<int>> _SavedCoords;

    //Constructor for Functions//
    Squretiles()
    {
        //Create a new grid, filled with randomized true and false//
        GenerateSqrTiles();

        //Draw to Console//
        DrawStringTiles();


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
    char sqr = '0';
    char wrong = 'X';

    // These are pretty straightforward, most of them have O2 algorithm that checks the _grid for grid randomization or checking tile true & false.
    void GenerateSqrTiles();
    void DrawStringTiles();
    void HideTiles(); // Simple Draw Grid of Os//
    bool CheckTiles(int, int); // Checks if the tile is true, returns tile bool. Input y,x coord and save it to _SavedCoords //
    void DrawInputedTiles(vector<int>); // Draws all guessed tiles //
    void IncreaseSize(); // Increase grid size //
};
