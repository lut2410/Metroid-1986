#ifndef AABB_H
#define AABB_H
#include <windows.h>		// to parse to RECT
#include <d3dx9.h>


enum Direction{
	None_Direction=0,
	Left_Direction = 1<<0,
	Right_Direction = 1<<1,
	Top_Direction = 1<<2,
	Bottom_Direction = 1<<3,
	TopLeft_Direction = 1<<4,
	TopRight_Direction = 1<<5,
	BottomLeft_Direction = 1<<6,
	BottomRight_Direction = 1<<7,
	Adjacent_Direction = 1<<8
};

struct Box{
	float x, y;
	float width, height;
	Box();
	Box(float, float, float, float);
	RECT ToRect();
	
};

bool isCollide(Box, Box);
bool isCollideR(RECT, RECT);
void setDirection(Direction& _direction, Direction direction);
void addDirection(Direction& _direction, Direction direction);
void removeDirection(Direction& _direction, Direction direction);
bool isHasDirection(Direction& _direction, Direction direction);

#endif
