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