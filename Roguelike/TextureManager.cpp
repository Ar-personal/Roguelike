#include "TextureManager.h"
#include "Game.h"
#include <iostream>

static SDL_Texture* def;

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	std::cout << "attempting to load: " << texture << std::endl;
	SDL_Surface* tempSurface = IMG_Load(texture);
	std::cout << texture << std::endl;
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

SDL_Texture* TextureManager::LoadTextureFromSheet(const char* filename, int x, int y, int w, int h)
{
	SDL_Surface* sprite_sheet = IMG_Load(filename);

	SDL_Rect* cropped = new SDL_Rect;

	cropped->w = w;
	cropped->h = h;
	cropped->x = x;
	cropped->y = y;

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
