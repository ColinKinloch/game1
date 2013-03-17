#ifndef CK_G1_SHADER
#define CK_G1_SHADER

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "GLLoad.h"

class Shader
{
		static std::map<std::string, Shader*> _shaders;
		
		GLuint _type;
		
	protected:
		GLuint _id;
		
	public:
		Shader(std::string Path, GLenum Type);
		~Shader();
		
		bool loadFromFile(std::string Path);
		GLuint getID();
};

class ShaderProgram
{
		static std::map<std::string, ShaderProgram*> _programs;
		
	protected:
		GLuint _id;
		Shader* _v;
		Shader* _f;
		
	public:
		ShaderProgram(std::string VertexPath, std::string FragmentPath);
		
		void use();
		GLuint getID();
};

#endif//CK_G1_SHADER
