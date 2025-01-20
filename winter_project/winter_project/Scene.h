#pragma once
#include "pch.h"

class Scene {
public:
	Scene();
	virtual ~Scene();

	virtual void Init()abstract;
	virtual void Render(HDC hdc)abstract;
	virtual void Update()abstract;
};

