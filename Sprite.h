#ifndef CK_G1_SPRITE
#define CK_G1_SPRITE

#include <string>
#include "GLLoad.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLStructs.h"
#include "Texture.h"
#include "Shader.h"
#include "Window.h"

struct point
{
	float x;
	float y;
};

class Sprite
{
		Texture* _t;
		ShaderProgram* _s;
		
		GLuint _tW;
		GLuint _tH;
		
		GLuint _vboID;
		GLuint _iboID;
		
		GLtexpoint _vData[4];
	public:
		Sprite();
		Sprite(float X, float Y, float Width, float Height, std::string TexturePath,
		 std::string VertexPath, std::string FragmentPath);
		~Sprite();
		
		
		point pos;
		point vel;
		point accel;
		
		float w;
		float h;
		
		void render();
		void step();
		GLuint getTextureID();
		int getWidth();
		int getHeight();
};

#endif//CK_G1_SPRITE

