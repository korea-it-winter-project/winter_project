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

class Player {
public:
	FPOINT pos;		//위치 값
	FPOINT dir;		//방향 값
	FPOINT speed;	//방향 속도 값

public :
	void move(float x, float y);
};