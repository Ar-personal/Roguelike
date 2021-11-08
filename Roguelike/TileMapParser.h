#pragma once

class TileMapParser
{
public:
	TileMapParser(ResourceAllocator<sf::Texture>& textureAllocator);
	std::vector<std::shared_ptr<Object>>
		Parse(const std::string& file, sf::Vector2i offset);
private:
	std::shared_ptr<TileSheetData> BuildTileSheetData(xml_node<>* rootNode);
	std::shared_ptr<MapTiles> BuildMapTiles(xml_node<>* rootNode);
	std::pair<std::string, std::shared_ptr<Layer>>
		BuildLayer(
			xml_node<>* layerNode, std::shared_ptr<TileSheetData> tileSheetData
		);
	ResourceAllocator<sf::Texture>& textureAllocator;
};
