//#include "Ripper.h"
//Ripper::Ripper()
//{}
//Ripper::Ripper(int x, int y, int type) :GameObject(Ripper_ID, x, y, 0, 0){
//	//take texture
//	Texture2* ripperTexture = NULL;
//	ripperTexture = TextureCollection::getInstance()->getTexture2(Ripper_ID);
//
//	switch (type)
//	{
//	case 1:
//		_attack = 8;
//		//take animation of its type( type1 in here)
//		_actionAnimation.push_back(new Animation(ripperTexture, "Type1"));
//		break;
//	case 2:
//		_attack = 10;
//		//take animation of its type( type1 in here)
//		_actionAnimation.push_back(new Animation(ripperTexture, "Type2"));
//		break;
//	case 3:
//		_attack = 12;
//		//take animation of its type( type1 in here)
//		_actionAnimation.push_back(new Animation(ripperTexture, "Type3"));
//		break;
//	case 4:
//		_attack = 14;
//		//take animation of its type( type1 in here)
//		_actionAnimation.push_back(new Animation(ripperTexture, "Type4"));
//		break;
//	case 5:
//		_attack = 16;
//		//take animation of its type( type1 in here)
//		_actionAnimation.push_back(new Animation(ripperTexture, "Type5"));
//		break;
//	}
//
//	//set default action and animation
//	_action = RipperAction::SuftToLeft;
//	_currentAnimation = _actionAnimation[_action];	//actually _actionAnimation just have 1 animation 
//}
//void Ripper::Update(int deltaTime)
//{
//
//	
//	//specify vel
//	switch (_action)
//	{
//	case RipperAction::SuftToLeft:		
//		_velX = -RIPPER_VEL;
//		_velY = 0;
//		break;
//	case RipperAction::SuftToRight:
//		_velX = RIPPER_VEL;
//		_velY = 0;
//		break;
//	}
//
//	//update position
//	_posX += _velX * deltaTime;
//	_posY += _velY * deltaTime;
//
//}
//void Ripper::Draw(Camera* camera)
//{
//
//	D3DXVECTOR2 center = camera->Transform(_posX, _posY);
//	switch (_action)
//	{
//	case RipperAction::SuftToLeft:		
//		_currentAnimation->Draw(center.x, center.y);
//		break;
//	case RipperAction::SuftToRight:
//		_currentAnimation->DrawFlipHorizontal(center.x, center.y);
//		break;
//	}
//	
//}
//void Ripper::handleCollision(map<int, GameObject*> objectList, float deltaTime)
//{
//	RECT a = getCollisionBound();
//	for (auto it = objectList.begin(); it != objectList.end(); it++)
//	{
//		GameObject* otherObject = it->second;
//		Direction direction;
//		if (otherObject->getObjectID() == ObjectID::Ground_ID)
//			if (handleObjectCollision(this, otherObject, direction, deltaTime))
//			{
//				if (_action == RipperAction::SuftToLeft)			
//					_action = RipperAction::SuftToRight;
//				else
//					_action = RipperAction::SuftToLeft;
//				break;
//			}
//		//exit for loop
//		//except the case Ripper touch 2 object Ground at the same time 
//		//=> SuftToLeft->SuftToRight->SuftToLeft (will be stucked)
//
//	}
//}
