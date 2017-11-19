#include "QuadTree.h"
QuadTree::QuadTree(){
	ID = -1;
	XNode = 0;
	YNode = 0;
	WidthNode = 0;
	HeightNode = 0;
	ChildNodeCout = 0;
	ObjectCout = 0;

	LeftTop = NULL;
	RightTop = NULL;
	LeftBottom = NULL;
	RightBottom = NULL;
}
QuadTree::QuadTree(int id, int xNode, int yNode, int widthNode, int heightNode, int chileNodeCout, int objectCout, vector<int> childIndexs){
	ID = -1;
	XNode = 0;
	YNode = 0;
	WidthNode = 0;
	HeightNode = 0;
	ChildNodeCout = 0;
	ObjectCout = 0;
	ChildIndexs = childIndexs;
	//TileGrid = tile;

	LeftTop = NULL;
	RightTop = NULL;
	LeftBottom = NULL;
	RightBottom = NULL;
}
QuadTree::QuadTree(string line){
	istringstream istr_line(line);
	istr_line >> ID >> XNode >> YNode >> WidthNode >> HeightNode >> ChildNodeCout >> ObjectCout; //import value-int type
	//import child index to list
	int value;
	while (istr_line >> value)
		ChildIndexs.push_back(value);
}

QuadTree::~QuadTree(){

}