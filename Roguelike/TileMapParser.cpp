#include "TileMapParser.h"
#include <iostream>
#include <filesystem>

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
	//std::vector<std::shared_ptr<Tile>> tileObjects;

	std::map<int, std::string> tileData;


	//layer tile imports
	int layer = 0;
	for (xml_node<>* node = rootNode->first_node("layer"); node; node = node->next_sibling()) {

		std::string name = node->first_attribute("name")->value();
		//tile layer
		if (name.find("Tile")!= std::string::npos) {
			xml_node<>* dataNode = node->first_node("data");

			if (dataNode != NULL) {
				std::string mapIndices = dataNode->value();
				std::stringstream fileStream(mapIndices);
				std::string line;
				std::cout << "value " << mapIndices << "\n";
				tileData.emplace(layer, mapIndices);
				layer++;
			}
		}

		//Tile not found in name so object layer
		else {
			xml_node<>* dataNode = node->first_node("data");

			if (dataNode != NULL) {
				std::string mapIndices = dataNode->value();
				std::stringstream fileStream(mapIndices);
				std::string line;
				std::cout << "value " << mapIndices << "\n";
				//layer -1 because of treating tile and object layer as the same
				tileObjectData.emplace(layer - 1, mapIndices);
			}
		}
	}

	//int collLayer = 0;
	//for (xml_node<>* node = rootNode->first_node("objectgroup"); node; node = node->next_sibling()) {
	//		xml_node<>* dataNode = node->first_node("object");
	//		std::vector<SDL_Rect> rects;

	//		//const char* name = rootNode->first_attribute("name")->value();

	//		//loop through object layers for collider objects
	//		while (dataNode) {
	//			SDL_Rect collider;
	//			collider.x = std::atoi(dataNode->first_attribute("x")->value());
	//			collider.y = std::atoi(dataNode->first_attribute("y")->value());
	//			collider.w = std::atoi(dataNode->first_attribute("width")->value());
	//			collider.h = std::atoi(dataNode->first_attribute("height")->value());

	//			rects.emplace_back(collider);
	//			dataNode = dataNode->next_sibling();
	//		}

	//		levelColliders.emplace(collLayer, rects);
	//		rects.clear();

	//		collLayer++;

	//}

	//int objLayer = 0;
	//for (xml_node<>* node = rootNode->first_node("object group"); node; node = node->next_sibling())
	//{



	//}

	return tileData;
}

std::map<int, std::string> TileMapParser::GetLevelColliders()
{
	return tileObjectData;
}

