#include "../header/Game.hpp"
#include "../header/TextureManager.hpp"
#include "../header/Map.hpp"
#include "../header/ECS/Components.hpp"
#include "../header/Vector2D.hpp"
#include"../header/Collision.hpp"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized. " << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
			std::cout << "Window Created." << std::endl;
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			std::cout << "Renderer Created." << std::endl;
		}
		isRunning = true;
	}
	map = new Map();

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/sprite1.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
}

void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	manager.refresh();
	manager.update();
	if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		wall.getComponent<ColliderComponent>().collider)) {
		player.getComponent<TransformComponent>().scale = 1;
		std::cout << "wall hit" << std::endl;
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	//add textures to be rendered in order
	map->DrawMap();
	manager.draw();
	//
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleared." << std::endl;
}