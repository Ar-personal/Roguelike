#include "Level.h"
#include "TextureManager.h"
#include "Maths.h"
#include "SDL.h"
#include "Tile.h"
#include <list>
#include <string>
#include <vector>
#include <iostream>

Level::Level() {

}


std::map<int, std::vector<Tile>> Level::CreateTileMap(std::map<int, std::string> tileData, int mapWidth, int mapHeight, int tileSize) {
	const char* path = "assets/outside.png";
	//create a reference to each new tile created to prevent re-creating the same tile however on new level creations this is reset,
	//so maybe move tile references elsewhere

	std::map<int, Tile> tiles;
	std::map<int, std::vector<Tile>> tileMap;
	std::vector<std::string> tileVector;
	std::vector<Tile> tileObjectVector;

	SDL_Texture* def = TextureManager::LoadTexture("assets/default.png");

	//temp code to calculate test spitesheet coords
	int l;
	int spriteSheetWidth = 10;

	for (int layer = 0; layer < tileData.size(); layer++) {
		l = layer;
		StringToVector(tileData[layer], ',', tileVector);
		std::cout << layer << std::endl;
		//loop through every tile ID in a layer
		for (int j = 0; j < tileVector.size(); j++) {
			
			std::string s = tileVector[j];
			int id = std::stoi(s);

			int row = 0;
			int column = 0;
			int colIdx = 0;
			for (int s = 0; s < id; s++) {
				column += 64;
				if (colIdx >= spriteSheetWidth) {
					colIdx = 0;
					column = 0;
					row += 64;
				}
				colIdx++;
			}

			//null texture
			if (id == 0) {
				Tile t = Tile(def, column, row, tileSize, tileSize, id);
				tileObjectVector.emplace_back(t);
				continue;
			}

			//check if we have loaded this tile type before
			if (tiles.find(id) != tiles.end()){ 
				//tile loaded before
				Tile t = tiles[id];
				tileObjectVector.emplace_back(t);
			}else {
				//new tile
				//create new tile with id texture and position
				Tile t = Tile(path, column, row, tileSize, tileSize, id);
				tiles.emplace(id, t);
				tileObjectVector.emplace_back(t);
			}
		}
		tileMap.emplace(l, tileObjectVector);
		tileObjectVector.clear();
		tileVector.clear();
	}

	return tileMap;
}


//should destroy all tile objects
Level::~Level() {
	SDL_DestroyTexture(dirt);
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(water);
}


void Level::DrawMap(std::map<int, std::vector<Tile>> tileMap, int mapSizeX, int mapSizeY) {
	SDL_Rect src, dst;
	//change hard coded variables
	dst.x = 0;
	dst.y = 0;
	dst.w = 64;
	dst.h = 64;

	src.x = 0;
	src.y = 0;
	src.w = 64;
	src.h = 64;

	int idx = 0;

	for (int l = 0; l < tileMap.size(); l++) {
		for (int row = 0; row < mapSizeX; row++) {
			for (int column = 0; column < mapSizeY; column++) {
				Tile tile = tileMap[l][idx];
				dst.x = column * 32;
				dst.y = row * 32;

				SDL_Point destination{ Maths::twoDToIso(dst.x, dst.y) };
				dst.x = destination.x;
				dst.y = destination.y;

				TextureManager::Draw(tile.texture, src, dst);
				idx++;
			}
		}
		idx = 0;
	}
}

void Level::StringToVector(std::string& str, char delim, std::vector<std::string>& out) {
	size_t start;
	size_t end = 0;

	str.erase(
		std::remove(str.begin(), str.end(), '\r'), str.end());
	str.erase(
		std::remove(str.begin(), str.end(), '\n'), str.end());


	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}