#ifndef CK_G1_INPUT
#define CK_G1_INPUT

#include <vector>
#include <SDL2/SDL.h>

class Input
{
	public:
		static std::vector<Input*> controllers;
		static bool init();
		static bool poll(SDL_Event);
		
		Input();
};

class Keyboard: public Input
{
	public:
		typedef Input super;
		Keyboard();
};

class Joystick: public Input
{
		SDL_Joystick* joystick;
	public:
		typedef Input super;
		Joystick();
};

#endif//CK_G1_INPUT
