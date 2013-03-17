#ifndef CK_G1_STRING
#define CK_G1_STRING

#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Sprite.h"

class String: public Sprite
{
		static FT_Library ftLibrary;
		static FT_Face ftTermN;
		static FT_Face ftTermB;
		static FT_GlyphSlot ftSlot;
		
	public:
		
		String(std::string Text, int X, int Y);
};

#endif//CK_G1_STRING
