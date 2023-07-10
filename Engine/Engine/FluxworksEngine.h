#pragma once
#include "pch.h"

#include <chrono>
#include <memory>
#include "EventDispatcher.h"
#include "Window.h"
#include "EventTypes.h"




namespace FluxworksEngine {
	/// <summary>
	/// Loop frequency in ticks per second. Has millisecond accuracy
	/// </summary>
	constexpr auto tickrate = 1;



	/// <summary>
	/// The Fluxworks Game Engine
	/// </summary>
	class FLUXWORKSENGINE_API Core {

	private:
		bool _running;

		std::chrono::steady_clock::time_point _previousTickTime;
		void _loop();

		std::shared_ptr<FluxworksEventDispatcher> _eventDispatcher = std::make_shared<FluxworksEventDispatcher>();

	public:
		Core();
		~Core();

		/// <summary>
		/// tickrate of the engine logic
		/// </summary>
		std::chrono::duration<double> tickFrameDuration;

		void registerEventHandler(_FluxworksEventHandlerBase* eventHandler);

		void registerEventHandlers(std::list<_FluxworksEventHandlerBase*> eventHandlers);

		/// <summary>
		/// Checks whether the engine is running
		/// </summary>
		/// <returns>Whether the engine is running</returns>
		bool isRunning();

		/// <summary>
		/// Starts the game engine. If the engine is already running, 
		/// will return a [FluxworksAlreadyRunningException]
		/// </summary>
		void start();

		FluxworksEngineWindow* createWindow(int width, int height, const char* name);

		/// <summary>
		/// Stops the game engine. If the engine is not running,
		/// no effect.
		/// </summary>
		void stop();
	};
}

