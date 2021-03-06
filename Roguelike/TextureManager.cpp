#include "TextureManager.h"
#include "Game.h"
#include <iostream>

static SDL_Texture* def;

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

SDL_Texture* TextureManager::LoadTextureFromSheet(const char* filename, SDL_Rect* src)
{
	SDL_Surface* sprite_sheet = IMG_Load(filename);

	SDL_Rect* cropped = new SDL_Rect;

	cropped = src;

	SDL_Surface* tempSurface2 = SDL_CreateRGBSurface(0, 64, 64, 32, 0xff, 0xff00, 0xff0000, 0xff000000);

	SDL_BlitSurface(sprite_sheet, cropped, tempSurface2, NULL);


	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface2);
	printf(SDL_GetError());
	SDL_FreeSurface(sprite_sheet);
	SDL_FreeSurface(tempSurface2);
	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
