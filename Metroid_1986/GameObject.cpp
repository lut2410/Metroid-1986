#include "GameObject.h"
GameObject::GameObject(void){}
GameObject::~GameObject(void){}
GameObject::GameObject(ObjectID objectID, int posX, int posY, float velX, float velY){
	_survive = true;
	_objectID = objectID;
	_posX = posX;
	_posY = posY;
	_velX = velX;
	_velY = velY;
	CreateSprite();
}
void GameObject::CreateSprite()
{
	switch (_objectID)
	{
	case Player_ID:
		//_sprite = new Sprite(TextureCollection::getInstance()->getTexture(_objectID), 100, 0, 3);
		break;
	default:
		break;
	}
}
RECT GameObject::getCollisionBound(){
	Box  objectBox = _currentAnimation->getCurrentSpriteSize();
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
bool GameObject::isSurvive()
{
	return _survive;
}

void GameObject::Update(int deltaTime)
{
	if (_objectID == Ground_ID)
		return;
	//update position
	_posX += _velX * deltaTime;
	_posY += _velY * deltaTime;
}
void GameObject::Draw(Camera* camera){
	if (_objectID == Ground_ID)
		return;
	D3DXVECTOR2 center = camera->Transform(_posX, _posY);
	_currentAnimation->Draw(center.x, center.y);
}