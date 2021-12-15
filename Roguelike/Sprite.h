#include "TextureManager.h"
#include <string>

struct Sprite{

	SDL_Texture* sheet;
	bool animated = false;
	int frames;
	int speed;

};