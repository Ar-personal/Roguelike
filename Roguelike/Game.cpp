#include "Game.h"
#include <iostream>
#include "Map.h"
#include "Transform.h"
#include "PhysicsSystem.h"
#include "Player.h"
#include "Coordinator.h"
#include "RenderSystem.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;
Coordinator gCoordinator;
std::shared_ptr<PhysicsSystem> physicsSys;
std::shared_ptr<RenderSystem> renderSys;

Game::Game(){}
Game::~Game(){}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window Created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created" << std::endl;
		}

		isRunning = true;
	}else{
		isRunning = false;
	}

	gCoordinator.Init();

	gCoordinator.RegisterComponent<Player>();
	gCoordinator.RegisterComponent<Transform>();

	physicsSys = gCoordinator.RegisterSystem<PhysicsSystem>();
	renderSys = gCoordinator.RegisterSystem<RenderSystem>();

	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<PhysicsSystem>(signature);
		
	}
	physicsSys->Init();

	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Player>());
		signature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<RenderSystem>(signature);
	}

	renderSys->Init();
	

	//Entity entity = gCoordinator.CreateEntity();
	//gCoordinator.AddComponent(entity, Player{});
	//gCoordinator.AddComponent<Transform>(
	//	entity,
	//	Transform{
	//		xpos = 0,
	//		ypos = 0,
	//	});

	std::vector<Entity> entities(MAX_ENTITIES - 1);

	Entity player;

	player = gCoordinator.CreateEntity();
	

	gCoordinator.AddComponent(
		player, Player
		{
		});
	

	gCoordinator.AddComponent(
		player, Transform{
			xpos = 100,
			ypos = 100
		});

		

	//for (auto& entity : entities)
	//{
	//	entity = gCoordinator.CreateEntity();
	//	gCoordinator.AddComponent(
	//		entity,
	//		Transform{
	//			xpos = 100,
	//			ypos = 100
	//		});


	//}

	//player = new GameObject("assets/player.png", 0, 0);
	map = new Map();
	//physicsSystem->Update();

}

void Game::handleEvents(){
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update(){
	physicsSys->Update();
}

void Game::render(){
	SDL_RenderClear(renderer);
	//
	map->DrawMap();
	renderSys->Render();
	//player->Render();
	//
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_QUIT;
}

