#include "Hedgehog.h"
Hedgehog::Hedgehog(){}
Hedgehog::Hedgehog(int x, int y) :GameObject(Hedgehog_ID, x, y,0,0){
	_hp = 3;
	_attack = 8;
	Texture2* hedgehogTexture = TextureCollection::getInstance()->getTexture2(Hedgehog_ID);

	_actionAnimation.resize(4);
	_actionAnimation[Crawl_Top]		= new Animation(hedgehogTexture, hedgehogTexture->_animationNames.at(Crawl_Top));
	_actionAnimation[Crawl_Right]	= new Animation(hedgehogTexture, hedgehogTexture->_animationNames.at(Crawl_Right));
	_actionAnimation[Crawl_Bottom]	= new Animation(hedgehogTexture, hedgehogTexture->_animationNames.at(Crawl_Bottom));
	_actionAnimation[Crawl_Left]	= new Animation(hedgehogTexture, hedgehogTexture->_animationNames.at(Crawl_Left));

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
	_posX += _velX * deltaTime;
	_posY += _velY * deltaTime;



}

void Hedgehog::Update2(int deltaTime){
	_currentAnimation = _actionAnimation[_action];
	_currentAnimation->Update(deltaTime);
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
			if (int i = IsCollideVsWall(this, object, direction, dt))
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

int Hedgehog::IsCollideVsWall(GameObject* considerObject, GameObject* otherObject, Direction& direction, int dt)
{
	//Direction direction; //direction of collision of considerObject
	float dxEntry = 0, dyEntry = 0;
	float time = AABBCollision(considerObject, otherObject, direction, dxEntry, dyEntry, dt);
	float moveX = 0, moveY = 0;
	if (time < 1.0f) // will collision
	{
		// cản lại
		//considerObject->_posX += dxEntry;
		considerObject->_posY += dyEntry;
		//direction was valid
		return 2;
	}
	else if (isCollidingEx(considerObject->getCollisionBound(), otherObject->getCollisionBound()))
		//consider the case 2 object is colliding
	{
		//if (moveX > 0)
		//	direction = Direction::Left_Direction;
		//else if (moveX<0)
		//	direction = Direction::Right_Direction;
		//else if (moveY>0)
		//	direction = Direction::Bottom_Direction;
		//else if (moveY < 0)
		//	direction = Direction::Top_Direction;
		//else //moveX=0&moveY=0
		//	direction = Direction::Adjacent_Direction; //2 object is adjacent together
		return 1;
	}
	else //don't happen collision or a long time to happen
	{
		direction = Direction::None_Direction;
		return 0;
	}
	// if direction != left or right => keep direction stable

	//after above statement, 2 object is adjacent together
}