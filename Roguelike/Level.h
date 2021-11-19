#pragma once

#include "Game.h"
#include <map>
#include <string>
#include <vector>
#include "Tile.h"
#include "Camera.h"
#include "Types.h"
#include "Coordinator.h"
#include "CameraSystem.h"
#include "Transform.h"
#include "Camera.h"
#include "Player.h"

class Level {
public:
	Level();
	~Level();

	static std::map<int, std::vector<Tile>> CreateTileMap(std::map<int, std::string> tileData, int mapWidth, int mapHeight, int tileSize, int scale);
	void DrawMap(std::map<int, std::vector<Tile>> tileMap, int mapSizeX, int mapSizeY);
	static void StringToVector(std::string& str, char delim, std::vector<std::string>& out);
private:

};
