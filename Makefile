CXXCOMP  := g++
CXXFLAGS := `sdl2-config --cflags` `freetype-config --cflags` -std=gnu++11 -frounding-math -fsignaling-nans
LIBFLAGS := -lGL -lGLU -lGLEW -lIL -lILU `sdl2-config --libs` `freetype-config --libs`

all: Game.o Window.o Input.o Shader.o String.o Sprite.o Texture.o
	$(CXXCOMP) Game.o Window.o Input.o Shader.o String.o Sprite.o Texture.o $(LIBFLAGS) -g -omain

Game.o: Game.h Game.cpp
	$(CXXCOMP) $(CXXFLAGS) -c Game.cpp

Window.o: Window.h Window.cpp
	$(CXXCOMP) $(CXXFLAGS) -c Window.cpp

Input.o: Input.h Input.cpp
	$(CXXCOMP) $(CXXFLAGS) -c Input.cpp

Shader.o: Shader.h Shader.cpp
	$(CXXCOMP) $(CXXFLAGS) -c Shader.cpp

String.o: String.h String.cpp
	$(CXXCOMP) $(CXXFLAGS) -c String.cpp

Sprite.o: Sprite.h Sprite.cpp
	$(CXXCOMP) $(CXXFLAGS) -c Sprite.cpp

Texture.o: Texture.h Texture.cpp
	$(CXXCOMP) $(CXXFLAGS) -c Texture.cpp
	
clean:
	rm -f *.o *~ *#
