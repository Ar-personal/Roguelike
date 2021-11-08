#include "CollisionSystem.h"
#include <iostream>
#include "Coordinator.h"
#include "Player.h"
#include "Transform.h"
#include "Collision.h"


extern Coordinator gCoordinator;
SDL_Rect bRect;


void CollisionSystem::Init()
{
}

void CollisionSystem::Update()
{
	for (Entity entityA : mEntities) {
		auto& playerA = gCoordinator.GetComponent<Player>(entityA);
		auto& transformA = gCoordinator.GetComponent<Transform>(entityA);
		auto& collisionA = gCoordinator.GetComponent<Collision>(entityA);

		collisionA.collider.x = transformA.position.x;
		collisionA.collider.y = transformA.position.y;
		collisionA.collider.w = 64;
		collisionA.collider.h = 64;

		for (Entity entityB : mEntities) {
			if (entityA == entityB) {
				std::cout << "skipping self" << std::endl;
				continue;
			}

			auto& playerB = gCoordinator.GetComponent<Player>(entityB);
			auto& transformB = gCoordinator.GetComponent<Transform>(entityA);
			auto& collisionB = gCoordinator.GetComponent<Collision>(entityB);

			collisionB.collider.x = transformB.position.x;
			collisionB.collider.y = transformB.position.y;
			collisionB.collider.w = 64;
			collisionB.collider.h = 64;


			if (AABB(playerA.destRect, playerB.destRect)) {
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