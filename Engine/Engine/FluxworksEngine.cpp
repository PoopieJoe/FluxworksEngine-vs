#include "pch.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

#include "FluxworksEngine.h"
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
	int i = 0;
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
	this->_eventDispatcher.addHandler(new GenericHandler);
	this->_eventDispatcher.addHandler(new InputHandler);

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

FluxworksError FluxworksEngine::start()
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
		return FluxworksError::Fluxworks_Success;
	}
	else
	{
		return FluxworksError::Fluxworks_Already_Running;
	}
	
}

FluxworksError FluxworksEngine::stop()
{
	this->_running = false;
	return FluxworksError::Fluxworks_Success;
}

FluxworksError FluxworksEngine::_loop()
{
	// Collect events
	std::cout << "-------------------" << std::endl;
	this->_eventDispatcher.dispatch(new GenericEvent);
	this->_eventDispatcher.dispatch(new InputEvent);



	// Dispatch events to handlers
	return FluxworksError::Fluxworks_Success;
}
