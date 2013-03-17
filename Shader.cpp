#include "Shader.h"

std::map<std::string, ShaderProgram*> ShaderProgram::_programs;

ShaderProgram::ShaderProgram(std::string VertexPath, std::string FragmentPath)
{
	std::string key = VertexPath+":"+FragmentPath;
	if(_programs.find(key)!=_programs.end())
	{
		_id = _programs[key]->_id;
		_v = _programs[key]->_v;
		_f = _programs[key]->_f;
	}
	else
	{
		_v = new Shader(VertexPath, GL_VERTEX_SHADER);
		_f = new Shader(FragmentPath, GL_FRAGMENT_SHADER);
		
		_id = glCreateProgram();
		
		glAttachShader(_id, _v->getID());
		glAttachShader(_id, _f->getID());
		
		glLinkProgram(_id);
		
		GLint succ = GL_TRUE;
		glGetProgramiv( _id, GL_LINK_STATUS, &succ );
		if( succ != GL_TRUE )
			printf( "Shader: link fail: %d\n", _id );
		
		_programs[key] = this;
	}
	SDL_Log("Tex: %i:%s", _id, key.c_str());
}

void ShaderProgram::use()
{
	glUseProgram(_id);
}

GLuint ShaderProgram::getID()
{
	return _id;
}

std::map<std::string, Shader*> Shader::_shaders;

Shader::Shader(std::string Path, GLenum Type)
{
	_type = Type;
	if(_shaders.find(Path)!=_shaders.end())
	{
		_id = _shaders[Path]->_id;
	}
	else
	{
		_id = glCreateShader(_type);
		loadFromFile(Path);
		glCompileShader(_id);
		_shaders[Path] = this;
	}
}

bool Shader::loadFromFile(std::string Path)
{
	std::fstream shadFile(Path, std::ios::in);
	std::string shadStr;
	if(shadFile.is_open())
	{
		std::stringstream buffer;
		buffer << shadFile.rdbuf();
		shadStr = buffer.str();
	}
	const char* vc_str = shadStr.c_str();
	glShaderSource(_id, 1, &vc_str, NULL);
}

GLuint Shader::getID()
{
	return _id;
}
