#ifndef AABB_H
#define AABB_H
#include <windows.h>		// to parse to RECT
#include <d3dx9.h>


enum DirectionOfCollision{
	None_DOF,
	Left_DOF,
	Right_DOF,
	Top_DOF,
	Bottom_DOF,
	TopLeft_DOF,
	TopRight_DOF,
	BottomLeft_DOF,
	BottomRight_DOF,
	Adjacent_DOF
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
