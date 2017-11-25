#include "Player.h"
Player::Player():GameObject(){
}
Player::Player(int x, int y):GameObject(Player_ID,x,y,0,0) {

	//_putHandUp = false;
	//_shoot = false;
	_action = Action::Stand;
	_directionOfMotion = DirectionOfMotion::Neutral;
	//Load all action-animation
	Texture2* playerTexture = TextureCollection::getInstance()->getTexture2(Player_ID);
	//resize = list name

	//for (int i = 1; i < playerTexture->_animationNames.size() ; i++){
	//	_actionAnimation[i] = new Animation(playerTexture, playerTexture->_animationNames.at(i));
	//	/*
	//	@example 
	//	_actionAnimation[ActionAnimation::StandIntro] 
	//		= new Animation(playerTexture, playerTexture->_animationNames.at(ActionAnimation::StandIntro_Ani));
	//	*/		
	//}

	//import all actionAnimation:
	_actionAnimation.resize(Jump_PutHandUp_Shoot_Ani+1);	//set size as biggest element value 
	_actionAnimation[StandIntro_Ani]			= new Animation(playerTexture, playerTexture->_animationNames.at(0));
	_actionAnimation[Stand_Ani]					= new Animation(playerTexture, playerTexture->_animationNames.at(1));
	_actionAnimation[Stand_PutHandUp_Ani]		= new Animation(playerTexture, playerTexture->_animationNames.at(2));
	_actionAnimation[Run_Ani]					= new Animation(playerTexture, playerTexture->_animationNames.at(3));
	_actionAnimation[Jump_Ani]					= new Animation(playerTexture, playerTexture->_animationNames.at(4));
	_actionAnimation[RollingJump_Ani]			= new Animation(playerTexture, playerTexture->_animationNames.at(5));
	_actionAnimation[Grovel_Ani]				= new Animation(playerTexture, playerTexture->_animationNames.at(6));
	_actionAnimation[Stand_Shoot_Ani]			= new Animation(playerTexture, playerTexture->_animationNames.at(7));
	_actionAnimation[Run_Shoot_Ani]				= new Animation(playerTexture, playerTexture->_animationNames.at(8));
	_actionAnimation[Stand_PutHandUp_Shoot_Ani] = new Animation(playerTexture, playerTexture->_animationNames.at(9));
	_actionAnimation[Run_PutHandUp_Ani]			= new Animation(playerTexture, playerTexture->_animationNames.at(10));
	_actionAnimation[Jump_PutHandUp_Ani]		= new Animation(playerTexture, playerTexture->_animationNames.at(11));
	_actionAnimation[Jump_PutHandUp_Shoot_Ani]	= new Animation(playerTexture, playerTexture->_animationNames.at(12));
	_acc = 0;

}

Player::~Player(){
}
DirectionOfMotion Player::getDirectionOfMotion(){
	return _directionOfMotion;
}

void Player::setAction(Action action){
	if (_action != action)
		_action = action;
};
void Player::addOrChangeAction(Action action){
	switch (action){
	case Action::Stand:
	case Action::Run:
	case Action::Jump:
	case Action::RollingJump:
	case Action::Grovel:
		//remove all foot action because only 1 foot action is performed
		if (isHasAction(Action::Stand))
			removeAction(Action::Stand);
		if (isHasAction(Action::Run))
			removeAction(Action::Run);
		if (isHasAction(Action::Jump))
			removeAction(Action::Jump);
		if (isHasAction(Action::RollingJump))
			removeAction(Action::RollingJump);
		if (isHasAction(Action::Grovel))
			removeAction(Action::Grovel);
		//set action
		setAction(Action(action));
		break;
	case Action::PutHandUp:
	case Action::Shoot:
		setAction(Action(_action | action));
		break;
	}
	
};
void Player::removeAction(Action action){
	if (isHasAction(action))
		setAction(Action(_action & ~action));
};
bool Player::isHasAction(Action action){
	return (_action & action) == action;
};

