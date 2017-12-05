#ifndef TILE_GRID_H
#define TILE_GRID_H

#include "Global Setting.h"
#include "Tile.h"
#include "QuadTree.h"
#include <utility>
#include <map>
#include "AABB.h"
#include "GameObject.h"
#include "Camera.h"

//object
#include "Ground.h"



//contain all object on screeen
class TileGrid{
	static vector<Tile>* _objectTiles;			//all object
	//static vector<GameObject*> _allObject;		//all object in map  
	static QuadTree* _rootQuadTree;				//root QuadTree
	vector<int>* CurrentTileNumbers;			//TileNumber = number what of element of_objecTiles
	map<int,GameObject*> CurrentObjects;		//objects maybe collision with player
	QuadTree* specifyQuatreeChilds(map<int, QuadTree*>,int);
	void GetTileIDInQuadTree(int, int, QuadTree*);
public:
	TileGrid();
	~TileGrid();
	void LoadObjectTileFromFile(string);
	void LoadQuadtreeFromFile(string);
	void UpdateCurrentTileNumbers(int, int);				//Get tile in the specified space
	void UpdateCurrentTileNumbers(Camera*);				//update tiles in viewport
	void UpdateCurrentObjects(Camera*);		//update objects in viewport
	void Update(Camera*);
	map<int, GameObject*> getCurrentObjects();
	GameObject* CreateObject(int id, int x, int y);
};


#endif