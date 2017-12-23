#include "AABB.h"
Box::Box(){
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}
Box::Box(float x, float y, float w, float h){
	this->x = x;
	this->y = y;
	width = w;
	height = h;
};
RECT Box::ToRect(){
	return RECT{ x, y, x + width, y + height };
};
bool isCollide(Box a, Box b){
	return !(b.x > a.x + a.width
		|| b.x + b.width < a.x
		|| b.y + b.height < a.y
		|| b.y > a.y + a.height);
};
bool isCollideR(RECT a, RECT b){
	return !(b.left > a.right
		|| b.right < a.left
		|| b.top < a.bottom
		|| b.bottom > a.top);
};
void setDirection(Direction& _direction, Direction direction){
	if (_direction != direction)
		_direction = direction;
};
void addDirection(Direction& _direction, Direction direction){
	setDirection(_direction, Direction(_direction | direction));
};
void removeDirection(Direction& _direction, Direction direction){
	if (isHasDirection(_direction, direction))
		setDirection(_direction, Direction(_direction & ~direction));
};
bool isHasDirection(Direction& _direction, Direction direction){
	return (_direction & direction) == direction;
};
