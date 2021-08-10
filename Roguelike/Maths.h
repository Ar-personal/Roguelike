#pragma once
#include "SDL.h"

class Maths {

public:
	Maths();
	~Maths();


	static SDL_Point isoTo2D(int x, int y);

	static SDL_Point twoDToIso(int x, int y);

};
