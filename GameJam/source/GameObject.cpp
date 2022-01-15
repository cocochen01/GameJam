#include "../header/GameObject.hpp"
#include "../header/TextureManager.hpp"

GameObject::GameObject(const char* textureSheet, int x, int y) {
	objTexture = TextureManager::LoadTexture(textureSheet);
	xpos = x;
	ypos = y;
}

void GameObject::Update() {
	xpos++;
	ypos++;

	srcRect.h = 60;
	srcRect.w = 60;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}