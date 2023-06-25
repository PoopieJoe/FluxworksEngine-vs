#pragma once
#include "pch.h"
#include "EventDispatcher.h"

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


struct KeyDown : public FluxworksEvent
{
    KeyDown(int key, bool held) : _BASEEVT(KeyDown)
    {
        this->key = key;
        this->held = held;
    }
    int key;
    bool held;

};

struct MouseMove : public FluxworksEvent
{
    MouseMove(InputModifiers modifier, long x, long y) : _BASEEVT(MouseMove)
    {
        this->modifier = modifier;
        this->x = x;
        this->y = y;
    }
    InputModifiers modifier;
    long x;
    long y;
};

struct MouseButtonDown : public FluxworksEvent
{
    MouseButtonDown(MouseButton button, InputModifiers modifiers, long x, long y) : _BASEEVT(MouseButtonDown)
    {
        this->button = button;
        this->modifiers = modifiers;
        this->x = x;
        this->y = y;
    }
    MouseButton button;
    InputModifiers modifiers;
    long x;
    long y;
};

struct Open : public FluxworksEvent
{
    Open(HWND windowHandle) : _BASEEVT(Open)
    {
        this->windowHandle = windowHandle;
    }
    HWND windowHandle;
};

struct Close : public FluxworksEvent
{
    Close(HWND windowHandle) : _BASEEVT(Close)
    {
        this->windowHandle = windowHandle;
    }
    HWND windowHandle;
};