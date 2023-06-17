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
/// Base Event class from which all others events may inherit
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

template <class Event>
class FluxworksEventHandler : public _FluxworksEventHandlerBase
{
public:
	void handler(FluxworksEvent*);
	virtual void handler(Event*) = 0;
};

template<class Event>
inline void FluxworksEventHandler<Event>::handler(FluxworksEvent* e)
{
	Event* derivedEvent = dynamic_cast<Event*>(e);
	if (derivedEvent)
	{
		this->handler(derivedEvent);
	}
}	

class FluxworksEventDispatcher
{
private:
    std::unordered_set<_FluxworksEventHandlerBase*> handlers;
public:
    void addHandler(_FluxworksEventHandlerBase* eventHandler);
	void dispatch(FluxworksEvent* event);
};

