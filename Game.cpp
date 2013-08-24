#include "Game.h"

SDL_Event e;
Sprite* sprite;
Sprite* sprite2;
String* string;
int loop = 0;
const Uint8 *keystates;
std::vector<bool> butstates;
Player player[4];


SDL_Joystick *joystick;

Game::Game()
{
	if(SDL_Init(SDL_INIT_JOYSTICK|SDL_INIT_VIDEO) <0)
	{
		fprintf(stderr, "Game: sdl: init fail");
		exit(1);
	}
	
	window = new Window();
	
	Texture::init();
	Input::init();
	
	for(int i=0; i<SDL_NumJoysticks(); i++)
	{
		SDL_Joystick *joystick = SDL_JoystickOpen(0);
		butstates.resize(SDL_JoystickNumButtons(joystick));
	}
	
	keystates = SDL_GetKeyboardState(NULL);
	
	running = true;
	
}

Game::~Game()
{
	SDL_Log("Goodbye.");
	SDL_Quit();
}

bool Game::event()
{
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_QUIT:
			{
				running = false;
				break;
			}
			case SDL_WINDOWEVENT:
			{
				switch(e.window.event)
				{
					case SDL_WINDOWEVENT_SIZE_CHANGED:
					{
						window->resize();
						break;
					}
				}
				break;
			}
			case SDL_JOYBUTTONDOWN:
			{
				butstates[e.jbutton.button] = true;
				break;
			}
			case SDL_JOYBUTTONUP:
			{
				butstates[e.jbutton.button] = false;
				break;
			}
			case SDL_KEYDOWN:
			{
				keystates = SDL_GetKeyboardState(NULL);
				if((keystates[SDL_SCANCODE_LCTRL]&&keystates[SDL_SCANCODE_Q])||keystates[SDL_SCANCODE_ESCAPE])
					running = false;
				if((keystates[SDL_SCANCODE_LALT]&&keystates[SDL_SCANCODE_RETURN])||(keystates[SDL_SCANCODE_F11]))
					window->fullscreen();
				Input::poll(e);
				break;
			}
		}
	}
	return true;
}

bool Game::step(int t, int dt)
{
	sprite->vel.y=0;
	sprite->vel.x=0;
	if(keystates[SDL_SCANCODE_UP])
		sprite->vel.y=-1;
	if(keystates[SDL_SCANCODE_DOWN])
		sprite->vel.y=1;
	if(keystates[SDL_SCANCODE_LEFT])
		sprite->vel.x=-1;
	if(keystates[SDL_SCANCODE_RIGHT])
		sprite->vel.x=1;
	sprite->step();
	sprite2->step();
	return true;
}

bool Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	sprite2->render();
	sprite->render();
	window->render();
	return true;
}

int main()
{
	Game* game = new Game();
	
	sprite2 = new Sprite(-200, 0, 100, 100, "data/imgs/bigface.png", "data/default2.glvs", "data/default2.glfs");
	sprite = new Sprite(0, 0, 10, 10, "data/imgs/char.png", "data/default.glvs", "data/default.glfs");
	string = new String("Hello World", 0, 0);
	
	player[0].input = Input::ctrls[0];
	player[0].sprites.push_back(sprite);
	player[0].sprites.push_back(sprite2);
	
	
	int t = 0;
	const int dt = 16;
	
	int currentTime = SDL_GetTicks();
	int accumulator = 0;
	
	while(game->running)
	{
		game->event();
		
		int newTime = SDL_GetTicks();
		int frameTime = newTime - currentTime;
		if(frameTime > (dt*25))
			frameTime = dt*25;
		currentTime = newTime;
		
		accumulator += frameTime;
		
		while(accumulator >= dt)
		{
			game->step(t, dt);
			t += dt;
			accumulator -= dt;
		}
		
		const int alpha = accumulator/dt;
		game->render();
	}
	delete game;
	return 0;
}
