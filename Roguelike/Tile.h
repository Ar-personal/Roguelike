#pragma once
#include "TextureManager.h"
#include "Vector2D.h"

class Tile {
public:

	Vector2D position;
	SDL_Texture* texture;
	SDL_Rect src;
	SDL_Rect dst;
	int id;
	bool empty = false;
	bool collider = false;
		
	Tile();
	Tile(const char* path, SDL_Rect src, SDL_Rect dst, int id);
	Tile(SDL_Texture* tex, SDL_Rect dst, int id);

};