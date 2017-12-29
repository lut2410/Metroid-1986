#ifndef TILE_GRID_H
#define TILE_GRID_H

#pragma once
#include "Global Setting.h"
#include "Tile.h"
#include "QuadTree.h"
#include <utility>
#include <map>
#include "AABB.h"
#include "GameObject.h"
#include "Camera.h"
#include "Collision.h"

//object
#include "Ground.h"
#include "Gate.h"
#include "BubbleDoor.h"
#include "Hedgehog.h"
#include "MaruMari.h"
//ID of Game Object (has divided by type)
enum ObjectIDFromFile{
	Ground_IDFF=0,
	Gate_IDFF=1,
	BubbleDoor_IDFF = 2,
	Hedgehog_IDFF=20,
	Hedgehog2_IDFF=21,
	MaruMari_IDFF=41
};

//contain all object on screeen
class TileGrid{
	static TileGrid* _tileGridInstance;
	vector<Tile>* ObjectTiles;				//all object
	//static vector<GameObject*> _allObject;		//all object in map  
	QuadTree* RootQuadTree;					//root QuadTree
	vector<int>* CurrentTileNumbers;				//TileNumber = number what of element of_objecTiles
	vector<QuadTree*> CurrentQuadTrees;	
	vector<QuadTree*> CurrentOutsideQuadTrees;
	vector<QuadTree*> CurrentNewInsideQuadTrees;
	map<int,GameObject*>* CurrentObjects;			//objects maybe collision with player
	QuadTree* specifyQuatreeChilds(map<int, QuadTree*>,int);
	void GetTileIDInQuadTree(int, int, QuadTree*);
	void GetCurrentQuadTrees(int, int, QuadTree*);
public:
	TileGrid();
	static TileGrid* getInstance();
	~TileGrid();
	void LoadObjectTileFromFile(string);
	void LoadQuadtreeFromFile(string);
	void DeleteTileNumberInCurrentQuadTrees(int tileNumber);//Delete tileNumber from quadtree
	void UpdateCurrentTileNumbers(int, int);				//Get tile in the specified space
	void UpdateCurrentTileNumbers(Camera*);					//update tiles in viewport
	bool isThisObjectIsOnThisQuadTree(GameObject*, QuadTree*);	//check object is being on quadtree base on position
	void UpdateObjectInQuadTreeBaseOnPosition(Camera* );
	void UpdateCurrentQuadTrees(Camera*);					//update tiles in viewport
	void UpdateCurrentObjects(Camera*);						//update objects in viewport
	void Update(Camera*,int time);
	void Update2(int time);
	void Draw(Camera*);
	//handle bullet vs other object
	void handleCollision(int time);							
	map<int, GameObject*>* getCurrentObjects();
	GameObject* CreateObject(int id, int x, int y);
};


#endif