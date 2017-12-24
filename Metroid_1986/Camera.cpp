#include "Camera.h"
Camera* Camera::_instance = NULL;
Camera* Camera::getInstance(){
	if (!_instance)
		_instance = new Camera();

	return _instance;
};
Camera::Camera()
{
	_directionOfTheGate = DirectionOfTheGate::None_DOTG;
	_viewport.x = 1;
	_viewport.y = _screenHeight;
}
void Camera::SetSizeMap(int leftBound, int rightBound){
	_leftBound = leftBound;
	_rightBound = rightBound;
}
void Camera::UpdateCamera(int x)
{

	//place player on 4-6 part of 10 center of screen
	if (x - _screenWidth * 4 / 10 < _viewport.x)
		_viewport.x = x - _screenWidth * 4 / 10;
	else if (x - _screenWidth * 6 / 10 > _viewport.x)
		_viewport.x = x - _screenWidth * 6 / 10;

	//but viewport camera has limit
	if (_viewport.x < _leftBound)
		_viewport.x = _leftBound;
	else if (_viewport.x > _rightBound - _screenWidth)
		_viewport.x = _rightBound - _screenWidth;
		

	//posite Y
}
void Camera::setTheGate(DirectionOfTheGate directionOfTheGate)
{

	_directionOfTheGate = directionOfTheGate;
	_remainningFramesToPassTheGate = FRAMESTOPASSTHEGATE;
	//_leftBound = _rightBound;
	//_rightBound += 256;
}
void Camera::passTheGate()
{
	//_remainningTimeToPassTheGate -= time;
	_viewport.x += 8;
	if (_remainningFramesToPassTheGate)
		_remainningFramesToPassTheGate--;
	else
		_directionOfTheGate = DirectionOfTheGate::None_DOTG;
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
