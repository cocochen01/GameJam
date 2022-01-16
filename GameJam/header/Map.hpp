#pragma once
#include <string>

class Map {
public:

	Map();
	~Map();

	static void LoadMap(std::string path, int sizex, int sizey);
	static void LoadMap(int sizex, int sizey);

private:
	static void generate(int& filled, int& currX, int& currY, int** map, int col, int row);
	static void ProceduralGen(int** map, int col, int row);

};