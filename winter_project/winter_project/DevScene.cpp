#include "pch.h"
#include "Player.h"
#include "DevScene.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"

FPOINT pos = { 300,300 };
float _speed = 1000;

DevScene::DevScene() {

}
DevScene::~DevScene() {

}
void DevScene::Init(HWND hwnd) {
	_player = new Player();
	_player->Init ();
}
void DevScene::Update() {
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	if (GET_SINGLE(InputManager)->GetButton(keytype::A))
		pos.x -= _speed * deltaTime;
	if (GET_SINGLE(InputManager)->GetButton(keytype::D))
		pos.x += _speed * deltaTime;
	if (GET_SINGLE(InputManager)->GetButton(keytype::W))
		pos.y -= _speed * deltaTime;

	if (GET_SINGLE(InputManager)->GetButton(keytype::S))
		pos.y += _speed * deltaTime;
}
void DevScene::Render(HDC hdc) {
	Rectangle(hdc, (int)pos.x - 25, (int)pos.y - 25, (int)pos.x + 25, (int)pos.y + 25);
}
