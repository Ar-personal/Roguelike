#pragma once

#include "Game.h"
#include <map>
#include <string>
#include <vector>
#include "Tile.h"
#include "Player.h"
#include "Types.h"

class Level {
public:
	Level(SDL_Rect camera);
	~Level();

	SDL_Rect camera;
	SDL_Rect* dst;

	std::map<int, std::vector<Tile>> CreateTileMap(std::map<int, std::string> tileData, int mapWidth, int mapHeight, int tileSize);
	void DrawMap(std::map<int, std::vector<Tile>> tileMap, int mapSizeX, int mapSizeY);
	void StringToVector(std::string& str, char delim, std::vector<std::string>& out);
private:

};
