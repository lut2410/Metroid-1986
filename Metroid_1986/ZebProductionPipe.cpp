#include "ZebProductionPipe.h"

ZebProductionPipe::ZebProductionPipe(){}
ZebProductionPipe::ZebProductionPipe(int x, int y, int type) :GameObject(ZebProductionPipe_ID, x, y, 0, 0){
	Texture2* zebPipeTexture = NULL;
	zebPipeTexture = TextureCollection::getInstance()->getTexture2(ZebProductionPipe_ID);
	switch (type)
	{
	case 1:
		_attack = 1;		//use to create the right zeb type
		//take animation of its type( type1 in here)
		_actionAnimation.push_back(new Animation(zebPipeTexture, "BluePipe"));
		break;
	case 2:
		_attack = 2;		//use to create the right zeb type
		OBJECT_VEL = 0.25f;
		_actionAnimation.push_back(new Animation(zebPipeTexture, "RedPipe"));
		break;
	}
	//set default action and animation
	_action = ZebProductionPipeAction::ReadyProduce_ZebProductionPipeA;
	_currentAnimation = _actionAnimation[_action];	//actually _actionAnimation just have 1 animation 
	_remainningTime = TIME_TO_PRODUCE_NEW_ZEB;
}
void ZebProductionPipe::Update(int deltaTime)
{
	//update time
	if (_remainningTime >= 0)
	{
		_remainningTime -= deltaTime;
		//_action = ZebProductionPipeAction::DontReadyProduce_ZebProductionPipeA;
		_hp = 0;
	}

	else
		//ready
	{
		_remainningTime = TIME_TO_PRODUCE_NEW_ZEB;
		//_action = ZebProductionPipeAction::ReadyProduce_ZebProductionPipeA;
		_hp = 1;
	}
		




}
void ZebProductionPipe::Draw(Camera* camera)
{
	D3DXVECTOR2 center = camera->Transform(_posX, _posY);
	_currentAnimation->Draw(center.x, center.y);
}