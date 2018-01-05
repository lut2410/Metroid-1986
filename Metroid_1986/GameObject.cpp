#include "GameObject.h"
GameObject::GameObject(void){}
GameObject::~GameObject(void){}
GameObject::GameObject(ObjectID objectID, int posX, int posY, float velX, float velY){
	_objectStatus = ObjectStatus::Survival_OS;
	_remainingWoundingTime = 0;
	_remainingExplodeTime = -1;
	_hp = 0;
	_attack = 0;
	_objectID = objectID;
	_posX = posX;
	_posY = posY;
	_velX = velX;
	_velY = velY;

	Texture2* explode = NULL;
	explode = TextureCollection::getInstance()->getTexture2(ExplodeObject_ID);
	explodingAnimation = new Animation(explode, explode->_animationNames.at(0));

}
D3DXVECTOR2 GameObject::getPositionOfGun()
{
	return D3DXVECTOR2{ 0, 0 };
}
D3DXVECTOR2 GameObject::getPositionOfGun2()
{
	return D3DXVECTOR2{ 0, 0 };
}
RECT GameObject::getCollisionBound(){
	Box  objectBox = _currentAnimation->getCurrentSpriteSize();

	if (_objectID == ObjectID::Zoomer_ID)
		objectBox = { 0, 0, 14, 14 };
	RECT objectBound = { _posX - objectBox.width / 2,		//left
		_posY + objectBox.height / 2,						//top
		_posX + objectBox.width / 2,						//right
		_posY - objectBox.height / 2 };						//bottom
	return objectBound;
};
D3DXVECTOR2 GameObject::getVelocity(){
	return D3DXVECTOR2(_velX, _velY);
};
ObjectID GameObject::getObjectID(){
	return _objectID;
}
ObjectType GameObject::getObjectType()
{

	switch (_objectID)
	{
		//nelative of wall
	case Ground_ID:
	case BubbleDoor_ID:
	case ZebProductionPipe_ID:
	case WeakGround_ID:
		return ObjectType::RelativesWithWall_OT;
		break;
		//player
	case Player_ID:
		return ObjectType::Player_OT;
		break;
	case Bullet_ID:
		return ObjectType::Bullet_OT;
		break;
		//enemy
	case Fire_ID:
	case Zoomer_ID:
	case Skree_ID:
	case Ripper_ID:
	case Zeb_ID:
	case Waver_ID:
	case Rio_ID:
	case ExplodeObject_ID:
		return ObjectType::Enemy_OT;
		break;
		//boss
	case Ridley_ID:
	case Kraid_ID:
		return ObjectType::Boss_OT;
		break;
		//item
	case HPTonic_ID:
	case MaruMari_ID:
	case LongBeam_ID:
	case IceBeam_ID:
	case WaveBeam_ID:
	case MissibleRocket_ID:
	case Bomb_ID:
	case EnergyTank_ID:
	case Rocket_ID:
		return ObjectType::Item_OT;
		break;

	}
}
DirectionOfFace GameObject::getDirectionOfFace()
{
	return _directionOfFace;
}
int GameObject::getAttackDame()
{
	return _attack;
}
int GameObject::getHP()
{
	return _hp;
}
bool GameObject::getActiveEnemy()
{
	return _activeEnemy;
}
int GameObject::getRemainingTimeToShoot()
{
	return _remainingTimeToShoot;
}
void GameObject::SetRemainingTimeToShoot(int time)
{
	_remainingTimeToShoot = time;
}
int GameObject::getRemainingTimeToShoot2()
{
	return _remainingTimeToShoot2;
}
void GameObject::SetRemainingTimeToShoot2(int time)
{
	_remainingTimeToShoot2 = time;
}
BulletType GameObject::getBulletType()
{
	return BulletType::IsntBullet;
}
ObjectStatus GameObject::getObjectStatus()
{
	return _objectStatus;
}
void GameObject::SetObjectStatus(ObjectStatus objectStatus)
{
	_objectStatus = objectStatus;
}

