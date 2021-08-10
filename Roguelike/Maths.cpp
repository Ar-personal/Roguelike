#include "Maths.h"

SDL_Point Maths::isoTo2D(int x, int y) {
	SDL_Point point;
	point.x = (2 * y + x) / 2;
	point.y = (2 * y - x) / 2;

	return point;
}

SDL_Point Maths::twoDToIso(int x, int y){
	SDL_Point point;
	point.x = x - y;
	point.y = (x + y) / 2;

	return point;
}