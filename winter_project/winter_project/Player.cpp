#include "pch.h"
#include "Player.h"
//#include "object.h"

//Player::Player():Object(ObjectType::Player) {
//	
//}
//Player::~Player() {
//
//}
void Player::Init() {
	_stat.Hp = 100;
	_stat.MaxHP = 100;
	_stat.speed = 500;

	_pos.x = 400;
	_pos.y = 500;
};
void Player::Update() {

};
void Player::Render(HDC hdc) {

}