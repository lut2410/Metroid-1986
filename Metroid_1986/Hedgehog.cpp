#include "Hedgehog.h"
Hedgehog::Hedgehog(){}
Hedgehog::Hedgehog(int x, int y, int type) :GameObject(Hedgehog_ID, x, y, 0, 0){

	Texture2* hedgehogTexture = NULL;
	hedgehogTexture = TextureCollection::getInstance()->getTexture2(Hedgehog_ID);

	if (type == 1)
	{
		_hp = 3;
		_attack = 8;
		_actionAnimation.resize(8);
		for (int i = 0; i < 8; i++)
			_actionAnimation[i] = new Animation(hedgehogTexture, hedgehogTexture->_animationNames.at(i));
	}
	else //type 2
	{
		_hp = 5;
		_attack = 8;
		_actionAnimation.resize(8);
		for (int i = 0; i < 8; i++)
			_actionAnimation[i] = new Animation(hedgehogTexture, hedgehogTexture->_animationNames.at(i+8));
	}
	

	//_actionAnimation[Crawl_Top]		= new Animation(hedgehogTexture, hedgehogTexture->_animationNames.at(Crawl_Top));
	//_actionAnimation[Crawl_Right]	= new Animation(hedgehogTexture, hedgehogTexture->_animationNames.at(Crawl_Right));
	//_actionAnimation[Crawl_Bottom]	= new Animation(hedgehogTexture, hedgehogTexture->_animationNames.at(Crawl_Bottom));
	//_actionAnimation[Crawl_Left]	= new Animation(hedgehogTexture, hedgehogTexture->_animationNames.at(Crawl_Left));

	_action = HedgehogAction::Crawl_Top;
	_currentAnimation = _actionAnimation[_action];
	_velX = HEDGEHOG_VEL;
}
void Hedgehog::Update(int deltaTime)
{
	switch (_action)
	{
	case HedgehogAction::Crawl_Top:		//crawl right
		_velX = HEDGEHOG_VEL;
		_velY = 0;
		break;
	case HedgehogAction::Crawl_Right:	//crawl bottom
		_velX = 0;
		_velY = -HEDGEHOG_VEL;
		break;
	case HedgehogAction::Crawl_Bottom:	//crawl left
		_velX = -HEDGEHOG_VEL;
		_velY = 0;
		break;
	case HedgehogAction::Crawl_Left:	//crawl top
		_velX = 0;
		_velY = HEDGEHOG_VEL;
		break;
	}

	//update position
	if (!_beAttacking)
	{
		_posX += _velX * deltaTime;
		_posY += _velY * deltaTime;

	}
	else
		_beAttacking--;


}

void Hedgehog::Update2(int deltaTime){

	if(enemyCheckExplode(deltaTime))
		return;

	//update animation
	//if be attacking then change animation
	/*int i = (bool)_beAttacking;*/
	if (!_beAttacking)
	{
		_currentAnimation = _actionAnimation[_action];
		_currentAnimation->Update(deltaTime);
	}
	else
	{
		_currentAnimation = _actionAnimation[_action + 4];
	}

}
Hedgehog::~Hedgehog(){}

void Hedgehog::handleCollision(map<int, GameObject*> objectList, float dt)
{
	FixPosition();
	bool OK = false;
	RECT a = this->getCollisionBound();
	//just collsion vs Wall
	for (auto it = objectList.begin(); it != objectList.end(); it++)
	{
		GameObject* object = it->second;

		if (object->getObjectID() == ObjectID::Ground_ID)
		{
			
			RECT b = object->getCollisionBound();
			Direction direction;
			//if (int i = IsCollideVsWall(this, object, direction, dt))
			if (int i = handleObjectCollision(this, object, direction, dt,false))
			{
				if (i == 2)
				{
					//change action
					switch (_action)
					{
					case HedgehogAction::Crawl_Top:
						_action = HedgehogAction::Crawl_Left;
						break;
					case HedgehogAction::Crawl_Right:
						_action = HedgehogAction::Crawl_Top;
						break;
					case HedgehogAction::Crawl_Bottom:
						_action = HedgehogAction::Crawl_Right;
						break;
					case HedgehogAction::Crawl_Left:
						_action = HedgehogAction::Crawl_Bottom;
						break;
					}
					OK = true;
				}
				else
					//has collided or is adjacent
				{
					////update
					//this->_posX += moveX;
					//this->_posY += moveY;
					OK = true;
				}
			}
		}
	}
	if (OK == false)
	{
		//change action
		switch (_action)
		{
		case HedgehogAction::Crawl_Top:
			_action = HedgehogAction::Crawl_Right;
			break;
		case HedgehogAction::Crawl_Right:
			_action = HedgehogAction::Crawl_Bottom;
			break;
		case HedgehogAction::Crawl_Bottom:
			_action = HedgehogAction::Crawl_Left;
			break;
		case HedgehogAction::Crawl_Left:
			_action = HedgehogAction::Crawl_Top;
			break;
		}
	}

}
void Hedgehog::FixPosition()
{
	//becase hedgehog size = 14x14

	switch (_action)
	{
	case HedgehogAction::Crawl_Top:		//foot touch wall => bottom always divisibility 16	
		_posY -= 7;
		_posY = round((double)_posY / 16) * 16;
		_posY += 7;
		break;
	case HedgehogAction::Crawl_Right:	
		_posX -= 7;
		_posX = round((double)_posX / 16) * 16;
		_posX += 7;
		break;
	case HedgehogAction::Crawl_Bottom:
		_posY = round((double)_posY / 16) * 16;
		_posY -= 7;
		break;
	case HedgehogAction::Crawl_Left:
		_posX += 7;
		_posX = round((double)_posX / 16) * 16;
		_posX -= 7;
		break;
	}
}

//int Hedgehog::IsCollideVsWall(GameObject* considerObject, GameObject* otherObject, Direction& direction, int dt)
//{
//	//Direction direction; //direction of collision of considerObject
//	float dxEntry = 0, dyEntry = 0;
//	float time = AABBCollision(considerObject, otherObject, direction, dxEntry, dyEntry, dt);
//	float moveX = 0, moveY = 0;
//	if (time < 1.0f) // will collision
//	{
//		// cản lại
//		considerObject->_posX += dxEntry;
//		considerObject->_posY += dyEntry;
//		//direction was valid
//		return 2;
//	}
//	else if (isCollidingEx(considerObject->getCollisionBound(), otherObject->getCollisionBound()))
//		//consider the case 2 object is colliding
//	{
//
//		return 1;
//	}
//	else //don't happen collision or a long time to happen
//	{
//		direction = Direction::None_Direction;
//		return 0;
//	}
//	// if direction != left or right => keep direction stable
//
//	//after above statement, 2 object is adjacent together
//}