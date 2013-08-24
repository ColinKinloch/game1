#ifndef CK_G1_GAME
#define CK_G1_GAME

#include <vector>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#define SDL_NO_GLEXT
#include <SDL2/SDL_opengl.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Window.h"
#include "Input.h"
#include "Sprite.h"
#include "String.h"
#include "Player.h"
#include "Texture.h"

class Game
{
	Window* window;
	
	public:
		
		Game();
		~Game();
		
		int pace;
		
		bool event();
		bool step(int t, int dt);
		bool render();
		bool running;
};

#endif//CK_G1_GAME

