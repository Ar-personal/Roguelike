#include "TileMapParser.h"
#include <iostream>

TileMapParser::TileMapParser() {

}


std::map<int, std::string> TileMapParser::GetTileMap(const std::string& file, int offsetX, int offsetY)
{
	char* fileLoc = new char[file.size() + 1]; // 1
	//TODO: make multi format version of string copy
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, file.size() + 1, file.c_str());
#endif 
	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<>* rootNode = doc.first_node("map");
		// Loads tile layers from XML.

	// We need these to calculate the tiles position in world space
	//tileSizeX = std::atoi(rootNode->first_attribute("tilewidth")->value());
	//tileSizeY = std::atoi(rootNode->first_attribute("tileheight")->value());
	mapSizeX = std::atoi(rootNode->first_attribute("width")->value());
	mapSizeY = std::atoi(rootNode->first_attribute("height")->value());
	// This will contain all of our tiles as objects.
	std::vector<std::shared_ptr<Tile>> tileObjects;

	std::map<int, std::string> tileData;

	int layer = 0;
	for (xml_node<>* node = rootNode->first_node("layer");node; node = node->next_sibling())
	{

			xml_node<>* dataNode = node->first_node("data");
			std::string mapIndices = dataNode->value();
			std::stringstream fileStream(mapIndices);
			int count = 0;
			std::string line;
			std::cout << "value " << mapIndices << "\n";
			tileData.emplace(layer, mapIndices);
			layer++;
		}

	return tileData;
}
