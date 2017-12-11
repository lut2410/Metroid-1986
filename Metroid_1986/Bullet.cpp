#include "Bullet.h"
Bullet::Bullet(){};
Bullet::Bullet(int x, int y, Direction direction, DWORD survivalTime) :GameObject(Bullet_ID, x, y, 0, 0){
	_hp = 1;
	_attack = 1;

	Texture2* bulletTexture = TextureCollection::getInstance()->getTexture2(Bullet_ID);

	_allAnimation.resize(2);//because bullet has 2 action
	//flying
	_allAnimation[0] = new Animation(bulletTexture, bulletTexture->_animationNames.at(0)); 
	//broken
	_allAnimation[1] = new Animation(bulletTexture, bulletTexture->_animationNames.at(1)); 

	this->_currentAnimation = _allAnimation[0];
	_remainingTime = survivalTime;
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
//void Bullet::IsWounded()
//{
//	hp--;
//}
void Bullet::Update(int deltaTime)
{
	//update remaining-time
	_remainingTime -= deltaTime;
	if (_remainingTime <= 0)
		_survive = false;
	else
	{
		//update position
		_posX += _velX * deltaTime;
		_posY += _velY * deltaTime;
	}
}
void Bullet::Update2(int deltaTime)
{
	if (_hp <= 0)
	{
		_survive = false;
		_currentAnimation = _allAnimation[1];
	}
		
}