#include "Tile.h"

Tile::Tile() {

}

Tile::Tile(const char* path, int x, int y, int w, int h, int id) {
	src->x = x;
	src->y = y;
	src->w = w;
	src->h = h;

	texture = TextureManager::LoadTextureFromSheet(path, x, y, w, h);
	this->id = id;
}

Tile::Tile(SDL_Texture* tex, int x, int y, int w, int h, int id)
{
	this->texture = tex;
	this->id = id;
	src->x = x;
	src->y = y;
	src->w = w;
	src->h = h;
}




