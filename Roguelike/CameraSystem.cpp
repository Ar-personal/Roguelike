#include <iostream>
#include "Coordinator.h"
#include "CameraSystem.h"
#include "Transform.h"
#include "Camera.h"
#include "Player.h"

extern Coordinator gCoordinator;


void CameraSystem::Init()
{
}

void CameraSystem::Update()
{
	for (Entity entity : mEntities) {
		auto& transform = gCoordinator.GetComponent<Transform>(entity);
		auto& camera = gCoordinator.GetComponent<Camera>(entity);
		auto& player = gCoordinator.GetComponent<Player>(entity);

		camera.x = player.destRect.x - 640;
		camera.y = player.destRect.y - 320;


		if (camera.x < 0) {
			camera.x = 0;
		}

		if (camera.y < 0) {
			camera.y = 0;
		}

		if (camera.x > camera.w) {
			camera.x = camera.w;
		}

		if (camera.y > camera.h) {
			camera.y = camera.h;
		}
	}
}