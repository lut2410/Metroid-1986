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

//OBJECT
//nelative of ground
#include "Ground.h"
#include "Gate.h"
#include "BubbleDoor.h"
#include "ZebProductionPipe.h"

//enemy
#include "Zoomer.h"
#include "Skree.h"
#include "Ripper.h"
#include "Zeb.h"
#include "Waver.h"
#include "Rio.h"

//boss
#include "Ridley.h"
#include "Kraid.h"

//item
#include "HPTonic.h"
#include "MaruMari.h"
#include "LongBeam.h"
#include "IceBeam.h"
#include "WaveBeam.h"
#include "MissibleRocket.h"
#include "Rocket.h"

//ID of Game Object (has divided by type)
enum ObjectIDFromFile{
	BlockX_IDFF=-2,
	BlockY_IDFF=-1,
	Ground_IDFF=0,
	Gate_IDFF=1,
	BubbleDoor_IDFF = 2,
	Zoomer_IDFF=20,
	Zoomer2_IDFF=21,
	Skree_IDFF=22,
	Skree2_IDFF=23,
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
	void handleCollision(int playerX, int playerY, int time);
	map<int, GameObject*>* getCurrentObjects();
	GameObject* CreateObject(int id, int x, int y);
	static void AddObjectToCurrentObjectList(GameObject* object);		//bullet Samus shoot out, and items appear from the enemies
};


#endif