#pragma once

#include "Game.h"
#include <map>
#include <string>
#include <vector>
#include "Tile.h"

class Level {
public:
	Level();
	~Level();

	std::map<int, std::vector<Tile>> CreateTileMap(std::map<int, std::string> tileData, int mapWidth, int mapHeight, int tileSize);
	void DrawMap(std::map<int, std::vector<Tile>> tileMap, int mapSizeX, int mapSizeY);
	void StringToVector(std::string& str, char delim, std::vector<std::string>& out);
private:

	SDL_Texture* dirt, *grass, *water;

};
