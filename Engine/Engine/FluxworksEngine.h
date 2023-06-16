#pragma once

#ifdef FLUXWORKSENGINE_EXPORTS
#define FLUXWORKSENGINE_API __declspec(dllexport)
#else
#define FLUXWORKSENGINE_API __declspec(dllimport)
#endif // FLUXWORKSENGINE_EXPORTS


extern "C" FLUXWORKSENGINE_API void testf(void);

class FLUXWORKSENGINE_API TestObj {
public:
	int i;
	void inc(void);
};