#include "GameObject.h"
GameObject::GameObject(void){}
GameObject::~GameObject(void){}
GameObject::GameObject(ObjectID objectID, int posX, int posY, float velX, float velY){
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