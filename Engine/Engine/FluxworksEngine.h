#pragma once

#ifdef FLUXWORKSENGINE_EXPORTS
#define FLUXWORKSENGINE_API __declspec(dllexport)
#else
#define FLUXWORKSENGINE_API __declspec(dllimport)
#endif // FLUXWORKSENGINE_EXPORTS

#include "pch.h"

#include <chrono>
#include <memory>
#include "EventDispatcher.h"
#include "Window.h"


/// <summary>
/// Loop frequency in ticks per second. Has millisecond accuracy
/// </summary>
constexpr auto TICKRATE = 1;

class TickEvent : public FluxworksEvent
{
public:
	TickEvent(std::chrono::duration<double> deltaTime, std::chrono::steady_clock::time_point time);

	std::chrono::duration<double> deltaTime;
	std::chrono::steady_clock::time_point time;
};

/// <summary>
/// The Fluxworks Game Engine
/// </summary>
class FLUXWORKSENGINE_API FluxworksEngine {

private:
	bool _running;

	std::chrono::steady_clock::time_point _previousTickTime;
	void _loop();

	std::shared_ptr<FluxworksEventDispatcher> _eventDispatcher = std::make_shared<FluxworksEventDispatcher>();
	//std::shared_ptr<WindowRenderer> window = std::make_shared<WindowRenderer>();

public:
	FluxworksEngine();
	~FluxworksEngine();

	/// <summary>
	/// tickrate of the engine logic
	/// </summary>
	std::chrono::duration<double> tickFrameDuration;

	void registerEventHandler(_FluxworksEventHandlerBase* eventHandler);

	void registerEventHandlers(std::list<_FluxworksEventHandlerBase*> eventHandlers);

	static void windowEventCallback(FluxworksEvent* event);

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

	void createWindow(int width, int height, const char* name);

	/// <summary>
	/// Stops the game engine. If the engine is not running,
	/// no effect.
	/// </summary>
	void stop();
};