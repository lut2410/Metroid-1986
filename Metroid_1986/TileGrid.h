#ifndef TILE_GRID_H
#define TILE_GRID_H

#include "Global Setting.h"
#include "Tile.h"
#include "QuadTree.h"
#include <utility>
#include <map>
#include "AABB.h"
//contain all object on screeen
class TileGrid{
	static vector<Tile>* _objectTiles;	//all object
	static QuadTree* _rootQuadTree;			//root QuadTree
	vector<int>* CurrentTileIDs;	//object in the specified space
	QuadTree* specifyQuatreeChilds(map<int, QuadTree*>,int);
	void GetTileIDInQuadTree(int, int, QuadTree*);
public:
	TileGrid();
	~TileGrid();
	void LoadObjectTileFromFile(string);
	void LoadQuadtreeFromFile(string);
	void GetCurrentTileIDs(int,int); //Get tile in the specified space
};


#endif