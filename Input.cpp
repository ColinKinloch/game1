#include "Input.h"

Input::Input()
{
}

std::vector<Input*> Input::ctrls;

bool Input::init()
{
	SDL_JoystickEventState(SDL_ENABLE);
	
	//for(int i=0; i<SDL_GetNumKeyboards(); i++)
	//	ctrls.push_back(new Keyboard(i));
	ctrls.push_back(new Keyboard(0));
	
	for(int i=0; i<SDL_NumJoysticks(); i++)
	{
		ctrls.push_back(new Joystick(i));
		SDL_Log(dynamic_cast<Joystick*>(ctrls.back())->getName());
		SDL_Log("hey");
	}
	
	return true;
}

bool Input::poll(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_KEYDOWN:
		{
			printf("key\n");
			break;
		}
		case SDL_JOYBUTTONDOWN:
		{
			printf("button\n");
			break;
		}
	}
	
	return true;
}

Keyboard::Keyboard(int Index)
{
	_id = Index;
	super();
}

Joystick::Joystick(int Index)
{
	SDL_JoystickOpen(Index);
	_id = Index;
	super();
}

const char* Joystick::getName()
{
	return SDL_JoystickName(_js);
}
