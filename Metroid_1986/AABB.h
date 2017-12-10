#ifndef AABB_H
#define AABB_H
#include <windows.h>		// to parse to RECT
#include <d3dx9.h>


enum Direction{
	None_Direction,
	Left_Direction,
	Right_Direction,
	Top_Direction,
	Bottom_Direction,
	TopLeft_Direction,
	TopRight_Direction,
	BottomLeft_Direction,
	BottomRight_Direction,
	Adjacent_Direction
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

#endif
