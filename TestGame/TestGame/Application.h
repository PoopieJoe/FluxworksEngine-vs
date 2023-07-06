#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdint>

#include "FluxworksEngine.h"

#define WINDOWNAME "TestGame"

class TestGameApp
{
public:
    TestGameApp();
    ~TestGameApp();

    static FluxworksEngineWindow* window;
    static FluxworksEngine::Core gameEngine;
    void run();

    //delete copy constructors
    TestGameApp(const TestGameApp&) = delete;
    TestGameApp& operator=(const TestGameApp&) = delete;
};