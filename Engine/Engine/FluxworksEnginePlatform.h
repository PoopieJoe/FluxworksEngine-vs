#pragma once
#ifdef FLUXWORKSENGINE_EXPORTS
#define FLUXWORKSENGINE_API __declspec(dllexport)
#else
#define FLUXWORKSENGINE_API __declspec(dllimport)
#endif // FLUXWORKSENGINE_EXPORTS