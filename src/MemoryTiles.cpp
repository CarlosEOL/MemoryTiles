
#include <iostream>
#include <string>
#include <thread>   //For sleep_for - From ChatGPT
#include <chrono>   //For duration - From ChatGPT
#include "Squretiles.h"
#include "WindowManager.h"

const unsigned int WIDTH = 800, HEIGHT = 800; //Window Size

using namespace std;
namespace Functions
{
    //Helper Codes//
    
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
    }

    int Functions::intUserInput()
    {
        int _temp;
        cin >> _temp;

        return _temp;
    }

}

// CONTEXT: THIS IS THE MAIN FILE //

using namespace Functions;
int main()
{
    
    //WindowManager window = WindowManager();
    //window.MakeNewWindow(WIDTH, HEIGHT);
    //cout<<"Made a new window.";
    
    int Lifes = 3;
    int Level = 1;
    
    //Create Squaretiles for tile function//
    Squretiles grid = Squretiles();
    
    //Enter Game State, handles user input// window.isClosed()
    while (1)
    {
        //Update Per Frame
        //window.Update();
        
        //Take in User Input in Console//
        cout << "\n\nEnter 2 numbers indicating rows and columns, ex - (y,x): \n";
        vector<int> array = intToVector(intUserInput());

        ///cout << _temp << " is what you inputed, covert to " << array[0] << "," << array[1]; //DEBUG CODE
        grid.DrawInputedTiles(array); //Temp Initialized Coord
        this_thread::sleep_for(chrono::seconds(1));

        if (!grid.CheckTiles(array[0], array[1])) //check if the tile is false
            Lifes--;

        //DEBUG CODE//
        //cout << grid.CheckTiles(array[0], array[1]);

        switch (!Lifes) //If the game continues
        {
        case true: //When Player has no more life, increase difficulty.

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

        case false: //Game Logic when player has life

            //grid.DrawStringTiles();
            //this_thread::sleep_for(chrono::seconds(1));
            //Lifes--;
            break;
        }
        
        this_thread::sleep_for(chrono::seconds(1));
    }
    
    glfwTerminate();
    return 0;
}