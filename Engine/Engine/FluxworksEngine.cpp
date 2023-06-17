#include "pch.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

#include "FluxworksEngine.h"
#include "ErrorTypes.h"
#include "EventDispatcher.h"

class GenericEvent : public FluxworksEvent 
{
public:
	int i = 0;
};

class GenericHandler : public FluxworksEventHandler<GenericEvent>
{
public:
	void handler(GenericEvent* event)
	{
		std::cout << "Generic event triggered with " << event->i << std::endl;
	}
};

class InputEvent : public FluxworksEvent
{
public:
	InputEvent(int i) { this->i = i; };
	int i;
};

class InputHandler : public FluxworksEventHandler<InputEvent>
{
public:
	void handler(InputEvent* event)
	{
		std::cout << "Input event triggered with " << event->i << std::endl;
	}
};

FluxworksEngine::FluxworksEngine()
{
	// Event dispatcher
	this->_eventDispatcher = FluxworksEventDispatcher();
	this->_eventDispatcher.registerHandler(new GenericHandler);
	this->_eventDispatcher.registerHandler(new InputHandler);

	// Loop parameters
	this->loopInterval_ms = 1000/TICKRATE; // default loop at 1Hz
	this->_running = false;
	this->_t_ms = 0;
	this->_previousLoopTime = std::chrono::high_resolution_clock::now();
}

FluxworksEngine::~FluxworksEngine()
{
}

bool FluxworksEngine::isRunning()
{
	return this->_running;
}

uint64_t FluxworksEngine::t()
{
	return this->_t_ms;
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
				this->_t_ms += this->loopInterval_ms;
				this->_loop();
				std::this_thread::sleep_until(this->_previousLoopTime + std::chrono::milliseconds(this->loopInterval_ms));
				this->_previousLoopTime = std::chrono::high_resolution_clock::now();
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

void FluxworksEngine::stop()
{
	this->_running = false;
	return;
}

void FluxworksEngine::_loop()
{
	// Collect events
	std::cout << "-------------------" << std::endl;
	this->_eventDispatcher.dispatchEvent(new GenericEvent);
	this->_eventDispatcher.dispatchEvent(new InputEvent(this->t()));



	// Dispatch events to handlers
	return;
}
