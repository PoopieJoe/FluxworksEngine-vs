#include "Application.h"

#include <chrono>

FluxworksEngine TestGameApp::gameEngine;

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

TestGameApp::TestGameApp()
{
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
    TestGameApp::gameEngine.start();
    TestGameApp::gameEngine.createWindow(480, 360, WINDOWNAME);

    //wait until window is closed
    while (TestGameApp::gameEngine.isRunning());
}
