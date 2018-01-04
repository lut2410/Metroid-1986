#include "Camera.h"
Camera* Camera::_instance = NULL;
Camera* Camera::getInstance(){
	if (!_instance)
		_instance = new Camera();

	return _instance;
};
Camera::Camera()
{
	_directionOfTheGate = Direction::None_Direction ;
	_viewport.x = 1;
	_viewport.y = _screenHeight;
	_bound = { MINMAP, MAXMAP, MAXMAP, MINMAP };
}

RECT Camera::getRECT()
{
	//width:16x16=256
	//height:15x16=240
	RECT cameraRECT = { _viewport.x,			//left
		_viewport.y,							//top
		_viewport.x + 256,						//right
		_viewport.y - 240};						//bottom
	return cameraRECT;
}
void Camera::UpdateCamera(int x, int y)
{

	//place player on 4-6 part of 10 center of screen
	if (x - _screenWidth * 4 / 10 < _viewport.x)
		_viewport.x = x - _screenWidth * 4 / 10;
	else if (x - _screenWidth * 6 / 10 > _viewport.x)
		_viewport.x = x - _screenWidth * 6 / 10;

	//but viewport camera has limit
	if (_viewport.x < _bound.left)
		_viewport.x = _bound.left;
	else if (_viewport.x > _bound.right - _screenWidth)
		_viewport.x = _bound.right - _screenWidth;
		

	//posite Y
	//place player on 4-6 part of 10 center of screen
	if (y + _screenHeight * 4 / 10 > _viewport.y)
		_viewport.y = y + _screenHeight * 4 / 10;
	else if (y + _screenHeight * 6 / 10 < _viewport.y)
		_viewport.y = y + _screenHeight * 6 / 10;

	//but viewport camera has limit
	if (_viewport.y > _bound.top)
		_viewport.y = _bound.top;
	else if (_viewport.y < _bound.bottom + _screenHeight)
		_viewport.y = _bound.bottom + _screenHeight;

}
void Camera::SetBoundX(int leftBound, int rightBound)
{
	_bound.left = leftBound;
	_bound.right = rightBound;
}
void Camera::SetBoundY(int topBound, int bottomBound)
{
	_bound.top = topBound;
	_bound.bottom = bottomBound;
}
void Camera::ResetBound()
{
	_bound = { MINMAP, MAXMAP, MAXMAP, MINMAP };
}
void Camera::setTheGate(Direction directionOfTheGate)
{

	_directionOfTheGate = directionOfTheGate;
	_remainningFramesToPassTheGate = FRAMESTOPASSTHEGATE;
	//_leftBound = _rightBound;
	//_rightBound += 256;
}
void Camera::passTheGate()
{
	
	if (_remainningFramesToPassTheGate)
	{
		_remainningFramesToPassTheGate--;
		if (_directionOfTheGate == Direction::Right_Direction)	//the gate is on the right
			_viewport.x += 8;
		else
			_viewport.x -= 8;
	}
		
	else					//finish
	{
		//if (_directionOfTheGate == Direction::Right_Direction)	//the gate is on the right
		//{
		//	_bound.left = _bound.right;							//set leftBound = old rightBound
		//	_bound.right = MAXMAP;
		//}
		//else
		//{
		//	_bound.right = _bound.left;							//set leftBound = old rightBound
		//	_bound.left = MINMAP;
		//}
			//reset to default
		_directionOfTheGate = Direction::None_Direction;
	}
		
}
D3DXVECTOR2 Camera::Transform(int x, int y)
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1;
	matrix._41 = -_viewport.x;
	matrix._42 = _viewport.y;

	D3DXVECTOR3 pos3(x, y, 1);
	D3DXVECTOR4 MatrixResult;
	D3DXVec3Transform(&MatrixResult, &pos3, &matrix);

	D3DXVECTOR2 result = D3DXVECTOR2(MatrixResult.x, MatrixResult.y);
	return result;
}