void GameObject::SpecifyStatusWhenHP0()
{
	if (_hp <= 0)
	{
		//enemy will 1 times to explode
		if (_objectStatus != ObjectStatus::Exploding_OS)
		{
			_objectStatus = ObjectStatus::Exploding_OS;
			_remainingExplodeTime = EXPLODE_FRAMES;
			if (getObjectType() == Enemy_OT)
			{
				GameSound* s = GameSound::getInstance();
				s->play(SOUND_EXPLODE, false);
			}
			else if (getObjectType() == Player_OT)
			{
				GameSound* s = GameSound::getInstance();
				s->play(SOUND_DIE, false);
			}
		}
	}
}
void GameObject::UpdateStatus()
{
	// specify object when HP = 0. Bewounding was defined before
	SpecifyStatusWhenHP0();

	switch (_objectStatus)
	{
		case ObjectStatus::BeWounding_OS:
			if (_remainingWoundingTime > 0)
				_remainingWoundingTime--;
			else
				_objectStatus = ObjectStatus::Survival_OS;
			break;
		case ObjectStatus::BeFreezing_OS:
			if (_remainingFreezingTime > 0)
				_remainingFreezingTime--;
			else
				_objectStatus = ObjectStatus::Survival_OS;
			break;
		case ObjectStatus::Exploding_OS:
			if (_remainingExplodeTime > 0)
				_remainingExplodeTime--;
			else
				_objectStatus = ObjectStatus::Died_OS;
			break;
		case ObjectStatus::Died_OS:
			//scene: gameover
			break;
	}

}
void GameObject::UpdateActionAndVelocity(int deltaTime)
{
}
void GameObject::Update(int deltaTime)
{	
	//if (getObjectType() == ObjectType::RelativesWithWall_OT || getObjectType() == ObjectType::Item_OT)
	//	//ground and its relative can't move
	//	return;

	//update status
	if (getObjectType() == ObjectType::Enemy_OT || getObjectType() == ObjectType::Boss_OT)
		UpdateStatus();
	//Update action and velocity
	UpdateActionAndVelocity(deltaTime);
	//update position
	if (_objectStatus == Survival_OS
		|| getObjectType() == ObjectType::Boss_OT )
	{
		_posX += _velX * deltaTime;
		_posY += _velY * deltaTime;
	}

}
void GameObject::UpdateAnimationBaseOnStatus()
{
	// virtual void
	switch (_objectStatus)
	{
	case ObjectStatus::Survival_OS:
		//_currentAnimation = _actionAnimation[_action];
		break;
	case ObjectStatus::BeWounding_OS:
		//_currentAnimation = _beWoundingAnimation[_action];
		break;
	case ObjectStatus::Exploding_OS:
		//_currentAnimation = explodingAnimation;
		break;
	case ObjectStatus::Died_OS:
		break;
	}
}
void GameObject::Update2(int deltaTime)
{
	if (getObjectType() == ObjectType::RelativesWithWall_OT)
		//ground and its relative is drawn in background
		return;
	UpdateAnimationBaseOnStatus();

	if (_objectStatus == ObjectStatus::Survival_OS || _objectStatus == ObjectStatus::Exploding_OS
		||getObjectType()==ObjectType::Boss_OT)
		_currentAnimation->Update(deltaTime);
	//update, use for the case object status is changed to BeFreezing
	_currentIndexOfAnimation = _currentAnimation->getCurrentFrameIndex();
}
void GameObject::Draw(Camera* camera){
	
	//if (getObjectType() == ObjectType::RelativesWithWall_OT )
	//	//ground and its relative has drawn in background
	//	return;

	D3DXVECTOR2 center = camera->Transform(_posX, _posY);

	switch (_directionOfFace)
	{
	case DirectionOfFace::Neutral:
	case DirectionOfFace::Right:
	
		_currentAnimation->Draw(center.x, center.y);
		break;
	case DirectionOfFace::Left:
		_currentAnimation->DrawFlipHorizontal(center.x, center.y);
		break;
	}

	//_currentAnimation->Draw(center.x, center.y);
}
void GameObject::handleCollision(map<int, GameObject*> objectList, float dt)
{

}
void GameObject::handleCollision(int playerX, int playerY, float dt)
{

}
void GameObject::BeWounded(int lossHP)
{
	SetObjectStatus(ObjectStatus::BeWounding_OS);
	if (getObjectType()!=ObjectType::Boss_OT)
		//boss: wounding isn't stop
		_remainingWoundingTime = WOUNDED_FRAMES;
	_hp -= lossHP;

	if (_objectID == Ripper_ID)
	{
		GameSound* s = GameSound::getInstance();
		s->play(SOUND_HIT_RIPPER);
	}
	else
	{
		GameSound* s = GameSound::getInstance();
		s->play(SOUND_HIT_ENEMY);
	}

	
}
void GameObject::BeFreezed(int lossHP)
{
	SetObjectStatus(ObjectStatus::BeFreezing_OS);
	if (getObjectType()==ObjectType::Boss_OT)
		_remainingFreezingTime = 1;
	else
		_remainingFreezingTime = FREEZED_FRAMES;
	_hp -= lossHP;
	
	if (getBulletType() != BulletType::IsntBullet)
	{
		_remainingFreezingTime = 5 * FREEZED_FRAMES;
		//update survival time
		_remainingTime += 30* _remainingFreezingTime;
	}

}