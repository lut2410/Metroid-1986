#include"Collision.h"

int handleObjectCollision(GameObject* considerObject, GameObject* otherObject,Direction& direction, int dt, bool isUpdate)
{
	RECT c = considerObject->getCollisionBound();
	if (otherObject->_posX == 632 && otherObject->_posY == 1080)
		int i = 0;
	//Direction direction; //direction of collision of considerObject
	float dxEntry=0, dyEntry=0;
	float time = AABBCollision(considerObject, otherObject, direction, dxEntry, dyEntry, dt);
	float moveX=0, moveY=0;
	if (time < 1.0f) // will collision
	{
		//	//direction was valid
		if (isUpdate)
		{
			considerObject->_posX += dxEntry;
			considerObject->_posY += dyEntry;
		}
			return 2;
	}	
	if (isColliding(considerObject, otherObject, direction, moveX, moveY, dt))
				//consider the case 2 object is colliding
	{
		if (isUpdate)
		{
			considerObject->_posX += moveX;
			considerObject->_posY += moveY;
		}
		return 1;
		
	}
	//don't happen collision or a long time to happen
	{
		direction = Direction::None_Direction;
		return 0;
	}
	// if direction != left or right => keep direction stable

	//after above statement, 2 object is adjacent together
}
float AABBCollision(GameObject* considerObject, GameObject* otherObject, Direction &direction, float& dxEntry, float& dyEntry, int dt){

	D3DXVECTOR2 considerObjectVel = D3DXVECTOR2(considerObject->getVelocity().x * dt, considerObject->getVelocity().y * dt);
	D3DXVECTOR2 otherObjectVel = D3DXVECTOR2(otherObject->getVelocity().x * dt, otherObject->getVelocity().y * dt);
	//D3DXVECTOR2 velocity = - considerObjectVel;
	//float velX = considerObjectVel.x, velY = considerObjectVel.y;

	D3DXVECTOR2 velocity = considerObjectVel - otherObjectVel;		// consider - other


	RECT considerRect = considerObject->getCollisionBound();
	RECT otherRect = otherObject->getCollisionBound();

	if (considerObject->getObjectID() == Player_ID&&otherRect.right == 512 && otherRect.top == 1104 && considerObject->getVelocity().x<0)
		considerRect = considerObject->getCollisionBound();
	
	RECT broadphaseRect = getSweptBroadphaseRect(considerRect, velocity);
	if (!isColliding(broadphaseRect, otherRect))				
	{
		direction = Direction::None_Direction;
		return 1.0f;
	}
	if (considerObject->getObjectID() == Player_ID&&otherObject->getObjectID() == Hedgehog_ID)
		considerRect = considerObject->getCollisionBound();
	
	// find the distance between the objects on the near and far sides for both x and y
	float dxExit, dyExit;
	if (velocity.x > 0)
	{
		dxEntry = otherRect.left - considerRect.right;
		dxExit = otherRect.right - considerRect.left;
	}
	else
	{
		dxEntry = otherRect.right - considerRect.left;
		dxExit = otherRect.left - considerRect.right;
	}

	if (velocity.y > 0)
	{
		dyEntry = otherRect.bottom - considerRect.top;
		dyExit = otherRect.top - considerRect.bottom;
	}
	else
	{
		dyEntry = otherRect.top - considerRect.bottom;
		dyExit = otherRect.bottom - considerRect.top;
	}


	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float txEntry, tyEntry, txExit, tyExit;
	if (velocity.x == 0)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / velocity.x;
		txExit = dxExit / velocity.x;
	}

	if (velocity.y == 0)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / velocity.y;
		tyExit = dyExit / velocity.y;
	}

	// find the earliest/latest times of collision
	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(txExit, tyExit);


	// if there was no collision
	if (entryTime > exitTime || txEntry < 0.0f && tyEntry < 0.0f || txEntry > 1.0f || tyEntry > 1.0f)
	{
		direction = Direction::None_Direction;
		return 1.0f;
	}

	// Nếu thời gian va chạm x lơn hơn y
	if (txEntry > tyEntry)	// width-collison later height-collsion
	{
		dyEntry = 0.0f;	//return dxEntry to update, clean dyEntry
		//collision on the right of considerObject
		//if (dxEntry > 0.0f)		//=(velocity.x>0) : right-> collide in right of considerObjcet
		if (velocity.x<0)
		{
			direction = Direction::Left_Direction;
		}
		//else if (dxEntry < 0.0f)
		else
		{
			direction = Direction::Right_Direction;
		}
	}
	else
	{
		dxEntry = 0.0f;			//return dyEntry to update, clean dxEntry
		//if (dyEntry > 0.0f)		//=(velocity.y>0) : up-> collide in top 
		if (velocity.y>0)
		{
			direction = Direction::Top_Direction; 
		}
		else
		{
			direction = Direction::Bottom_Direction;
		}
	}

	return entryTime;
};

