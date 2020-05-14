#pragma once
#include "Event.h"


class Object
{
public:
	Object();
	virtual ~Object();
	virtual void Show() const = 0;
	virtual void Input() = 0;
	virtual int HandleEvent(const TEvent &e) = 0;
};

