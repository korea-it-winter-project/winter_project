#pragma once

//#include "Manager_instance.h"
//#include <BaseTsd.h>
#include "pch.h"


class TimeManager
{
	DECLARE_SINGLE(TimeManager)

	

public:

	void Init();
	void Update();

	UINT32 GetFps() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }

private:
	UINT64 _frequency = 0;
	UINT64 _prevCount = 0;
	float _deltaTime = 0.f;

private:
	UINT32 _frameCount = 0;
	float _frameTime = 0.f;
	UINT32 _fps = 0;
};
