#pragma once

#include "System.h"
#include <map>
#include "Tile.h"
#include <vector>


class Event;


class PlayerControlSystem : public System
{
public:
	void Init(std::map<int, std::vector<Tile>> tileMap);

	void Update();

	int getTileIndex(std::map<int, std::vector<Tile>> tileMap, int x, int y);

private:
	std::bitset<8> mButtons;
	std::map<int, std::vector<Tile>> tileMap;
	void InputListener(Event& event);
};