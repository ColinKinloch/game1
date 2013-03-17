#include "Input.h"

Input::Input()
{
	
}

std::vector<Input*> Input::controllers;

bool Input::init()
{
	/*SDL_JoystickEventState(SDL_ENABLE);
	
	Keyboard *keyb = new Keyboard();
	
	Input::controllers.push_back(keyb);
	
	for(int i=0; i<SDL_NumJoysticks(); i++)
	{
		
	}
	*/
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

Keyboard::Keyboard()
{
	super();
}

Joystick::Joystick()
{
	super();
}
