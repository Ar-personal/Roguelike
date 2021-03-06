#include "Level.h"
#include "TextureManager.h"
#include "Maths.h"
#include "SDL.h"
#include "Tile.h"
#include <list>
#include <string>
#include <vector>
#include <iostream>

extern Coordinator gCoordinator;

Level::Level() {

}


std::map<int, std::vector<Tile>> Level::CreateTileMap(std::map<int, std::string> tileData, std::map<int, std::string> tileObjectData, int mapWidth, int mapHeight, int tileSize, int scale) {
	const char* path = "assets/outside.png";
	//create a reference to each new tile created to prevent re-creating the same tile however on new level creations this is reset,
	//so maybe move tile references elsewhere

	std::map<int, Tile> tiles;
	std::map<int, std::vector<Tile>> tileMap;
	std::vector<std::string> tileStringVector;
	std::vector<std::string> tileObjectStringVector;
	std::vector<Tile> tileObjectVector;

	SDL_Texture* def = TextureManager::LoadTexture("assets/void.png");

	//temp code to calculate test spitesheet coords
	int spriteSheetWidth = 10;
	SDL_Rect spriteSheetCoords = { 0, 0, 64, 64 };
	SDL_Rect dst = { 0, 0, 64, 64 };

	for (int layer = 0; layer < tileData.size(); layer++) {
		StringToVector(tileData[layer], ',', tileStringVector);
		StringToVector(tileObjectData[layer], ',', tileObjectStringVector);
		int idx = 0;
		for (int row = 0; row < mapHeight; row++) {
			for (int column = 0; column < mapWidth; column++) {
				std::string s = tileStringVector[idx];
				int id = std::stoi(s);
				//code calculates the coordinates of the tile in the spritesheet
				int rowT = 0;
				int colT = -64;
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

				spriteSheetCoords.x = colT;
				spriteSheetCoords.y = rowT;
				spriteSheetCoords.w = tileSize;
				spriteSheetCoords.h = tileSize;

				//scale the map
				dst.x = (column * 32) * scale;
				dst.y = (row * 32) * scale;

				//squash y values for isometric affect
				SDL_Point destination{ Maths::twoDToIso(dst.x, dst.y) };
				dst.x = destination.x;
				dst.y = destination.y;

				Tile t;
				bool collider = false;

				//if tile at same layer and position as object is non-zero for now its a colldier
				std::string tileID = tileObjectStringVector[idx];
				int objId = std::stoi(tileID);
				if (objId != 0) {
					collider = true;
				}
				else {
					collider = false;
				}

				//null texture
				if (id == -1) {
					t = Tile(def, dst, id);
					t.empty = true;
					tileObjectVector.emplace_back(t);
					continue;
				}
				//check if we have loaded this tile type before
				if (tiles.find(id) != tiles.end()) {
					//tile loaded before created a tile with same texture and adjust its destination
					t = Tile(tiles[id].texture, tiles[id].dst, tiles[id].id);
					t.dst.x = dst.x;
					t.dst.y = dst.y;
					t.position.x = dst.x;
					t.position.y = dst.y;
					t.collider = collider;
					tileObjectVector.emplace_back(t);
				}
				else {
					//create new tile with id texture and position
					t = Tile(path, spriteSheetCoords, dst, id);
					t.collider = collider;
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