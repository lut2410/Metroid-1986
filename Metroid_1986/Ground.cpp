#include "Ground.h"

Ground::Ground(){

}
Ground::Ground( int x, int y) :GameObject(Ground_ID, x, y, 0, 0){
	_isRelativeWithGround = true;
	_currentAnimation = NULL;	//have drawn by backroundmap
}
RECT Ground::getCollisionBound(){
	//size: 16x16 
	RECT groundBound = { _posX - 8,		//left
		_posY + 8,						//top
		_posX + 8,						//right
		_posY - 8 };					//bottom
	return groundBound;
};