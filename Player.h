#ifndef CK_G1_PLAYER
#define CK_G1_PLAYER

#include <vector>
#include "Sprite.h"
#include "Input.h"

struct Player
{
	std::vector<Sprite*> sprites;
	Input* input;
};

#endif//CK_G1_PLAYER
