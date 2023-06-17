#pragma once

#include <stdint.h>
#include <unordered_map>

/* Idea: Create required Event Types, inheriting from [IEventType],
* Then the event must be registered with the [EventDispatcher]
* When an Event occurs, all listeners with a handler for that type
* of event have said handler invoked by the dispatcher
* https://codereview.stackexchange.com/questions/200049/simple-event-dispatcher
* https://stackoverflow.com/questions/14033271/design-event-dispatcher-event-source-event-watcher-with-type-safety-in-c
* 
*/

enum class FluxworksEventType : uint64_t
{
	UserInput = 0,
	UnknownEvent = UINT64_MAX
};

class IEventType {

};




class EventDispatcher {
public:

	void addListener(IEventType event, EventHandler handler);
	void removeListener(IEventType event);
	void dispatch(IEventType event);

private:
	std::unordered_map<IEventType, EventHandler> listeners;
};