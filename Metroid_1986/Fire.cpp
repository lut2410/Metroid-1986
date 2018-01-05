#include "Fire.h"

Fire::Fire(){

}
Fire::Fire(int x, int y, int type) :GameObject(Fire_ID, x, y, 0, 0){
	_attack = type;
}
void Fire::Update(int deltaTime)
{

}
void Fire::Update2(int deltaTime)
{
	
}
void Fire::Draw(Camera* camera)
{
	//was drawn in background
}
RECT Fire::getCollisionBound(){
	//size: 16x16 
	RECT groundBound = { _posX - 8,		//left
		_posY + 8,						//top
		_posX + 8,						//right
		_posY - 8 };					//bottom
	return groundBound;
};