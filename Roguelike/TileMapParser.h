#ifndef TileMapParser_h
#define TileMapParser_h
#include <unordered_map>
#include <sstream>
#include "rapidxml.h"
#include "rapidxml_utils.h"
#include "Tile.h"
#include <string>
#include <map>
using namespace rapidxml;


class TileMapParser
{
public:
	int textureId; // The id of the tile sets texture. 
	int mapSizeX;
	int mapSizeY;
	int columns; // How many columns in the tile sheet.
	int rows; // How many rows in the tile sheet.
	int tileSizeX;
	int tileSizeY;

		TileMapParser();
		std::map<int, std::string> GetTileMap(const std::string& file, int offsetX, int offsetY);
private:
	std::map<int, char*> tileData;

};


#endif /* TileMapParser_hpp */


