#include "Level.h"
#include "TextureManager.h"
#include "Maths.h"
#include "SDL.h"
#include "Tile.h"
#include <list>
#include <string>
#include <vector>
#include <iostream>




Level::Level(SDL_Rect camera) {
	this->camera = camera;
}


std::map<int, std::vector<Tile>> Level::CreateTileMap(std::map<int, std::string> tileData, int mapWidth, int mapHeight, int tileSize) {
	const char* path = "assets/outside.png";
	//create a reference to each new tile created to prevent re-creating the same tile however on new level creations this is reset,
	//so maybe move tile references elsewhere

	std::map<int, Tile> tiles;
	std::map<int, std::vector<Tile>> tileMap;
	std::vector<std::string> tileStringVector;
	std::vector<Tile> tileObjectVector;

	SDL_Texture* def = TextureManager::LoadTexture("assets/default.png");

	//temp code to calculate test spitesheet coords
	int spriteSheetWidth = 10;
	SDL_Rect src = { 0, 0, 64, 64 };
	SDL_Rect dst = { 0, 0, 64, 64 };

	for (int layer = 0; layer < tileData.size(); layer++) {
		StringToVector(tileData[layer], ',', tileStringVector);
		int idx = 0;
		for (int row = 0; row < mapHeight; row++) {
			for (int column = 0; column < mapWidth; column++) {
				std::string s = tileStringVector[idx];
				int id = std::stoi(s);
				//code calculates the coordinates of the tile in the spritesheet
				int rowT = 0;
				int colT = 0;
				int colIdx = 0;
				for (int s = 0; s < id; s++) {
					colT += 64;
					if (colIdx >= spriteSheetWidth) {
						colIdx = 0;
						colT = 0;
						rowT += 64;
					}
					colIdx++;
				}
				src.x = colT;
				src.y = rowT;
				src.w = tileSize;
				src.h = tileSize;

				dst.x = (column * 32);
				dst.y = (row * 32);

				//squash y values for isometric affect
				SDL_Point destination{ Maths::twoDToIso(dst.x, dst.y) };
				dst.x = destination.x;
				dst.y = destination.y;

				//null texture
				if (id == 0) {
					Tile t = Tile(def, dst, id);
					tileObjectVector.emplace_back(t);
					continue;
				}
				//check if we have loaded this tile type before
				if (tiles.find(id) != tiles.end()) {
					//tile loaded before created a tile with same texture and adjust its destination
					Tile tile = Tile(tiles[id].texture, tiles[id].dst, tiles[id].id);
					tile.dst.x = dst.x;
					tile.dst.y = dst.y;
					tile.position.x = dst.x;
					tile.position.y = dst.y;
					tileObjectVector.emplace_back(tile);
				}else{
					//create new tile with id texture and position
					Tile t = Tile(path, src, dst, id);
					tiles.emplace(id, t);
					tileObjectVector.emplace_back(t);
				}
				idx++;
			}
		}

		std::cout << "creating tile at idx: " << idx << " layer: " << layer << std::endl;
		tileMap.emplace(layer, tileObjectVector);
		//reset the tile layer
		tileObjectVector.clear();
		tileStringVector.clear();
	}

	return tileMap;
}


//should destroy all tile objects
Level::~Level() {

}


void Level::DrawMap(std::map<int, std::vector<Tile>> tileMap, int mapSizeX, int mapSizeY) {
	SDL_Rect src = { 0, 0, 64, 64 };
	//change hard coded variables


	int idx = 0;

	for (int l = 0; l < tileMap.size(); l++) {
		for (int row = 0; row < mapSizeX; row++) {
			for (int column = 0; column < mapSizeY; column++) {
				Tile tile = tileMap[l][idx];
				TextureManager::Draw(tile.texture, src, tile.dst);
				idx++;
			}
		}
		
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