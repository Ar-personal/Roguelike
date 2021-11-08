#pragma once
#include <SDL_rect.h>


class Camera {
public:
	SDL_Rect camera;
	int x;
	int y;
	int w;
	int h;
	
	Camera(int x, int y, int w, int h) {
		camera.x = x;
		camera.y = y;
		camera.w = w;
		camera.h = h;
	}

};
