#include "TileGrid.h"
vector<Tile>* TileGrid::_objectTiles = new vector<Tile>();
QuadTree* TileGrid::_rootQuadTree = NULL;
QuadTree* _quadTree = new QuadTree();
TileGrid::TileGrid(){
	CurrentTileNumbers = new vector<int>();
	//CurrentObjects = new map<int,GameObject*>();

	LoadObjectTileFromFile(FILEPATH_OBJECTTILE);

	LoadQuadtreeFromFile(FILEPATH_QUADTREE);
}
TileGrid::~TileGrid(){
}
void TileGrid::LoadObjectTileFromFile(string filePath){
	ifstream file(filePath);
	if (!file) {
		MessageBox(G_hWnd, strcat("Cannot open file:",filePath.c_str()), "Error", MB_OK);
		return;
	}

	//Read text in file

	//pretermit 3 first lines
	string line;
	getline(file, line);
	getline(file, line);
	getline(file, line);


	// import to matrix use world-coordinates type
	while (!file.eof())
	{
		getline(file, line);
		Tile* tile = new Tile(line);
		
		_objectTiles->push_back(*tile);

	}
	file.close();
	
}
void TileGrid::LoadQuadtreeFromFile(string filePath){
	ifstream file(filePath);
	if (!file) {
		MessageBox(G_hWnd, strcat("Cannot open file:", filePath.c_str()), "Error", MB_OK);
		return;
	}

	//Read text in file

	//pretermit 1 first lines
	string line;
	getline(file, line);

	//creat 1 list contain all quadtree

	//map<int, QuadTree*>* quadTrees = new map<int, QuadTree*>();
	map<int, QuadTree*> quadTrees;
	// import quadtree from file
	//quadTree list
	while (!file.eof())
	{
		getline(file, line);
		QuadTree* quadTree = new QuadTree(line);
	/*	pair<int, QuadTree*> quadTreePair;
		quadTreePair.first = quadTree->getID();
		quadTreePair.second = quadTree;*/
		quadTrees.insert(pair<int, QuadTree*>(quadTree->ID, quadTree));
	}
	
	// specify child quadtree of all quadtree, begin at root quadtree
	_rootQuadTree = specifyQuatreeChilds(quadTrees,0);
	
	file.close();

};
QuadTree* TileGrid::specifyQuatreeChilds(map<int, QuadTree*> quadTrees, int id){
	map<int, QuadTree*>::iterator it = quadTrees.find(id);
	QuadTree* quadTree = it->second;		//quadtree is identifed
	if (quadTree->ChildNodeCout)		//has child tree
	{
		quadTree->LeftTop = specifyQuatreeChilds(quadTrees, id * 10 + 1);
		quadTree->RightTop = specifyQuatreeChilds(quadTrees, id * 10 + 2);
		quadTree->LeftBottom= specifyQuatreeChilds(quadTrees, id * 10 + 3);
		quadTree->RightBottom = specifyQuatreeChilds(quadTrees, id * 10 + 4);
	}
	return quadTree;

}
void TileGrid::UpdateCurrentTileNumbers(int x, int y){
	CurrentTileNumbers->clear();

	//insert tiles exist on screen to CurrentTile
	GetTileIDInQuadTree(x, y, _rootQuadTree);
}
void TileGrid::UpdateCurrentTileNumbers(Camera* camera){
	CurrentTileNumbers->clear();

	//insert tiles exist on screen to CurrentTile
	GetTileIDInQuadTree(camera->_viewport.x, camera->_viewport.y, _rootQuadTree);
}

void TileGrid::UpdateCurrentObjects(Camera* camera){

	//for (auto index = CurrentTileNumbers->begin(); index != CurrentTileNumbers->end(); index++)
	for (int i = 0; i < CurrentTileNumbers->size();i++)
	{
		//if list object don't have object has TileID in listCurrentNumber
		//create object is corresponding with TileID
		int TileNumber = CurrentTileNumbers->at(i);
		//int TileNumber = CurrentTileNumbers->at(*index);
		if (!CurrentObjects.count(TileNumber))	//don't have
		{
			Tile objectTile = _objectTiles->at(TileNumber);
			GameObject* ob = CreateObject(objectTile.ID, objectTile.X, objectTile.Y);

			CurrentObjects.insert(pair<int, GameObject*>(TileNumber, ob));
		}

		////except object has number listCurrentNumber don't have
		//for (auto it = CurrentObjects.begin(); it != CurrentObjects.end(); it++)
		//{
		//	int number = it->first;
		//	//for (auto i = CurrentTileNumbers->begin(); i != CurrentTileNumbers->end();i++)
		//		auto i = CurrentTileNumbers->begin();
		//		//i==number
		//		while (i != CurrentTileNumbers->end() && *i != it->first)
		//			i++;
		//		if (*i == number)
		//			;									//OK
		//		else									//don't have number is corresponding with object
		//			CurrentObjects.erase(number);		//delete object, because this object is outside of viewport
		//}

	}
	
}
void TileGrid::Update(Camera* camera){
	UpdateCurrentTileNumbers(camera);				//update tiles in viewport
	UpdateCurrentObjects(camera);
}
GameObject* TileGrid::CreateObject(int id, int x, int y){
	GameObject* object;

	switch (id){
	case 0:
		object = new Ground(x, y);
		return object;
		break;
	}
};
map<int, GameObject*> TileGrid::getCurrentObjects(){
	return CurrentObjects;
};
void TileGrid::GetTileIDInQuadTree(int x, int y, QuadTree* quadTree){
	if (quadTree->ChildNodeCout)		//has child tree
	{
		GetTileIDInQuadTree(x, y, quadTree->LeftTop);
		GetTileIDInQuadTree(x, y, quadTree->RightTop);
		GetTileIDInQuadTree(x, y, quadTree->LeftBottom);
		GetTileIDInQuadTree(x, y, quadTree->RightBottom);
	}
	Box cameraBox = Box(x, y, _screenWidth, -_screenHeight);
	Box quadTreeBox = Box(quadTree->XNode, quadTree->YNode, quadTree->WidthNode, quadTree->HeightNode);
	if (isCollide(cameraBox, quadTreeBox))			//has overlap together			
		//import tile
		for (vector<int>::iterator index = quadTree->ChildIndexs.begin(); index != quadTree->ChildIndexs.end(); index++)
		{
			CurrentTileNumbers->push_back(*index);
		}
}