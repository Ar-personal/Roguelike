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

		if (!transform.init) {
			transform.startX = transform.xpos;
			transform.startY = transform.ypos;
			transform.init = true;
		}

		if (transform.canMove) {
			transform.xpos += (transform.velocity.x * transform.speed);
			transform.ypos += (transform.velocity.y * transform.speed);
		}


		//if (transform.canMove) {
		//	SDL_Point destination{ Maths::twoDToIso(transform.velocity.x * transform.speed, transform.velocity.y * transform.speed) };

		//	transform.xpos += destination.x;
		//	transform.ypos += destination.y;
		//}
	}
}