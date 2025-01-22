#pragma once

// �̱��� ���� ��ũ�� ����
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


// Windows ���� ��� ���� (�ʿ��� �ּ����� �͸� ����)
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN    // Windows ������� ���� ������ �ʴ� ������ �����մϴ�.
#include <windows.h>

// C ��Ÿ�� ���� ��� ����
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <crtdbg.h>

// C++ ǥ�� ���̺귯�� ��� ����
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <format>

// ������Ʈ ���� ��� ����
#include "sceneManager.h"
#include "Game.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Scene.h"
#include "Fpoint.h"
#include "Player.h"
#include "object.h"


// ����� ���� ���� (����� ���忡�� �޸� �Ҵ� ����)
#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif
