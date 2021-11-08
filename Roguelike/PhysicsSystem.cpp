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

		if (transform.canMove) {
			transform.xpos += (transform.velocity.x * transform.speed);
			transform.ypos += (transform.velocity.y * transform.speed);
		}
	}
}