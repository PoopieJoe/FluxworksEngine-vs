// TestGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "FluxworksEngine.h"

#define WINDOWNAME "TestGame"

FluxworksEngine gameEngine;

class TickHandler : public FluxworksEventHandler<TickEvent>
{
public:
    void handler(TickEvent* event)
    {
        std::cout << "Custom Tick handler. Seconds since last tick: " << event->deltaTime.count() << std::endl;
    }
};

//class LMBDownHandler : public FluxworksEventHandler<MouseLMBDown>
//{
//public:
//    void handler(MouseLMBDown* event)
//    {
//        std::cout << "MouseLMBDown (" << event->x << "," << event->y  << ")" << std::endl;
//    }
//};

class MouseClickHandler : public FluxworksEventHandler<MouseButtonDown>
{
public:
    void handler(MouseButtonDown* event)
    {
        std::cout << "MouseButtonDown " << int(event->button) << " (" << event->x << "," << event->y << ")" << std::endl;
    }
};

class WindowCloseHandler : public FluxworksEventHandler<Close>
{
public:
    void handler(Close* event)
    {
        gameEngine.stop();
    }
};

int main()
{
    try {
        gameEngine.tickFrameDuration = std::chrono::duration<double>(1.0 / 2.0);
        gameEngine.registerEventHandlers({
            new TickHandler,
            new MouseClickHandler,
            new WindowCloseHandler
            });

        std::chrono::steady_clock::time_point startTime = std::chrono::high_resolution_clock::now();
        gameEngine.start();
        gameEngine.createWindow(1280,720,WINDOWNAME);

        //wait until window is closed
        while (gameEngine.isRunning());

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