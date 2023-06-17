#include "pch.h"
#include "EventDispatcher.h"

void FluxworksEventDispatcher::addHandler(_FluxworksEventHandlerBase* eventHandler)
{
    this->handlers.insert(eventHandler);
}

void FluxworksEventDispatcher::dispatch(FluxworksEvent* event)
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
