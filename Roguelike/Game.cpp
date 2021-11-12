#include "Game.h"
#include <iostream>
#include "Level.h"
#include "Transform.h"
#include "PhysicsSystem.h"
#include "Player.h"
#include "Sprite.h"
#include "Coordinator.h"
#include "RenderSystem.h"
#include "PlayerControlSystem.h"
#include "Collision.h"
#include "CollisionSystem.h"
#include "TileMapParser.h"

TileMapParser tileMapParser;
Level* level;
std::map<int, std::vector<Tile>> tileMap;

SDL_Renderer* Game::renderer = nullptr;
Coordinator gCoordinator;

std::shared_ptr<PhysicsSystem> physicsSys;
std::shared_ptr<RenderSystem> renderSys;
std::shared_ptr<PlayerControlSystem> pControlSys;
std::shared_ptr<CollisionSystem> collisionSys;
SDL_Event Game::event;

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
	}
	else {
		isRunning = false;
	}

	gCoordinator.Init();

	gCoordinator.RegisterComponent<Player>();
	gCoordinator.RegisterComponent<Transform>();
	gCoordinator.RegisterComponent<Sprite>();
	gCoordinator.RegisterComponent<Collision>();

	physicsSys = gCoordinator.RegisterSystem<PhysicsSystem>();
	renderSys = gCoordinator.RegisterSystem<RenderSystem>();
	pControlSys = gCoordinator.RegisterSystem <PlayerControlSystem>();
	collisionSys = gCoordinator.RegisterSystem<CollisionSystem>();

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
		signature.set(gCoordinator.GetComponentType<Sprite>());
		gCoordinator.SetSystemSignature<RenderSystem>(signature);
	}

	renderSys->Init();

	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Transform>());
		signature.set(gCoordinator.GetComponentType<Player>());
		gCoordinator.SetSystemSignature<PlayerControlSystem>(signature);
	}

	pControlSys->Init();

	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Transform>());
		signature.set(gCoordinator.GetComponentType<Player>());
		signature.set(gCoordinator.GetComponentType<Collision>());
		gCoordinator.SetSystemSignature<CollisionSystem>(signature);
	}

	collisionSys->Init();

	Entity player;
	Entity enemy;

	player = gCoordinator.CreateEntity();
	enemy = gCoordinator.CreateEntity();

	gCoordinator.AddComponent(
		player, Player{
		});

	gCoordinator.AddComponent(
		enemy, Player{

		});

	gCoordinator.AddComponent(
		player, Transform{
			0,
			0,
			true,
		});

	gCoordinator.AddComponent(
		enemy, Transform{
			200,
			200,
			false,
			0,

		});


	gCoordinator.AddComponent(
		player, Sprite{
			8,
			TextureManager::LoadTexture("assets/mechsheet.png"),

			0,
			0,

			0,
			64,

			0,
			64 * 2,

			0,
			64 * 3,

			0,
			64 * 4,

			0,
			64 * 5,

			0,
			64 * 6,

			0,
			64 * 7,

		});

	gCoordinator.AddComponent(
		enemy, Sprite{
			1,
			TextureManager::LoadTexture("assets/player.png"),
		});


	gCoordinator.AddComponent(
		player, Collision{

		});

	gCoordinator.AddComponent(
		enemy, Collision{

		});


	std::map<int, std::string> tiles = tileMapParser.GetTileMap("assets/testmap.tmx", 0, 0);
	level = new Level();
	tileMap = level->CreateTileMap(tiles, tileMapParser.mapSizeX, tileMapParser.mapSizeY, 64);
}

void Game::handleEvents(){

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
	pControlSys->Update();
	collisionSys->Update();
}

void Game::render(){
	SDL_RenderClear(renderer);
	//
	level->DrawMap(tileMap, 25, 25);
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

