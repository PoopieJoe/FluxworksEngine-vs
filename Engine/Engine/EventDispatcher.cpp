#include "pch.h"
#include "EventDispatcher.h"

void FluxworksEventDispatcher::registerHandler(_FluxworksEventHandlerBase* eventHandler)
{
    this->handlers.insert(eventHandler);
}

void FluxworksEventDispatcher::dispatchEvent(FluxworksEvent* event)
{
    for (const auto& elem : this->handlers)
    {
        elem->handler(event);
    }
}

void FluxworksEventDispatcher::queueEvent(FluxworksEvent* event)
{
    this->eventQueue.push_back(event);
}

void FluxworksEventDispatcher::dispatchQueue(void)
{
    this->dispatchQueue(this->eventQueue.size());
}

void FluxworksEventDispatcher::dispatchQueue(int n)
{
    for (int i = 0; i < n; i++)
    {
        this->dispatchEvent(this->eventQueue.front());
        this->eventQueue.pop_front();
    }
}

FluxworksEvent::FluxworksEvent()
{
}
