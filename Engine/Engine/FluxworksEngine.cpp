#include "pch.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include "FluxworksEngine.h"

FluxworksEngine::FluxworksEngine()
{
	this->loopInterval_ms = 10; // default loop at 100Hz
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
	// Dispatch events to handlers
	return FluxworksError::Fluxworks_Success;
}
