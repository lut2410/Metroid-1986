#include "Player.h"
Player::Player():GameObject(){
}
Player::Player(int x, int y) : GameObject(Player_ID, x, y, 0, 0) {
	_hp = 30;
	_attack = 0;//attack by bullet, isn't by body

	//Load all action-animation
	Texture2* playerTexture = NULL;
	playerTexture = TextureCollection::getInstance()->getTexture2(Player_ID);

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
	_actionAnimation[Jump_Shoot_Ani]			= new Animation(playerTexture, playerTexture->_animationNames.at(9));
	_actionAnimation[Stand_PutHandUp_Shoot_Ani] = new Animation(playerTexture, playerTexture->_animationNames.at(10));
	_actionAnimation[Run_PutHandUp_Ani]			= new Animation(playerTexture, playerTexture->_animationNames.at(11));
	_actionAnimation[Run_PutHandUp_Shoot_Ani]	= _actionAnimation[Run_PutHandUp_Ani];
	_actionAnimation[Jump_PutHandUp_Ani]		= new Animation(playerTexture, playerTexture->_animationNames.at(12));
	_actionAnimation[Jump_PutHandUp_Shoot_Ani]	= new Animation(playerTexture, playerTexture->_animationNames.at(13));


	//set up parameters
	_action = Action::Stand;
	_directionOfMotion = DirectionOfMotion::Neutral;
	this->_currentAnimation = _actionAnimation[StandIntro_Ani];
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
		setAction(Action(_action | action));
		break;
	case Action::PutHandUp:
	case Action::Shoot:
	case Action::BeWounded:
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

int Player::getHP()
{
	return _hp;
}
RECT Player::getCollisionBound(){
	Box playerBox = _currentAnimation->getCurrentSpriteSize(); //get bound of current sprite
	RECT playerBound = { _posX - playerBox.width / 2,		//left
		_posY + playerBox.height / 2,						//top
		_posX + playerBox.width / 2,						//right
		_posY - playerBox.height / 2 };						//bottom
	
	//edit parameter of bound for collision: except hand of sprite
	if (isHasAction(Action::PutHandUp))
		playerBound.top -= 6;
	else // don't put hand up

	{
		if (isHasAction(Action::Stand) && !isHasAction(Shoot))							//stand : 14
		{
			if (_directionOfMotion == DirectionOfMotion::Right)
				playerBound.right -= 6;
			else if (_directionOfMotion == DirectionOfMotion::Left)
				playerBound.left += 6;
			else //neutral
			{
				playerBound.right -= 6;
				playerBound.left += 6;
			}
		}
		else if (isHasAction(Action::Stand) && isHasAction(Shoot)
			|| isHasAction(Action::Run) && isHasAction(Shoot)		//run + shoot
			|| isHasAction(Action::Jump) && isHasAction(Shoot))		//jump + shoot)
		{
			if (_directionOfMotion == DirectionOfMotion::Right)
				playerBound.right -= 5;
			else //if (_directionOfMotion == DirectionOfMotion::Left)
				playerBound.left += 5;
		}
		//else if ()
	}
	playerBound.top--;
	return playerBound;
}
D3DXVECTOR2 Player::getPositionOfHand(){
	//get bound of player
	Box playerBox = _currentAnimation->getCurrentSpriteSize(); //get bound of current sprite
	RECT playerBound = { _posX - playerBox.width / 2,		//left
		_posY + playerBox.height / 2,						//top
		_posX + playerBox.width / 2,						//right
		_posY - playerBox.height / 2 };						//bottom

	D3DXVECTOR2 appearancePlaceOfBullet;

	if (_directionOfMotion == DirectionOfMotion::Right)
	{
		if (isHasAction(Action::PutHandUp))
		{
			if (isHasAction(Action::Stand))
				appearancePlaceOfBullet = { (float)playerBound.right - 5, (float)playerBound.top };
			else if (isHasAction(Action::Run))
				appearancePlaceOfBullet = { (float)playerBound.right - 4, (float)playerBound.top };
			else if (isHasAction(Action::Jump))
				appearancePlaceOfBullet = { (float)playerBound.right - 6, (float)playerBound.top };
		}
		else
		{
			if (isHasAction(Action::Stand))
				appearancePlaceOfBullet = { (float)playerBound.right, (float)playerBound.top - 10 };
			else if (isHasAction(Action::Run))
				appearancePlaceOfBullet = { (float)playerBound.right, (float)playerBound.top - 9 };
			else if (isHasAction(Action::Jump))
				appearancePlaceOfBullet = { (float)playerBound.right, (float)playerBound.top - 9 };
		}
	}
	else
	{
		if (isHasAction(Action::PutHandUp))
		{
			if (isHasAction(Action::Stand))
				appearancePlaceOfBullet = { (float)playerBound.left + 5, (float)playerBound.top };
			else if (isHasAction(Action::Run))
				appearancePlaceOfBullet = { (float)playerBound.left + 4, (float)playerBound.top };
			else if (isHasAction(Action::Jump))
				appearancePlaceOfBullet = { (float)playerBound.left + 6, (float)playerBound.top };
		}
		else
		{
			if (isHasAction(Action::Stand))
				appearancePlaceOfBullet = { (float)playerBound.left, (float)playerBound.top - 10 };
			else if (isHasAction(Action::Run))
				appearancePlaceOfBullet = { (float)playerBound.left, (float)playerBound.top - 9 };
			else if (isHasAction(Action::Jump))
				appearancePlaceOfBullet = { (float)playerBound.left, (float)playerBound.top - 9 };
		}
	}
	return appearancePlaceOfBullet;
}

void Player::handleCollision(map<int, GameObject*> objectList, float dt){
	RECT playerBound = getCollisionBound();
	Direction directionVsWall = Direction::None_Direction;
	// check each element in list maybe make collision with player
	//check collision with ground, wall
	for (auto it = objectList.begin(); it != objectList.end(); it++)
	{
		GameObject* object = it->second;
		Direction direction;
		if (object->getObjectID() == ObjectID::Ground_ID)
			if (handleObjectCollision(this, object, direction, dt)) //is collison
			{
				directionVsWall = Direction(directionVsWall | direction);
			}
	}
	//check collision with enemy
	//if player isn't be wounded
	// otherwise, wounded => immortal : don't check collision with enemy
	if (!isHasAction(Action::BeWounded))
	{
		for (auto it = objectList.begin(); it != objectList.end(); it++)
		{
			GameObject* object = it->second;
			Direction direction;

			switch (object->getObjectID())
			{
			case Hedgehog_ID:
				if (handleObjectCollision(this, object, direction, dt, false))
				{
					addOrChangeAction(Action::BeWounded);
					beWounded_remainningTime = TIMEIMMORTAL_WOUNDED;
					this->IsWounded(object->getAttackDame());
					switch (direction)
					{
					case Direction::Left_Direction:
						_velX = SPEED_WOUND;
						_velY = SPEED_WOUND;

						break;
					case Direction::Right_Direction:
						_velX = -SPEED_WOUND;
						_velY = SPEED_WOUND;
						//_pass = true;
						Camera::getInstance()->setTheGate(DirectionOfTheGate::Right_DOTG);
						break;
					case Direction::Top_Direction:
						_velY = -SPEED_WOUND;
						break;
					case Direction::Bottom_Direction:
						_velY = SPEED_WOUND;

						break;
					}
				}
				break;
			}
		}
	}
	
	//handle collision vs wall, after check collision between player with all walls
	handleVsWall(directionVsWall,dt);

	return;
}
void Player::handleVsWall(Direction directionVsWall, int deltaTime)
{
	_block = Block::None_Block;
	if (isHasDirection(directionVsWall, Direction::Left_Direction))	//width collision
	{
		_velX = 0;
		_block = Block::Left_Block;
	}
	if (isHasDirection(directionVsWall, Direction::Right_Direction))
	{
		_velX = 0;
		_block = Block::Right_Block;
	}
	if (isHasDirection(directionVsWall, Direction::Top_Direction))
		//head touch with the ground
	{
		_velY = 0;
	}
	if (isHasDirection(directionVsWall, Direction::Bottom_Direction))
		// foot on the ground 
	{
		if (isHasAction(Action::Grovel))
			//bounce
			_velY = -_velY * 9 / 10;
		else			//other actions
		{
			if (_velY > 0)	//is going up
				;
			else			//is going down
			{
				_velY = 0;
				if (isHasAction(Action::BeWounded))
				{
					_velX = _velY = 0;
				}
				if (isHasAction(Action::Jump) || isHasAction(Action::RollingJump))
					if (_velX == 0)
						addOrChangeAction(Action::Stand);
					else
						addOrChangeAction(Action::Run);
			}
			
		}

	}
	else
		//none collide vs wall
		//is in the space, don't touch ground
		//player will going down
		//gravity acceleration
	{
		if (isHasAction(Action::Stand)||isHasAction(Action::Run))
			addOrChangeAction(Action::Jump);

			_velY += ACCELERATION*deltaTime;
	}
}
void Player::UpdatePosition(int deltaTime){
	//Update posX base velX
	_posX += _velX * deltaTime;
	_posY += _velY * deltaTime;
	//if (isHasAction(Action::Jump) || isHasAction(Action::RollingJump) || isHasAction(Action::Grovel) || isHasAction(Action::Stand) || isHasAction(Action::Run))
	//if (!isHasAction(Action::Stand) && !isHasAction(Action::Run))
	//if (isHasAction(Action::Jump))
	//	_velY += ACCELERATION*deltaTime;
	//else
	//	_velY = SPEED_Y;

		
};
void Player::Update(int deltaTime){
	if (beWounded_remainningTime>0)
		beWounded_remainningTime -= deltaTime;

	//update action by key
	SpecifyAction();
	if (isHasAction(Action::BeWounded))		//be wounded => draw flicker
		this->_currentAnimation = _actionAnimation[_action - Action::BeWounded];
	else
		this->_currentAnimation = _actionAnimation[_action];
	//update Postion
	UpdatePosition(deltaTime);
}
void Player::Update2(int deltaTime){
	

	//update current animation

	
	if (isHasAction(Action::Stand) && _directionOfMotion == DirectionOfMotion::Neutral)
	{//Intro
		this->_currentAnimation = _actionAnimation[StandIntro_Ani];
		flicker = true;
		if (_currentAnimation->getCurrentFrameIndex() == 3)	//but if current frame is ending frame of Intro 
		{
			flicker = false;
			return;
		}
			
	}
	else
	{
		if (isHasAction(Action::BeWounded))		//be wounded => draw flicker
		{
			this->_currentAnimation = _actionAnimation[_action - Action::BeWounded];
			flicker = true;
		}
			
		else
		{
			this->_currentAnimation = _actionAnimation[_action];
			flicker = false;
		}
			
	}
		


	//update sprite to next frame
												//then keep drawing end frame	
	_currentAnimation->Update(deltaTime);



	//bullets are shooted between 1/3s
	if (_remainningTimeToShoot)
		_remainningTimeToShoot--;		//countdown to create new bullet
	else	//allow to shoot
		;	//==0

	if (isHasAction(Action::Shoot))
	{
		if (_remainningTimeToShoot == 0)
		{
			CreateBullet();
			//reset time : 5 frames later don't allow to create bullet
			_remainningTimeToShoot = TIMETOCREATNEWBULLET;
		}
			
			
	}
}

void Player::Draw(Camera* camera)
{
	flicker;
	D3DXVECTOR2 center = camera->Transform(_posX, _posY);
	switch (_directionOfMotion)
	{
	case DirectionOfMotion::Neutral://Intro stage
		/*if (flicker == false)
		{
			_currentAnimation->Draw(center.x, center.y);
			flicker = true;
		}
		else
			flicker = false;*/
		if (flicker)
			_currentAnimation->DrawFlicker(center.x, center.y);
		else
			_currentAnimation->Draw(center.x, center.y);
		break;
	case DirectionOfMotion::Right:
		//edit center position because each sprite have size different together
		if (isHasAction(Action::PutHandUp))
			center.y ;
		else if (isHasAction(Action::Stand) && !isHasAction(Shoot)		//stand / stand + shoot
			|| isHasAction(Action::Run) && isHasAction(Shoot)			//run + shoot
			|| isHasAction(Action::Jump) && isHasAction(Shoot))			//jump + shoot
			center.x += 3;
		else if (isHasAction(Action::Stand) && isHasAction(Shoot))
			center.x += 2;

		if (flicker)
			_currentAnimation->DrawFlicker(center.x, center.y);
		else
			_currentAnimation->Draw(center.x, center.y);

		break;
	case DirectionOfMotion::Left://drawfip
		if (isHasAction(Action::PutHandUp))
			;//center.y -= 3;
		else if (isHasAction(Action::Stand) && !isHasAction(Shoot)		//stand / stand + shoot
			|| isHasAction(Action::Run) && isHasAction(Shoot)			//run + shoot
			|| isHasAction(Action::Jump) && isHasAction(Shoot))			//jump + shoot
			center.x -= 3;
		else if (isHasAction(Action::Stand) && isHasAction(Shoot))
			center.x -= 2;
		if (flicker)
			_currentAnimation->DrawFlipHorizontalFlicker(center.x, center.y);
		else
			_currentAnimation->DrawFlipHorizontal(center.x, center.y);
		break;
	}

}



void Player::SpecifyAction(){

	if (SpecifyBeWounded())
		//be wounded => lose control
		return;
	SpecifyDirectionOfMotion();
	SpecifyFootAction();
	SpecifyHavingPutHandUp();
	SpecifyHavingShoot();
};

bool Player::SpecifyBeWounded()
{
	if (beWounded_remainningTime <= 0)			//time up player is immortal
	{
		removeAction(Action::BeWounded);
		return false;
	}
	else
		//be wounded => don't update from keyboard
	{
		if (_velX)			//decrease velocity 
			_velX -= _velX * SPEED_WOUND / 10; //decrease 1/10 velocity
		//else					//vel ==0 => back to normal status
		//if (_velY)
		//	_velY -= _velY * SPEED_WOUND / 10;

		return true;
	}
}
void Player::SpecifyDirectionOfMotion(){



	if (isHasKey(Left_Key) && !isHasKey(Right_Key) && _block != Block::Left_Block)
	{
		_directionOfMotion = DirectionOfMotion::Left;
		_velX = -SPEED_X;
		if (isHasAction(Action::Stand))			//stand->run, otherwise jump,grovel,v.v. then is unchanged
			addOrChangeAction(Action::Run);
	}
	else if (isHasKey(Right_Key) && !isHasKey(Left_Key) && _block != Block::Right_Block)
	{
		_directionOfMotion = DirectionOfMotion::Right;
		_velX = SPEED_X;
		if (isHasAction(Action::Stand))			//stand->run, otherwise jump,grovel,v.v. then is unchanged
			addOrChangeAction(Action::Run);
	}
	//else if (isHasKey(Right_Key))		//left+key / none key / touch wall
	//{
	//	_velX = 0;
	//	if (isHasAction(Action::Run))				//run->stand, otherwise jump,grovel,v.v. then is unchange
	//		addOrChangeAction(Action::Stand);
	//}
	else
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
		//if the face is neutral and press the key=> the face direct right
		if (_directionOfMotion == DirectionOfMotion::Neutral)
			_directionOfMotion = DirectionOfMotion::Right;
		//switch (_action){
		if (isHasAction(Action::Stand) || isHasAction(Action::Run)&&isHasAction(Action::PutHandUp))//run but puthandup then normal jump
		{
			_velY = MAX_VEL_JUMP;
			addOrChangeAction(Action::Jump);				// jump key
		}
		if (isHasAction(Action::Run))
		{
			_velY = MAX_VEL_JUMP;
			addOrChangeAction(Action::RollingJump);			// left/right key + jump key
		}
		if (isHasAction(Action::Jump) || isHasAction(Action::RollingJump))
			;
		if (isHasAction(Action::Grovel))
		{
			//is groveling, press jump=>stand or run (base on velX)
			if (!isHasKey(Down_Key))
			{
				
				addOrChangeAction(Action::Jump);			// jump key
				if(checkToStandUpInThisLocation())		//check posible of the case player is jump/ stand in location
					addOrChangeAction(Action::Grovel);
				else
					_velY = MAX_VEL_JUMP / 10;					//light jump 
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
		//if the face is neutral and press the key=> the face direct right
		if (_directionOfMotion == DirectionOfMotion::Neutral)
			_directionOfMotion = DirectionOfMotion::Right;

		if (isHasAction(Action::Stand) || isHasAction(Action::Run))
		{									//standing/running +put hand up => standing/running, don't put hand up
			if (isHasAction(Action::PutHandUp))
				removeAction(Action::PutHandUp);
			else							//standing/running=>grovel
			{
				addOrChangeAction(Action::Grovel);
				if (isHasAction(Action::Shoot))
					removeAction(Action::Shoot);
			}
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
			;
	}
}

void Player::SpecifyHavingPutHandUp(){
	if (isHasKey(Up_Key))
	{
		//if the face is neutral and press the key=> the face direct right
		if (_directionOfMotion == DirectionOfMotion::Neutral)
			_directionOfMotion = DirectionOfMotion::Right;

		if (isHasAction(Action::Stand) || isHasAction(Action::Run) || isHasAction(Action::Jump))		//perform concurrently
		if (!isHasKey(Down_Key))
			addOrChangeAction(Action::PutHandUp);
		//else
		//	removeAction(Action::PutHandUp);
		if (isHasAction(Action::RollingJump))						//can't perform concurrently:
			addOrChangeAction(Action::Jump);						//don't put hand up
		
		if (isHasAction(Action::Grovel))
			if (!isHasKey(Down_Key))
			{
				//_velY = MAX_VEL_JUMP / 10;					//light jump 
				//addOrChangeAction(Action::Jump);
				addOrChangeAction(Action::Jump);			// jump key
				if (checkToStandUpInThisLocation())		//check posible of the case player is jump/ stand in location
					addOrChangeAction(Action::Grovel);	//grovel
				else									//jump+puthandup
				{
					_velY = MAX_VEL_JUMP / 10;					//light jump 
					addOrChangeAction(Action::PutHandUp);
				}

			}										//else downkey-> downkey+upkey => continue grovel
	}
	else //isn't have Up_Key
	{
		if (isHasAction(Action::Stand) || isHasAction(Action::Run) || isHasAction(Action::Jump))	
			//standing/running +put hand up => standing/running, don't put hand up
			//if (isHasKey(ActionKey::Down_Key))		// meaning the down key is pressing
			removeAction(Action::PutHandUp);
			//else										//standing/running=>grovel

		if (isHasAction(Action::RollingJump))			//the case can't be exist
			;											
		if (isHasAction(Action::Grovel))				//the case can't be exist
			;
	}
}
void Player::SpecifyHavingShoot(){
	
	if (isHasKey(ActionKey::Shoot_Key))
	{
		
			//if the face is neutral and press the key=> the face direct right
			if (_directionOfMotion == DirectionOfMotion::Neutral)
				_directionOfMotion = DirectionOfMotion::Right;

			if (isHasAction(Action::Stand) || isHasAction(Action::Run) || isHasAction(Action::Jump))		//perform concurrently
				addOrChangeAction(Action::Shoot);
			if (isHasAction(Action::RollingJump))						//can't perform concurrently:
				addOrChangeAction(Action::Jump);
			if (isHasAction(Action::Grovel))
				;

		
	}
	else{
		if (isHasAction(Action::Stand) || isHasAction(Action::Run) || isHasAction(Action::Jump))		//perform concurrently
			removeAction(Action::Shoot);
		if (isHasAction(Action::RollingJump))						//the case can't be exist
			;
		if (isHasAction(Action::Grovel))							//the case can't be exist
			;
	}
}
void Player::CreateBullet()
{

		Direction directionOfBullet;//dependent on direction of the player's face and the hand

		if (isHasAction(PutHandUp) == true)
			directionOfBullet = Direction::Top_Direction;
		else
		{
			if (_directionOfMotion == DirectionOfMotion::Left)
				directionOfBullet = Direction::Left_Direction;
			else
				directionOfBullet = Direction::Right_Direction;
		}

			//bullet is appear at hand of player
			Bullet* bullet = new Bullet(getPositionOfHand().x, getPositionOfHand().y, directionOfBullet);
			//Bullet* bullet = new Bullet(660, 1100, Right_Direction);
			//add to 
			map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
			int key = 10000; //usually object number <10000.
			while (currentObjects->count(key)) // existed
				key++;
			//insert object with the key
			currentObjects->insert(pair<int, GameObject*>(key, bullet));
}
bool Player::checkToStandUpInThisLocation()
{
	// playerbound: take value if player stand
	RECT playerBound = getCollisionBound();
	playerBound.top = playerBound.bottom + 30;
	map<int, GameObject*> currentObjects = *TileGrid::getInstance()->getCurrentObjects();
	// check each element in list maybe make collision with player
	for (auto it = currentObjects.begin(); it != currentObjects.end(); it++)
	{
		GameObject* object = it->second;
		Direction direction;

		switch (object->getObjectID())
		{
		case ObjectID::Ground_ID:
			//if (int i = handleObjectCollision(this, object, direction, 16)) //is collison
			RECT otherBound = object->getCollisionBound();
			if (isColliding(playerBound, otherBound))
			{
				//if (direction == Direction::Top_Direction)
				if (float bottom = otherBound.bottom - playerBound.top)
					return true;
			}
		}
	}
	return false;
}