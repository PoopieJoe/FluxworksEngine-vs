// TestGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "FluxworksEngine.h"

#define WINDOWNAME L"TestGame"

class CustomTickHandler : public FluxworksEventHandler<TickEvent>
{
public:
    void handler(TickEvent* event)
    {
        std::cout << "Custom Tick handler. Seconds since last tick: " << event->deltaTime.count() << std::endl;
    }
};

class CustomEvent : public FluxworksEvent
{
public:
    CustomEvent(std::string msg) { this->msg = msg; }; 
    std::string msg;
};

class CustomEventHandler : public FluxworksEventHandler<CustomEvent>
{
public:
    void handler(CustomEvent* event)
    {
        std::cout << "Custom event generated with message " << event->msg << std::endl;
    }
};

int main()
{
    FluxworksEngine gameEngine = FluxworksEngine();
    gameEngine.registerEventHandler(new CustomTickHandler);
    gameEngine.registerEventHandler(new CustomEventHandler);

    std::chrono::steady_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    //gameEngine.start();
    gameEngine.createWindow(WINDOWNAME);

    //wait on enter
    std::cout << "Engine started. To quit, press ENTER..." << std::endl;
    std::cin.ignore();
    //gameEngine.stop();

    std::chrono::steady_clock::time_point stopTime = std::chrono::high_resolution_clock::now();
    std::cout << "time elapsed is " << std::chrono::duration<double>(stopTime-startTime).count() << " s" << std::endl;
}