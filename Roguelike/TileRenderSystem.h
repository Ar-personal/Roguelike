#pragma once

#include "System.h"
#include <map>
#include "Tile.h"
#include <iostream>
#include <vector>



class TileRenderSystem : public System
{
public:
	void Init(std::map<int, std::vector<Tile>> tileMap, int mapSizeX, int mapSizeY, int tileSize, int mapOffsetX, int mapOffsetY, int scale);

	void Render();

	void DrawMap(std::map<int, std::vector<Tile>> tileMap, int cameraX, int cameraY, int mapSizeX, int mapSizeY, int mapOffsetX, int mapOffsetY, int playerMovedX, int playerMovedY);

	std::map<int, std::vector<Tile>> tileMap;
	int mapSizeX, mapSizeY, tileSize, cameraX, cameraY, mapOffsetX, mapOffsetY, scale;

	Tile getTileAtIndex(std::map<int, std::vector<Tile>> tileMap, int x, int y);

	int getTileIndex(std::map<int, std::vector<Tile>> tileMap, int x, int y);

};