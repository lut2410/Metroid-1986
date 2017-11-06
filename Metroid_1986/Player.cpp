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
	_standIntro_Spr = new Sprite(playerTexture, 600, 0, 3);
	_stand_Spr = new Sprite(playerTexture, 300, 4, 4);
	_standPutHandUp_Spr = new Sprite(playerTexture, 300, 5, 5);
	_run_Spr = new Sprite(playerTexture, 0, 6, 8);
	_jump_Spr = new Sprite(playerTexture, 300, 9, 9);
	_rollingJump_Spr = new Sprite(playerTexture, 0, 9, 13);
	_grovel_Spr = new Sprite(playerTexture, 0, 14, 17);
}

Player::~Player(){
}
void Player::Update(int deltaTime){

	//Update posX base velX
	_posX += _velX * deltaTime;
	_posY += _velY*deltaTime;
	if (_putHandUp == false)
	{
		switch (_footAction)
		{
		case FootAction::Stand:
			if (_directionOfMotion == DirectionOfMotion::Neutral)//intro standing
				this->_sprite = _standIntro_Spr;
			else//nomal stand
				this->_sprite = _stand_Spr;
			break;
		case FootAction::Run:
			this->_sprite = _run_Spr;
			break;
		case FootAction::Jump:
			//posY
			_velY += ACCELERATION*deltaTime;
			this->_sprite = _jump_Spr;
			break;
		case FootAction::RollingJump:
			//posY
			_velY += ACCELERATION*deltaTime;
			this->_sprite = _rollingJump_Spr;
			break;
		case FootAction::Grovel:
			this->_sprite = _grovel_Spr;
			break;
		}
	}
	else //put hand up
	{
		switch (_footAction)
		{
		case FootAction::Stand:		//include nomal standing + intro standing
				this->_sprite = _standPutHandUp_Spr;
			break;
		case FootAction::Run:
			this->_sprite = _run_Spr;
			break;
		case FootAction::Jump:
			//posY
			//this->_putHandUpSpr->Update(t);
			break;
		case FootAction::RollingJump:
			//posY
			break;
		case FootAction::Grovel:
			break;
		}
	}

	//Collision
	if (_posY > 300)
	{
		_posY = 300;
		_velY = 0;
		if (_velX == 0)
		{
			_footAction = FootAction::Stand;
			this->_sprite = _stand_Spr;
		}
		else
		{
			_footAction = FootAction::Run;
			this->_sprite = _run_Spr;
		}
	}

	//update sprite to next frame
	if (_sprite == _standIntro_Spr &(_sprite->getCurrentIndex() == 3))	//but if current frame is ending frame of Intro 
		return;															//then keep drawing end frame	
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
void Player::IdentifyFootAction_KeyPress(int KeyCode){

	//jump, grovel inspect footAction to identify action
	if (KeyCode == DIK_F)//jump
	{
		switch (_footAction){
		case FootAction::Stand://nomal jump
			//_acc = -ACCELERATION;
			//_velY = sqrt(-2 * _acc*MAX_HEIGHT_JUMP);
			_velY = MAX_VEL_JUMP;
			_footAction = FootAction::Jump;
			break;
		case FootAction::Run://=>rolling jump
			//_acc = -ACCELERATION;
			//_velY = sqrt(-2 * _acc*MAX_HEIGHT_JUMP);
			_velY = MAX_VEL_JUMP;
			_footAction = FootAction::RollingJump;
			break;
		case FootAction::Jump:
		case FootAction::RollingJump:
			break;
		case FootAction::Grovel://is groveling, press jump=>stand or run (base on velX)
			if (_velX == 0)
				_footAction = FootAction::Stand;
			else
				_footAction = FootAction::Run;
			break;
		}
	}
	else if (KeyCode == DIK_DOWN)//Grovel
	{
		switch (_footAction){
		case FootAction::Stand:				//standing/running +put hand up => standing/running, don't put hand up
		case FootAction::Run:
			if (_putHandUp == true)			
				_putHandUp = false;
			else							//standing/running=>grovel
			_footAction = FootAction::Grovel;
			break;
		case FootAction::Jump:
		case FootAction::RollingJump:		//jumping + downkey => standing/running
			if (_velX == 0)
				_footAction = FootAction::Stand;
			else
				_footAction = FootAction::Run;
			break;
		case FootAction::Grovel:
			break;
		}
	}
}
void Player::IdentifyFootAction_KeyRelease(int KeyCode){
	if (KeyCode == DIK_F)// release jump key
	{
		switch (_footAction){
		case FootAction::Stand://nomal jump
			//_velY = MAX_VEL_JUMP;
			//_footAction = FootAction::Jump;
			break;
		case FootAction::Run://=>rolling jump
			//_velY = MAX_VEL_JUMP;
			//_footAction = FootAction::RollingJump;
			break;
		case FootAction::Jump:
		case FootAction::RollingJump:
			break;
		case FootAction::Grovel://is groveling, press jump=>stand or run (base on velX)
			if (_velX == 0)
				_footAction = FootAction::Stand;
			else
				_footAction = FootAction::Run;
			break;
		}
	}
	else if(KeyCode == DIK_DOWN)//Grovel
	{
		switch (_footAction){
		case FootAction::Stand:				
		case FootAction::Run:			
			if (_velY == 0)					//it's case : standing/running action + up key + down key => now release down key	
				_putHandUp = true;
			else							//it's case : jumping + down key => now release down key
				_footAction = FootAction::Jump;
			break;
		case FootAction::Jump:
		case FootAction::RollingJump:
			break;
		case FootAction::Grovel:			//is groveling, press jump=>stand or run (base on velX)
			if (_velX == 0)
				_footAction = FootAction::Stand;
			else
				_footAction = FootAction::Run;
			break;
		}
	}
}
void Player::IdentifyHavingPutHandUp_KeyPress(){
	switch (_footAction)
	{
	case FootAction::Stand:			//perform concurrently
	case FootAction::Run:
	case FootAction::Jump:
		_putHandUp = true;
		break;
	case FootAction::RollingJump:			//can't perform concurrently:
		break;								//don't put hand up
	case FootAction::Grovel:				//can't perform concurrently:
		_putHandUp = false;					//
		if (_velX == 0)						//stand or run(base on velX)
			_footAction = FootAction::Stand;
		else
			_footAction = FootAction::Run;
		break;
	}
}
void Player::IdentifyHavingPutHandUp_KeyRelease(){
	switch (_footAction)
	{
	case FootAction::Stand:				//standing/running +put hand up => standing/running, don't put hand up
	case FootAction::Run:
		if (_putHandUp == true)
			_putHandUp = false;
		else							//standing/running=>grovel
			_footAction = FootAction::Grovel;
		break;
	case FootAction::Jump:
		_putHandUp = false;
		break;
	case FootAction::RollingJump:			//can't perform concurrently:
		break;								//don't put hand up
	case FootAction::Grovel:				//the case can't be exist
		break;
	}
}
//có 2 hướng,
// 1: cho thêm 1 biến vô player đang giữ trạng thái trên không + dùng hình stand/run
// 2: không cho nhấn phím down lúc đang trên không
// 3: làm thêm biến bool _downKey float _jumpKey