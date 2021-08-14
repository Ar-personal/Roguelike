#include "RenderSystem.h"
#include "Coordinator.h"
#include <iostream>
#include "Player.h"
#include <SDL.h>
#include "Game.h"
#include "Transform.h"

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

/*		player.objTexture = TextureManager::LoadTexture(player.texturesheet)*/;


		player.srcRect.h = 32;
		player.srcRect.w = 32;
		player.srcRect.x = 0;
		player.srcRect.y = 0;

		player.destRect.x = transform.xpos;
		player.destRect.y = transform.ypos;
		player.destRect.w = player.srcRect.w * 2;
		player.destRect.h = player.srcRect.h * 2;

		SDL_RenderCopy(Game::renderer, player.objTexture, &player.srcRect, &player.destRect);
	}
}