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
#include "WeakGround.h"
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
	BubbleDoorBlue_IDFF = 1,
	BubbleDoorRed_IDFF = 2,
	BlueZebPipe_IDFF=3,
	RedZebPipe_IDFF=4,
	WeakGroundOrange_IDFF=5,
	WeakGroundBlue_IDFF = 6,
	//enemy
	Zoomer1_IDFF=20,
	Zoomer2_IDFF=21,
	Skree1_IDFF=22,
	Skree2_IDFF=23,
	Ripper1_IDFF=24,
	Ripper2_IDFF=25,
	Ripper3_IDFF=26,
	Zeb1_IDFF=27,
	Zeb2_IDFF=28,
	Waver1_IDFF=29,
	Waver2_IDFF=30,
	Rio1_IDFF=31,
	Rio2_IDFF=32,
	//boss
	Ridley_IDFF=50,
	Kraid1_IDFF=51,
	Kraid2_IDFF=52,
	//item

	MaruMari_IDFF=60,
	LongBeam_IDFF=61,
	IceBeam_IDFF=62,
	WaveBeam_IDFF=63,
	MissibleRocket_IDFF=64,
	Bomb_IDFF=65,
	EnergyTank_IDFF=66,
	//Rocket and HpTonic is appear when enemy die
};

//contain all object on screeen
class TileGrid{
	static TileGrid* _tileGridInstance;
	vector<Tile>* ObjectTiles;						//all object
	//static vector<GameObject*> _allObject;		//all object in map  
	QuadTree* RootQuadTree;							//root QuadTree
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