// TestGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Application.h"

int main()
{
    try {
        TestGameApp app;

        std::chrono::steady_clock::time_point startTime = std::chrono::high_resolution_clock::now();
        
        app.run();

        std::chrono::steady_clock::time_point stopTime = std::chrono::high_resolution_clock::now();
        std::cout << "time elapsed is " << std::chrono::duration<double>(stopTime - startTime).count() << " s" << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cout << e.what();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }
}

