#include "Game.hpp"

class Map {
public:

	Map();
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();

private:

	SDL_Rect src, dest;
	SDL_Texture* dirt, * grass, * water;

	int map[20][25];

};