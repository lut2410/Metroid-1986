#ifndef AABB_H
#define AABB_H
#include <windows.h>		// to parse to RECT

struct Box{
	float x, y;
	float width, height;
	Box();
	Box(float, float, float, float);
	RECT ToRect();
	
};
bool collide(Box, Box);
#endif
