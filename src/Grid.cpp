
#include <iostream>
#include <thread>
#include <chrono>

#include "AssetManager.h"
#include "Tile.h"
#include "Grid.h"

using namespace std;

void Grid::GenerateGrid()
{
    srand(time(NULL)); //From https://stackoverflow.com/questions/14849866/c-rand-is-not-really-random, so that rand() is truly random
    
    //Properly initialize an nested vectors by filling it with data, if the saved coords are -1 they are ignored. 
    //_SavedCoords = vector<vector<int>>(maxSaveIndex, vector<int>(2, -1));
    
    //vector<vector<bool>> grid = vector<vector<bool>>(_sizeX, vector<bool>(_sizeX, false));
    auto& assets = AssetManager::Get(); //auto is sort of like var in C#, it deduces object type, get asset manager's instance

    std::cout << "HiddenTex ID: " << assets.hiddenTex << "\n";
    std::cout << "RightTex ID: " << assets.rightTex << "\n";
    std::cout << "WrongTex ID: " << assets.wrongTex << "\n";
    
    float tileSize = 1.0f / _size; //This can change depend on the size of the grid.
    float tileSpacing = tileSize * 2.01f;

    cout<<"Tile Spacing: " << tileSpacing << "\n";

    float gridWidth = _size * tileSpacing;
    float gridHeight = _size * tileSpacing;
    
    float startX = -gridWidth / 2.0f + tileSpacing / 2.0f;
    float startY =  gridHeight / 2.0f - tileSpacing / 2.0f;
    
    for (int row = 0; row < _size; row++) {
        for (int col = 0; col < _size; col++) {

            //This is scaled for image size
            float x = startX + col * tileSpacing;
            float y = startY - row * tileSpacing;

            tileGrid.emplace_back(Tile(x, y, tileSize,
                assets.hiddenTex, assets.rightTex, assets.wrongTex, rand()%2)); //Takes in coord, image assets and random true/false
        }
    }
    cout << "Grid Size: " << tileGrid.size() << endl; // Size is 0 for some reason.
/*
    for (int y = 0; y < _size; y++)
    {
        for (int x = 0; x < _size; x++)
        {
            grid[y][x] = rand()%2;

            //std::cout << grid[y][x]; //Debug
        }
        //std::cout << "\n"; //Debug
    }
*/
    //std::cout << "Max Size Initiated: " << grid.size(); //Debug

    //Override local grid with generated grid//
    //_grid = grid;

    //Then clean up the memories afterwards, I've heard it's a good practice.
    //grid.clear();
    //grid.shrink_to_fit();
    
}

Tile& Grid::GetTile(int row, int col) {
    return tileGrid[row * _size + col];
}

vector<Tile>& Grid::GetGrid()
{
    return tileGrid;
}

void Grid::IncreaseSize() 
{
    _size++;
    //currentSaveIndex = 0;
    //maxSaveIndex = _size * _size;
    //_SavedCoords = vector<vector<int>>(maxSaveIndex, vector<int>(2, -1));
}

void Grid::Draw()
{
    for (Tile& tile : tileGrid)
        tile.Draw();
}

int Grid::GetSize()
{
    return _size;
}


void Grid::DrawStringTiles()
{
    system("cls");

/*
    for (int y = 0; y < _size; y++)
    {
        std::cout << "\n";
        for (int x = 0; x < _size; x++)
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
*/
    this_thread::sleep_for(std::chrono::seconds(3));
}

/*
void Grid::DrawInputedTiles(vector<int> tempCoord) // IM ACTUALLY GOING INSANE TRYING TO FIGURE THIS OUT PLEASE HELP.
{
    system("cls");
    
    if (tempCoord == PreviousCoord)
        currentSaveIndex--;
    
    _SavedCoords[currentSaveIndex] = tempCoord;
    
    PreviousCoord = tempCoord;

    // CHECK TILE GRID USING SAVED COORDS //

    for (int y = 0; y < _size; y++) //Column
    {
        cout << "\n";
        for (int x = 0; x < _size; x++) //Row
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
*/
void Grid::HideTiles() 
{
    system("cls"); //GeeksForGeeks//
/*
    for (int y = 0; y < _sizeX; y++)
    {
        std::cout << "\n";
        for (int x = 0; x < _sizeX; x++)
        {
            std::cout << "O";
        }
    }
*/
    //std::this_thread::sleep_for(std::chrono::seconds(1));
}
/*
bool Grid::CheckTiles(int row, int col) 
{

    cout << _grid[col][row];

    //return _grid[col][row]; //y,x
    //return _SavedCoords[row][col]; //NOT USED, DO NOT MARK THIS
}
*/

