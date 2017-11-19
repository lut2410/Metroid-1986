#ifndef AABB_H
#define AABB_H

struct Box{
	float _x, _y;
	float _w, _h;
	Box(float, float, float, float);
	
};
bool collide(Box, Box);
#endif
