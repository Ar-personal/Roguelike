#include "TextureManager.h"
#include "Game.h"
#include <iostream>


SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	std::cout << "attempting to load: " << texture << std::endl;
	SDL_Surface* tempSurface = IMG_Load(texture);
	std::cout << texture << std::endl;
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

SDL_Texture* TextureManager::LoadTextureFromSheet(const char* filename, int x, int y, int width, int height)
{
	SDL_Surface* tempSurface = IMG_Load(filename);
	SDL_Surface* croppedSurface = NULL;
	SDL_Rect* dest = new SDL_Rect;
	SDL_Rect* cropped = new SDL_Rect;

	cropped->w = width;
	cropped->h = height;
	cropped->x = x;
	cropped->y = y;

	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, croppedSurface);
	SDL_FreeSurface(croppedSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
