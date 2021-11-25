//#define SDL_MAIN_HANDLED
#include "Game.hpp"
Game* game = nullptr;

int main(int argc, char* argv[]) {
	
	game = new Game();

	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}