#include "PhysicsSystem.h"

#include "Transform.h"
#include <iostream>
#include "Coordinator.h"

extern Coordinator gCoordinator;


void PhysicsSystem::Init()
{
}

void PhysicsSystem::Update()
{
	for (Entity entity : mEntities) {
		auto& transform = gCoordinator.GetComponent<Transform>(entity);

		transform.position.x = transform.xpos;
		transform.position.y = transform.ypos;

		//remember starting position of entity
		if (!transform.init) {
			transform.startX = transform.xpos;
			transform.startY = transform.ypos;
			transform.init = true;
		}

		//move entity towards its dstination tile
		if (transform.canMove) {
			transform.destination.x *= 64 + 32;
			transform.destination.y *= 64 + 16;

			Vector2D distance = transform.position.Subtract(transform.destination);;


			transform.xpos += transform.xpos / distance.x * transform.speed;
			transform.ypos += transform.ypos / distance.y * transform.speed;

		}


		//if (transform.canMove) {
		//	SDL_Point destination{ Maths::twoDToIso(transform.velocity.x * transform.speed, transform.velocity.y * transform.speed) };

		//	transform.xpos += destination.x;
		//	transform.ypos += destination.y;
		//}
	}
}