#ifndef CK_G1_GLSTRUCTS
#define CK_G1_GLSTRUCTS

#include <GL/glew.h>
#define SDL_NO_GLEXT
#include <SDL2/SDL_opengl.h>
#include <GL/glext.h>

struct GLfpoint
{
	GLfloat x;
	GLfloat y;
};

struct GLftex
{
	GLfloat s;
	GLfloat t;
};

struct GLcolorRGBA
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
};

struct GLpointRGBA
{
	GLfpoint pos;
	GLcolorRGBA rgba;
};

struct GLtexpoint
{
	GLfpoint position;
	GLftex texCoord;
};

#endif//CK_G1_GLSTRUCTS
