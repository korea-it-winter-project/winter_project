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
	FPOINT pos;		//��ġ ��
	FPOINT dir;		//���� ��
	FPOINT speed;	//���� �ӵ� ��

public :
	void move(float x, float y);
};