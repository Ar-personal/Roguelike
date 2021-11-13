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

void CameraSystem::Update(){

	for (Entity entity : mEntities) {
		auto& camera = gCoordinator.GetComponent<Camera>(entity);
		auto& player = gCoordinator.GetComponent<Player>(entity);
		auto& transform = gCoordinator.GetComponent<Transform>(entity);

		//doesnt make much sense because every camera will follow a particular player right now

		camera.x = (player.destRect.x * transform.speed)  - 640;
		camera.y = (player.destRect.y * transform.speed) - 360;


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