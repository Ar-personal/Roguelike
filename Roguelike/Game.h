#pragma once
#include "SDL.h"
#undef main



class Game {

public:
	Game();
	~Game();


	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	static SDL_Renderer* renderer;
	static SDL_Event event;

	bool running() { return isRunning; }

private:
	bool isRunning;
	SDL_Window* window;

};

