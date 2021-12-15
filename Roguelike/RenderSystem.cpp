#include "RenderSystem.h"
#include "Coordinator.h"
#include <iostream>
#include "Player.h"
#include <SDL.h>
#include "Game.h"
#include "Transform.h"
#include "Sprite.h"
#include "Camera.h"

extern Coordinator gCoordinator;


void RenderSystem::Init()
{
}


void RenderSystem::Render()
{
	for (Entity entity : mEntities) {
		auto& player = gCoordinator.GetComponent<Player>(entity);
		auto& transform = gCoordinator.GetComponent<Transform>(entity);
		auto& sprite = gCoordinator.GetComponent<Sprite>(entity);
		auto& camera = gCoordinator.GetComponent<Camera>(entity);



		player.srcRect.h = 64;
		player.srcRect.w = 64;
		player.srcRect.x = 0;
		player.srcRect.y = 0;


		player.destRect.x = transform.xpos - camera.x;
		player.destRect.y = transform.ypos - camera.y;
		player.destRect.w = player.srcRect.w * 2;
		player.destRect.h = player.srcRect.h * 2;



		if (sprite.animated) {

			if (transform.velocity.x == 0 && transform.velocity.y == 0) {
				player.srcRect.x = player.srcRect.w * 4;
				player.srcRect.y = 0;
				SDL_RenderCopy(Game::renderer, sprite.sheet, &player.srcRect, &player.destRect);
				return;
			}


			if (transform.velocity.x == 0) {
				//moving down
				if (transform.velocity.y > 0) {
					player.srcRect.y = player.srcRect.h * 0;
				}

				//moving up
				if (transform.velocity.y < 0) {
					player.srcRect.y = player.srcRect.h * 4;
				}
			}

			//moving right
			if (transform.velocity.x > 0) {
				player.srcRect.y = player.srcRect.h * 2;

					//moving right down
					if (transform.velocity.y > 0) {
						player.srcRect.y = player.srcRect.h * 1;
					}
					else

					//moving right up
					if (transform.velocity.y < 0) {
						player.srcRect.y = player.srcRect.h * 3;
					}


			}

			//moving left
			if (transform.velocity.x < 0) {
				player.srcRect.y = player.srcRect.h * 6;
					//moving left up
					if (transform.velocity.y > 0) {
						player.srcRect.y = player.srcRect.h * 7;
					}
					else
						//moving left down
					if (transform.velocity.y < 0) {
						player.srcRect.y = player.srcRect.h * 5;
					}
			}

			player.srcRect.x = player.srcRect.w * static_cast<int> ((SDL_GetTicks() / sprite.speed) % sprite.frames);
		}

			SDL_RenderCopy(Game::renderer, sprite.sheet, &player.srcRect, &player.destRect);
		
	}
}