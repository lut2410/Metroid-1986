#include "Bullet.h"
Bullet::Bullet(){};
Bullet::Bullet(BulletType bulletType, int x, int y, Direction direction, DWORD survivalTime) :GameObject(Bullet_ID, x, y, 0, 0){
	BULLET_VEL = 0.2f;	//delfault
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
	case BulletType::BulletFromRidley:
		BULLET_VEL = 0.1f;
		_hp = 10;
		_attack = 8;
		bulletTexture = TextureCollection::getInstance()->getTexture2(Ridley_ID);
		//flying
		_actionAnimation.push_back(new Animation(bulletTexture, "Ball:Flying"));
		//broken
		_beWoundingAnimation.push_back(new Animation(bulletTexture, "Ball:Flying"));
		//freeze
		_beFreezingAnimation.push_back(new Animation(bulletTexture, "Ball:BeFreezing"));
		break;
	case BulletType::BulletFromKraid_Boomerang:
		BULLET_VEL = 0.1f;
		_hp = 5;
		_attack = 8;
		bulletTexture = TextureCollection::getInstance()->getTexture2(Kraid_ID);
		//flying
		_actionAnimation.push_back(new Animation(bulletTexture, "Boomerang:Fly"));
		//broken
		_beWoundingAnimation.push_back(new Animation(bulletTexture, "Boomerang:Fly"));
		//freeze
		_beFreezingAnimation.push_back(new Animation(bulletTexture, "Boomerang:Befreezing"));
		break;
	case BulletType::BulletFromKraid_Rocket:
		if (direction == Direction::Left_Direction)
			_directionOfFace = DirectionOfFace::Left;
		else 
			_directionOfFace = DirectionOfFace::Right;
		BULLET_VEL = 0.1f;
		_hp = 5;
		_attack = 8;
		bulletTexture = TextureCollection::getInstance()->getTexture2(Kraid_ID);
		//flying
		_actionAnimation.push_back(new Animation(bulletTexture, "Rocket:Fly"));
		//broken
		_beWoundingAnimation.push_back(new Animation(bulletTexture, "Rocket:Fly"));
		//freeze
		_beFreezingAnimation.push_back(new Animation(bulletTexture, "Rocket:Freezing"));
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

	if (_bulletType == BulletType::BulletFromRidley || _bulletType == BulletType::BulletFromKraid_Boomerang)
	{
		//_velX /= 2;
		_velY = _velY * 3;
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

	switch (_bulletType)
	{
	case BulletType::BulletFromRidley:
	case BulletType::BulletFromKraid_Boomerang:
		_velY += BULLET_ACCELERATION;
		break;

	}
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
		_currentAnimation->SetIndex(_currentIndexOfAnimation);
		break;
	case ObjectStatus::BeFreezing_OS:
		_currentAnimation = _beFreezingAnimation[0];
		_currentAnimation->SetIndex(_currentIndexOfAnimation);
	case ObjectStatus::Exploding_OS:
		break;
	case ObjectStatus::Died_OS:
		break;
	}
}
void Bullet::Draw(Camera* camera)
{
	D3DXVECTOR2 center = camera->Transform(_posX, _posY);

	switch (_directionOfFace)
	{
	case DirectionOfFace::Right:
		_currentAnimation->DrawFlipHorizontal(center.x, center.y);
		break;
	case DirectionOfFace::Neutral:
	case DirectionOfFace::Left:
		_currentAnimation->Draw(center.x, center.y);
		break;
	}
}
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
					case ObjectID::Ripper_ID:
					case ObjectID::Rio_ID:
						this->BeWounded();
						otherObject->BeWounded();
						break;
					case ObjectID::Waver_ID:
						this->BeWounded();
						break;
						//boss
					case ObjectID::Ridley_ID:
						this->BeWounded();
						otherObject->BeWounded();
						break;
					}
				}
			}
		}
		break;
	case BulletType::BulletFromPlayer_Freeze:	//freezing enemy
		for (auto it = objectList.begin(); it != objectList.end(); it++)
		{
			GameObject* otherObject = it->second;
			if (otherObject->getObjectID() != ObjectID::Bullet_ID || otherObject->getBulletType() != BulletType::BulletFromPlayer_Freeze)
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
					case ObjectID::Bullet_ID://enemy bullet => freezing
						this->BeWounded();
						otherObject->BeFreezed();
						break;
						//enemy
					case ObjectID::Zoomer_ID:
					case ObjectID::Skree_ID:
					case ObjectID::Zeb_ID:
					case ObjectID::Ripper_ID:
					case ObjectID::Waver_ID:
						this->BeWounded();
						otherObject->BeFreezed();
						break;
						//boss
					case ObjectID::Ridley_ID:
					case ObjectID::Kraid_ID:
						this->BeWounded();
						otherObject->BeFreezed();
						break;
					}
				}
			}
		}
		break;
	case BulletType::BulletFromPlayer_Rocket:
		break;
	case BulletType::BulletFromSkree:			//will check collision in handleCollision function of Player
		break;
	case BulletType::BulletFromRidley:	//collision with wall
	case BulletType::BulletFromKraid_Boomerang:
		for (auto it = objectList.begin(); it != objectList.end(); it++)
		{
			GameObject* otherObject = it->second;
			if (otherObject->getObjectType() == ObjectType::RelativesWithWall_OT)
			{
				Direction direction;
				
				if (handleObjectCollision(this, otherObject, direction, deltaTime)) 
				{
					switch (direction)
					{
					case Direction::Left_Direction:
					case Direction::Right_Direction:
						_velX = -_velX;
						break;
					case Direction::Bottom_Direction:
						_velY = -_velY * 9 / 10;
						break;
						break;
					}
				}
			}
		}
		break;
	case BulletType::BulletFromKraid_Rocket:
		for (auto it = objectList.begin(); it != objectList.end(); it++)
		{
			GameObject* otherObject = it->second;
			if (otherObject->getObjectType() == ObjectType::RelativesWithWall_OT)
			{
				Direction direction;

				if (handleObjectCollision(this, otherObject, direction, deltaTime))
				{
					this->BeWounded(this->_hp);	//destroy
				}
			}
		}
		break;
	}
	
	
}