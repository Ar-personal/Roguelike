#include "TileRenderSystem.h"
#include "Coordinator.h"
#include "Game.h"
#include <SDL.h>
#include "Maths.h"
#include "Mouse.h"
#include "Player.h"
#include <iostream>
#include "Transform.h"

extern Coordinator gCoordinator;
int playerMovedX;
int playerMovedY;

void TileRenderSystem::Init(std::map<int, std::vector<Tile>> tileMap, int width, int height, int tileSize, int mapOffsetX, int mapOffsetY, int scale)
{
	this->tileMap = tileMap;
	this->mapSizeX = width;
	this->mapSizeY = height;
	this->tileSize = tileSize;
	this->mapOffsetX = mapOffsetX;
	this->mapOffsetY = mapOffsetY;
	this->scale = scale;
}


void TileRenderSystem::Render(){

	for (Entity entity : mEntities) {
		auto& player = gCoordinator.GetComponent<Player>(entity);
		auto& mouse = gCoordinator.GetComponent<Mouse>(entity);
		auto& transform = gCoordinator.GetComponent<Transform>(entity);

		if (entity != 0) {
			continue;
		}

		playerMovedX = transform.startX - transform.xpos;
		playerMovedY = transform.startY - transform.ypos;

		cameraX = player.camera.x;
		cameraY = player.camera.y;

		//figure out player coords

		SDL_Point playerDestination{ Maths::isoTo2D(player.destRect.x + cameraX, player.destRect.y + cameraY) };
		player.mapPosition.x = playerDestination.x;
		player.mapPosition.y = playerDestination.y;

		int pNormX = playerDestination.x / (32 * scale);
		int pNormY = playerDestination.y / (32 * scale);

		player.mapPositionScaled.x = pNormX;
		player.mapPositionScaled.y = pNormY;

		player.mapIndex = getTileIndex(tileMap, pNormX, pNormY);


		std::cout << "player map x: " << player.mapPosition.x <<  " player map y: " << player.mapPosition.y << std::endl;
		std::cout << "player map index " << player.mapIndex << std::endl;
		if (mouse.rightClicked) {
			//camera coords chould be topleft corner of the map at camera position
			cameraX = player.camera.x;
			cameraY = player.camera.y;

			//world position
			mouse.position.x - cameraX;
			mouse.position.y - cameraY;

			int tileOffsetX = mapOffsetX / (32 * scale);
			int tileOffsetY = mapOffsetY / (32 * scale);


			SDL_Point destination{ Maths::isoTo2D(mouse.position.x - (32 * scale) + cameraX, mouse.position.y - (32 * scale) + cameraY)};

			int screenX = (destination.x / (32 * scale));
			int screenY = (destination.y / (32 * scale));
			player.destinationTile.x = screenX;
			player.destinationTile.y = screenY;

			int t = getTileIndex(tileMap, screenX, screenY);

			if (t >= 0 && t < mapSizeX * mapSizeY) {
				SDL_Texture* def = TextureManager::LoadTexture("assets/grass.png");
				tileMap[0][t].texture = def;
			}
		}
	}

	//HANDLE NULL VALUES
	DrawMap(tileMap, cameraX, cameraY, mapSizeX, mapSizeY, mapOffsetX, mapOffsetY, playerMovedX, playerMovedY);
	
}

void TileRenderSystem::DrawMap(std::map<int, std::vector<Tile>> tileMap, int cameraX, int cameraY, int mapSizeX, int mapSizeY, int mapOffsetX, int mapOffsetY, int playerMovedX, int playerMovedY) {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 64;
	src.h = 64;

	int idx = 0;

	for (int l = 0; l < tileMap.size(); l++) {
		std::vector<Tile> tileObjectVector = tileMap[l];
		for (int row = 0; row < mapSizeX; row++) {
			for (int column = 0; column < mapSizeY; column++) {
				Tile tile = tileObjectVector[idx];
				if (tile.empty) {
					continue;
				}
				if (tile.collider) {
					tile.texture = TextureManager::LoadTexture("assets/grass.png");
				}

				tile.dst.x = tile.position.x - cameraX;
				tile.dst.y = tile.position.y - cameraY;
				tile.dst.w *= scale;
				tile.dst.h *= scale;

				TextureManager::Draw(tile.texture, src, tile.dst);
				idx++;
			}
		}
		idx = 0;
	}
}



int TileRenderSystem::getTileIndex(std::map<int, std::vector<Tile>> tileMap, int x, int y) {
	return (y * mapSizeX + x);
}