#pragma once
#include "SDL.h"
#undef main
#include "TextureManager.h"

class GameObject {
public:
	GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);

	void Update();
	void Render();
private:
	int ypos;
	int xpos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};
