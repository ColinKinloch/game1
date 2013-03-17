#include "Window.h"

GLuint tID;
GLuint tWidth;
GLuint tHeight;

GLuint Window::vShadObj;
GLuint Window::fShadObj;

GLuint Window::shadProg;

glm::mat4 Window::_projMat;
glm::mat4 Window::_modViewMat;

Window::Window()
{
	window = SDL_CreateWindow("game1 test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	
	zoom = 3;
	
	_gl = SDL_GL_CreateContext(window);
	
	GLuint GLEWerr = glewInit();
	if(GLEWerr != GLEW_OK)
		printf("GLEW: %s\n", glewGetErrorString(GLEWerr));
	
	if( !GLEW_VERSION_3_2 )
		printf( "OpenGL 3.2 not supported!\n" );
	
	SDL_Surface *icon = SDL_LoadBMP("imgs/icon.bmp");
	icon->format->Amask = 0xFF000000; 
	SDL_SetWindowIcon(window, icon);
	
	SDL_GetWindowSize(window, &_width, &_height);
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	
	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable( GL_LIGHTING );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		printf("Error: %s\n", gluErrorString(err));
	}
	
	
	printf( "VENDOR = %s\n", glGetString( GL_VENDOR ) ) ;
	printf( "RENDERER = %s\n", glGetString( GL_RENDERER ) ) ;
	printf( "VERSION = %s\n", glGetString( GL_VERSION ) ) ;
	/*
	vShadObj = glCreateShader(GL_VERTEX_SHADER);
	fShadObj = glCreateShader(GL_FRAGMENT_SHADER);
	
	std::fstream vShadFile("default.glvs", std::ios::in);
	std::string vShadStr;
	if(vShadFile.is_open())
	{
		std::stringstream buffer;
		buffer << vShadFile.rdbuf();
		vShadStr = buffer.str();
	}
	std::fstream fShadFile("default.glfs", std::ios::in);
	std::string fShadStr;
	if(fShadFile.is_open())
	{
		std::stringstream buffer;
		buffer << fShadFile.rdbuf();
		fShadStr = buffer.str();
	}
	
	const char* vc_str = vShadStr.c_str();
	glShaderSource(vShadObj, 1, &vc_str, NULL);
	const char* fc_str = fShadStr.c_str();
	glShaderSource(fShadObj, 1, &fc_str, NULL);
	
	glCompileShader(vShadObj);
	glCompileShader(fShadObj);
	
	shadProg = glCreateProgram();
	
	glAttachShader(shadProg, vShadObj);
	glAttachShader(shadProg, fShadObj);
	
	glLinkProgram(shadProg);
	
	GLint programSuccess = GL_TRUE;
	glGetProgramiv( shadProg, GL_LINK_STATUS, &programSuccess );
	if( programSuccess != GL_TRUE )
		printf( "Error linking program %d!\n", shadProg );
	
	glUseProgram(shadProg);
	
	_projPointer = glGetUniformLocation(shadProg, "LProjectionMatrix");
	_modViewPointer = glGetUniformLocation(shadProg, "LModelViewMatrix");
	*/
	
	glHint(GL_NICEST, GL_FRAGMENT_SHADER_DERIVATIVE_HINT);
	glHint(GL_NICEST, GL_LINE_SMOOTH_HINT);
	glHint(GL_NICEST, GL_POLYGON_SMOOTH_HINT);
	glHint(GL_NICEST, GL_TEXTURE_COMPRESSION_HINT);
	glEnable(GL_MULTISAMPLE);
	
	resize();
	
	err = glGetError();
	if(err != GL_NO_ERROR)
		printf("Window: Shader: %s\n", gluErrorString(err));
	
	ilInit();
	ilClearColour(255, 255, 255, 000);
	
	ILenum ilError = ilGetError();
	if(ilError != IL_NO_ERROR)
	{
		printf("error loading DevIL: %s\n", iluErrorString(ilError));
	}
	
}

Window::~Window()
{
	char hello[1000];
	glGetShaderInfoLog(vShadObj, 1000, NULL, hello);
	
	printf("%s\n", hello);
	
	SDL_GL_DeleteContext(_gl);
}


bool Window::fullscreen()
{
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	SDL_SetWindowDisplayMode(window, &dm);
	SDL_SetWindowFullscreen(window, !(SDL_GetWindowFlags(window)&SDL_WINDOW_FULLSCREEN));
	return true;
}

void Window::resize()
{
	SDL_GetWindowSize(window, &_width, &_height);
	
	glViewport(0, 0, _width, _height);
	
	_projMat = glm::ortho<GLfloat>(_width/-(2*zoom), _width/(2*zoom), _height/(2*zoom), _height/-(2*zoom), 1.0, -1.0);
	_modViewMat = glm::mat4();
	
//	glUniformMatrix4fv(_projPointer, 1, GL_FALSE, glm::value_ptr(_projMat));
//	glUniformMatrix4fv(_modViewPointer, 1, GL_FALSE, glm::value_ptr(_modViewMat));
}

bool Window::render()
{
	SDL_GL_SwapWindow(window);
	return true;
}

