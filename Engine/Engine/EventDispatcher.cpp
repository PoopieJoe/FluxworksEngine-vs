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

_FluxworksEventHandlerBase::~_FluxworksEventHandlerBase()
{
}

FluxworksEvent::FluxworksEvent()
{
}
