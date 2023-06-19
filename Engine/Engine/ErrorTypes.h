#pragma once
#include "pch.h"
#include <stdexcept>

class FluxworksAlreadyRunningException : public std::runtime_error { using std::runtime_error::runtime_error; };
class FluxworksWindowAlreadyOpenException : public std::runtime_error { using std::runtime_error::runtime_error; };
class FluxworksUnknownException : public std::runtime_error { using std::runtime_error::runtime_error; };
