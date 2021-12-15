#include "PlayerControlSystem.h"
#include "Coordinator.h"
#include "Game.h"
#include "Player.h"
#include "Transform.h"

extern Coordinator gCoordinator;

void PlayerControlSystem::Init(std::map<int, std::vector<Tile>> tileMap)
{
	this->tileMap = tileMap;
}

void PlayerControlSystem::Update()
{
	for (Entity entity : mEntities) {

		auto& player = gCoordinator.GetComponent<Player>(entity);
		auto& transform = gCoordinator.GetComponent<Transform>(entity);


		if (player.mapPosition.x != player.destinationTile.x || player.mapPosition.y != player.destinationTile.y) {
			//the player is not at the tired it desires to move to
			//player map pos starts at -9 for some reason
			if (player.mapPositionScaled.x < 0) {
				player.mapPositionScaled.x = 0;
			}

			if (player.mapPositionScaled.y < 0) {
				player.mapPositionScaled.y = 0;
			}

			int diffX = player.destinationTile.x - player.mapPositionScaled.x;
			int diffY = player.destinationTile.y - player.mapPositionScaled.y;
			std::cout << "tile distances: " << diffX << " " << diffY;




		//try to move along the x axis
			if (diffX > 0) {
				int x = getTileIndex(tileMap, player.mapPositionScaled.x, player.mapPositionScaled.y);
				//within map bounds
				if(x + 1 < 25)
					//tile on the players level is not walkable
					if (tileMap[player.level][x + 1].collider) {
						transform.canMove = false;
					}
						//walkable tile
					else {
						transform.canMove = true;
						transform.destination = {(float) player.mapPositionScaled.x + 1, (float) player.mapPositionScaled.y };
					
				}
			}
		}


			switch (Game::event.type) {
			case SDL_KEYDOWN:
				switch (Game::event.key.keysym.sym) {
				case SDLK_w:
					std::cout << "w" << std::endl;
					transform.velocity.y = -1;
					break;
				case SDLK_a:
					transform.velocity.x = -1;
					std::cout << "a" << std::endl;
					break;
				case SDLK_s:
					transform.velocity.y = 1;
					std::cout << "s" << std::endl;
					break;
				case SDLK_d:
					transform.velocity.x = 1;
					std::cout << "d" << std::endl;
					break;
				default:
					break;
				}
				break;

			case SDL_KEYUP:
				transform.velocity.x = 0;
				transform.velocity.y = 0;
				switch (Game::event.key.keysym.sym) {
				case SDLK_w:
					if (transform.velocity.x < 0) {
						transform.velocity.x = 0;
					}
					break;
				case SDLK_a:
					if (transform.velocity.x > 0) {
						transform.velocity.x = 0;
					}
					break;
				case SDLK_s:
					if (transform.velocity.y < 0) {
						transform.velocity.y = 0;
					}
					break;
				case SDLK_d:
					if (transform.velocity.y > 0) {
						transform.velocity.y = 0;
					}
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
}

int PlayerControlSystem::getTileIndex(std::map<int, std::vector<Tile>> tileMap, int x, int y) {
	return (y * 25 + x);
}