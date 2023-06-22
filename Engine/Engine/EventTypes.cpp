#include "pch.h"
#include "EventTypes.h"

InputModifiers::InputModifiers(bool leftMouseButton, bool middleMouseButton, bool rightMouseButton, bool ctrl, bool shift, bool alt, bool xButton1, bool xButton2)
{
	this->ctrl = ctrl;
	this->alt = alt;
	this->leftMouseButton = leftMouseButton;
	this->rightMouseButton = rightMouseButton;
	this->middleMouseButton = middleMouseButton;
	this->shift = shift;
	this->xButton1 = xButton1;
	this->xButton2 = xButton2;
}
