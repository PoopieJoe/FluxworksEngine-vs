#pragma once
#include "pch.h"
#include <stdint.h>
#include <unordered_set>
#include <list>
#include <iostream>
#include <functional>
#include <algorithm>
#include <stdexcept>

/// <summary>
/// Base Event class from which all events must inherit
/// </summary>
class FluxworksEvent 
{
public:
	FluxworksEvent(const char* typeName);
	virtual ~FluxworksEvent() {};

	const char* typeName;
};

class _FluxworksEventHandlerBase
{
public:
	virtual void handler(FluxworksEvent*) = 0;
	virtual ~_FluxworksEventHandlerBase() {};
};

/// <summary>
/// Event handler class for a specific type of [FluxworksEvent].
/// This handler should implement its own [handler] for its associated [Event].
/// Every tick all handlers will receive a call for each occurance of its associated events.
/// </summary>
/// <typeparam name="Event">The associated Event type</typeparam>
template <class Event>
class FluxworksEventHandler : public _FluxworksEventHandlerBase
{
public:
	virtual void handler(Event*) = 0;
	void handler(FluxworksEvent*);
};

/// <summary>
/// Attempts to cast the generated event to its associated type, if it fails, nothing happens.
/// If it succeeds, the handler function is called
/// </summary>
/// <typeparam name="Event">The associated event</typeparam>
/// <param name="e">The generated event</param>
template<class Event>
inline void FluxworksEventHandler<Event>::handler(FluxworksEvent* e)
{
	Event* derivedEvent = dynamic_cast<Event*>(e);
	if (derivedEvent)
	{
		this->handler(derivedEvent);
	}
}	

/// <summary>
/// The dispatcher gathers registered handlers. When an event 
/// is dispatched, all associated handlers of the event type are called
/// </summary>
class FluxworksEventDispatcher
{
private:
    std::unordered_set<_FluxworksEventHandlerBase*> handlers;
	std::list< FluxworksEvent*> eventQueue;
public:

    /// <summary>
    /// Registers a handler with the dispatcher.
    /// </summary>
    /// <param name="eventHandler">Handler object to add</param>
    void registerHandler(_FluxworksEventHandlerBase* eventHandler);

	/// <summary>
	/// Dispatches an event to all handlers, registered using
	/// [registerHandler], of the event type.
	/// </summary>
	/// <param name="event">Event to dispatch</param>
	void dispatchEvent(FluxworksEvent* event);

	void queueEvent(FluxworksEvent* event);
	void dispatchQueue(void);
	void dispatchQueue(int n);
};

