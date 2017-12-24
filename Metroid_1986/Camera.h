#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Global Setting.h"
#include "Sprite.h"

#define FRAMESTOPASSTHEGATE 32
enum DirectionOfTheGate
{
	None_DOTG,
	Left_DOTG,
	Right_DOTG
};

class Camera
{
protected:
	static Camera* _instance;
public:
	

	D3DXVECTOR2 _viewport;							//set coordinates of camera
	int _leftBound;									//limit place camera can go to
	int _rightBound;								//limit place camera can go to
	DirectionOfTheGate _directionOfTheGate;			//use when player passing the gate
	int _remainningFramesToPassTheGate;

	static Camera* getInstance();
	Camera();
	void UpdateCamera(int x);								//place position of player on screen base on posX of Player
	D3DXVECTOR2 Transform(int x, int y);					//transform world-coordinates to viewport-coordinates
	void SetSizeMap(int leftBound, int rightBound);			//
	void setTheGate(DirectionOfTheGate diretionOfTheGate);					//true/fase if to right/left
	void passTheGate();
};

#endif