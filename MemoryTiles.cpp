
#include <iostream>
#include <thread>   // For sleep_for
#include <chrono>   // For duration
#include "Squretiles.h"

int main()
{
    while (0) 
    {
        Squretiles grid = Squretiles();

        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
    
    return 0;
}
