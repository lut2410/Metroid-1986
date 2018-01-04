#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Global Setting.h"
#include "Sprite.h"

#define FRAMESTOPASSTHEGATE 32
#define MAX 10000
#define MIN 0
class Camera
{
protected:
	static Camera* _instance;
public:
	

	D3DXVECTOR2 _viewport;							//set coordinates of camera
	//int _leftBound;									//limit place camera can go to
	//int _rightBound;								//limit place camera can go to
	RECT _bound;									//limit place camera can go to
	Direction _directionOfTheGate;			//use when player passing the gate
	int _remainningFramesToPassTheGate;

	static Camera* getInstance();
	Camera();
	RECT getRECT();
	void UpdateCamera(int x, int y);								//place position of player on screen base on posX of Player
	D3DXVECTOR2 Transform(int x, int y);					//transform world-coordinates to viewport-coordinates
	void SetSizeMap(int leftBound, int rightBound);			//
	void setTheGate(Direction diretionOfTheGate);					//true/fase if to right/left
	void passTheGate();
};

#endif