bool Player::isHasKey(ActionKey actionKey){
	return (_currentKeys & actionKey) == actionKey;
};
RECT Player::getCollisionRect(){
	RECT result{ 0, 0, 0, 0 };
	//if (_putHandUp)
	//	;

	
	//result.left= _posX-
	return result;
}
void Player::UpdatePosition(int deltaTime){
	//Update posX base velX
	_posX += _velX * deltaTime;
	_posY += _velY * deltaTime;
	if (isHasAction(Action::Jump) || isHasAction(Action::RollingJump))
		_velY += ACCELERATION*deltaTime;

};
void Player::Update(int deltaTime){

	
	//if (!isHasAction( Action::PutHandUp))
	//{
	//	switch (_action)
	//	{
	//	case None:
	//		//if (_directionOfMotion == DirectionOfMotion::Neutral)	//intro standing
	//		this->_currentAnimation = _actionAnimation[_action];
	//	case Stand:			
	//		this->_currentAnimation = _actionAnimation[_action];
	//		break;
	//	case Run:														//run
	//		this->_currentAnimation = _actionAnimation[_action];
	//		break;
	//	case Action::Jump:
	//		this->_currentAnimation = _actionAnimation[_action];
	//		break;
	//	case Action::RollingJump:
	//		this->_currentAnimation = _actionAnimation[_action];
	//		break;
	//	case Action::Grovel:
	//		this->_currentAnimation = _actionAnimation[_action];
	//		break;
	//	}
	//}
	//else //put hand up
	//{
	//	switch (_action)
	//	{
	//	case Action::None:
	//		this->_currentAnimation = _actionAnimation[Stand_PutHandUp_Ani];
	//	case Action::Stand:		//include nomal standing + intro standing
	//			this->_currentAnimation = _actionAnimation[_action];
	//	case Action::Run:
	//		this->_currentAnimation = _actionAnimation[_action];
	//		break;
	//	case Action::Jump:
	//		this->_currentAnimation = _actionAnimation[_action];
	//		break;
	//	case Action::RollingJump:		//don't exist
	//		break;
	//	case Action::Grovel:			//don't exist 
	//		break;
	//	}
	//}

	SpecifyAction();
	//update Postion
	UpdatePosition(deltaTime);
	//update current animation
	if (isHasAction(Action::Stand) && _directionOfMotion == DirectionOfMotion::Neutral)
	{
		this->_currentAnimation = _actionAnimation[StandIntro_Ani];
		if (_currentAnimation->getCurrentFrameIndex() == 3)	//but if current frame is ending frame of Intro 
			return;
	}
	else
		this->_currentAnimation = _actionAnimation[_action];


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
	/*if (_posY < 48)
	{
		_posY = 48;
		_velY = 0;
		
		if (_velX == 0)
		{
			addOrChangeAction(Action::Stand);
			this->_currentAnimation = _actionAnimation[_action];
		}
		else
		{
			addOrChangeAction(Action::Run);
			this->_currentAnimation = _actionAnimation[_action];
		}
	}*/

	//update sprite to next frame
												//then keep drawing end frame	
	_currentAnimation->Update(deltaTime);
}

void Player::Draw(Camera* camera)
{
	D3DXVECTOR2 center = camera->Transform(_posX, _posY);
	switch (_directionOfMotion)
	{
	case DirectionOfMotion::Neutral://Intro stage
		_currentAnimation->Draw(center.x, center.y);
		break;
	case DirectionOfMotion::Right:
		_currentAnimation->Draw(center.x, center.y);
		break;
	case DirectionOfMotion::Left://drawfip
		_currentAnimation->DrawFlipHorizontal(center.x, center.y);
		break;
	}

}
void Player::SpecifyAction(){
	SpecifyDirectionOfMotion();
	SpecifyFootAction();
	SpecifyHavingPutHandUp();
};

void Player::SpecifyDirectionOfMotion(){

	if (isHasKey(Left_Key) && !isHasKey(Right_Key))
	{
		_directionOfMotion = DirectionOfMotion::Left;
		_velX = -SPEED_X;
		if (isHasAction(Action::Stand))			//stand->run, otherwise jump,grovel,v.v. then is unchanged
			addOrChangeAction(Action::Run);
	}
	else if (isHasKey(Right_Key) && !isHasKey(Left_Key))
	{
		_directionOfMotion = DirectionOfMotion::Right;
		_velX = SPEED_X;
		if (isHasAction(Action::Stand))			//stand->run, otherwise jump,grovel,v.v. then is unchanged
			addOrChangeAction(Action::Run);
	}
	else													//left+key / none key
	{
		_velX = 0;
		if (isHasAction(Action::Run))				//run->stand, otherwise jump,grovel,v.v. then is unchange
			addOrChangeAction(Action::Stand);
	}
		
}

