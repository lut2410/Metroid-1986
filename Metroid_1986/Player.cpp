#include "Player.h"
Player::Player():GameObject(){
}
Player::Player(int x, int y) : GameObject(Player_ID, x, y, 0, 0) {
	_hp = 30;
	_attack = 0;//attack by bullet, isn't by body
	_currentBulletType = BulletType::BulletFromPlayer_Nomal;
	//_rocketNumbers = 5;

	//Load all action-animation
	Texture2* playerTexture = NULL;
	playerTexture = TextureCollection::getInstance()->getTexture2(Player_ID);

	//import all actionAnimation:
	_actionAnimation.resize(Jump_PutHandUp_Shoot_Ani+1);	//set size as biggest element value 
	_actionAnimation[StandIntro_Ani]			= new Animation(playerTexture, "StandIntro");
	_actionAnimation[Stand_Ani]					= new Animation(playerTexture, "Stand");
	_actionAnimation[Stand_PutHandUp_Ani]		= new Animation(playerTexture, "StandPutHandUp");
	_actionAnimation[Run_Ani]					= new Animation(playerTexture, "Run");
	_actionAnimation[Jump_Ani]					= new Animation(playerTexture, "Jump");
	_actionAnimation[RollingJump_Ani]			= new Animation(playerTexture, "RollingJump");
	_actionAnimation[Grovel_Ani]				= new Animation(playerTexture, "Grovel");
	_actionAnimation[Stand_Shoot_Ani]			= new Animation(playerTexture, "StandShoot");
	_actionAnimation[Run_Shoot_Ani]				= new Animation(playerTexture, "RunShoot");
	_actionAnimation[Jump_Shoot_Ani]			= new Animation(playerTexture, "JumpShoot");
	_actionAnimation[Stand_PutHandUp_Shoot_Ani] = new Animation(playerTexture, "StandPutHandUpShoot");
	_actionAnimation[Run_PutHandUp_Ani]			= new Animation(playerTexture, "RunPutHandUp");
	_actionAnimation[Run_PutHandUp_Shoot_Ani]	= _actionAnimation[Run_PutHandUp_Ani];
	_actionAnimation[Jump_PutHandUp_Ani]		= new Animation(playerTexture, "JumpPutHandUp");
	_actionAnimation[Jump_PutHandUp_Shoot_Ani]	= new Animation(playerTexture, "JumpPutHandUpShoot");


	//set up parameters
	_action = Action::Stand;
	_directionOfFace = DirectionOfFace::Neutral;
	this->_currentAnimation = _actionAnimation[StandIntro_Ani];
}
Player::~Player(){
}
DirectionOfFace Player::getDirectionOfFace(){
	return _directionOfFace;
}
bool Player::isHasSpecialAbility(PlayerSpecialAbility specialAbility)
{
	return (_specialAbility & specialAbility) == specialAbility;
}
void Player::addSpecialAbility(PlayerSpecialAbility specialAbility)
{
	_specialAbility = PlayerSpecialAbility (_specialAbility | specialAbility);
	if (specialAbility == PlayerSpecialAbility::ShootLonger_PSA)
		_remainingTimeToShoot2 = 800;	//borrow
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
		//check ability to grovel
		if (action == Action::Grovel&&isHasSpecialAbility(PlayerSpecialAbility::Grovel_PSA) == false)
			return;

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
			if (_directionOfFace == DirectionOfFace::Right)
			{
				playerBound.right -= 5;
				playerBound.left = playerBound.right - 12;
			}

			else if (_directionOfFace == DirectionOfFace::Left)
			{
				playerBound.left += 6;
				playerBound.right = playerBound.left + 12;
			}
				
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
			if (_directionOfFace == DirectionOfFace::Right)
			{
				playerBound.right -= 5;
				playerBound.left = playerBound.right - 12;
			}

			else //if (_DirectionOfFace == DirectionOfFace::Left)
			{
				playerBound.left += 5;
				playerBound.right = playerBound.left + 12;
			}

		}
		else if (isHasAction(Action::Grovel))
			;
		else
		{
			if (_directionOfFace == DirectionOfFace::Right)
			{
				playerBound.right -= 2;
				playerBound.left = playerBound.right - 12;
			}

			else //if (_DirectionOfFace == DirectionOfFace::Left)
			{
				playerBound.left += 2;
				playerBound.right = playerBound.left + 12;
			}
		}
		//switch (_action)
		//{
		//case Action::Stand:
		//	//12x31
		//	if (_directionOfFace == DirectionOfFace::Right)
		//		playerBound = { playerBound.right - 21,			//left
		//			playerBound.bottom + 31,						//top
		//			playerBound.right - 9,						//right
		//			playerBound.bottom };						//bottom
		//	else 
		//		playerBound = { playerBound.left +9,			//left
		//		playerBound.bottom + 31,						//top
		//		playerBound.left +21,						//right
		//		playerBound.bottom };						//bottom
		//	break;
		//case Action::Run:
		//	//12x31
		//	if (_directionOfFace == DirectionOfFace::Right)
		//		playerBound = { playerBound.right - 18,			//left
		//			playerBound.bottom +31,						//top
		//			playerBound.right - 6 ,						//right
		//			playerBound.bottom };						//bottom
		//	else
		//		playerBound = { playerBound.left + 2 ,			//left
		//			playerBound.bottom + 31,						//top
		//			playerBound.left + 14,						//right
		//			playerBound.bottom };						//bottom
		//	break;
		//}
	}
	playerBound.top--;
	return playerBound;
}
D3DXVECTOR2 Player::getPositionOfGun(){
	//get bound of player
	Box playerBox = _currentAnimation->getCurrentSpriteSize(); //get bound of current sprite
	RECT playerBound = { _posX - playerBox.width / 2,		//left
		_posY + playerBox.height / 2,						//top
		_posX + playerBox.width / 2,						//right
		_posY - playerBox.height / 2 };						//bottom

	D3DXVECTOR2 appearancePlaceOfBullet;

	if (_directionOfFace == DirectionOfFace::Right)
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
	//map<int, GameObject*> objectList = *TileGrid::getInstance()->getCurrentObjects();
	

	RECT playerBound = getCollisionBound();
	Direction directionVsWall = Direction::None_Direction;
	// check each element in list maybe make collision with player
	//check collision with ground, wall
	for (auto it = objectList.begin(); it != objectList.end(); it++)
	{
		GameObject* object = it->second;
		Direction direction;
		if (object->getObjectType()==ObjectType::RelativesWithWall_OT||object->getObjectStatus()==ObjectStatus::BeFreezing_OS)
			if (handleObjectCollision(this, object, direction, dt)) //is collison
			{
				directionVsWall = Direction(directionVsWall | direction);
			}
	}
	//check collision with enemy
	//if player isn't be wounded
	// otherwise, wounded, explode, die => immortal : don't check collision with enemy
	if (_objectStatus== ObjectStatus::Survival_OS)
	{
		for (auto it = objectList.begin(); it != objectList.end(); it++)
		{
			GameObject* object = it->second;
			Direction direction;
			if (handleObjectCollision(this, object, direction, dt))
			{
				
				//collide
				switch (object->getObjectID())
				{
					//nelative of ground
				case Gate_ID:	//pass the gate
					Camera::getInstance()->setTheGate(direction);
					//reset time to open the gate
					break;

					//enemy
				case Zoomer_ID:
				case Skree_ID:
				case Ripper_ID:
				case Zeb_ID:
				case Waver_ID:
				case Rio_ID:
					if (object->getObjectStatus() != ObjectStatus::BeFreezing_OS)
						this->BeWounded(direction, object->getAttackDame());
					break;
					//boss
				case Ridley_ID:
					this->BeWounded(direction, object->getAttackDame());
					break;

				case Bullet_ID:
					if (object->getBulletType() == BulletType::BulletFromSkree
						||object->getBulletType() == BulletType::BulletFromRidley
						||object->getBulletType() == BulletType::BulletFromKraid_Boomerang
						||object->getBulletType() == BulletType::BulletFromKraid_Rocket)
						//except the bullet player shoot out
					{
						if (object->getObjectStatus()!=ObjectStatus::BeFreezing_OS)
							this->BeWounded(direction, object->getAttackDame());
					}
						
					break;
					//item
				case MaruMari_ID:
					if (this->isHasSpecialAbility(Grovel_PSA) == false)
						//first time
						this->addSpecialAbility(Grovel_PSA);
					else
						//2nd time(meaning player has "eaten" this item)
						//pause game 2s and delete MaruMari
					{
						Sleep(2000);
						object->SetObjectStatus(ObjectStatus::Died_OS);
					}
					break;
				case HPTonic_ID:
					this->BuffHP(5);
					object->SetObjectStatus(ObjectStatus::Died_OS);
					break;
				case LongBeam_ID:
					if (this->isHasSpecialAbility(ShootLonger_PSA) == false)
						//first time
						this->addSpecialAbility(ShootLonger_PSA);
					else
						//2nd time(meaning player has "eaten" this item)
						//pause game 2s and delete MaruMari
					{
						Sleep(2000);
						object->SetObjectStatus(ObjectStatus::Died_OS);
					}
					break;
				case IceBeam_ID:
					if (this->isHasSpecialAbility(ShootIceBeam_PSA) == false)
						//first time
						this->addSpecialAbility(ShootIceBeam_PSA);
					else
						//2nd time(meaning player has "eaten" this item)
						//pause game 2s and delete MaruMari
					{
						Sleep(2000);
						object->SetObjectStatus(ObjectStatus::Died_OS);
					}
					break;
				case WaveBeam_ID:
					if (this->isHasSpecialAbility(ShootWaveBeam_PSA) == false)
						//first time
						this->addSpecialAbility(ShootWaveBeam_PSA);
					else
						//2nd time(meaning player has "eaten" this item)
						//pause game 2s and delete MaruMari
					{
						Sleep(2000);
						object->SetObjectStatus(ObjectStatus::Died_OS);
					}
					break;
				case MissibleRocket_ID:
					if (this->isHasSpecialAbility(ShootRocket_PSA) == false)
						//first time
						this->addSpecialAbility(ShootRocket_PSA);
					else
						//2nd time(meaning player has "eaten" this item)
						//pause game 2s and delete MaruMari
					{
						Sleep(2000);
						object->SetObjectStatus(ObjectStatus::Died_OS);
					}
					break;
				}

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
				if (_objectStatus==ObjectStatus::BeWounding_OS)
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

		
};
void Player::Update(int deltaTime){


	UpdateStatus();
	//UPDATE ACTION AND VELOCITY
	//by key
	UpdateActionAndVelocity(deltaTime);
	//update Postion
	UpdatePosition(deltaTime);
}
void Player::UpdateAnimationBaseOnStatus()
{
	switch (_objectStatus)
	{
	case ObjectStatus::Survival_OS:
		_currentAnimation = _actionAnimation[_action];
		flicker = false;
		break;
	case ObjectStatus::BeWounding_OS:
		
		if (isHasAction(Action::Stand) && _directionOfFace == DirectionOfFace::Neutral)
			_currentAnimation = _actionAnimation[StandIntro_Ani];
		else
			_currentAnimation = _actionAnimation[_action];
		flicker = true;
		break;
	case ObjectStatus::Exploding_OS:
		_currentAnimation = explodingAnimation;
		break;
	case ObjectStatus::Died_OS:
		break;
	}
}

void Player::Update2(int deltaTime){
	

	//update current animation
	UpdateAnimationBaseOnStatus();

	//update sprite to next frame
	if (isHasAction(Action::Stand) && _directionOfFace == DirectionOfFace::Neutral)
	{//Intro
		if (_currentAnimation->getCurrentFrameIndex() != 4)	//but if current frame is ending frame of Intro 
			_currentAnimation->Update(deltaTime);
		return;
	}
	_currentAnimation->Update(deltaTime);

	//bullets are shooted between 1/3s
	if (_remainingTimeToShoot)
		_remainingTimeToShoot--;		//countdown to create new bullet
	else	//allow to shoot
		;	//==0

	if (isHasAction(Action::Shoot))
	{
		if (_remainingTimeToShoot == 0)
		{
			CreateBullet();
			//reset time : 5 frames later don't allow to create bullet
			_remainingTimeToShoot = TIMETOCREATNEWBULLET;
		}
	}
}
void Player::BeWounded(Direction direction, int lossHP)
{
	SetObjectStatus(ObjectStatus::BeWounding_OS);
	_remainingWoundingTime = 30;		//1s
	_hp -= lossHP;
	switch (direction)
	{
	case Direction::None_Direction:
		break;
	case Direction::Left_Direction:
		_velX = SPEED_WOUND;
		_velY = SPEED_WOUND;

		break;
	case Direction::Right_Direction:
		_velX = -SPEED_WOUND;
		_velY = SPEED_WOUND;
		break;
	case Direction::Top_Direction:
		_velY = -SPEED_WOUND;
		break;
	case Direction::Bottom_Direction:
		_velY = SPEED_WOUND;
	}
}
void Player::BuffHP(int buffHP)
{
	_hp += buffHP;
}
void Player::Draw(Camera* camera)
{
	flicker;
	D3DXVECTOR2 center = camera->Transform(_posX, _posY);
	switch (_directionOfFace)
	{
	case DirectionOfFace::Neutral://Intro stage
		if (flicker)
			_currentAnimation->DrawFlicker(center.x, center.y);
		else
			_currentAnimation->Draw(center.x, center.y);
		break;
	case DirectionOfFace::Right:
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
	case DirectionOfFace::Left://drawfip
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

void Player::UpdatePostionToInsideCamera()
{
	Camera* camera = Camera::getInstance();
	//update
	if (_posX < camera->_bound.left)
		_posX = camera->_bound.left + 27;
	if (_posX > camera->_bound.right)
		_posX = camera->_bound.right - 27;
}

void Player::UpdateActionAndVelocity(int deltaTime){

	switch (_objectStatus)
	{
	case ObjectStatus::Survival_OS:
		SpecifyDirectionOfFace();
		SpecifyFootAction();
		SpecifyHavingPutHandUp();
		SpecifyHavingShoot();
		break;
	case ObjectStatus::BeWounding_OS:
		if (_velX)			//decrease velocity 
			_velX -= _velX * SPEED_WOUND / 10; //decrease 1/10 velocity
		//else					//vel ==0 => back to normal status
		//if (_velY)
		//	_velY -= _velY * SPEED_WOUND / 10;
		break;
	case ObjectStatus::Exploding_OS:
		break;
	case ObjectStatus::Died_OS:
		break;
	}
	
};


void Player::SpecifyDirectionOfFace(){



	if (isHasKey(Left_Key) && !isHasKey(Right_Key) && _block != Block::Left_Block)
	{
		_directionOfFace = DirectionOfFace::Left;
		_velX = -SPEED_X;
		if (isHasAction(Action::Stand))			//stand->run, otherwise jump,grovel,v.v. then is unchanged
			addOrChangeAction(Action::Run);
	}
	else if (isHasKey(Right_Key) && !isHasKey(Left_Key) && _block != Block::Right_Block)
	{
		_directionOfFace = DirectionOfFace::Right;
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
		if (_directionOfFace == DirectionOfFace::Neutral)
			_directionOfFace = DirectionOfFace::Right;
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
		if (_directionOfFace == DirectionOfFace::Neutral)
			_directionOfFace = DirectionOfFace::Right;

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
		if (_directionOfFace == DirectionOfFace::Neutral)
			_directionOfFace = DirectionOfFace::Right;

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
			if (_directionOfFace == DirectionOfFace::Neutral)
				_directionOfFace = DirectionOfFace::Right;

			if (isHasAction(Action::Stand) || isHasAction(Action::Run) || isHasAction(Action::Jump))		//perform concurrently
				addOrChangeAction(Action::Shoot);
			if (isHasAction(Action::RollingJump))						//can't perform concurrently:
			{
				addOrChangeAction(Action::Jump);
				addOrChangeAction(Action::Shoot);
			}
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
void Player::SwitchToOtherBulletType()
{
	switch (_currentBulletType)
	{
	case BulletType::BulletFromPlayer_Nomal:
		if (isHasSpecialAbility(PlayerSpecialAbility::ShootIceBeam_PSA))
			_currentBulletType = BulletType::BulletFromPlayer_Freeze;
		else if (isHasSpecialAbility(PlayerSpecialAbility::ShootWaveBeam_PSA))
			_currentBulletType = BulletType::BulletFromPlayer_Wave;
		else if (isHasSpecialAbility(PlayerSpecialAbility::ShootRocket_PSA))
			_currentBulletType = BulletType::BulletFromPlayer_Rocket;
		//else : Normal Bullet
		break;
	case BulletType::BulletFromPlayer_Freeze:

		if (isHasSpecialAbility(PlayerSpecialAbility::ShootWaveBeam_PSA))
			_currentBulletType = BulletType::BulletFromPlayer_Wave;
		else if (isHasSpecialAbility(PlayerSpecialAbility::ShootRocket_PSA))
			_currentBulletType = BulletType::BulletFromPlayer_Rocket;
		else /*if (!isHasSpecialAbility(PlayerSpecialAbility::ShootIceBeam_PSA))*/
			_currentBulletType = BulletType::BulletFromPlayer_Nomal;
		break;
	case BulletType::BulletFromPlayer_Wave:
		if (isHasSpecialAbility(PlayerSpecialAbility::ShootRocket_PSA))
			_currentBulletType = BulletType::BulletFromPlayer_Rocket;
		else 
			_currentBulletType = BulletType::BulletFromPlayer_Nomal;
		break;
	case BulletType::BulletFromPlayer_Rocket:
		_currentBulletType = BulletType::BulletFromPlayer_Nomal;
		break;
	}
}
void Player::CreateBullet()
{

		Direction directionOfBullet;//dependent on direction of the player's face and the hand

		if (isHasAction(PutHandUp) == true)
			directionOfBullet = Direction::Top_Direction;
		else
		{
			if (_directionOfFace == DirectionOfFace::Left)
				directionOfBullet = Direction::Left_Direction;
			else
				directionOfBullet = Direction::Right_Direction;
		}

		Bullet* bullet = NULL;
		//bullet is appear at hand of player
		if (_currentBulletType == BulletType::BulletFromPlayer_Rocket)
		{
			if (_rocketNumbers > 0)
			{
				bullet = new Bullet(_currentBulletType, getPositionOfGun().x, getPositionOfGun().y, directionOfBullet, 800);
				//add to currentObjectList
				TileGrid::AddObjectToCurrentObjectList(bullet);
				_rocketNumbers--;
			}
		}
		else
		{
			if (isHasSpecialAbility(ShootLonger_PSA))
				bullet = new Bullet(_currentBulletType, getPositionOfGun().x, getPositionOfGun().y, directionOfBullet, 800);
			else
				bullet = new Bullet(_currentBulletType, getPositionOfGun().x, getPositionOfGun().y, directionOfBullet, 300);
			//add to currentObjectList
			TileGrid::AddObjectToCurrentObjectList(bullet);
		}
		
		
		
			
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