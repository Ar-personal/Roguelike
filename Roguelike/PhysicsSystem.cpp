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
	for (Entity entity : mEntities){
		std::cout << "here" << std::endl;
		auto& transform = gCoordinator.GetComponent<Transform>(entity);




	}
}