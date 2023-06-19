#include "pch.h"
#include <windows.h>
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
		std::cout << "Builtin tick handler for engine things" << std::endl;
	}
};

FluxworksEngine::FluxworksEngine()
{
	// Event dispatcher
	this->_eventDispatcher = FluxworksEventDispatcher();
	this->_eventDispatcher.registerHandler(new _BuiltinTickHandler);

	// Loop parameters
	this->tickFrameDuration = std::chrono::seconds(1/TICKRATE); // default loop at 1Hz
	this->_running = false;
	this->_previousTickTime = std::chrono::high_resolution_clock::now();

	this->window = WindowRenderer();
	this->window.initializeWindow();
}

FluxworksEngine::~FluxworksEngine()
{
}

void FluxworksEngine::registerEventHandler(_FluxworksEventHandlerBase* eventHandler)
{
	this->_eventDispatcher.registerHandler(eventHandler);
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

void FluxworksEngine::openWindow()
{
	this->window.createWindow();
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
	this->_eventDispatcher.dispatchQueue();


	// Tick
	this->_eventDispatcher.dispatchEvent(new TickEvent(
		dt,
		t
	));

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

TickEvent::TickEvent(std::chrono::duration<double> deltaTime, std::chrono::steady_clock::time_point time)
{
	this->deltaTime = deltaTime;
	this->time = time;
}
