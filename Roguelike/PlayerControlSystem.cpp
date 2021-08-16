#include "PlayerControlSystem.h"
#include "Coordinator.h"
#include "Game.h"
#include "Player.h"
#include "Transform.h"

extern Coordinator gCoordinator;

void PlayerControlSystem::Init()
{
}

void PlayerControlSystem::Update()
{
	for (Entity entity : mEntities) {

		auto& player = gCoordinator.GetComponent<Player>(entity);
		auto& transform = gCoordinator.GetComponent<Transform>(entity);

			switch (Game::event.type) {
			case SDL_KEYDOWN:
				switch (Game::event.key.keysym.sym) {
				case SDLK_w:
					std::cout << "w" << std::endl;
					transform.velocity.y = -1;
					break;
				case SDLK_a:
					transform.velocity.x = -1;
					break;
				case SDLK_s:
					transform.velocity.y = 1;
					break;
				case SDLK_d:
					transform.velocity.x = 1;
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