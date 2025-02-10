#pragma once
#pragma once
#include "Scene.h"

class StartScene :public Scene {
public:
	StartScene();
	virtual ~StartScene() override;

	virtual void Init()override;
	virtual void Update()override;
	virtual void Render(HDC hdc)override;
};
