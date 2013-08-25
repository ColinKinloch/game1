#include "Sprite.h"

Sprite::Sprite()
{
	
}

Sprite::Sprite(float X, float Y, float Width, float Height,
 std::string TexturePath, std::string VertexPath, std::string FragmentPath)
{
	_tH = 0;
	_tW = 0;
	
	pos = {X, Y};
	vel = {0, 0};
	accel = {0, 0};
	h = Height;
	w = Width;
	
	_t = new Texture(TexturePath);
	_tH = _t->getHeight();
	_tW = _t->getWidth();
	
	_s = new ShaderProgram(VertexPath, FragmentPath);
	
	GLfpoint quadVertices[4];
	GLuint indices[4];
	
	indices[ 0 ] = 0;
	indices[ 1 ] = 1;
	indices[ 2 ] = 2;
	indices[ 3 ] = 3;
	
	glGenBuffers(1, &_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(GLtexpoint), quadVertices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &_iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indices, GL_STATIC_DRAW);
	
	
	_vData[0].texCoord.s =    0.f; _vData[0].texCoord.t =    0.f;
	_vData[1].texCoord.s =  (float)_tH/_tW; _vData[1].texCoord.t =    0.f;
	_vData[2].texCoord.s =  (float)_tH/_tW; _vData[2].texCoord.t =  1.f;
	_vData[3].texCoord.s =    0.f; _vData[3].texCoord.t = 1.f;
	SDL_Log("%f|%i:%i", ((float)_tH/_tW),_tW, _tH);
	//Vertex positions
	_vData[0].position.x = w/-2; _vData[0].position.y =   h/-2;
	_vData[1].position.x =   w/2; _vData[1].position.y =   h/-2;
	_vData[2].position.x =   w/2; _vData[2].position.y = h/2;
	_vData[3].position.x = w/-2; _vData[3].position.y = h/2;
	
	GLint texcoord = glGetAttribLocation(_s->getID(), "TexCoord");
	GLint vertexpos = glGetAttribLocation(_s->getID(), "VertOffset");
	
	glBindBuffer( GL_ARRAY_BUFFER, _vboID );
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(GLtexpoint), _vData);
	
	glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(GLtexpoint), (GLvoid*)offsetof(GLtexpoint, texCoord));
	glVertexAttribPointer(vertexpos, 2, GL_FLOAT, GL_FALSE, sizeof(GLtexpoint), (GLvoid*)offsetof(GLtexpoint, position));
	
	
	GLint berr = glGetError();
	if(berr != GL_NO_ERROR)
	 printf("Sprite: render:berr %s\n", gluErrorString(berr));
}

Sprite::~Sprite()
{
}

void Sprite::render()
{
	_s->use();
	
	GLuint _projPointer = glGetUniformLocation(_s->getID(), "LProjectionMatrix");
	GLuint _modViewPointer = glGetUniformLocation(_s->getID(), "LModelViewMatrix");
	
	glUniformMatrix4fv(_projPointer, 1, GL_FALSE, glm::value_ptr(Window::_projMat));
	glUniformMatrix4fv(_modViewPointer, 1, GL_FALSE, glm::value_ptr(Window::_modViewMat));
	
	GLint sampunit = glGetUniformLocation(_s->getID(), "LTextureUnit");
	GLint sampcol = glGetUniformLocation(_s->getID(), "LTextureColor");
	
	
	
	GLint objpos = glGetUniformLocation(_s->getID(), "Pos");
	//v^ different id
	glActiveTexture(GL_TEXTURE0+(_t->getID()));
	glBindTexture(GL_TEXTURE_2D, _t->getID());
	glUniform1i(sampunit, _t->getID());
	float hey[4] = {1.f, 1.f, 1.f, 1.f};
	glUniform4fv(sampcol, 1, (const GLfloat*)&hey);
	glUniform2fv(objpos, 1, (const GLfloat*)&pos);
	
	GLint texcoord = glGetAttribLocation(_s->getID(), "TexCoord");
	GLint vertexpos = glGetAttribLocation(_s->getID(), "VertOffset");
	
	
	//GLfpoint point[4]; point[0] = point[1] = point[2] = point[3] = {x,y};
	
	glEnableVertexAttribArray(texcoord);
	glEnableVertexAttribArray(vertexpos);
		
		glBindBuffer( GL_ARRAY_BUFFER, _vboID );
		
		glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(GLtexpoint), (GLvoid*)offsetof(GLtexpoint, texCoord));
		glVertexAttribPointer(vertexpos, 2, GL_FLOAT, GL_FALSE, sizeof(GLtexpoint), (GLvoid*)offsetof(GLtexpoint, position));
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
		
		
	glDisableVertexAttribArray(texcoord);
	glDisableVertexAttribArray(vertexpos);
	
		
	GLint err = glGetError();
	if(err != GL_NO_ERROR)
		printf("Sprite: render: %s\n", gluErrorString(err));
}

GLuint Sprite::getTextureID()
{
	return _t->getID();
}

void Sprite::step()
{
	pos.x += vel.x;
	pos.y += vel.y;
	vel.x += accel.x;
	vel.y += accel.y;
}

