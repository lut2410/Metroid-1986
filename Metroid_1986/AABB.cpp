#include "AABB.h"
Box::Box(float x, float y, float w, float h){
	_x = x;
	_y = y;
	_w = w;
	_h = h;
};
bool collide(Box a, Box b){
	return !(b._x > a._x+a._w
		|| b._x+b._w < a._x
		|| b._y + b._h < a._y
		|| b._y > a._y + a._h);
};