#ifndef CK_G1_TEXTURE
#define CK_G1_TEXTURE

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "GLLoad.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include "Animation.h"

class Texture
{
		static std::map<std::string, Texture*> _textures;
		
	protected:
		GLuint _id;
		GLuint _width;
		GLuint _height;
		
	public:
		Texture(std::string path);
		~Texture();
		
		GLuint getID();
		GLuint getWidth();
		GLuint getHeight();
		bool loadFromFile(std::string path);
		bool loadFromPixels32(GLuint* pixels);
		void free();
		
		void addAnim(std::string Name, std::vector<int>frames, int FrameRate, bool Loop);
};

#endif//CK_G1_TEXTURE
