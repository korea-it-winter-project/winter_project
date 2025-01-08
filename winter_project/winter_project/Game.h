#pragma once
#include "pch.h"

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
	/*Game();
	~Game();*/
public:
	void Init(HWND hwnd);
	void Update();
	void Render();
private:
	HWND _hwnd = {};
	HDC _hdc = {};
};