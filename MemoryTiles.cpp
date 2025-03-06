
#include <iostream>
#include <string>
#include <thread>   //For sleep_for - From ChatGPT
#include <chrono>   //For duration - From ChatGPT
#include "GLFW/glfw3.h"
#include "Squretiles.h"

using namespace std;


namespace Functions
{
    //Helper Code
    vector<int> intToVector(int);
    int intUserInput();

    //Function Def
    vector<int> Functions::intToVector(int num) //See Reference: https://stackoverflow.com/questions/1860983/convert-integer-to-array
    {
        vector <int> resultArray = vector<int>(2, 0);
        while (true)
        {
            resultArray.insert(resultArray.begin(), num % 10);
            num /= 10;
            if (num == 0)
                return resultArray;
        }
        return resultArray;
    }

    int Functions::intUserInput()
    {
        int _temp;
        cin >> _temp;

        return _temp;
    }

}

using namespace Functions;
int main()
{
    int Lifes = 3;
    int Level = 1;
    //Create Squaretiles for game function//
    Squretiles grid = Squretiles();

    //Enter Game State, handles user input//
    while (1)
    {
        //Take in User Input in Console//
        cout << "\n\nEnter 2 numbers indicating rows and columns, ex - (y,x): \n";
        vector<int> array = Functions::intToVector(intUserInput());

        ///cout << _temp << " is what you inputed, covert to " << array[0] << "," << array[1]; //DEBUG CODE
        grid.DrawInputedTiles(array); //Temp Initialized Coord
        this_thread::sleep_for(chrono::seconds(1));

        //DEBUG CODE//
        //cout << grid.CheckTiles(array[0], array[1]);

        switch (!Lifes) //If the game continues
        {
        case true:

            Level++;
            Lifes = 3;
            if (Level & 2)
            {
                
                grid.IncreaseSize();
                grid.GenerateSqrTiles();
                grid.DrawStringTiles();
                grid.HideTiles();
            }

            break;

        case false:

            //grid.DrawStringTiles();
            //this_thread::sleep_for(chrono::seconds(1));
            Lifes--;
            grid.HideTiles();
            break;
        }
        
        //this_thread::sleep_for(chrono::seconds(10));
    }

    return 0;
}