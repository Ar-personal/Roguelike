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
#include "CameraSystem.h"
#include "Mouse.h"
#include "MouseControlSystem.h"
#include "TileRenderSystem.h"
#include "Maths.h"

TileMapParser tileMapParser;
std::map<int, std::vector<Tile>> tileMap;
Camera camera;

SDL_Renderer* Game::renderer = nullptr;
Coordinator gCoordinator;

std::shared_ptr<PhysicsSystem> physicsSys;
std::shared_ptr<RenderSystem> renderSys;
std::shared_ptr<PlayerControlSystem> pControlSys;
std::shared_ptr<MouseControlSystem> mouseControlSys;
std::shared_ptr<CollisionSystem> collisionSys;
std::shared_ptr<CameraSystem> cameraSys;
std::shared_ptr<TileRenderSystem> tileRenderSys;

SDL_Event Game::event;

Game::Game(){}
Game::~Game(){}

int mapOffsetX = 0;
int mapOffsetY = 0;
int tileSize = 64;
int scale = 2;

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {




	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_RESIZABLE;
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


	std::map<int, std::string> tiles = tileMapParser.GetTileMap("assets/testmap.tmx", 0, 0);
	std::map<int, std::string> levelColliders = tileMapParser.GetLevelColliders();
	tileMap = Level::CreateTileMap(tiles, levelColliders, tileMapParser.mapSizeX, tileMapParser.mapSizeY, tileSize, scale);

	gCoordinator.Init();

	gCoordinator.RegisterComponent<Player>();
	gCoordinator.RegisterComponent<Transform>();
	gCoordinator.RegisterComponent<Sprite>();
	gCoordinator.RegisterComponent<Collision>();
	gCoordinator.RegisterComponent<Camera>();
	gCoordinator.RegisterComponent<Mouse>();

	physicsSys = gCoordinator.RegisterSystem<PhysicsSystem>();
	renderSys = gCoordinator.RegisterSystem<RenderSystem>();
	pControlSys = gCoordinator.RegisterSystem <PlayerControlSystem>();
	mouseControlSys = gCoordinator.RegisterSystem <MouseControlSystem>();
	collisionSys = gCoordinator.RegisterSystem<CollisionSystem>();
	cameraSys = gCoordinator.RegisterSystem<CameraSystem>();
	tileRenderSys = gCoordinator.RegisterSystem<TileRenderSystem>();

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
		signature.set(gCoordinator.GetComponentType<Camera>());
		gCoordinator.SetSystemSignature<RenderSystem>(signature);
	}

	renderSys->Init();

	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Transform>());
		signature.set(gCoordinator.GetComponentType<Player>());
		gCoordinator.SetSystemSignature<PlayerControlSystem>(signature);
	}

	pControlSys->Init(tileMap);


	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Transform>());
		signature.set(gCoordinator.GetComponentType<Player>());
		signature.set(gCoordinator.GetComponentType<Collision>());
		gCoordinator.SetSystemSignature<CollisionSystem>(signature);
	}

	collisionSys->Init(tileMap, levelColliders);


	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Transform>());
		signature.set(gCoordinator.GetComponentType<Player>());
		signature.set(gCoordinator.GetComponentType<Camera>());
		gCoordinator.SetSystemSignature<CameraSystem>(signature);
	}

	cameraSys->Init();

	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Player>());
		signature.set(gCoordinator.GetComponentType<Mouse>());
		gCoordinator.SetSystemSignature<MouseControlSystem>(signature);
	}

	mouseControlSys->Init();

	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Player>());
		signature.set(gCoordinator.GetComponentType<Mouse>());
		signature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<TileRenderSystem>(signature);
	}

	tileRenderSys->Init(tileMap, tileMapParser.mapSizeX, tileMapParser.mapSizeY, 64, mapOffsetX, mapOffsetY, scale);

	Entity player;
	Entity enemy;

	player = gCoordinator.CreateEntity();
	enemy = gCoordinator.CreateEntity();

	gCoordinator.AddComponent(
		player, Player{
			0,
		});

	gCoordinator.AddComponent(
		player, Mouse{
			{0, 0},
			false,
			false
		});

	gCoordinator.AddComponent(
		enemy, Player{

		});


	gCoordinator.AddComponent(
		player, Collision{

		});

	gCoordinator.AddComponent(
		player, Camera{
			0, 0, 1280, 720
		});


	gCoordinator.AddComponent(
		player, Transform{
			0,
			0,
			true,
		});

	gCoordinator.AddComponent(
		enemy, Transform{
			0,
			0,
			false,
			0,

		});


	gCoordinator.AddComponent(
		player, Sprite{
			TextureManager::LoadTexture("assets/mechsheet.png"),
			true,
			15,
			60,
		});

	gCoordinator.AddComponent(
		enemy, Sprite{
			TextureManager::LoadTexture("assets/player.png"),
			false,
		});

	gCoordinator.AddComponent(
		enemy, Collision{

		});



	//handle tile coordinate and mouse coordinates
	//do i need a mapsystem? mouse input system or component
	//ability to render highlighted tiles differently so check layer x and y
	//how to choose layer? choose top layer of tile unless its invisible so loop top down til visible
	//player should be locked into center of tiles
	//mouse position component, mouseSystem only for player components

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
	mouseControlSys->Update();
	pControlSys->Update();
	collisionSys->Update();
	cameraSys->Update();
}

void Game::render(){
	SDL_RenderClear(renderer);
	//
	tileRenderSys->Render();
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

