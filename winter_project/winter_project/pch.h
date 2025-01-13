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
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
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

