#pragma once
#include "TextureManager.h"

class Tile {
public:

	SDL_Texture* texture;
	SDL_Rect* src = new SDL_Rect;
	int id;
		
		Tile();
		Tile(const char* path, int x, int y, int w, int h, int id);
		Tile(SDL_Texture* tex, int x, int y, int w, int h, int id);

};