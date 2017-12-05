#include <windows.h>		// to parse to RECT
//#include <d3dx9.h>
#include "GameObject.h"
enum Block{
	None_Block,
	Left_Block,
	Right_Block
};
// Check collision and return retyTime and direction of collision
float AABBCollision(GameObject* considerObject, GameObject* otherObject, DirectionOfCollision &direction, float& dxEntry, float& dyEntry, int dt);
int updateCollisionPosition(GameObject considerObject, DirectionOfCollision& direction);
RECT getSweptBroadphaseRect(GameObject* object, float dt);
DirectionOfCollision isCollidingExtend(GameObject* player, GameObject* ground); //direction of collsion between player and ground
bool isColliding(RECT myRect, RECT otherRect);
bool isColliding(GameObject* considerObject, GameObject* otherObject, float& moveX, float& moveY, float dt);
bool handleObjectCollision(GameObject* considerObject, GameObject* otherObject, DirectionOfCollision& direction, int dt);