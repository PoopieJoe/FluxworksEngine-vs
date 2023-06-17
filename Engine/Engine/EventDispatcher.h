#pragma once

#include <stdint.h>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <stdexcept>

/* Idea: Create required Event Types, inheriting from [IEventType],
* Then the event must be registered with the [EventDispatcher]
* When an Event occurs, all listeners with a handler for that type
* of event have said handler invoked by the dispatcher
* https://codereview.stackexchange.com/questions/200049/simple-event-dispatcher
* https://stackoverflow.com/questions/14033271/design-event-dispatcher-event-source-event-watcher-with-type-safety-in-c
* 
*/


/// <summary>
/// Base Event class from which all (custom) events may inherit
/// </summary>
class FluxworksEvent 
{
public:
	FluxworksEvent();
	virtual ~FluxworksEvent() {};
};

class _FluxworksEventHandlerBase
{
public:
	virtual void handler(FluxworksEvent*) = 0;
	virtual ~_FluxworksEventHandlerBase();
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
private:
	void handler(FluxworksEvent*);
public:
	virtual void handler(Event*) = 0;
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
public:
    void registerHandler(_FluxworksEventHandlerBase* eventHandler);
	void dispatchEvent(FluxworksEvent* event);
};

