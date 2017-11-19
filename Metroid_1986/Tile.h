#ifndef TILE_H
#define TILE_H

#include "Global Setting.h"
using namespace std;
class Tile{
	int ID;
	int X;
	int Y;
	int Width;
	int Height;
	int Collision;
	string CollisionName;
public:
	Tile();
	Tile(int, int, int, int, int, int, string);
	Tile(string); //import from 1 line of file
	~Tile();
};

#endif