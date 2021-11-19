#include "MouseControlSystem.h"
#include "Coordinator.h"
#include "Player.h"
#include "Game.h"
#include "Mouse.h"
#include "Maths.h"

extern Coordinator gCoordinator;


void MouseControlSystem::Init(){
}

void MouseControlSystem::Update(){

for (Entity entity : mEntities) {
	auto& player = gCoordinator.GetComponent<Player>(entity);
	auto& mouse = gCoordinator.GetComponent<Mouse>(entity);


	switch (Game::event.type) {
		case SDL_MOUSEMOTION:
			int x, y;
			SDL_GetMouseState(&x, &y);

			mouse.position.x = x;
			mouse.position.y = y;
			std::cout << "Mouse x & y : " << x << "  " << y << " Mouse right clicked: " << mouse.rightClicked << std::endl;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (Game::event.button.button) {
			case SDL_BUTTON_LEFT:
				std::cout << "left down" << std::endl;
				mouse.leftClicked = true;
				break;


			case SDL_BUTTON_RIGHT:
				std::cout << "right down" << std::endl;
				mouse.rightClicked = true;
				break;
			}

			break;

		case SDL_MOUSEBUTTONUP:
			switch (Game::event.button.button) {
			case SDL_BUTTON_LEFT:
				std::cout << "left up" << std::endl;
				mouse.leftClicked = false;
				break;


			case SDL_BUTTON_RIGHT:
				std::cout << "right up" << std::endl;
				mouse.rightClicked = false;
				break;
			}
			break;

		default:
			break;
		}
	}
}