RECT getSweptBroadphaseRect(RECT rect, D3DXVECTOR2 velocity)
{
	//velocity of 2 object

	RECT rs;
	rs.left = velocity.x > 0 ? rect.left : rect.left + velocity.x;
	rs.top = velocity.y > 0 ? rect.top + velocity.y : rect.top;
	rs.right = velocity.x > 0 ? rect.right + velocity.x : rect.right;
	rs.bottom = velocity.y > 0 ? rect.bottom : rect.bottom + velocity.y;

	return rs;
}

bool isColliding(RECT myRect, RECT otherRect)
{
	float left = otherRect.left - myRect.right;
	float top = otherRect.top - myRect.bottom;
	float right = otherRect.right - myRect.left;
	float bottom = otherRect.bottom - myRect.top;

	return !(left >= 0 || top <= 0 || right <= 0 || bottom >= 0);
}
bool isCollidingEx(RECT myRect, RECT otherRect)
{
	float left = otherRect.left - myRect.right;
	float top = otherRect.top - myRect.bottom;
	float right = otherRect.right - myRect.left;
	float bottom = otherRect.bottom - myRect.top;

	return !(left > 0 || top < 0 || right < 0 || bottom > 0);
}
Direction isCollidingExtend(GameObject* player, GameObject* ground)
{
	RECT playerRect = player->getCollisionBound();
	//extend rect to check collision with ground
	playerRect.left--; playerRect.right++;//extend
	playerRect.top; playerRect.bottom++;	//narrow bottom to just check left and right
		
	RECT groundRect = ground->getCollisionBound();

	if (!isColliding(playerRect, groundRect))
		return Direction::Bottom_Direction;

	float left = groundRect.left - playerRect.right;
	//float top = otherRect.top - myRect.bottom;
	float right = groundRect.right - playerRect.left;
	//float bottom = otherRect.bottom - myRect.top;

	
	if (left == -1)		//otherrect is on ther right side of myrect
		return Direction::Right_Direction;
	if (right == 1)
		return Direction::Left_Direction;
	else
		return Direction::Bottom_Direction;
	//if (top == 1)
	//	return Direction::Bottom_Direction;
	//if (bottom == -1)
	//	return Direction::Top_Direction;

}
bool isColliding(GameObject* considerObject, GameObject* otherObject,Direction& direction, float& moveX, float& moveY, float dt)
{
	moveX = moveY = 0.0f;
	RECT considerRect = considerObject->getCollisionBound();
	RECT otherRect = otherObject->getCollisionBound();

	float left = otherRect.left - considerRect.right;
	float top = otherRect.top - considerRect.bottom;
	float right = otherRect.right - considerRect.left;
	float bottom = otherRect.bottom - considerRect.top;

	// collide when
	// left <= 0 && right >= 0 && top >= 0 && bottom <= 0
	if (left > 0  || right < 0  || top < 0  || bottom > 0 )
		return false;

	// if there are collide
	moveX = abs(left) < right ? left : right;
	moveY = top < abs(bottom) ? top : bottom;

	//D3DXVECTOR2 considerObjectVel = D3DXVECTOR2(considerObject->getVelocity().x * dt, considerObject->getVelocity().y * dt);
	//D3DXVECTOR2 otherObjectVel = D3DXVECTOR2(otherObject->getVelocity().x * dt, otherObject->getVelocity().y * dt);
	//D3DXVECTOR2 velocity = considerObjectVel - otherObjectVel;

	//collide at corner of 2 object
	if (moveX == 0 && moveY == 0)
		return false;
	//adjacent at 1 edge
	if (moveX == 0 || moveY == 0)
	{
		if (top == 0)
			direction = Direction::Bottom_Direction;
		else if (bottom == 0)
			direction = Direction::Top_Direction;
		else if (left == 0)
			direction = Direction::Right_Direction;
		else if (right == 0)
			direction = Direction::Left_Direction;

		moveX = moveY = 0.0f;
		return true;
	}
	//overlap
	// take smaller 
	if (abs(moveX) < abs(moveY))
	{
		moveY = 0.0f;
		if (moveX > 0)
			direction = Direction::Left_Direction; 
		if (moveX < 0)
			direction = Direction::Right_Direction;	
	}
	else
	{
		moveX = 0.0f;
		if (moveY > 0)
			direction = Direction::Bottom_Direction;
		if (moveY < 0)
			direction = Direction::Top_Direction;
	}


	return true;
}

int updateCollisionPosition(GameObject otherObject, Direction& direction){
	return 1;
}