#pragma once
#include <string>
#include <utility>

class Map {
public:

	Map(int x, int y);
	~Map();


	static void LoadMap(std::string path, int sizex, int sizey);
	int** LoadMap();
	std::pair<int, int> getStart();

private:
	int x, y;
	std::pair<int, int>start;
	void generate(int& filled, int& currX, int& currY, int** map, int col, int row);
	void ProceduralGen(int** map, int col, int row);

};