#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "Camera.h"

#define SPEED_X 0.16f
#define SPEED_Y 0.4f
#define MAX_HEIGHT_JUMP 70.0f
#define MAX_VEL_JUMP 0.5f
#define ACCELERATION -0.0015f

enum Action{
	None,
	Stand=1 << 0,
	Run = 1 << 1,
	Jump = 1 << 2,
	RollingJump = 1 << 3,
	Grovel = 1 << 4,
	Fall = 1 << 5,
	Die = 1 << 6,
	PutHandUp = 1 << 7,
	Shoot = 1 << 8,
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
	Stand_PutHandUp_Shoot_Ani=Stand+PutHandUp+Shoot,
	Run_PutHandUp_Ani = Run + PutHandUp,
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
	//friend class Camera;
	float _acc;//acceleration of jump

	Action _action;
	DirectionOfMotion _directionOfMotion;//transform of position X : left or right?
	//bool _putHandUp;//is putting hand up?
	//bool _shoot;//is shooting?

	vector<Animation*> _actionAnimation;
	
public:
	//Current Key
	ActionKey _currentKeys;
	bool _isStop;		//are both player and game stop? => if yes then don't allow press or release key
	Player();
	Player(int x, int y);
	~Player();
	DirectionOfMotion getDirectionOfMotion();

	void setAction(Action action);
	void addOrChangeAction(Action action);		//add if action is hand action, otherwise change action if action is foot action
	void removeAction(Action action);
	bool isHasAction(Action action);
	bool isHasKey(ActionKey);
	RECT getCollisionRect();
	void UpdatePosition(int );
	void Update(int time);	//update frame of sprite and position of sprite
	void Draw(Camera* camera);

	//Action
	void SpecifyAction();				//specify action base on keys are press
	void SpecifyDirectionOfMotion();//Specify direction and  base on key pressed
	void SpecifyFootAction();
	void SpecifyHavingPutHandUp();
	void SpecifyHavingPutHandUp_KeyRelease();
};
#endif

