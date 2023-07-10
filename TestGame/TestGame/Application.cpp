#include "Application.h"

#include <chrono>
#include <cmath>
#include <numbers>

FluxworksEngine::Core TestGameApp::gameEngine;
FluxworksEngineWindow* TestGameApp::window;
std::tuple<float, float, float> TestGameApp::bgcolor;
bool TestGameApp::windowActive;


class TickHandler : public FluxworksEventHandler<TickEvent>
{
public:
    void handler(TickEvent* event)
    {
        std::cout << "Tick handler. Seconds since last tick: " << event->deltaTime.count() << std::endl;
        if (TestGameApp::windowActive)
        {
            std::get<0>(TestGameApp::bgcolor) = std::sinf(std::chrono::time_point_cast<std::chrono::milliseconds>(event->time).time_since_epoch().count() / 1000.0f);
            std::get<1>(TestGameApp::bgcolor) = std::sinf(std::chrono::time_point_cast<std::chrono::milliseconds>(event->time).time_since_epoch().count() / 1000.0f + 3.141f /2);
            std::get<2>(TestGameApp::bgcolor) = std::sinf(std::chrono::time_point_cast<std::chrono::milliseconds>(event->time).time_since_epoch().count() / 1000.0f + 3.141f);
            TestGameApp::repaint();
        }
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
        TestGameApp::window = event->windowInstance;
        std::cout << "Created Window: \"" << event->windowInstance->name << "\", id " << event->windowInstance->identifier() << std::endl;
        TestGameApp::repaint();
        TestGameApp::windowActive = true;
    };
};

class WindowCloseHandler : public FluxworksEventHandler<WindowEvents::Close>
{
public:
    void handler(WindowEvents::Close* event)
    {
        //std::cout << "Destroyed Window: \"" << event->windowInstance->name << "\", id " << event->windowInstance->identifier() << std::endl;
        TestGameApp::gameEngine.stop();
    }
};

/* END OF WINDOW HANDLERS */

TestGameApp::TestGameApp()
{
    TestGameApp::bgcolor = std::make_tuple(0, 0, 0);
    TestGameApp::gameEngine.stop();
    TestGameApp::gameEngine.tickFrameDuration = std::chrono::duration<double>(1.0 / 2.0);
    TestGameApp::gameEngine.registerEventHandlers({
        new TickHandler,
        new MBDownHandler,
        new MBUpHandler,
        new ScrollHandler,
        new WindowOpenHandler,
        new WindowCloseHandler,
        new KeyDownHandler,
        new KeyUpHandler
    });
}

TestGameApp::~TestGameApp()
{

}

void TestGameApp::run()
{
    TestGameApp::windowActive = false;
    TestGameApp::gameEngine.tickFrameDuration = std::chrono::duration<double>(0.01f);
    TestGameApp::gameEngine.start();
    TestGameApp::window = TestGameApp::gameEngine.createWindow(480, 360, WINDOWNAME);

    //wait until window is closed
    while (TestGameApp::gameEngine.isRunning());
}

void TestGameApp::repaint()
{
    TestGameApp::window->fill(std::get<0>(TestGameApp::bgcolor), std::get<1>(TestGameApp::bgcolor), std::get<2>(TestGameApp::bgcolor));
}
