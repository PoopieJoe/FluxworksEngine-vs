#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdint>
#include <tuple>

#include "FluxworksEngine.h"

#define WINDOWNAME "TestGame"

class TestGameApp
{
public:
    TestGameApp();
    ~TestGameApp();

    static FluxworksEngineWindow* window;
    static bool windowActive;
    static FluxworksEngine::Core gameEngine;
    void run();

    static std::tuple<float, float, float> bgcolor;

    static void repaint();

    //delete copy constructors
    TestGameApp(const TestGameApp&) = delete;
    TestGameApp& operator=(const TestGameApp&) = delete;
};