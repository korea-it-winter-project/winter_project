#pragma once
#include "pch.h"
#include "SceneManager.h"

#define DECLARE_SINGLE(classname)		\
private:								\
	classname() { }						\
public:									\
	static classname* GetInstance()		\
{										\
static classname s_instance;			\
return &s_instance;						\
}
#define GET_SINGLE(classname) classname::GetInstance()

class Game {
public:
	Game() {
		int* p = new int();
	}
	~Game() {
		GET_SINGLE(SceneManager)->clear();
	}
public:
	void Init(HWND hwnd);
	void Update();
	void Render();
private:
	HWND _hwnd = {};
	HDC _hdc = {};
};