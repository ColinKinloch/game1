#include "Texture.h"

std::map<std::string, Texture*> Texture::_textures;

Texture::Texture(std::string path)
{
	_id = 0;
	if(_textures.find(path)!=_textures.end())
	{
		_id = _textures[path]->_id;
		_width = _textures[path]->_width;
		_height = _textures[path]->_height;
	}
	else
	{
		free();
		glGenTextures(1, &_id);
		glBindTexture(GL_TEXTURE_2D, _id);
		
		
		loadFromFile(path);
		_textures[path] = this;
	}
	SDL_Log("Tex: %i:%s", _id, path.c_str());
}

Texture::~Texture()
{
	free();
}

GLuint Texture::getID()
{
	return _id;
}

GLuint Texture::getHeight()
{
	return _height;
}

GLuint Texture::getWidth()
{
	return _width;
}

void Texture::free()
{
	
	if(_id != 0)
	{
		glDeleteTextures(1, &_id);
		_id = 0;
	}
	_height = 0;
	_width = 0;
}

bool Texture::loadFromPixels32(GLuint* pixels)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		printf("Texture: load from pixel fail: %s\n", gluErrorString(err));
	}
	
	return true;
}

bool Texture::loadFromFile(std::string path)
{
	bool textureLoaded = false;
	
	ILuint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);
	ILboolean success = ilLoadImage(path.c_str());
	
	if(IL_TRUE == success)
	{
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if(IL_TRUE == success)
		{
			_width = ilGetInteger( IL_IMAGE_WIDTH );
			_height = ilGetInteger( IL_IMAGE_HEIGHT );
			SDL_Log("%i", _height);
			loadFromPixels32((GLuint*)ilGetData());
			
			textureLoaded = true;
		}
	}
	
	ilDeleteImages(1, &imgID);
	
	return textureLoaded;
}

