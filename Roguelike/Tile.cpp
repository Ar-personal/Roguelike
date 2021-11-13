#include "Tile.h"

Tile::Tile() {

}

Tile::Tile(const char* path, SDL_Rect src, SDL_Rect dst, int id) {
	this->src = src;
	this->dst = dst;

	position.x = dst.x;
	position.y = dst.y;

	texture = TextureManager::LoadTextureFromSheet(path, &src);
	this->id = id;
}

Tile::Tile(SDL_Texture* tex, SDL_Rect dst, int id)
{
	position.x = dst.x;
	position.y = dst.y;
	this->texture = tex;
	this->id = id;
	this->dst = dst;
}




