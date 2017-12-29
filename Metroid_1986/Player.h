#ifndef PLAYER_H_
#define PLAYER_H_

#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "AABB.h"
#include "Collision.h"
#include "TileGrid.h"
#define SPEED_WOUND 0.2f
#define TIMEIMMORTAL_WOUNDED 1000
#define SPEED_X 0.16f
#define SPEED_Y -0.01f
#define MAX_HEIGHT_JUMP 70.0f
#define MAX_VEL_JUMP 0.5f
#define ACCELERATION -0.0015f
#define TIMETOCREATNEWBULLET 5 //frames
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
	Shoot = 1 << 8,
	BeWounded = 1<<9
	
};

enum DirectionOfMotion{
	Neutral,
	Left,
	Right
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
	bool flicker;						//player is flicker? use for draw
	int beWounded_remainningTime;
	Block _block;
	DirectionOfMotion _directionOfMotion;//transform of position X : left or right?
	int _remainningTimeToShoot;
	bool _isAbilityToGrovel;

	
public:
	bool _isMotionless;	//unactive
	//Current Key
	ActionKey _currentKeys;
	Player();
	Player(int x, int y);
	~Player();
	DirectionOfMotion getDirectionOfMotion();

	void setAction(Action action);
	void addOrChangeAction(Action action);		//add if action is hand action, otherwise change action if action is foot action
	void removeAction(Action action);
	bool isHasAction(Action action);
	bool isHasKey(ActionKey);

	//void PauseGame(int time);
	bool isAbilityToGrovel();
	void AddAbilityToGrovel();
	int getHP();
	RECT getCollisionBound();					//use for check collision
	D3DXVECTOR2 getPositionOfHand();			//bullet fly-out from hand
	void handleCollision(map<int, GameObject*> objectList,float dt);
	void handleVsWall(Direction d, int dt);				
	void UpdatePosition(int );
	void Update(int time);	//update action and position after press key
	void Update2(int time);	//update frame of sprite and position of sprite
	void BeWounded(Direction direction,int lossHP);
	void BuffHP(int buffHP);
	void Draw(Camera* camera);
	void UpdatePostionToInsideCamera();
	//int checkCollision();
	//Action
	void SpecifyAction();				//specify action base on keys are press
	bool SpecifyBeWounded();
	void SpecifyDirectionOfMotion();//Specify direction and  base on key pressed
	void SpecifyFootAction();
	void SpecifyHavingPutHandUp();
	void SpecifyHavingShoot();
	void CreateBullet();
	bool checkToStandUpInThisLocation();
};
#endif

