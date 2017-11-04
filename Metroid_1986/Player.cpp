#include "Player.h"
Player::Player():GameObject(){
}
Player::Player(int x, int y):GameObject(Player_ID,x,y,0,0) {

}

Player::~Player(){

}
void Player::Update(int t){
	_sprite->Update(t);
}
void Player::Draw(){
	_sprite->Draw(_posX, _posY);
}