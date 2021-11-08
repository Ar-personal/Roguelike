#pragma once
#include <SDL_rect.h>

class Tile {
public:

	SDL_Rect tileRect;
	int tileID;
	const char* path;
	
	Tile(int x, int y, int w, int h, int id) {
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;


		switch (tileID) {
		case 0:
			path = "assets/grass.png";
			break;
		case 1:
			path = "assets/grass2.png";
			break;
		case 2:
			path = "assets/stone.png";
			break;
		default:
			break;
		
		}
	}


};
