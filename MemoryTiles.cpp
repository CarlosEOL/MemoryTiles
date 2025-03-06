
#include <iostream>
#include <string>
#include <thread>   //For sleep_for - From ChatGPT
#include <chrono>   //For duration - From ChatGPT
#include "GLFW/glfw3.h"
#include "Squretiles.h"

using namespace std;


namespace Functions
{
    vector<int> intToArray(int);

}

vector<int> Functions::intToArray(int num) //See Reference: https://stackoverflow.com/questions/1860983/convert-integer-to-array
{
    vector <int> resultArray;
    while (true)
    {
        resultArray.insert(resultArray.begin(), num % 10);
        num /= 10;
        if (num == 0)
            return resultArray;
    }
    return resultArray;
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
        int _temp;
        cout << "\n\nEnter 2 numbers indicating rows and columns, ex - (y,x): \n";
        cin >> _temp;

        //Future Codes
        grid.DrawInputedTiles() //Temp Initialized Coord

        //array = Functions::intToArray(_temp);

        //grid.CheckTiles(_coord[0], _coord[1]);
        switch (true)
        {
        case true:
            grid.GenerateSqrTiles();
            this_thread::sleep_for(chrono::seconds(1));
            grid.DrawStringTiles();
            break;

        case false:

            break;
        }

        if (true)
        {
            Level++;
        }

        if (Level & 2)
        {
            Level++;
            grid.IncreaseSize();
        }

        this_thread::sleep_for(chrono::seconds(10));
    }

    return 0;
}