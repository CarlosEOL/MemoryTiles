
#include <iostream>
#include <string>
#include <thread>   //For sleep_for - From ChatGPT
#include <chrono>   //For duration - From ChatGPT
#include "GLFW/glfw3.h"
#include "Squretiles.h"

using namespace std;


namespace Functions
{
    vector<int> intToVector(int);
    int intUserInput();

}

vector<int> Functions::intToVector(int num) //See Reference: https://stackoverflow.com/questions/1860983/convert-integer-to-array
{
    vector <int> resultArray = vector<int>(2,0);
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

using namespace Functions;
int main()
{
    int Level = 1;
    //Create Squaretiles for game function//
    Squretiles grid = Squretiles();

    //Enter Game State, handles user input//
    while (1)
    {
        //Take in User Input in Console//
        
        cout << "\n\nEnter 2 numbers indicating rows and columns, ex - (y,x): \n";
        
        vector<int> array = Functions::intToVector(intUserInput());

        ///cout << _temp << " is what you inputed, covert to " << array[0] << "," << array[1];
        grid.DrawInputedTiles(array); //Temp Initialized Coord
        this_thread::sleep_for(chrono::seconds(1));

        //array = Functions::intToVector(_temp);

        //grid.CheckTiles(_coord[0], _coord[1]);
        switch (true)
        {
        case true:
            
            grid.GenerateSqrTiles();
            grid.DrawStringTiles();
            this_thread::sleep_for(chrono::seconds(1));
            grid.HideTiles();
            break;

        case false:

            break;
        }

        Level++;

        if (Level & 2)
        {
            Level++;
            grid.IncreaseSize();
        }

        //this_thread::sleep_for(chrono::seconds(10));
    }

    return 0;
}