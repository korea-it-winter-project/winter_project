#pragma once

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


#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <windows.h>
// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <list>
#include <map>
#include <string>
#include<algorithm>
#include <unordered_map>
#include "Game.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Fpoint.h"
//#include "Player.h"
using namespace std;

#include <format>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif

