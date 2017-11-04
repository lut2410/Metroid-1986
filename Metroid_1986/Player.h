#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"



class Player :public GameObject {
public:
	Player();
	Player(int x, int y);
	~Player();
	void Update(int time);
	void Draw();
};
#endif

