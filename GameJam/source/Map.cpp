#pragma once
#include "../header/Map.hpp"
#include "../header/Game.hpp"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Map::Map(int a, int b) {
	x = a;
	y = b;
}

Map::~Map() {
}

void Map::LoadMap(std::string path, int sizex, int sizey) {
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < sizey; y++) {
		for (int x = 0; x < sizex; x++) {
			mapFile.get(tile);
			Game::AddTile(atoi(&tile), x * 32, y * 32);
			mapFile.ignore();
		}
	}

	mapFile.close();
}

void Map::generate(int& filled, int& currX, int& currY, int** map, int col, int row) {
	int dir = 0;
	int choices = 4;
	int arr[] = { 0,0,0,0 };
	if (currY - 1 < 1) {//n
		arr[0] = 1;
		choices--;
	}
	if (currX + 1 > col - 2) {//e
		arr[1] = 1;
		choices--;
	}
	if (currY + 1 > row - 2) {//s
		arr[2] = 1;
		choices--;
	}
	if (currX - 1 < 1) {//w
		arr[3] = 1;
		choices--;
	}
	if (choices == 0) {
	}
	dir = rand() % choices;
	bool flag = 0;
	for (int i = 0; i < 4; i++) {
		if (arr[i] == 0 && --dir == -1) {
			if (map[currX][currY]) flag = 1;
			switch (i) {
			case 0://n
				currY--;
				break;
			case 1://e
				currX++;
				break;
			case 2://s
				currY++;
				break;
			case 3://w
				currX--;
				break;
			}
			map[currX][currY] = 1;
			if (flag) filled++;
			std::cout << filled << std::endl;
			break;
		}
	}
}
void Map::ProceduralGen(int** map, int col, int row) {
	int filled = 0;
	srand(time(0));
	//int currX = rand() % (col - 2) + 1;
	//int currY = rand() % (row - 2) + 1;
	int currX = 15;
	int currY = 9;
	map[currX][currY] = 1;
	//start = std::make_pair(currX, currY);
	while (filled < col * row * .9) {
		generate(filled, currX, currY, map, col, row);
		if (filled > col * row * .8 && !(rand() % 10)) break;
	}
}
int** Map::LoadMap() {
	int**map = new int* [x];
	for (int i = 0; i < x; i++) {
		map[i] = new int[y];
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			map[i][j] = 0;
		}
	}
	Map::ProceduralGen(map, x, y);
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			Game::AddTile(map[i][j], i * 40, j * 40);
		}
	}
	return map;
}

std::pair<int, int> Map::getStart() {
	return Map::start;
}