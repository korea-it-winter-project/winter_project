#pragma once
#include "pch.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"


class Game {

public:
	Game();
	~Game();
	void Init(HWND hwnd);
	void Update();
	void Render();
	void SceneSzieCH(HWND hwnd);
private:
	HWND _hwnd = {};
	HDC _hdc = {};

	/////////double buffer
	RECT _rect;
	HDC _hdcBack = {};
	HDC _hdcText = {};
	HBITMAP _tempBack = {};

	//Camera camera;
};
