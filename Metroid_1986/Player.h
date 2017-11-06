#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"


#define SPEED_X 0.4f
#define SPEED_Y 0.4f
#define MAX_HEIGHT_JUMP 70.0f
#define MAX_VEL_JUMP -0.7f
#define ACCELERATION 0.005f
enum FootAction{
	Stand,
	Run,
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
	float _acc;//acceleration of jump
	FootAction _footAction;
	DirectionOfMotion _directionOfMotion;//transform of position X : left or right?
	bool _putHandUp;//is putting hand up?
	bool _shoot;//is shooting?

	//Sprites
	Sprite* _standIntro_Spr;
	Sprite* _stand_Spr;
	Sprite* _standPutHandUp_Spr;
	Sprite* _run_Spr;
	Sprite* _jump_Spr;
	Sprite* _rollingJump_Spr;
	Sprite* _grovel_Spr;

public:
	Player();
	Player(int x, int y);
	~Player();
	void Update(int time);	//update frame of sprite and position of sprite
	void Draw();

	//Action
	void IdentifyDirectionOfMotion_KeyPress(int KeyCode);//identify direction and  base on key pressed
	void IdentifyDirectionOfMotion_KeyRelease(int KeyCode);//identify direction and  base on key released
	void IdentifyFootAction_KeyPress(int KeyCode);
	void IdentifyFootAction_KeyRelease(int KeyCode);
	void IdentifyHavingPutHandUp_KeyPress();
	void IdentifyHavingPutHandUp_KeyRelease();
};
#endif

