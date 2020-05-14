#include "Dialog.h"


Dialog::Dialog() : Vector()
{
	EndState = 0;
}

Dialog::~Dialog()
{ }

void Dialog::GetEvent(TEvent &event) const
{
	std::string commands = "m+-szq";

	std::cout << "Enter command code: ";
	std::string str;
	std::cin >> str;

	char code = str[0];

	if(commands.find(code) >= 0) //если элемент не найден возвращается значение npos = -1
	{
		event.what = evMessage;

		switch(code)
		{
			case 'm': event.command = cmMake; break;
			case '+': event.command = cmAdd; break;
			case '-': event.command = cmDel; break;
			case 's': event.command = cmShow; break;
			case 'z': event.command = cmGet; break;
			case 'q': event.command = cmQuit; break;
		}

		if(str.length() > 1)
		{
			std::string param = str.substr(1, str.length()-1);
			int _param = atoi(param.c_str()); //преобразуем параметр в число
			event.param = _param;
		}
	}
	else
		event.what = evNothing;
}

int Dialog::Execute()
{
	TEvent event;

	do
	{
		EndState = 0;
		GetEvent(event);
		HandleEvent(event);
	} 
	while(!Valid());

	return EndState;
}

int Dialog::Valid()
{
	if(EndState == 0)
		return 0;
	else 
		return 1;
}

void Dialog::ClearEvent(TEvent &event)
{
	event.what = evNothing;
}

void Dialog::EndExec()
{
	EndState = 1;
}

void Dialog::HandleEvent(TEvent &event)
{
	if(event.what == evMessage)
	{
		switch(event.command)
		{
			case cmMake: 
				size = event.param;
				beg = new Object*[size];
				cur = 0;
				ClearEvent(event);
				break;
			case cmAdd:
				Add();
				ClearEvent(event);
				break;
			case cmDel:
				Del();
				ClearEvent(event);
				break;
			case cmGet:
				Vector::HandleEvent(event);
				ClearEvent(event);
				break;
			case cmShow:
				Show();
				ClearEvent(event);
				break;
			case cmQuit:
				EndExec();
				ClearEvent(event);
				break;
		}
	}
}