#include "Map.h"
#include "TextureManager.h"
#include "Maths.h"
#include "SDL.h"

int lvl1[20][25] = {
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},
	{0000000000000000000000000},


};

Map::Map() {
	dirt = TextureManager::LoadTexture("assets/stone2.png");
	grass = TextureManager::LoadTexture("assets/grass.png");
	water = TextureManager::LoadTexture("assets/grass2.png");

	LoadMap(lvl1);


	src.x = src.y = 0;
	src.w = dest.w = 64;
	src.h = dest.h = 64;

	dest.x = dest.y = 0;
}

void Map::LoadMap(int arr[20][25]) {
	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 25; column++) {
			map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap() {
	int type = 0;
	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 25; column++) {
			type = map[row][column];
			dest.x = column * 32;
			dest.y = row * 32;

			SDL_Point destination {Maths::twoDToIso(dest.x, dest.y)};
			dest.x = destination.x;
			dest.y = destination.y;


			switch (type)
			{

			case 0:
				TextureManager::Draw(water, src, dest);
				break;

			case 1:
				TextureManager::Draw(grass, src, dest);
				break;
			case 2:
				TextureManager::Draw(dirt, src, dest);
				break;


			default:
				break;
			}
		}
	}
}