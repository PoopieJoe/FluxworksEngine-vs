#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdint>

#include "FluxworksEngine.h"

#define WINDOWNAME "TestGame"

class TestGameApp
{
private:

    class TickHandler : public FluxworksEventHandler<TickEvent>
    {
    public:
        void handler(TickEvent* event)
        {
            std::cout << "Tick handler. Seconds since last tick: " << event->deltaTime.count() << std::endl;
        }
    };

    /* MOUSE HANDLERS */

    class MBDownHandler : public FluxworksEventHandler<WindowEvents::MouseButtonDown>
    {
    public:
        void handler(WindowEvents::MouseButtonDown* event)
        {
            std::cout << "MouseButtonDown " << int(event->button) << " (" << event->x << "," << event->y << ")" << std::endl;
        }
    };

    class MBUpHandler : public FluxworksEventHandler<WindowEvents::MouseButtonUp>
    {
    public:
        void handler(WindowEvents::MouseButtonUp* event)
        {
            std::cout << "MouseButtonUp " << int(event->button) << " (" << event->x << "," << event->y << ")" << std::endl;
        }
    };

    class ScrollHandler : public FluxworksEventHandler<WindowEvents::MouseWheel>
    {
    public:
        void handler(WindowEvents::MouseWheel* event)
        {
            std::cout << "Scrolling " << event->delta << (event->delta > 0 ? " up" : " down") << " (" << event->x << "," << event->y << ")" << std::endl;
        }
    };

    /* END OF MOUSE HANDLERS */

    /* KEYBOARD HANDLERS */

    class KeyDownHandler : public FluxworksEventHandler<WindowEvents::KeyDown>
    {
    public:
        void handler(WindowEvents::KeyDown* event)
        {
            std::cout << "Key Down: " << event->key << std::endl;
        }
    };

    class KeyUpHandler : public FluxworksEventHandler<WindowEvents::KeyUp>
    {
    public:
        void handler(WindowEvents::KeyUp* event)
        {
            std::cout << "Key Up: " << event->key << std::endl;
        }
    };

    /* END OF KEYBOARD HANDLERS */

    /* WINDOW HANDLERS */

    class WindowOpenHandler : public FluxworksEventHandler<WindowEvents::Open>
    {
    public:
        void handler(WindowEvents::Open* event)
        {
            std::cout << "Created Window: \"" << event->windowInstance->name << "\", id " << event->windowInstance->identifier() << std::endl;
        };
    };

    class WindowCloseHandler : public FluxworksEventHandler<WindowEvents::Close>
    {
    public:
        void handler(WindowEvents::Close* event)
        {
            TestGameApp::gameEngine.stop();
        }
    };

    /* END OF WINDOW HANDLERS */

public:
    TestGameApp();
    ~TestGameApp();

    static FluxworksEngine gameEngine;
    void run();

    //delete copy constructors
    TestGameApp(const TestGameApp&) = delete;
    TestGameApp& operator=(const TestGameApp&) = delete;
};