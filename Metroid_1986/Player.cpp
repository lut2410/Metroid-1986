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
		_sprite->DrawFlipHorizontal(_posX, _posY);
		break;
	}
}

void Player::IdentifyDirectionOfMotion_KeyPress(int KeyCode){
	

	if (_velX == 0)	//pressed 0 key -> 1key
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
		if (_footAction == FootAction::Stand)//standing=>run
			_footAction = FootAction::Run;
	}
	else //(actually press 1-> 2 key: left + right) = >keep direction, change velX = 0
	{
			_velX = 0;				// = >keep direction, change velX = 0
		if (_footAction == FootAction::Run)	//press 2 key left+ right at the same times => change action run-> stand
			_footAction = FootAction::Stand;//other cases: keep action
	}

		
}
void Player::IdentifyDirectionOfMotion_KeyRelease(int KeyCode){
	if (_directionOfMotion == DirectionOfMotion::Neutral)	//if this line is'n exist=> error logic when: press
		return;												//key in time intro, then release key after intro
	if (_velX == 0)	//pressed 2 key -> 1key (2 key is pressing, and release 1 key)
	{
		if (KeyCode == DIK_LEFT)	//release left key => remain right key is pressing
		{
			_directionOfMotion = DirectionOfMotion::Right;
			_velX = SPEED_X;
		}
		else	//release right key=> remain left key is pressing
		{
			_directionOfMotion = DirectionOfMotion::Left;
			_velX = -SPEED_X;
		}
		if (_footAction == FootAction::Stand)//press 2 key ->1 key => change action stand-> run
			_footAction = FootAction::Run;//other cases: keep action
	}
	else	//release one key: 1key->0 key pressed => keep direction, change velX=0
	{
			_velX = 0;//move horizontally -> don't
		if (_footAction == FootAction::Run)///change action run-> stand
			_footAction = FootAction::Stand;//other cases: keep action
	}
	

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