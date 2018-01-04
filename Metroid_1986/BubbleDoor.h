#ifndef BUBBLEDOOR_H
#define BUBBLEDOOR_H

#pragma once
#include "GameObject.h"
#include "Collision.h"
#define TIMEOPEN 1000
enum BubbleDoorAction{
	Close_BDA,
	Open_BDA,
	Openning_BDA,
	Closing_BDA
};
class BubbleDoor : public GameObject{
	int _type;
	BubbleDoorAction _action;
	int _remainningTimeToAutoClose;
	int _countdownFrames;
public:
	BubbleDoor();
	BubbleDoor(int x, int y, int type =1);
	void Update(int deltaTime);
	void Update2(int deltaTime);
	void Draw(Camera* camera);
	void ChangeAction();
	void BeWounded(int lossHP = 1);	//openning
	void Open();
	void Openning();
	void Closing();
	void Close();
	~BubbleDoor();
};
#endif