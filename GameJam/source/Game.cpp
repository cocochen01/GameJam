#include "../header/Game.hpp"
#include "../header/TextureManager.hpp"
#include "../header/GameObject.hpp"

GameObject* player;
GameObject* enemy;

SDL_Renderer* Game::renderer = nullptr;

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
	player = new GameObject("assets/sprite1.png", 0, 0);
	enemy = new GameObject("assets/enemy1.png", 50, 50);
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
	player->Update();
	enemy->Update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	//add textures to be rendered in order
	player->Render();
	enemy->Render();
	//
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleared." << std::endl;
}