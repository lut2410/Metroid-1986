#include "TileGrid.h"
vector<Tile>* TileGrid::_objectTiles = new vector<Tile>();
QuadTree* TileGrid::_rootQuadTree = NULL;
QuadTree* _quadTree = new QuadTree();
TileGrid::TileGrid(){
	CurrentTileIDs = new vector<int>();
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
void TileGrid::GetCurrentTileIDs(int x, int y){
	CurrentTileIDs->clear();

	//insert tiles exist on screen to CurrentTile
	GetTileIDInQuadTree(x, y, _rootQuadTree);
}
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
	if (collide(cameraBox, quadTreeBox))			//has overlap together			
		//import tile
		for (vector<int>::iterator index = quadTree->ChildIndexs.begin(); index != quadTree->ChildIndexs.end(); index++)
		{
			CurrentTileIDs->push_back(*index);
		}
}