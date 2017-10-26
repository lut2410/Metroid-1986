#include "Sprite.h"
enum ObjectID{

};
class Object{
protected:
	Sprite* _Sprite;
	//Position of Object
	int _PosX;
	int _PosY;
	//Velocity of Object
	float _VelX;
	float _VelY;
	
	//Other Parameters

public:
	Object(ObjectID objectID, int posX, int posY);
};