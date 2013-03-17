#ifndef CK_G1_WINDOW
#define CK_G1_WINDOW

#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <GL/glext.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <IL/il.h>
#include <IL/ilu.h>


class Window
{
	SDL_GLContext _gl;
	int _width;
	int _height;
	
	
	
	GLuint _projPointer;
	GLuint _modViewPointer;
	
	public:
		SDL_Window* window;
		float zoom;
		
		static GLuint vShadObj;
		static GLuint fShadObj;
		static GLuint shadProg;
		
		static glm::mat4 _projMat;
		static glm::mat4 _modViewMat;
		
		float ratio;
		
		Window();
		~Window();
		
		bool fullscreen();
		void resize();
		bool render();
		
};

#endif//CK_G1_WINDOW

