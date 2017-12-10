#include"Collision.h"

bool handleObjectCollision(GameObject* considerObject, GameObject* otherObject,Direction& direction, int dt)
{
	//Direction direction; //direction of collision of considerObject
	float dxEntry=0, dyEntry=0;
	float time = AABBCollision(considerObject, otherObject, direction, dxEntry, dyEntry, dt);
	float moveX=0, moveY=0;
	if (time < 1.0f) // will collision
	{
		// cản lại
		//updateTargetPosition(otherObject, direction, true);

		//if (direction==Left_Direction||direction==Right_Direction)	//width-collision //don't neccessary because dxEntry or dyEntry =0 -> + constant
			considerObject->_posX += dxEntry;
		//else											//height-collision
			considerObject->_posY += dyEntry;
			//direction was valid
			return true;
	}	
	else if (isColliding(considerObject, otherObject, moveX, moveY, dt))
		//consider the case 2 object is colliding
		{
			considerObject->_posX += moveX;
			considerObject->_posY += moveY;
			if (moveX > 0)
				direction = Direction::Left_Direction;
			else if (moveX<0)
				direction = Direction::Right_Direction;
			else if (moveY>0)
				direction = Direction::Bottom_Direction;
			else if (moveY < 0)
				direction = Direction::Top_Direction;
			else //moveX=0&moveY=0
				direction = Direction::Adjacent_Direction; //2 object is adjacent together
			return true;
		}
	else //don't happen collision or a long time to happen
	{
		direction = Direction::None_Direction;
		return false;
	}
	// if direction != left or right => keep direction stable

	//after above statement, 2 object is adjacent together
}
float AABBCollision(GameObject* considerObject, GameObject* otherObject, Direction &direction, float& dxEntry, float& dyEntry, int dt){

	RECT considerRect = considerObject->getCollisionBound();
	RECT otherRect = otherObject->getCollisionBound();


	RECT broadphaseRect = getSweptBroadphaseRect(considerObject, dt);	
	if (!isColliding(broadphaseRect, otherRect))				
	{
		direction = Direction::None_Direction;
		return 1.0f;
	}

	D3DXVECTOR2 considerObjectVel = D3DXVECTOR2(considerObject->getVelocity().x * dt , considerObject->getVelocity().y * dt );
	D3DXVECTOR2 otherObjectVel = D3DXVECTOR2(otherObject->getVelocity().x * dt , otherObject->getVelocity().y * dt );
	//D3DXVECTOR2 velocity = - considerObjectVel;
	//float velX = considerObjectVel.x, velY = considerObjectVel.y;

	D3DXVECTOR2 velocity = considerObjectVel - otherObjectVel ;		// consider - other

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

	// Không xảy ra va chạm khi:
	// thời gian bắt đầu va chạm lớn hơn thời gian kết thúc va chạm
	// thời gian va chạm x, y nhỏ hơn 0 (2 object đang đi xa ra nhau)
	// thời gian va chạm x, y lớn hơn 1 (còn xa quá chưa thể va chạm)
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

RECT getSweptBroadphaseRect(GameObject* object, float dt)
{
	// Vận tốc mỗi frame (vX, vY)
	auto velocity = D3DXVECTOR2(object->getVelocity().x * dt, object->getVelocity().y * dt);
	auto myRect = object->getCollisionBound();

	RECT rect;
	rect.left = velocity.x > 0 ? myRect.left : myRect.left + velocity.x;
	rect.top = velocity.y > 0 ? myRect.top + velocity.y : myRect.top;
	rect.right = velocity.y > 0 ? myRect.right + velocity.x : myRect.right;
	rect.bottom = velocity.y > 0 ? myRect.bottom : myRect.bottom + velocity.y;

	return rect;
}

bool isColliding(RECT myRect, RECT otherRect)
{
	float left = otherRect.left - myRect.right;
	float top = otherRect.top - myRect.bottom;
	float right = otherRect.right - myRect.left;
	float bottom = otherRect.bottom - myRect.top;

	return !(left >= 0 || top <= 0 || right <= 0 || bottom >= 0);
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
bool isColliding(GameObject* considerObject, GameObject* otherObject, float& moveX, float& moveY, float dt)
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
	if (left >= 0 || right <= 0 || top <= 0 || bottom >= 0)
		return false;

	// if there are collide
	moveX = abs(left) < right ? left : right;
	moveY = top < abs(bottom) ? top : bottom;

	D3DXVECTOR2 considerObjectVel = D3DXVECTOR2(considerObject->getVelocity().x * dt, considerObject->getVelocity().y * dt);
	D3DXVECTOR2 otherObjectVel = D3DXVECTOR2(otherObject->getVelocity().x * dt, otherObject->getVelocity().y * dt);
	D3DXVECTOR2 velocity = considerObjectVel - otherObjectVel;

	// take smaller 
	if (abs(moveX/velocity.x) < abs(moveY/velocity.y)||velocity.y==0)
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;
}

int updateCollisionPosition(GameObject otherObject, Direction& direction){
	return 1;
}