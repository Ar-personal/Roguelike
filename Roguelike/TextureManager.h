#pragma once
#include "SDL.h"
#include "SDL_image.h"

class TextureManager {
	public:
		static SDL_Rect cropped;
		static SDL_Texture* LoadTexture(const char* filename);
		static SDL_Texture* LoadTextureFromSheet(const char* filename, int x, int y, int width, int height);
		static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
		static SDL_Texture* GetAreaTexture(SDL_Rect rect, SDL_Renderer* renderer, SDL_Texture* source);
};