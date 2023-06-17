// TestGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <thread>

#include "FluxworksEngine.h"

int main()
{
    FluxworksEngine gameEngine = FluxworksEngine();
    gameEngine.start();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    gameEngine.stop();
    std::cout << "time elapsed is " << gameEngine.t() << " ms" << std::endl;
}