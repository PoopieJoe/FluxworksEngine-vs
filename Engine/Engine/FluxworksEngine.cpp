#include "pch.h"
#include "WindowsIncludes.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

#include "FluxworksEngine.h"
#include "GraphicsEngine.h"
#include "ErrorTypes.h"
#include "EventDispatcher.h"

class _BuiltinTickHandler : public FluxworksEventHandler<TickEvent>
{
public:
	void handler(TickEvent* event)
	{
		//std::cout << "Builtin tick handler for engine things" << std::endl;
	}
};

FluxworksEngine::FluxworksEngine()
{
	// Event dispatcher
	this->_eventDispatcher->registerHandler(new _BuiltinTickHandler);

	// Loop parameters
	this->tickFrameDuration = std::chrono::seconds(1/TICKRATE); // default loop at 1Hz
	this->_running = false;
	this->_previousTickTime = std::chrono::high_resolution_clock::now();
}

FluxworksEngine::~FluxworksEngine()
{
}

void FluxworksEngine::registerEventHandler(_FluxworksEventHandlerBase* eventHandler)
{
	this->_eventDispatcher->registerHandler(eventHandler);
}

void FluxworksEngine::registerEventHandlers(std::list<_FluxworksEventHandlerBase*> eventHandlers)
{
	for (_FluxworksEventHandlerBase* const& i : eventHandlers) this->registerEventHandler(i);
}

void FluxworksEngine::windowEventCallback(FluxworksEvent* event)
{
	std::cout << "windowCallback" << std::endl;
}

bool FluxworksEngine::isRunning()
{
	return this->_running;
}

void FluxworksEngine::start()
{
	if (!this->_running)
	{
		this->_running = true;
		std::thread thread_obj([this]()
		{
			while (this->_running)
			{
				this->_loop();
			}
		});
		thread_obj.detach();
		return;
	}
	else
	{
		throw FluxworksAlreadyRunningException("Fluxworks Engine is already active");
	}
}

void FluxworksEngine::createWindow(const wchar_t* title)
{
	std::thread windowThread([this,title]()
	{
		MainWindow window = MainWindow(this->_eventDispatcher,title);
		MSG message = MSG();

		while (WM_QUIT != message.message)
		{
			bool bGotMsg = (PeekMessage(&message, NULL, 0U, 0U, PM_REMOVE) != 0);

			if (bGotMsg)
			{
				// Translate and dispatch the message
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			else
			{
				// Update the scene.

				// Render frames during idle time (when no messages are waiting).

				// Present the frame to the screen.
			}
		}
	});
	windowThread.detach();
}



void FluxworksEngine::stop()
{
	this->_running = false;
	return;
}

void FluxworksEngine::_loop()
{
	// fetch time for this tick
	std::chrono::steady_clock::time_point t = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> dt = t - this->_previousTickTime;
	this->_previousTickTime = t;

	// Handle events generated in previous tick
	this->_eventDispatcher->dispatchQueue();


	// Tick
	// DISABLED WHILE IM DOING GRAPHICS THINGS
	//this->_eventDispatcher->dispatchEvent(new TickEvent(
	//	dt,
	//	t
	//));

	// Put thread to sleep until next tick starts
	// If tickframe overrun -> skip
	if (std::chrono::high_resolution_clock::now() - t > this->tickFrameDuration)
	{
		std::cout << "TICKFRAME OVERRUN. SKIPPING TICKS" << std::endl;
		std::this_thread::sleep_until(t + 2*this->tickFrameDuration);
	}
	else
	{
		std::this_thread::sleep_until(t + this->tickFrameDuration);
	}
	
	return;
}



TickEvent::TickEvent(std::chrono::duration<double> deltaTime, std::chrono::steady_clock::time_point time) : FluxworksEvent("TickEvent")
{
	this->deltaTime = deltaTime;
	this->time = time;
}