void Player::SpecifyFootAction(){

	//jump, grovel inspect Action to Specify action
	if (isHasKey(Jump_Key))
	{
		//switch (_action){
		if (isHasAction(Action::Stand) || isHasAction(Action::PutHandUp))//run but puthandup then normal jump
		{
			_velY = MAX_VEL_JUMP;
			addOrChangeAction(Action::Jump);			// jump key
		}
		if (isHasAction(Action::Run))
		{
			_velY = MAX_VEL_JUMP;
			addOrChangeAction(Action::RollingJump);	// left/right key + jump key
		}
		if (isHasAction(Action::Jump) || isHasAction(Action::RollingJump))
			;
		if (isHasAction(Action::Grovel))
		{
			//is groveling, press jump=>stand or run (base on velX)
			if (!isHasKey(Down_Key))
			{
				_velY = MAX_VEL_JUMP/10;					//light jump 
				addOrChangeAction(Action::Jump);			// jump key
			}
			//else has Down_Key: unchange

		}
	}
	else		//release Jump_Key
	{
		if (isHasAction(Action::Jump) || isHasAction(Action::RollingJump))
			{
				if (_velY > 0)			//player jump don't reache the top, but release the jump key
				_velY = 0;				//vY = 0 instantly
			}
	}

	if (isHasKey(Down_Key))
	{
		if (isHasAction(Action::Stand) || isHasAction(Action::Run))
		{									//standing/running +put hand up => standing/running, don't put hand up
			if (isHasAction(Action::PutHandUp))
				removeAction(Action::PutHandUp);
			else							//standing/running=>grovel
				addOrChangeAction(Action::Grovel);
		}
		//else: don't change
	}
	else
	{
		if (isHasAction(Action::Stand) || isHasAction(Action::Run))
		{
			if (isHasKey(Up_Key))					//it's case : standing/running action + up key + down key => now release down key	
				addOrChangeAction(Action::PutHandUp);
		}
		if (isHasAction(Action::Grovel))	//downkey + upkey -> upkey => stand/run + puthandup
			if (isHasKey(Up_Key))
			{
				addOrChangeAction(Action::PutHandUp);
				if (_velX == 0)
					addOrChangeAction(Action::Stand);
				else
					addOrChangeAction(Action::Run);
			}
	}
	

}
//void Player::SpecifyAction_KeyRelease(ActionKey actionKey){
//	if (KeyCode == DIK_F)// release jump key
//	{
//		_jumpKey = false;
//		if (isHasAction(Action::Jump)||isHasAction(Action::RollingJump))
//		{
//			if (_velY > 0)			//player jump don't reache the top, but release the jump key
//			_velY = 0;				//vY = 0 instantly
//		}
//	}
//	else if(KeyCode == DIK_DOWN)//Grovel
//	{
//		_downKey = false;
//		if (isHasAction(Action::Stand) || isHasAction(Action::Run))
//		{
//			if (_upKey==true)					//it's case : standing/running action + up key + down key => now release down key	
//				addOrChangeAction(Action::PutHandUp);
//		}
//		if(isHasAction(Action::Grovel))	//downkey + upkey -> upkey => stand/run + puthandup
//			if (_upKey == true)
//			{
//				addOrChangeAction(Action::PutHandUp);
//				if (_velX == 0)
//					addOrChangeAction(Action::Stand);
//				else
//					addOrChangeAction(Action::Run);
//			}
//
//		
//	}
//}

void Player::SpecifyHavingPutHandUp(){
	if (isHasKey(Up_Key))
	{
		if (isHasAction(Action::Stand) || isHasAction(Action::Run) || isHasAction(Action::Jump))		//perform concurrently
			addOrChangeAction(Action::PutHandUp);
		if (isHasAction(Action::RollingJump))						//can't perform concurrently:
			addOrChangeAction(Action::Jump);						//don't put hand up
		
		if (isHasAction(Action::Grovel))
			if (!isHasKey(Down_Key))
			{
				addOrChangeAction(Action::PutHandUp);
				_velY = MAX_VEL_JUMP / 10;					//light jump 
				addOrChangeAction(Action::Jump);
			}										//else downkey-> downkey+upkey => continue grovel
	}
	else //isn't have Up_Key
	{
		if (isHasAction(Action::Stand) || isHasAction(Action::Run))
		{											//standing/running +put hand up => standing/running, don't put hand up
			//if (isHasKey(ActionKey::Down_Key))		// meaning the down key is pressing
			removeAction(Action::PutHandUp);
			//else							//standing/running=>grovel
			//	addOrChangeAction(Action::Grovel);
		}
		if (isHasAction(Action::Jump))
			removeAction(Action::PutHandUp);
		if (isHasAction(Action::RollingJump))			//can't perform concurrently:
			;								//don't put hand up
		if (isHasAction(Action::Grovel))				//the case can't be exist
			;
	}
}
