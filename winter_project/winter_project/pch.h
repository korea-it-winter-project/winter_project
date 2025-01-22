#pragma once

// 싱글턴 패턴 매크로 정의
#define DECLARE_SINGLE(classname)        \
private:                                  \
    classname() { }                       \
public:                                   \
    static classname* GetInstance()      \
{                                         \
    static classname s_instance;         \
    return &s_instance;                   \
}
#define GET_SINGLE(classname) classname::GetInstance()


// Windows 관련 헤더 파일 (필요한 최소한의 것만 포함)
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN    // Windows 헤더에서 거의 사용되지 않는 내용을 제외합니다.
#include <windows.h>

// C 런타임 관련 헤더 파일
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <crtdbg.h>

// C++ 표준 라이브러리 헤더 파일
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <format>

// 프로젝트 관련 헤더 파일
#include "sceneManager.h"
#include "Game.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Scene.h"
#include "Fpoint.h"
#include "Player.h"
#include "object.h"


// 디버깅 관련 설정 (디버그 빌드에서 메모리 할당 추적)
#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif
