
#include <iostream>
#include <string>
#include <thread>   //For sleep_for - From ChatGPT
#include <chrono>   //For duration - From ChatGPT
#include "Squretiles.h"

namespace Functions 
{
   void intToArray(int);

}

void Functions::intToArray(int i)
{

}

using namespace std;

int main()
{
    int Level = 1;

    Squretiles grid = Squretiles();

    //Enter Game State, handles user input//
    while (1) 
    {
        int _temp;
        cout << "\n\nEnter 2 numbers indicating rows and columns, ex - (y,x): \n";
        cin >> _temp;

        Functions::intToArray(_temp);

        //int _coord[2] = Functions::intToArray(_temp);

        //grid.CheckTiles(_coord[0], _coord[1]);

        if (Level & 2) 
        {
            Level++;
            grid.IncreaseSize();
        }

        this_thread::sleep_for(chrono::seconds(10));
    }
    
    return 0;
}
