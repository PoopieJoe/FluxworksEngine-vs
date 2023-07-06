#include "pch.h"

#include "FluxworksEngine.h"
#include "Window.h"
#include "ErrorTypes.h"
#include "EventDispatcher.h"

class _BuiltinTickHandler : public FluxworksEventHandler<TickEvent>
{
public:
	void handler(TickEvent* event)
	{
		// TODO implement builtin tick handler
		//std::cout << "Builtin tick handler for engine things" << std::endl;
	}
};

FluxworksEngine::Core::Core()
{
	// Event dispatcher
	this->_eventDispatcher->registerHandler(new _BuiltinTickHandler);

	// Loop parameters
	this->tickFrameDuration = std::chrono::seconds(1/tickrate); // default loop at 1Hz
	this->_running = false;
	this->_previousTickTime = std::chrono::high_resolution_clock::now();
}

FluxworksEngine::Core::~Core()
{
}

void FluxworksEngine::Core::registerEventHandler(_FluxworksEventHandlerBase* eventHandler)
{
	this->_eventDispatcher->registerHandler(eventHandler);
}

void FluxworksEngine::Core::registerEventHandlers(std::list<_FluxworksEventHandlerBase*> eventHandlers)
{
	for (_FluxworksEventHandlerBase* const& i : eventHandlers) this->registerEventHandler(i);
}

bool FluxworksEngine::Core::isRunning()
{
	return this->_running;
}

void FluxworksEngine::Core::start()
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

FluxworksEngineWindow* FluxworksEngine::Core::createWindow(int width, int height, const char* name)
{
	FluxworksEngineWindow* pWindow;
	std::thread windowThread([this, pWindow, width, height, name]() mutable
	{
		FluxworksEngineWindow window(width, height, name, this->_eventDispatcher);
		pWindow = &window;
		MSG message = MSG();
		while (WM_QUIT != message.message)
		{
			bool bGotMsg = (PeekMessageA(&message, NULL, 0U, 0U, PM_REMOVE) != 0);

			if (bGotMsg)
			{
				// Translate and dispatch the message
				TranslateMessage(&message);
				DispatchMessageA(&message);
			}
			else
			{
				// Update the scene.
				//window.GFX().clear(0.0f, 0.5f, 0.5f, 1.0f);

				// Render frames during idle time (when no messages are waiting).

				// Present the frame to the screen.
				window.GFX().present();
			}
		}
	});
	windowThread.detach();
	return pWindow;
}



void FluxworksEngine::Core::stop()
{
	this->_running = false;
	return;
}

void FluxworksEngine::Core::_loop()
{
	// fetch time for this tick
	std::chrono::steady_clock::time_point t = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> dt = t - this->_previousTickTime;
	this->_previousTickTime = t;

	// Handle events generated in previous tick
	this->_eventDispatcher->dispatchQueue();


	// Tick
	this->_eventDispatcher->dispatchEvent(
		new TickEvent(dt,t), 
		false
	);

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