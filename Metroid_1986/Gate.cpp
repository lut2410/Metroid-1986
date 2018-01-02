#include "Gate.h"

Gate::Gate(){

}
Gate::Gate(int x, int y) :GameObject(Gate_ID, x, y, 0, 0){
	_currentAnimation = NULL;	//have drawn by backroundmap
}
RECT Gate::getCollisionBound(){
	//size: 16x16 
	RECT groundBound = { _posX - 8,		//left
		_posY + 8,						//top
		_posX + 8,						//right
		_posY - 8 };					//bottom
	return groundBound;
};
void Gate::Update2(int time)
{
	//just check with camera

	RECT cameraRECT = Camera::getInstance()->getRECT();
	RECT gateRECT = getCollisionBound();
	if (isColliding(cameraRECT, gateRECT))
	{
		D3DXVECTOR2 cameraCenter = { (float)(cameraRECT.left + cameraRECT.right) / 2, (float) (cameraRECT.top + cameraRECT.bottom) / 2 };
		D3DXVECTOR2 gateCenter = { (float)(gateRECT.left + gateRECT.right) / 2, (float)(gateRECT.top + gateRECT.bottom) / 2 };

		if (gateCenter.x > cameraCenter.x)//gate is on the right of the camera
			//set rightbound of camera = rightbound of the gate
			Camera::getInstance()->_bound.right = gateRECT.right;
		else //if (gateCenter.x < cameraCenter.x)//gate is on the right of the camera
			Camera::getInstance()->_bound.left = gateRECT.left;
	}
	//this time, the camera is limited by the gate
}
void Gate::Draw(Camera* camera)
{

}