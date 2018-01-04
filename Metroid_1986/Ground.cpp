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
void Ground::Update(int time)
{
	//set block camera
	Camera* camera = Camera::getInstance();

	/*int distanceX = abs(this->_posX - object->_posX);
	int distanceY = abs(this->_posY - object->_posY);
	if (distanceX < _screenWidth / 2 && distanceY < _screenHeight / 2)*/
	RECT cameraRect = Camera::getInstance()->getRECT();
	RECT blockRect = this->getCollisionBound();
	if (isCollideR(cameraRect, blockRect))			// camera is contain block		
	{
		if (this->getHP() == -2)//blockX
		{
			int leftBoundCamera = this->_posX - 8;
			camera->SetBoundX(leftBoundCamera, leftBoundCamera + _screenWidth);
		}
		if (this->getHP() == -1)//blockY
		{
			int bottomBoundCamera = this->_posY - 8;
			camera->SetBoundY(bottomBoundCamera + _screenHeight, bottomBoundCamera);
		}
	}

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