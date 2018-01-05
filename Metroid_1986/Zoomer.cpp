#include "Zoomer.h"
Zoomer::Zoomer(){}
Zoomer::Zoomer(int x, int y, int type) :GameObject(Zoomer_ID, x, y, 0, 0){

	Texture2* ZoomerTexture = NULL;
	ZoomerTexture = TextureCollection::getInstance()->getTexture2(Zoomer_ID);

	if (type == 1)
	{
		_hp = 3;
		_attack = 8;
		OBJECT_VEL = 0.0625f;
		_actionAnimation.push_back( new Animation(ZoomerTexture,"Type1:Top"));
		_actionAnimation.push_back(new Animation(ZoomerTexture, "Type1:Right"));
		_actionAnimation.push_back(new Animation(ZoomerTexture, "Type1:Bottom"));
		_actionAnimation.push_back(new Animation(ZoomerTexture, "Type1:Left"));
	}
	else //type 2
	{
		_hp = 5;
		_attack = 8;
		OBJECT_VEL = 0.0625f;
		_actionAnimation.push_back(new Animation(ZoomerTexture, "Type2:Top"));
		_actionAnimation.push_back(new Animation(ZoomerTexture, "Type2:Right"));
		_actionAnimation.push_back(new Animation(ZoomerTexture, "Type2:Bottom"));
		_actionAnimation.push_back(new Animation(ZoomerTexture, "Type2:Left"));
	}
	//
	_beWoundingAnimation.push_back(new Animation(ZoomerTexture, "BeWounding:Top"));
	_beWoundingAnimation.push_back(new Animation(ZoomerTexture, "BeWounding:Right"));
	_beWoundingAnimation.push_back(new Animation(ZoomerTexture, "BeWounding:Bottom"));
	_beWoundingAnimation.push_back(new Animation(ZoomerTexture, "BeWounding:Left"));
	//
	_beFreezingAnimation.push_back(new Animation(ZoomerTexture, "BeFreezing:Top"));
	_beFreezingAnimation.push_back(new Animation(ZoomerTexture, "BeFreezing:Right"));
	_beFreezingAnimation.push_back(new Animation(ZoomerTexture, "BeFreezing:Bottom"));
	_beFreezingAnimation.push_back(new Animation(ZoomerTexture, "BeFreezing:Left"));
	//

	_action = ZoomerAction::Crawl_Top;
	_currentAnimation = _actionAnimation[_action];
	_velX = OBJECT_VEL;
}
void Zoomer::UpdateActionAndVelocity(int deltaTime)
{
	//zoomer update action base on collision (in handleCollision)
	//not here
	switch (_action)
	{
	case ZoomerAction::Crawl_Top:		//crawl right
		_velX = OBJECT_VEL;
		_velY = 0;
		break;
	case ZoomerAction::Crawl_Right:	//crawl bottom
		_velX = 0;
		_velY = -OBJECT_VEL;
		break;
	case ZoomerAction::Crawl_Bottom:	//crawl left
		_velX = -OBJECT_VEL;
		_velY = 0;
		break;
	case ZoomerAction::Crawl_Left:	//crawl top
		_velX = 0;
		_velY = OBJECT_VEL;
		break;
	}
}

void Zoomer::UpdateAnimationBaseOnStatus()
{
	switch (_objectStatus)
	{
	case ObjectStatus::Survival_OS:
		_currentAnimation = _actionAnimation[_action];
		break;
	case ObjectStatus::BeWounding_OS:
		_currentAnimation = _beWoundingAnimation[_action];
		_currentAnimation->SetIndex(_currentIndexOfAnimation);
		break;
	case ObjectStatus::BeFreezing_OS:
		_currentAnimation = _beFreezingAnimation[_action];
		_currentAnimation->SetIndex(_currentIndexOfAnimation);
		break;
	case ObjectStatus::Exploding_OS:
		_currentAnimation = explodingAnimation;
		break;
	case ObjectStatus::Died_OS:
		break;
	}
}
Zoomer::~Zoomer(){}

void Zoomer::handleCollision(map<int, GameObject*> objectList, float dt)
{
	FixPosition();
	bool OK = false;
	RECT a = this->getCollisionBound();
	//just collsion vs Wall
	for (auto it = objectList.begin(); it != objectList.end(); it++)
	{
		GameObject* object = it->second;

		if (object->getObjectType()==ObjectType::RelativesWithWall_OT)
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
					case ZoomerAction::Crawl_Top:
						_action = ZoomerAction::Crawl_Left;
						break;
					case ZoomerAction::Crawl_Right:
						_action = ZoomerAction::Crawl_Top;
						break;
					case ZoomerAction::Crawl_Bottom:
						_action = ZoomerAction::Crawl_Right;
						break;
					case ZoomerAction::Crawl_Left:
						_action = ZoomerAction::Crawl_Bottom;
						break;
					}
					OK = true;
					break;
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
		case ZoomerAction::Crawl_Top:
			_action = ZoomerAction::Crawl_Right;
			break;
		case ZoomerAction::Crawl_Right:
			_action = ZoomerAction::Crawl_Bottom;
			break;
		case ZoomerAction::Crawl_Bottom:
			_action = ZoomerAction::Crawl_Left;
			break;
		case ZoomerAction::Crawl_Left:
			_action = ZoomerAction::Crawl_Top;
			break;
		}
	}

}
void Zoomer::FixPosition()
{
	//becase Zoomer size = 14x14

	switch (_action)
	{
	case ZoomerAction::Crawl_Top:		//foot touch wall => bottom always divisibility 16	
		_posY -= 7;
		_posY = round((double)_posY / 8) * 8;
		_posY += 7;
		break;
	case ZoomerAction::Crawl_Right:	
		_posX -= 7;
		_posX = round((double)_posX / 8) * 8;
		_posX += 7;
		break;
	case ZoomerAction::Crawl_Bottom:
		_posY += 7;
		_posY = round((double)_posY / 8) * 8;
		_posY -= 7;
		break;
	case ZoomerAction::Crawl_Left:
		_posX += 7;
		_posX = round((double)_posX / 8) * 8;
		_posX -= 7;
		break;
	}
}