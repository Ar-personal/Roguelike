#pragma once
#include <iostream>
#include "TextureManager.h"
struct Player
{
	//SDL_Texture* objTexture = TextureManager::LoadTexture("assets/player.png");
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Rect camera;
	int level;
	SDL_Point mapPosition, mapPositionScaled;
	SDL_Point previousPos;
	SDL_Point destinationTile;
	int mapIndex;
};