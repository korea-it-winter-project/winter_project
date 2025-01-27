#pragma once
#include "Scene.h"

class GameScene :public Scene {
public :
	GameScene();
	virtual ~GameScene() override;

	virtual void Init(HWND hwnd)override;
	virtual void Update()override;
	virtual void Render(HDC hdc)override;
	

};
