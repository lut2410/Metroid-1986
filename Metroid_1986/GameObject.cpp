#include "GameObject.h"
GameObject::GameObject(void){}
GameObject::~GameObject(void){}
GameObject::GameObject(ObjectID objectID, int posX, int posY, float velX, float velY){
	_survive = true;
	_beAttacking = 0;
	_hp = 0;
	_attack = 0;
	_objectID = objectID;
	_isRelativeWithGround = false;
	_posX = posX;
	_posY = posY;
	_velX = velX;
	_velY = velY;

	Texture2* explode = NULL;
	explode = TextureCollection::getInstance()->getTexture2(ExplodeObject_ID);
	expoldeAnimation = new Animation(explode, explode->_animationNames.at(0));
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
bool GameObject::isRelativeWithGround()
{
	return _isRelativeWithGround;
}
int GameObject::getAttackDame()
{
	return _attack;
}
bool GameObject::isSurvive()
{
	return _survive;
}
void GameObject::SetDestroy()
{
	_survive = false;
}
void GameObject::Update(int deltaTime)
{

	if (_isRelativeWithGround == true)
		//ground and its relative can't move
		return;
	//update position
	_posX += _velX * deltaTime;
	_posY += _velY * deltaTime;
}
void GameObject::Update2(int deltaTime)
{

}
void GameObject::Draw(Camera* camera){
	
	if (_isRelativeWithGround == true)
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
	_beAttacking = WOUNDED_FRAMES;
	_hp -= lossHP;
}
bool GameObject::enemyCheckExplode(int deltaTime)
{
	if (_hp <= 0)	//draw 3 frames when Zoomer is explde
	{
		_currentAnimation = expoldeAnimation;
		_currentAnimation->Update(deltaTime);
		if (_hp>-2)
			_hp--;
		else
			_survive = false;
		return true;
	}
	return false;
}