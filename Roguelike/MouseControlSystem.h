#pragma once

#include "System.h"
#include <map>
#include "Tile.h"
#include <iostream>
#include <vector>

class Event;


class MouseControlSystem : public System
{
public:
	void Init();

	void Update();
	void RightClick();

	
	int mapSizeX;
	int mapSizeY;
	int x, y;


private:

	void InputListener(Event& event);
};
