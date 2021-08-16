#include "RenderSystem.h"
#include "Coordinator.h"
#include <iostream>
#include "Player.h"
#include <SDL.h>
#include "Game.h"
#include "Transform.h"
#include "Sprite.h"

extern Coordinator gCoordinator;


void RenderSystem::Init()
{
}


void RenderSystem::Render()
{
	for (Entity entity : mEntities) {
		std::cout << "rendering" << std::endl;
		auto& player = gCoordinator.GetComponent<Player>(entity);
		auto& transform = gCoordinator.GetComponent<Transform>(entity);
		auto& sprite = gCoordinator.GetComponent<Sprite>(entity);



		transform.xpos += (transform.velocity.x * transform.speed);
		transform.ypos += (transform.velocity.y * transform.speed);

		player.srcRect.h = 64;
		player.srcRect.w = 64;
		player.srcRect.x = 0;
		player.srcRect.y = 0;

		player.destRect.x = transform.xpos;
		player.destRect.y = transform.ypos;
		player.destRect.w = player.srcRect.w * 2;
		player.destRect.h = player.srcRect.h * 2;


		if (transform.velocity.x > 0) {
			player.srcRect.h = 64;
			player.srcRect.w = 64;
			player.srcRect.x = sprite.rightx;
			player.srcRect.y = sprite.righty;

			if (transform.velocity.y > 0) {
				player.srcRect.h = 64;
				player.srcRect.w = 64;
				player.srcRect.x = sprite.downRightx;
				player.srcRect.y = sprite.downRighty;
			}else

			if (transform.velocity.y < 0) {
				player.srcRect.h = 64;
				player.srcRect.w = 64;
				player.srcRect.x = sprite.upRightx;
				player.srcRect.y = sprite.upRighty;
			}

		}

		if (transform.velocity.x < 0) {
			player.srcRect.h = 64;
			player.srcRect.w = 64;
			player.srcRect.x = sprite.leftx;
			player.srcRect.y = sprite.lefty;


			if (transform.velocity.y > 0) {
				player.srcRect.h = 64;
				player.srcRect.w = 64;
				player.srcRect.x = sprite.downLeftx;
				player.srcRect.y = sprite.downLefty;
			}else

			if (transform.velocity.y < 0) {
				player.srcRect.h = 64;
				player.srcRect.w = 64;
				player.srcRect.x = sprite.upLeftx;
				player.srcRect.y = sprite.upLefty;
			}
		}



			SDL_RenderCopy(Game::renderer, sprite.sheet, &player.srcRect, &player.destRect);
		
	}
}