#include "../Header Files/Game.h"
#include "../Header Files/TextureManager.h"
#include "../Header Files/Map.h"
#include "../ECS/Components.h"
#include "../Header Files/Vector2D.h"
#include "../Header Files/Collision.h"



Map* map = nullptr;
Manager manager;

SDL_Event Game::event; 
SDL_Renderer* Game::renderer = nullptr;  //init once for all obj



Entity& player(manager.addEntity()); // player of type entity
Entity& wall(manager.addEntity());


Game::Game() {

}
Game::~Game() {

}

bool Game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}
	                                                                                                               // true for fullscreen
	window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	if (window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0); // assign ren an adress
	if (renderer == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}

	map = new Map;


	player.addComponent<TransformComponent>(2); // explicitly specifying type for template func
	player.addComponent<SpriteComponent>("assets/player2.png");
	player.addComponent<KeyboardController>();
	player.getComponent<TransformComponent>().speed = 4;
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");

	return isRunning = true;
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{                         
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	manager.refresh();

	manager.update();

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider, 
		wall.getComponent<ColliderComponent>().collider))
	{
		player.getComponent<TransformComponent>().position = playerPos;

		std::cout << "Collision!\n";
	}

}

void Game::render()
{
	SDL_RenderClear(renderer);
	                        // render/draw
	      
	map->drawMap();
	
	manager.draw(); // draws all entities
	

	SDL_RenderPresent(renderer);
}


void Game::quit()
{
	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);

	SDL_Quit();

	delete  map;   // delete dynamic objs
	map = nullptr;
}
