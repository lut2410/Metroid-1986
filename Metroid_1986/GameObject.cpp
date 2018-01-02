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

RECT GameObject::getCollisionBound(){
	Box  objectBox = _currentAnimation->getCurrentSpriteSize();
	//objectBox.width -= 2;
	//objectBox.height -= 2;

	if (_objectID == ObjectID::Zoomer_ID)
		objectBox = { 0, 0, 14, 14 };
	if (_objectID == ObjectID::BubbleDoor_ID)
		int i = 0;
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
	case Gate_ID:
	case BubbleDoor_ID:
	case ZebProductionPipe:
		return ObjectType::RelativesWithWall_OT;
		break;
		//player
	case Player_ID:
	case Bullet_ID:
		return ObjectType::Player_OT;
		break;
		//enemy
	case Zoomer_ID:
	case Skree_ID:
	case Ripper_ID:
	case Zeb_ID:
	case Waver_ID:
	case Rio_ID:
	case ExplodeObject_ID:
		return ObjectType::Enemy_OT;
		break;
		//item
	case HPTonic_ID:
	case MaruMari_ID:
		return ObjectType::Item_OT;
		break;

	}
}
int GameObject::getAttackDame()
{
	return _attack;
}
int GameObject::getHP()
{
	return _hp;
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
	if (getObjectType() == ObjectType::RelativesWithWall_OT || getObjectType() == ObjectType::Item_OT)
		//ground and its relative can't move
		return;

	//update status
	if(getObjectType()==ObjectType::Enemy_OT)
		UpdateStatus();
	//Update action and velocity
	UpdateActionAndVelocity(deltaTime);
	//update position
	if (_objectStatus == Survival_OS)
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

	if (_objectStatus==ObjectStatus::Survival_OS||_objectStatus==ObjectStatus::Exploding_OS)
		_currentAnimation->Update(deltaTime);
	//update, use for the case object status is changed to BeFreezing
	_currentIndexOfAnimation = _currentAnimation->getCurrentFrameIndex();
}
void GameObject::Draw(Camera* camera){
	
	if (getObjectType() == ObjectType::RelativesWithWall_OT)
		//ground and its relative has drawn in background
		return;
	D3DXVECTOR2 center = camera->Transform(_posX, _posY);
	_currentAnimation->Draw(center.x, center.y);
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
	_remainingWoundingTime = WOUNDED_FRAMES;
	_hp -= lossHP;
}
void GameObject::BeFreezed(int lossHP)
{
	SetObjectStatus(ObjectStatus::BeFreezing_OS);
	_remainingFreezingTime = FREEZED_FRAMES;
	_hp -= lossHP;
}