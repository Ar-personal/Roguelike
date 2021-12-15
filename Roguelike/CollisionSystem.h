#pragma once
#include "System.h"
#include <SDL_rect.h>
#include <map>
#include "Player.h"
#include <vector>
#include "Tile.h"

class CollisionSystem : public System
{
public:
	void Init(std::map<int, std::vector<Tile>> tileMap, std::map<int, std::string> tileObjectData);

	void Update();

	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);

	bool checkLevelCollissions(Player e);
	int getTileIndex(std::map<int, std::vector<Tile>> tileMap, int x, int y);
private:
	std::map<int, std::vector<Tile>> tileMap;
	std::map<int, std::string> tileObjectData;
};
