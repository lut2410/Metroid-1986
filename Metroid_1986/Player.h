#ifndef PLAYER_H_
#define PLAYER_H_

#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "AABB.h"
#include "Collision.h"
#include "TileGrid.h"
#include "Infor.h"
#define SPEED_WOUND 0.2f
#define TIMEIMMORTAL_WOUNDED 1000
#define SPEED_X 0.16f
#define SPEED_Y -0.01f
#define MAX_HEIGHT_JUMP 70.0f
#define MAX_VEL_JUMP 0.5f
#define ACCELERATION -0.0015f
#define TIMETOCREATNEWBULLET 6 //frames
enum Action{
	None,
	Stand=1 << 0,
	Run = 1 << 1,
	Jump = 1 << 2,
	RollingJump = 1 << 3,
	Grovel = 1 << 4,
	PrepareGrounding = 1 << 5,
	Die = 1 << 6,
	PutHandUp = 1 << 7,
	Shoot = 1 << 8
	
};


enum ActionAnimation{
	StandIntro_Ani=None,
	Stand_Ani=Stand,
	Stand_PutHandUp_Ani=Stand+PutHandUp,
	Run_Ani=Run,
	Jump_Ani=Jump,
	RollingJump_Ani=RollingJump,
	Grovel_Ani=Grovel,
	Stand_Shoot_Ani=Stand+Shoot,
	Run_Shoot_Ani=Run+Shoot,
	Jump_Shoot_Ani= Jump+Shoot,
	Stand_PutHandUp_Shoot_Ani=Stand+PutHandUp+Shoot,
	Run_PutHandUp_Ani = Run + PutHandUp,
	Run_PutHandUp_Shoot_Ani = Run+PutHandUp+Shoot,
	Jump_PutHandUp_Ani=Jump+PutHandUp,
	Jump_PutHandUp_Shoot_Ani=Jump+PutHandUp+Shoot
};
enum PlayerSpecialAbility{
	None_PSA,
	Grovel_PSA = 1 << 0,
	ShootLonger_PSA = 1 << 1,
	ShootIceBeam_PSA = 1 << 2,
	ShootWaveBeam_PSA = 1 << 3,
	ShootRocket_PSA = 1 << 4,
	PutBomb_PSA = 1 << 5
};
enum ActionKey{
	None_Key,
	Up_Key = 1 << 0,
	Down_Key = 1 << 1,
	Left_Key = 1 << 2,
	Right_Key = 1 << 3,
	Jump_Key = 1 << 4,
	Shoot_Key = 1 << 5
};


class Player :public GameObject {

	Action _action;
	PlayerSpecialAbility _specialAbility;
	Block _block;
	bool flicker;							//player is flicker? use for draw
	BulletType _currentBulletType;
	int _rocketNumber;
public:
	//Current Key
	ActionKey _currentKeys;
	Player();
	Player(int x, int y);
	~Player();
	DirectionOfFace getDirectionOfFace();

	bool isHasSpecialAbility(PlayerSpecialAbility );
	void addSpecialAbility(PlayerSpecialAbility );

	void setAction(Action action);
	void addOrChangeAction(Action action);		//add if action is hand action, otherwise change action if action is foot action
	void removeAction(Action action);
	bool isHasAction(Action action);
	bool isHasKey(ActionKey);

	//void PauseGame(int time);
	int getHP();
	void BuffHP(int buffHP);
	int getRocketNumber();
	void BuffRocket(int buffRocketNumber);
	RECT getCollisionBound();					//use for check collision
	D3DXVECTOR2 getPositionOfGun();			//bullet fly-out from hand
	void handleCollision(map<int, GameObject*> objectList,float dt);
	void handleVsWall(Direction d, int dt);				
	void UpdatePosition(int );
	void Update(int time);	//update action and position after press key
	void UpdateAnimationBaseOnStatus();
	void Update2(int time);	//update frame of sprite and position of sprite
	void Draw(Camera* camera);
	void BeWounded(Direction direction,int lossHP);
	void UpdatePostionToInsideCamera();
	//int checkCollision();
	//Action
	void UpdateActionAndVelocity(int deltaTime);				//specify action base on keys are press
	void SpecifyDirectionOfFace();//Specify direction and  base on key pressed
	void SpecifyFootAction();
	void SpecifyHavingPutHandUp();
	void SpecifyHavingShoot();
	void SwitchToOtherBulletType();
	void CreateBullet();
	bool checkToStandUpInThisLocation();
};
#endif

