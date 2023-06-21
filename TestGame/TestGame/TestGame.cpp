// TestGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "FluxworksEngine.h"

#define WINDOWNAME L"TestGame"

FluxworksEngine gameEngine;

class TickHandler : public FluxworksEventHandler<TickEvent>
{
public:
    void handler(TickEvent* event)
    {
        std::cout << "Custom Tick handler. Seconds since last tick: " << event->deltaTime.count() << std::endl;
    }
};

class LMBDownHandler : public FluxworksEventHandler<WindowEvents::Mouse::LMBDown>
{
public:
    void handler(WindowEvents::Mouse::LMBDown* event)
    {
        std::cout << "LMBDown (" << event->x << "," << event->y  << ")" << std::endl;
    }
};

class WindowCloseHandler : public FluxworksEventHandler<WindowEvents::Close>
{
public:
    void handler(WindowEvents::Close* event)
    {
        gameEngine.stop();
    }
};

int main()
{
    gameEngine.registerEventHandlers({ 
        new TickHandler, 
        new LMBDownHandler, 
        new WindowCloseHandler 
    });

    std::chrono::steady_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    gameEngine.start();
    gameEngine.createWindow(WINDOWNAME);

    //wait until window is closed
    while (gameEngine.isRunning());

    std::chrono::steady_clock::time_point stopTime = std::chrono::high_resolution_clock::now();
    std::cout << "time elapsed is " << std::chrono::duration<double>(stopTime-startTime).count() << " s" << std::endl;
}