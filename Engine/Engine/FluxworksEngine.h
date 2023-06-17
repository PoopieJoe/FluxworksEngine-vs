#pragma once

#ifdef FLUXWORKSENGINE_EXPORTS
#define FLUXWORKSENGINE_API __declspec(dllexport)
#else
#define FLUXWORKSENGINE_API __declspec(dllimport)
#endif // FLUXWORKSENGINE_EXPORTS

#include <chrono>
#include "EventDispatcher.h"

constexpr auto TICKRATE = 1;

enum class FluxworksError : uint64_t
{
	Fluxworks_Success = 0,
	Fluxworks_Already_Running,
	Fluxworks_Unknown_Error = UINT64_MAX
};

class FLUXWORKSENGINE_API FluxworksEngine {

private:
	bool _running;
	uint64_t _t_ms;
	FluxworksEventDispatcher _eventDispatcher;

	std::chrono::steady_clock::time_point _previousLoopTime;
	FluxworksError _loop();

public:
	FluxworksEngine();
	~FluxworksEngine();

	uint32_t loopInterval_ms;

	bool isRunning();
	uint64_t t();

	FluxworksError start();
	FluxworksError stop();
};