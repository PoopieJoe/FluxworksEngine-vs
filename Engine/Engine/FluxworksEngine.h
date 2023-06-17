#pragma once

#ifdef FLUXWORKSENGINE_EXPORTS
#define FLUXWORKSENGINE_API __declspec(dllexport)
#else
#define FLUXWORKSENGINE_API __declspec(dllimport)
#endif // FLUXWORKSENGINE_EXPORTS

#include <chrono>
#include "EventDispatcher.h"


/// <summary>
/// Loop frequency in ticks per second. Has millisecond accuracy
/// </summary>
constexpr auto TICKRATE = 1;

/// <summary>
/// The Fluxworks Game Engine
/// </summary>
class FLUXWORKSENGINE_API FluxworksEngine {

private:
	bool _running;
	uint64_t _t_ms;
	FluxworksEventDispatcher _eventDispatcher;

	std::chrono::steady_clock::time_point _previousLoopTime;
	void _loop();

public:
	FluxworksEngine();
	~FluxworksEngine();

	/// <summary>
	/// tickrate of the engine logic
	/// </summary>
	uint32_t loopInterval_ms;

	/// <summary>
	/// Checks whether the engine is running
	/// </summary>
	/// <returns>Whether the engine is running</returns>
	bool isRunning();

	/// <summary>
	/// Fetches the current in-engine time, in ms
	/// </summary>
	/// <returns>Current in-engine time</returns>
	uint64_t t();

	/// <summary>
	/// Starts the game engine. If the engine is already running, 
	/// will return a [FluxworksAlreadyRunningException]
	/// </summary>
	void start();

	/// <summary>
	/// Stops the game engine. If the engine is not running,
	/// no effect.
	/// </summary>
	void stop();
};