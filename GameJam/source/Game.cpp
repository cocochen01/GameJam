#include "../header/Game.hpp"
#include "../header/TextureManager.hpp"
#include "../header/Map.hpp"
#include "../header/ECS/Components.hpp"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;

auto& player(manager.addEntity());

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

	player.addComponent<PositionComponent>(10, 20);
	player.addComponent<SpriteComponent>("assets/sprite1.png");
}

void Game::handleEvents() {
	SDL_Event event;
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

	if (player.getComponent<PositionComponent>().x() > 100) {
		player.getComponent<SpriteComponent>().setTex("assets/enemy1.png");
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