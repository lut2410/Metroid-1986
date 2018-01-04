#include "Ground.h"

Ground::Ground(){

}
Ground::Ground( int x, int y, int type) :GameObject(Ground_ID, x, y, 0, 0){

	_hp = type;	//borrow
	//_hp=0: normal
	//_hp=-1: blockY
	//_hp=-2: blockX
	_currentAnimation = NULL;	//have drawn by backroundmap
}
void Ground::Update2(int time)
{
}
void Ground::Draw(Camera* camera)
{}
RECT Ground::getCollisionBound(){
	//size: 16x16 
	RECT groundBound = { _posX - 8,		//left
		_posY + 8,						//top
		_posX + 8,						//right
		_posY - 8 };					//bottom
	return groundBound;
};