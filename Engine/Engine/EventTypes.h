#pragma once
#include "pch.h"
#include "EventDispatcher.h"
#include "Window.h"

#define _BASEEVT(x) FluxworksEvent(#x)


struct InputModifiers {
    InputModifiers(
        bool leftMouseButton = false,
        bool middleMouseButton = false,
        bool rightMouseButton = false,
        bool ctrl = false,
        bool shift = false,
        bool alt = false,
        bool xButton1 = false,
        bool xButton2 = false
    );

    bool ctrl;
    bool leftMouseButton;
    bool middleMouseButton;
    bool rightMouseButton;
    bool shift;
    bool alt;
    bool xButton1;
    bool xButton2;
};

enum class MouseButton {
    LeftMouseButton,
    RightMouseButton,
    MiddleMouseButton,
    XButton1,
    XButton2
};

class TickEvent : public FluxworksEvent
{
public:
    TickEvent(std::chrono::duration<double> deltaTime, std::chrono::steady_clock::time_point time) : _BASEEVT(TickEvent),
        deltaTime(deltaTime), time(time)
    {
        this->deltaTime = deltaTime;
        this->time = time;
    }

    std::chrono::duration<double> deltaTime;
    std::chrono::steady_clock::time_point time;
};

namespace WindowEvents 
{
    struct KeyDown : public FluxworksEvent
    {
        KeyDown(FluxworksEngineWindow* windowInstance, unsigned int key) : _BASEEVT(KeyDown),
            windowInstance(windowInstance), key(key)
        {
        };
        FluxworksEngineWindow* windowInstance;
        unsigned int key;

    };

    struct KeyUp : public FluxworksEvent
    {
        KeyUp(FluxworksEngineWindow* windowInstance, unsigned int key) : _BASEEVT(KeyUp),
            windowInstance(windowInstance), key(key)
        {
        };
        FluxworksEngineWindow* windowInstance;
        unsigned int key;
    };

    struct MouseMove : public FluxworksEvent
    {
        MouseMove(FluxworksEngineWindow* windowInstance, InputModifiers modifier, long x, long y) : _BASEEVT(MouseMove),
            windowInstance(windowInstance), x(x), y(y), modifier(modifier)
        {
        };
        FluxworksEngineWindow* windowInstance;
        InputModifiers modifier;
        long x;
        long y;
    };

    struct MouseButtonDown : public FluxworksEvent
    {
        MouseButtonDown(FluxworksEngineWindow* windowInstance, MouseButton button, InputModifiers modifiers, long x, long y) : _BASEEVT(MouseButtonDown),
            windowInstance(windowInstance), button(button), modifiers(modifiers), x(x), y(y)
        {
        };
        FluxworksEngineWindow* windowInstance;
        MouseButton button;
        InputModifiers modifiers;
        long x;
        long y;
    };

    struct MouseButtonUp : public FluxworksEvent
    {
        MouseButtonUp(FluxworksEngineWindow* windowInstance, MouseButton button, InputModifiers modifiers, long x, long y) : _BASEEVT(MouseButtonUp),
            windowInstance(windowInstance), button(button), modifiers(modifiers), x(x), y(y)
        {
        };
        FluxworksEngineWindow* windowInstance;
        MouseButton button;
        InputModifiers modifiers;
        long x;
        long y;
    };

    struct MouseWheel : public FluxworksEvent
    {
        MouseWheel(FluxworksEngineWindow* windowInstance, InputModifiers modifiers, int delta, long x, long y) : _BASEEVT(MouseWheel),
            windowInstance(windowInstance), modifiers(modifiers), delta(delta), x(x), y(y)
        {
        };
        FluxworksEngineWindow* windowInstance;
        InputModifiers modifiers;
        int delta;
        long x;
        long y;
    };

    struct Open : public FluxworksEvent
    {
        Open(FluxworksEngineWindow* windowInstance) : _BASEEVT(Open),
            windowInstance(windowInstance)
        {
        };
        FluxworksEngineWindow* windowInstance;
    };

    struct Close : public FluxworksEvent
    {
        Close(FluxworksEngineWindow* windowInstance) : _BASEEVT(Close),
            windowInstance(windowInstance)
        {
        };
        FluxworksEngineWindow* windowInstance;
    };
}