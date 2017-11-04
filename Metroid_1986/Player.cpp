#include "Player.h"
Player::Player():GameObject(){
}
Player::Player(int x, int y):GameObject(Player_ID,x,y,0,0) {
	_acc = 0;
	FootAction _footAction;
	_directionOfMotion = DirectionOfMotion::Neutral;
	_putHandUp = false;
	_shoot = false;

	//Load sprite
	Texture* playerTexture = TextureCollection::getInstance()->getTexture(Player_ID);
	_standIntroSpr = new Sprite(playerTexture, 300, 0, 3);
	_standSpr = new Sprite(playerTexture, 300, 4, 4);
	_putHandUpSpr = new Sprite(playerTexture, 300, 5, 5);
	_runSpr = new Sprite(playerTexture, 50, 6, 8);
	//_jumpSpr;


}

Player::~Player(){
}
void Player::Update(int deltaTime){

	//Update posX base velX
	_posX += _velX * deltaTime;

	switch (_footAction)
	{
	case FootAction::Stand:
		if (_directionOfMotion==DirectionOfMotion::Neutral)//intro standing
			this->_sprite = _standIntroSpr;
		else//nomal stand
			this->_sprite=_standSpr;
		break;
	case FootAction::Run:
		this->_sprite=_runSpr;
		break;
	case FootAction::Jump:
		//posY
		//this->_putHandUpSpr->Update(t);
		break;
	}
	//update sprite to next frame
	_sprite->Update(deltaTime);
}
void Player::Draw(){
	switch (_directionOfMotion)
	{
	case DirectionOfMotion::Neutral://Intro stage
		_sprite->Draw(_posX, _posY);
		break;
	case DirectionOfMotion::Right:
		_sprite->Draw(_posX, _posY);
		break;
	case DirectionOfMotion::Left://drawfip
		//_sprite->Draw(_posX, _posY);
		break;
	}
}

void Player::IdentifyDirectionOfMotion(int KeyCode){
	
	if (_velX == 0)//stand=>change motion and velX
	{
		if (KeyCode == DIK_LEFT)
		{
			_directionOfMotion = DirectionOfMotion::Left;
			_velX = -SPEED_X;
		}
		else
		{
			_directionOfMotion = DirectionOfMotion::Right;
			_velX = SPEED_X;
		}
	}
	else if (_velX > 0)//right direction
	{
		if (KeyCode == DIK_LEFT)//+ left key(actually press 2 key: left+right) =>keep direction, change velX=0
			_velX = 0;
	}
	else //left direction
	{
		if (KeyCode == DIK_RIGHT)//+ right key(actually press 2 key: left+right) =>keep direction, change velX=0
			_velX = 0;
	}
	if (_footAction == FootAction::Stand)//standing=>run
		_footAction = FootAction::Run;
		
}
void Player::IdentifyFootAction(int KeyCode){

	//jump, grovel inspect footAction to identify action
	if (KeyCode == DIK_F)//jump
	{
		switch (_footAction){
		case FootAction::Stand://nomal jump
			_acc = -ACCELERATION;
			_velY = sqrt(-2 * _acc*MAX_HEIGHT_JUMP);
			_footAction = FootAction::Jump;
			break;
		case FootAction::Run://=>rolling jump
			_acc = -ACCELERATION;
			_velY = sqrt(-2 * _acc*MAX_HEIGHT_JUMP);
			_footAction = FootAction::RollingJump;
			break;
		case FootAction::Jump:
		case FootAction::RollingJump:
			break;
		case FootAction::Grovel://is groveling, press jump=>stand
			_velY = 0;
			_footAction = FootAction::Stand;
			break;
		}
	}
}

void Player::PutHandUp(){
	if (_footAction != FootAction::Grovel)//Groveling can't put hand up
		_putHandUp = true;
};