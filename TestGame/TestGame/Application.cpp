#include "Application.h"

#include <chrono>

FluxworksEngine TestGameApp::gameEngine;

TestGameApp::TestGameApp()
{
    TestGameApp::gameEngine.stop();
    TestGameApp::gameEngine.tickFrameDuration = std::chrono::duration<double>(1.0 / 2.0);
    TestGameApp::gameEngine.registerEventHandlers({
        new TestGameApp::TickHandler,
        new TestGameApp::MBDownHandler,
        new TestGameApp::MBUpHandler,
        new TestGameApp::ScrollHandler,
        new TestGameApp::WindowOpenHandler,
        new TestGameApp::WindowCloseHandler,
        new TestGameApp::KeyDownHandler,
        new TestGameApp::KeyUpHandler
    });
}

TestGameApp::~TestGameApp()
{

}

void TestGameApp::run()
{
    TestGameApp::gameEngine.start();
    TestGameApp::gameEngine.createWindow(1280, 720, WINDOWNAME);

    //wait until window is closed
    while (TestGameApp::gameEngine.isRunning());
}
