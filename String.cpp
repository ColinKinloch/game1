#include "String.h"

FT_Library String::ftLibrary;
FT_Face String::ftTermN;
FT_Face String::ftTermB;
FT_GlyphSlot String::ftSlot;

String::String(std::string Text, int X, int Y)
 :Sprite()
{
	if(ftLibrary)
		if(FT_Init_FreeType(&ftLibrary))
		{
			fprintf(stderr, "String: freetype: init fail");
		}
}
