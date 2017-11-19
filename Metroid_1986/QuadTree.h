#ifndef QUADTREE_H
#define QUADTREE_H

#include "Global Setting.h"
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
class QuadTree{
	friend class TileGrid;

	//real value
	int ID;
	int XNode;
	int YNode;
	int WidthNode;
	int HeightNode;
	int ChildNodeCout;
	int ObjectCout;
	vector<int> ChildIndexs;	//= serial of title in file Object.txt
	//vector<Tile> TileGrid;

	//child quadtrees

	QuadTree* LeftTop;
	QuadTree* RightTop;
	QuadTree* LeftBottom;
	QuadTree* RightBottom;
public:
	QuadTree();
	QuadTree(int, int, int, int, int, int, int, vector<int>);
	QuadTree(string);				//import from a line of file text
	~QuadTree();
};

#endif