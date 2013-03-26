#ifndef CK_G1_INPUT
#define CK_G1_INPUT

#include <vector>
#include <string>
#include <SDL2/SDL.h>

class Input
{
	public:
		static std::vector<Input*> ctrls;
		static bool init();
		static bool poll(SDL_Event);
		
		int _id;
		
		Input();
		
		virtual const char* getName() {};
};

class Keyboard: public Input
{
	public:
		typedef Input super;
		Keyboard(int Index);
};

class Joystick: public Input
{
		SDL_Joystick* _js;
	public:
		typedef Input super;
		Joystick(int Index);
		
		const char* getName();
};

#endif//CK_G1_INPUT
