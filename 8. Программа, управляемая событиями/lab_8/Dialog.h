#pragma once
#include "Event.h"
#include "Vector.h"
#include <string>


class Dialog : public Vector
{
protected:
	int EndState;

public:
	Dialog();
	virtual ~Dialog();
	virtual void GetEvent(TEvent &event) const;
	virtual int Execute();
	virtual void ClearEvent(TEvent &event); 
	virtual void HandleEvent(TEvent &event); //обработчик
	int Valid(); //проверка атрибута EndState
	void EndExec();
};

