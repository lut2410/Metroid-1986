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
	_stand_PutHandUp_Spr = new Sprite(playerTexture, 300, 5, 5);
	_run_Spr = new Sprite(playerTexture, 0, 6, 8);
	_jump_Spr = new Sprite(playerTexture, 300, 9, 9);
	_rollingJump_Spr = new Sprite(playerTexture, 0, 9, 13);
	_grovel_Spr = new Sprite(playerTexture, 0, 14, 17);
	_stand_PutHandUp_Shoot_Spr = new Sprite(playerTexture, 300, 18, 18);
	_run_Shoot_Spr = new Sprite(playerTexture, 0, 19, 22);
	_stand_PutHandUp_Shoot_Spr = new Sprite(playerTexture, 0, 23, 23);
	_run_PutHandUp_Spr = new Sprite(playerTexture, 0, 24, 26);
	_jump_PutHandUp_Spr = new Sprite(playerTexture, 300, 27, 27);
	_jump_PutHandUp_Shoot_Spr = new Sprite(playerTexture, 300, 28, 28);
}

Player::~Player(){
}
DirectionOfMotion Player::getDirectionOfMotion(){
	return _directionOfMotion;
}
void Player::Update(int deltaTime){

	//Update posX base velX
	_posX += _velX * deltaTime;
	_posY += _velY*deltaTime;
	if (_putHandUp == false)
	{
		switch (_footAction)
		{
		case FootAction::StandOrRun:
			if (_velX == 0){											//stand
				if (_directionOfMotion == DirectionOfMotion::Neutral)//intro standing
					this->_sprite = _standIntro_Spr;
				else//nomal stand
					this->_sprite = _stand_Spr;
			}
			else														//run
			this->_sprite = _run_Spr;
			break;
		case FootAction::Jump:
			_velY += ACCELERATION*deltaTime;
			this->_sprite = _jump_Spr;
			break;
		case FootAction::RollingJump:
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
		case FootAction::StandOrRun:		//include nomal standing + intro standing
			if (_velX==0)
				this->_sprite = _stand_PutHandUp_Spr;
			else
			this->_sprite = _run_PutHandUp_Spr;
			break;
		case FootAction::Jump:
			_velY += ACCELERATION*deltaTime;
			this->_sprite = _jump_PutHandUp_Spr;
			break;
		case FootAction::RollingJump:		//don't exist
			break;
		case FootAction::Grovel:			//don't exist 
			break;
		}
	}

	//Collision
	// if(foot_collision_vs_theground||collision_vs_stone)
	//	locate the play to true location
	// if(foot_collision_vs_theground)
	//	if(_downkey && _upkey)
	//		_putHandUp=false;
	// if(collision_vs_enemy)
	//	change "knocked flag" to true (knocked flag is true in 1s)
	//
	//
	//
	if (_posY < 300)
	{
		_posY = 300;
		_velY = 0;
		_footAction = FootAction::StandOrRun;
		if (_putHandUp == false)
		{
			if (_velX == 0)
			{
				this->_sprite = _stand_Spr;
			}
			else
			{
				this->_sprite = _run_Spr;
			}
		}
		else
		{
			if (_velX == 0)
			{
				this->_sprite = _stand_PutHandUp_Spr;
			}
			else
			{
				this->_sprite = _run_PutHandUp_Spr;
			}
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
void Player::Draw(Camera* camera)
{
	D3DXVECTOR2 center = camera->Transform(_posX, _posY);
	switch (_directionOfMotion)
	{
	case DirectionOfMotion::Neutral://Intro stage
		_sprite->Draw(center.x, center.y);
		break;
	case DirectionOfMotion::Right:
		_sprite->Draw(center.x, center.y);
		break;
	case DirectionOfMotion::Left://drawfip
		_sprite->DrawFlipHorizontal(center.x, center.y);
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
	}
	else //(actually press 1-> 2 key: left + right) = >keep direction, change velX = 0
	{
			_velX = 0;				// = >keep direction, change velX = 0
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
		//if (_footAction == FootAction::Stand)//press 2 key ->1 key => change action stand-> run
		//	_footAction = FootAction::Run;//other cases: keep action
	}
	else	//release one key: 1key->0 key pressed => keep direction, change velX=0
	{
			_velX = 0;//move horizontally -> don't
		//if (_footAction == FootAction::Run)///change action run-> stand
		//	_footAction = FootAction::Stand;//other cases: keep action
	}
}
void Player::IdentifyFootAction_KeyPress(int KeyCode){

	//jump, grovel inspect footAction to identify action
	if (KeyCode == DIK_F)//jump
	{
		_jumpKey = true;
		switch (_footAction){
		case FootAction::StandOrRun:
			_velY = MAX_VEL_JUMP;
			if (_velX==0)
			_footAction = FootAction::Jump;			// jump key
			else
			_footAction = FootAction::RollingJump;	// left/right key + jump key
			break;
		case FootAction::Jump:
		case FootAction::RollingJump:
			break;
		case FootAction::Grovel:
			if (_downKey == false)
				_footAction = FootAction::StandOrRun;
			break;
		}
	}
	else if (KeyCode == DIK_DOWN)//Grovel
	{
		_downKey = true;
		switch (_footAction){
		case FootAction::StandOrRun:				//standing/running +put hand up => standing/running, don't put hand up
			if (_putHandUp == true)			
				_putHandUp = false;
			else							//standing/running=>grovel
			_footAction = FootAction::Grovel;
			break;
		case FootAction::Jump:
		case FootAction::RollingJump:		//jumping + downkey => standing/running
			break;
		case FootAction::Grovel:
			break;
		}
	}
}
void Player::IdentifyFootAction_KeyRelease(int KeyCode){
	if (KeyCode == DIK_F)// release jump key
	{
		_jumpKey = false;
		switch (_footAction){
		case FootAction::StandOrRun:
			break;
		case FootAction::Jump:
		case FootAction::RollingJump:
			if (_velY > 0)			//player jump don't reache the top
			_velY = 0;				//vY = 0 instantly
			break;
		case FootAction::Grovel://is groveling, press jump=>stand or run (base on velX)
				//if (_velX == 0)
				//	_footAction = FootAction::Stand;
				//else
				//	_footAction = FootAction::Run;
			break;
		}
	}
	else if(KeyCode == DIK_DOWN)//Grovel
	{
		_downKey = false;
		switch (_footAction){
		case FootAction::StandOrRun:						
			if (_velY == 0)					//it's case : standing/running action + up key + down key => now release down key	
				_putHandUp = true;
			break;
		case FootAction::Jump:
		case FootAction::RollingJump:
			break;
		case FootAction::Grovel:	//downkey + upkey -> upkey => stand/run + puthandup
			if (_upKey == true)
			{
				_putHandUp = true;
				_footAction = FootAction::StandOrRun;
			}
			break;
		}
	}
}
void Player::IdentifyHavingPutHandUp_KeyPress(){
	_upKey = true;
	switch (_footAction)
	{
	case FootAction::StandOrRun:			//perform concurrently
	case FootAction::Jump:
		_putHandUp = true;
		break;
	case FootAction::RollingJump:			//can't perform concurrently:
		break;								//don't put hand up
	case FootAction::Grovel:				//can't perform concurrently:
		if (_downKey == false)
		{
			_putHandUp = true;
			_footAction = FootAction::StandOrRun;
		}										//else downkey-> downkey+upkey => continue grovel
		break;
		
	}
}
void Player::IdentifyHavingPutHandUp_KeyRelease(){
	_upKey = false;
	switch (_footAction)
	{
	case FootAction::StandOrRun:				//standing/running +put hand up => standing/running, don't put hand up
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