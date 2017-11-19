#include"Tile.h"
Tile::Tile(){
	ID = -1;
	X = 0;
	Y = 0;
	Width = 0;
	Height = 0;
	Collision = 0;
	CollisionName = "";
}
Tile::Tile(int id, int x, int y, int width, int height, int collision, string collisionName){
	ID = id;
	X = x;
	Y = y;
	Width = width;
	Height = height;
	Collision = collision;
	CollisionName = collisionName;
}
Tile::Tile(string line){
	istringstream istr_line (line);
	if (!(istr_line >> ID >> X >> Y >> Width >> Height >> Collision >> CollisionName))
		MessageBox(G_hWnd,"Error import tile from line","Error",MB_OK);
	//istr_line >> ID >> X >> Y >> Width >> Height >> Collision>>CollisionName;
}
Tile::~Tile(){
}