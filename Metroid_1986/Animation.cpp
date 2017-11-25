#include "Animation.h"

Animation::Animation(){

	_currentFrameIndex = 0;
	_timeAnimation = -1;
	_timeLocal = 0;
};
Animation::Animation(const Animation& animation){
	_spriteList = animation._spriteList;
	_currentFrameIndex = animation._currentFrameIndex;
	_timeAnimation = animation._timeAnimation;
	_timeLocal = animation._timeLocal;
};
Animation::Animation(Texture2* texture, string name){
	_spriteList = new vector<Sprite>();
	auto it = texture->_animationList->find(name);
	//set timeanimation 
	_timeAnimation = it->second[2];
	//import sprite to list
	for (int index = it->second[0]; index <= it->second[1]; index++)//index increase base index
		_spriteList->push_back(Sprite(texture, index));
}
Animation::~Animation(){}


void Animation::SetIndex(int index){
	_currentFrameIndex = index;
}
int Animation::getCurrentFrameIndex(){
	return _currentFrameIndex;
}
Box	Animation::getSpriteSize(){
	return _spriteList->at(_currentFrameIndex).getSpriteSize();
};
void Animation::Next(){
	if (_currentFrameIndex < _spriteList->size()-1)
		_currentFrameIndex++;
	else
		_currentFrameIndex = 0;
}
void Animation::Update(int t){
	if (_timeAnimation < 0)			//no update
		return;
	_timeLocal += t;
	if (_timeLocal >= _timeAnimation)
	{
		_timeLocal = 0;
		this->Next();
	}
}

void Animation::Draw(int x, int y){
	_spriteList->at(_currentFrameIndex).Draw(x,y);
}
void Animation::DrawFlipHorizontal(int x, int y)
{
	_spriteList->at(_currentFrameIndex).DrawFlipHorizontal(x, y);
}
