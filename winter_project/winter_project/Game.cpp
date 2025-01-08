#include "pch.h"
//#include "Manager_instance.h"
//#include "Game.h"


void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);
	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->init(hwnd);
}

void Game::Update()
{
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
}

void Game::Render() {
    Rectangle(_hdc, 200, 200, 400, 400);
}