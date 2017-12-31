#include "Bullet.h"
Bullet::Bullet(){};
Bullet::Bullet(BulletType bulletType, int x, int y, Direction direction, DWORD survivalTime) :GameObject(Bullet_ID, x, y, 0, 0){
	_bulletType = bulletType;
	_remainingTime = survivalTime;
	Texture2* bulletTexture = NULL;
	switch (bulletType)
	{
	case BulletType::BulletFromPlayer_Nomal:
		_hp = 1;
		_attack = 1;

		bulletTexture = TextureCollection::getInstance()->getTexture2(Bullet_ID);
		//flying
		_actionAnimation.push_back(new Animation(bulletTexture, "Normal:Flying"));
		//broken
		_beWoundingAnimation.push_back(new Animation(bulletTexture, "Normal:Broken"));
		break;
	case BulletType::BulletFromPlayer_Freeze:
		_hp = 1;
		_attack = 1;

		bulletTexture = TextureCollection::getInstance()->getTexture2(Bullet_ID);
		//flying
		_actionAnimation.push_back(new Animation(bulletTexture, "Freeze:Flying"));
		//broken
		_beWoundingAnimation.push_back(new Animation(bulletTexture, "Freeze:Broken"));
		break;
	case BulletType::BulletFromSkree:
		_hp = 1;
		_attack = 3;
		bulletTexture = TextureCollection::getInstance()->getTexture2(Skree_ID);
		//flying
		_actionAnimation.push_back(new Animation(bulletTexture, "BulletFromSkee"));
		//broken
		_beWoundingAnimation.push_back(new Animation(bulletTexture, "BulletFromSkee"));
		break;
	}
	



	this->_currentAnimation = _actionAnimation[0];
	//VEL base on direction
	switch (direction){
	case Direction::None_Direction:
		_velX = 0;
		_velY = 0;
		break;
	case Direction::Left_Direction:
		_velX = -BULLET_VEL;
		_velY = 0;
		break;
	case Direction::Top_Direction:
		_velX = 0;
		_velY = BULLET_VEL;
		break;
	case Direction::Right_Direction:
		_velX = BULLET_VEL;
		_velY = 0;
		break;
	case Direction::Bottom_Direction:
		_velX = 0;
		_velY = -BULLET_VEL;
		break;
	case Direction::TopLeft_Direction:
		_velX = -BULLET_VEL;
		_velY = BULLET_VEL;
		break;
	case Direction::TopRight_Direction:
		_velX = BULLET_VEL;
		_velY = BULLET_VEL;
		break;
	case Direction::BottomLeft_Direction:
		_velX = -BULLET_VEL;
		_velY = -BULLET_VEL;
		break;
	case Direction::BottomRight_Direction:
		_velX = BULLET_VEL;
		_velY = -BULLET_VEL;
		break;
	}

}
Bullet::~Bullet()
{
}
BulletType Bullet::getBulletType()
{
	return _bulletType;
}
void Bullet::UpdateActionAndVelocity(int deltaTime)
{
	//UPDATE ACTION
	//update remaining-time
	_remainingTime -= deltaTime;
	if (_remainingTime <= 0)
		SetObjectStatus(ObjectStatus::Died_OS);
	// specify object when HP = 0. Bewounding was defined before
	if (_hp <= 0)
		_objectStatus = ObjectStatus::Died_OS;

}

void Bullet::UpdateAnimationBaseOnStatus()
{
	// virtual void
	switch (_objectStatus)
	{
	case ObjectStatus::Survival_OS:
		_currentAnimation = _actionAnimation[0];
		break;
	case ObjectStatus::BeWounding_OS:
		_currentAnimation = _beWoundingAnimation[0];
		break;
	case ObjectStatus::Exploding_OS:
		break;
	case ObjectStatus::Died_OS:
		break;
	}
}
//void Bullet::Update2(int deltaTime)
//{
//	if (_hp <= 0)
//	{
//		SetObjectStatus(ObjectStatus::Died_OS);
//		_currentAnimation = _actionAnimation[1];
//	}
//		
//}
void Bullet::handleCollision(map<int, GameObject*> objectList, float deltaTime)
{
	switch (_bulletType)
	{
	case BulletType::BulletFromPlayer_Nomal:	// -HP enemy
		for (auto it = objectList.begin(); it != objectList.end(); it++)
		{
			GameObject* otherObject = it->second;
			if (otherObject->getObjectID() != ObjectID::Bullet_ID)
			{
				Direction direction;
				if (handleObjectCollision(this, otherObject, direction, deltaTime)) //collision 
				{
					switch (otherObject->getObjectID())
					{
					case ObjectID::Ground_ID:	//bullet collide vs wall
						//bullet will be broken
						this->BeWounded();
						break;
					case ObjectID::BubbleDoor_ID:
						this->BeWounded();
						otherObject->BeWounded();
						break;

						//enemy
					case ObjectID::Zoomer_ID:
					case ObjectID::Skree_ID:
					case ObjectID::Zeb_ID:
						this->BeWounded();
						otherObject->BeWounded();
						break;
					case ObjectID::Ripper_ID:
						this->BeWounded();
						//otherObject->BeWounded(); - Ripper isn't wounded by bullet
						break;
					}
				}
			}
		}
		break;
	case BulletType::BulletFromPlayer_Freeze:	//freezing enemy

		break;
	case BulletType::BulletFromSkree:			//will check collision in handleCollision function of Player
		break;
	}
	
	
}