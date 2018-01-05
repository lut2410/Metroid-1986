#include "Bullet.h"
Bullet::Bullet(){};
Bullet::Bullet(BulletType bulletType, int x, int y, Direction direction, DWORD survivalTime) :GameObject(Bullet_ID, x, y, 0, 0){
	BULLET_VEL = 0.2f;	//delfault
	_bulletType = bulletType;
	_remainingTime = survivalTime;
	Texture2* bulletTexture = NULL;
	GameSound* s = GameSound::getInstance();
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
		s->play(SOUND_SHOOT_NORMAL, false);
		break;
	case BulletType::BulletFromPlayer_Freeze:
		_hp = 1;
		_attack = 1;

		bulletTexture = TextureCollection::getInstance()->getTexture2(Bullet_ID);
		//flying
		_actionAnimation.push_back(new Animation(bulletTexture, "Freeze:Flying"));
		//broken
		_beWoundingAnimation.push_back(new Animation(bulletTexture, "Freeze:Broken"));
		s->play(SOUND_SHOOT_ICE, false);
		break;
	case BulletType::BulletFromPlayer_Wave:
		_hp = 1;
		_attack = 1;
		if (direction == Direction::Top_Direction)
			_originpos = _posX;
		else
			_originpos = _posY;

		bulletTexture = TextureCollection::getInstance()->getTexture2(Bullet_ID);
		//flying
		_actionAnimation.push_back(new Animation(bulletTexture, "Wave"));
		//broken
		_beWoundingAnimation.push_back(new Animation(bulletTexture, "Wave"));

		s->play(SOUND_SHOOT_WAVE, false);
		break;
	case BulletType::BulletFromPlayer_Rocket:
		_hp = 1;
		_attack = 5;
		_remainingTime = 800;// independent in player has longbeam yet
		bulletTexture = TextureCollection::getInstance()->getTexture2(Bullet_ID);
		//flying
		if (direction == Direction::Top_Direction)
			_actionAnimation.push_back(new Animation(bulletTexture, "Rocket:Top"));
		else
		{
			if (direction == Direction::Right_Direction)
				_directionOfFace = DirectionOfFace::Right;
			else //left
				_directionOfFace = DirectionOfFace::Left;
			_actionAnimation.push_back(new Animation(bulletTexture, "Rocket:Right"));
		}
			
		
		//broken
		_beWoundingAnimation.push_back(new Animation(bulletTexture, "Rocket:Broken"));

		s->play(SOUND_SHOOT_ROCKET, false);
		break;
	case BulletType::Bomb:
		_hp = 1;
		_attack = 5;
		_remainingTime = 800;// independent in player has longbeam yet
		bulletTexture = TextureCollection::getInstance()->getTexture2(Bullet_ID);
		_actionAnimation.push_back(new Animation(bulletTexture, "Bomb"));

		////broken
		_beWoundingAnimation.push_back(new Animation(bulletTexture, "Bomb"));

		s->play(SOUND_SET_BOMB);
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
		_velY = _velY * 5/2;
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
	{
		if (_bulletType == BulletType::Bomb) //has explode
			_hp = 0;
		else
			SetObjectStatus(ObjectStatus::Died_OS);
	}
		

	// specify object when HP = 0. Bewounding was defined before
	if (_bulletType==BulletType::Bomb) //has explode
		UpdateStatus();
	else
	{
		if (_hp <= 0)
			_objectStatus = ObjectStatus::Died_OS;
	}
	

	float angle;
	switch (_bulletType)
	{
	case BulletType::BulletFromPlayer_Nomal:
	case BulletType::BulletFromPlayer_Freeze:
	case BulletType::BulletFromPlayer_Rocket:
		//vel = const
		break;
	case BulletType::BulletFromPlayer_Wave:
		_localTime += deltaTime;
		if (_localTime >= WAVEBULLET_TIME_A_CYCLE)
			_localTime -= WAVEBULLET_TIME_A_CYCLE;
		angle = ((float)_localTime / WAVEBULLET_TIME_A_CYCLE - (float)1 / 4)* PI;
		if (_velX==0)// direct to top
			_posX = _originpos + 10 * sin(angle);
		else
			_posY = _originpos + 10* sin(angle);
		break;
	case BulletType::Bomb:
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
		if (_bulletType == BulletType::Bomb)
			_currentAnimation = explodingAnimation;
		break;
	case ObjectStatus::Died_OS:
		break;
	}
}
void Bullet::handleCollision(map<int, GameObject*> objectList, float deltaTime)
{
	switch (_bulletType)
	{
	case BulletType::BulletFromPlayer_Nomal:	// -HP enemy
	case BulletType::BulletFromPlayer_Rocket:
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
					case ObjectID::WeakGround_ID:	//bullet collide vs wall
						//bullet will be broken
						this->BeWounded();
						otherObject->BeWounded(_attack);
						break;
					case ObjectID::BubbleDoor_ID:
						this->BeWounded();
						if (otherObject->getHP() > 1)//type 2:red
						{
							if (_bulletType == BulletType::BulletFromPlayer_Rocket)
								otherObject->BeWounded(1);
						}
						else //type 1
							otherObject->BeWounded(_attack);
						break;

						//enemy
					case ObjectID::Zoomer_ID:
					case ObjectID::Skree_ID:
					case ObjectID::Zeb_ID:
					case ObjectID::Ripper_ID:
					case ObjectID::Rio_ID:
					case ObjectID::Waver_ID:
						this->BeWounded();
						otherObject->BeWounded(_attack);
						break;
						//boss
					case ObjectID::Ridley_ID:
						this->BeWounded();
						otherObject->BeWounded(_attack);
						break;
					}
				}
			}
		}
		break;
	case BulletType::BulletFromPlayer_Wave:	// -HP enemy
		for (auto it = objectList.begin(); it != objectList.end(); it++)
		{
			GameObject* otherObject = it->second;
			if (otherObject->getObjectID() != ObjectID::Bullet_ID&&otherObject->getObjectType()!=ObjectType::RelativesWithWall_OT)
			{
				Direction direction;
				if (handleObjectCollision(this, otherObject, direction, deltaTime)) //collision 
				{
					switch (otherObject->getObjectID())
					{

						//enemy
					case ObjectID::Zoomer_ID:
					case ObjectID::Skree_ID:
					case ObjectID::Ripper_ID:
					case ObjectID::Zeb_ID:
					case ObjectID::Waver_ID:
					case ObjectID::Rio_ID:
						this->BeWounded();
						otherObject->BeWounded();
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
					case ObjectID::Ripper_ID:
					case ObjectID::Zeb_ID:
					case ObjectID::Waver_ID:
					case ObjectID::Rio_ID:
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

	case BulletType::BulletFromSkree:			//will check collision in handleCollision function of Player
		break;
	case BulletType::BulletFromRidley:	//collision with wall
		break;
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
	case BulletType::Bomb:
		for (auto it = objectList.begin(); it != objectList.end(); it++)
		{
			GameObject* otherObject = it->second;
			if (_objectStatus == Survival_OS)
			{
				if (otherObject->getObjectType() == ObjectType::RelativesWithWall_OT)
				{
					Direction direction;

					if (handleObjectCollision(this, otherObject, direction, deltaTime))
					{
						if (direction == Direction::Bottom_Direction)
						{
							_velY = 0;
						}
					}
				}
			}
			else if(_objectStatus == Exploding_OS)
			{
				Direction direction;
				if (handleObjectCollision(this, otherObject, direction, deltaTime,false))
				switch (otherObject->getObjectID())
				{
				case ObjectID::WeakGround_ID:	//bullet collide vs wall
					otherObject->BeWounded(_attack);
					break;
				case ObjectID::BubbleDoor_ID:
					otherObject->BeWounded(_attack);
					break;
				case ObjectID::Bullet_ID:
					break;
					//enemy
				case ObjectID::Zoomer_ID:
				case ObjectID::Skree_ID:
				case ObjectID::Ripper_ID:
				case ObjectID::Zeb_ID:
				case ObjectID::Waver_ID:
				case ObjectID::Rio_ID:
					//boss
				case ObjectID::Ridley_ID:
				case ObjectID::Kraid_ID:
					otherObject->BeWounded(_attack);
					break;


				}
			}
		}
		break;
	}
	
	
}