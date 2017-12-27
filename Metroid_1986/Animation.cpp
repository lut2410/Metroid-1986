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
	if (it->second[0] <= it->second[1])
		for (int index = it->second[0]; index <= it->second[1]; index++)//index increase base index
			_spriteList->push_back(Sprite(texture, index));
	else //import decrease. ex: 3->1 : sprite[3]->sprite[2]->sprite[1]
		for (int index = it->second[1]; index >= it->second[0]; index++)	
		_spriteList->push_back(Sprite(texture, index));
}
Animation::~Animation(){}


void Animation::SetIndex(int index){
	_currentFrameIndex = index;
}
int Animation::getCurrentFrameIndex(){
	return _currentFrameIndex;
}
Box Animation::getCurrentSpriteSize(){
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
void Animation::DrawFlicker(int x, int y){
	if (flicker == false)
	{
		_spriteList->at(_currentFrameIndex).Draw(x, y);
		flicker = true;
	}
	else
		flicker = false;
	//_spriteList->at(_currentFrameIndex).Draw(x, y);
}
void Animation::DrawFlipHorizontal(int x, int y)
{

	_spriteList->at(_currentFrameIndex).DrawFlipHorizontal(x, y);
}

void Animation::DrawFlipHorizontalFlicker(int x, int y)
{
	if (flicker == false)
	{
		_spriteList->at(_currentFrameIndex).DrawFlipHorizontal(x, y);
		flicker = true;
	}
	else
		flicker = false;
	
}