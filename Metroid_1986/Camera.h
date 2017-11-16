#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Global Setting.h"
#include "Sprite.h"

class Camera
{
public:
	D3DXVECTOR2 _viewport;		//set coordinates of camera
	int _leftBound;				//limit place camera can go to
	int _rightBound;				//limit place camera can go to

	Camera();
	void UpdateCamera(int x);								//place position of player on screen base on posX of Player
	D3DXVECTOR2 Transform(int x, int y);					//transform viewport-coordinates to world-coordinates
	void SetSizeMap(int leftBound, int rightBound);			//
};

#endif