#include "Animation.h"

Animation::Animation(){

	_currentIndex = 0;
	_timeAnimation = -1;
	_timeLocal = 0;
};
Animation::Animation(const Animation& animation){
	_spriteList = animation._spriteList;
	_currentIndex = animation._currentIndex;
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


void Animation::SelectIndex(int index){
	_currentIndex = index;
}
int Animation::getCurrentIndex(){
	return _currentIndex;
}
void Animation::Next(){
	if (_currentIndex < _spriteList->size()-1)
		_currentIndex++;
	else
		_currentIndex = 0;
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
	_spriteList->at(_currentIndex).Draw(x,y);
}
void Animation::DrawFlipHorizontal(int x, int y)
{
	_spriteList->at(_currentIndex).DrawFlipHorizontal(x, y);
}
