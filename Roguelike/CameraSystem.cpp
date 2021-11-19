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
	
		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);
		auto Width = DM.w;
		auto Height = DM.h;

		camera.x = (transform.xpos) - (640 - 32);
		camera.y = (transform.ypos) - (360 - 32);

		//set player specific camera position
		player.camera.x = camera.x;
		player.camera.y = camera.y;
		player.camera.w = camera.w;
		player.camera.h = camera.h;

		//handle map boundary scrolling

		//if (camera.x < 0) {
		//	camera.x = 0;
		//}

		//if (camera.y < 0) {
		//	camera.y = 0;
		//}

		//if (camera.x > camera.w) {
		//	camera.x = camera.w;
		//}

		//if (camera.y > camera.h) {
		//	camera.y = camera.h;
		//}
	}
}