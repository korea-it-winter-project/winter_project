#include "pch.h"
#include "Player.h"
#include "DevScene.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"

//FPOINT pos = { 300,300 };
float _speed = 1000;

DevScene::DevScene() {

}
DevScene::~DevScene() {

}
void DevScene::Init() {
	_player = new Player();
	_player->Init ();
}
void DevScene::Update() {
	
}
void DevScene::Render(HDC hdc) {
	//Rectangle(hdc, (int)_pos.x - 25, (int)_pos.y - 25, (int)_pos.x + 25, (int)_pos.y + 25);
}
