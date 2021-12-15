#include "CollisionSystem.h"
#include <iostream>
#include "Coordinator.h"
#include "Transform.h"
#include "Collision.h"
#include "Tile.h"
#include "Maths.h"


extern Coordinator gCoordinator;
SDL_Rect bRect;
int mapSizeX = 25;

void CollisionSystem::Init(std::map<int, std::vector<Tile>> tileMap, std::map<int, std::string> tileObjectData)
{
	this->tileMap = tileMap;
	this->tileObjectData = tileObjectData;
}

void CollisionSystem::Update()
{
	for (Entity entity : mEntities) {
		Player player = gCoordinator.GetComponent<Player>(entity);
		int level = player.level;
		auto& transform = gCoordinator.GetComponent<Transform>(entity);
		auto& collisionA= gCoordinator.GetComponent<Collision>(entity);
		

		if (checkLevelCollissions(player)) {
			SDL_Point reset{Maths::isoTo2D(transform.previousPos.x, transform.previousPos.y)};

			//transform.xpos = reset.x;
			//transform.xpos = reset.y;
		}

		collisionA.collider.x = transform.xpos;
		collisionA.collider.y = transform.ypos;
		collisionA.collider.w = 64;
		collisionA.collider.h = 64;

		for (Entity entityB : mEntities) {
			if (entity == entityB) {
				continue;
			}

			auto& playerB = gCoordinator.GetComponent<Player>(entityB);
			auto& transformB = gCoordinator.GetComponent<Transform>(entity);
			auto& collisionB = gCoordinator.GetComponent<Collision>(entityB);

			collisionB.collider.x = transformB.xpos;
			collisionB.collider.y = transformB.ypos;
			collisionB.collider.w = 64;
			collisionB.collider.h = 64;


			if (AABB(player.destRect, playerB.destRect)) {
				std::cout << "collide" << std::endl;
			}
		}
	}
}


bool CollisionSystem::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		){
			return true;
		}
	return false;
}


//check the next position of the player, if it is the same tile index and layer as the collision layer
//then we send the player back to previous position
bool CollisionSystem::checkLevelCollissions(Player e)
{	
	for(int level = 0; level < tileObjectData.size(); level++) {
		//entity is on this level and can collide with objects
		std::vector<SDL_Rect> colliders;
		//if (e.level = level) {
			int idX = e.mapPositionScaled.x;
			int idY = e.mapPositionScaled.y;

			int t = getTileIndex(tileMap, idX, idY);

			if (t >= 0 && t < mapSizeX * mapSizeX) {
				if (tileMap[level][t].collider) {
					return true;
				}

			}



		//}
		//}
	}
	return false;
}

int CollisionSystem::getTileIndex(std::map<int, std::vector<Tile>> tileMap, int x, int y) {
	return (y * mapSizeX + x);
}
