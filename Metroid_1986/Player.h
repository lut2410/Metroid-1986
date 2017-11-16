#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "Camera.h"

#define SPEED_X 0.16f
#define SPEED_Y 0.4f
#define MAX_HEIGHT_JUMP 70.0f
#define MAX_VEL_JUMP 0.5f
#define ACCELERATION -0.0015f
enum FootAction{
	StandOrRun,
	Jump,
	RollingJump,
	Grovel
};
enum DirectionOfMotion{
	Neutral,
	Left,
	Right
};
//enum PutHandUp{
//	No,
//	Yes,
//};
//enum Shoot{
//	No,
//	Yes
//};

class Player :public GameObject {
	//friend class Camera;
	float _acc;//acceleration of jump
	//key support
	bool _upKey;
	bool _downKey;
	bool _jumpKey;


	FootAction _footAction;
	DirectionOfMotion _directionOfMotion;//transform of position X : left or right?
	bool _putHandUp;//is putting hand up?
	bool _shoot;//is shooting?

	//Sprites
	Sprite* _standIntro_Spr;
	Sprite* _stand_Spr;
	Sprite* _stand_PutHandUp_Spr;
	Sprite* _run_Spr;
	Sprite* _run_PutHandUp_Spr;
	Sprite* _jump_Spr;
	Sprite* _jump_PutHandUp_Spr;
	Sprite* _rollingJump_Spr;
	Sprite* _grovel_Spr;
	//shoot sprite, other action don't have shoot sprite because of non-existing, or because shoot sprite don't different nomal sprite	
	Sprite* _stand_PutHandUp_Shoot_Spr;
	Sprite* _run_Shoot_Spr;
	Sprite* _jump_Shoot_Spr;
	Sprite* _jump_PutHandUp_Shoot_Spr;
public:
	Player();
	Player(int x, int y);
	~Player();
	DirectionOfMotion getDirectionOfMotion();

	void Update(int time);	//update frame of sprite and position of sprite
	void Draw();
	void Draw(Camera* camera);

	//Action
	void IdentifyDirectionOfMotion_KeyPress(int KeyCode);//identify direction and  base on key pressed
	void IdentifyDirectionOfMotion_KeyRelease(int KeyCode);//identify direction and  base on key released
	void IdentifyFootAction_KeyPress(int KeyCode);
	void IdentifyFootAction_KeyRelease(int KeyCode);
	void IdentifyHavingPutHandUp_KeyPress();
	void IdentifyHavingPutHandUp_KeyRelease();
};
#endif

