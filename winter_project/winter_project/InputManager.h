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



enum class keytype {
	L_mouse = VK_LBUTTON,
	R_mouse = VK_RBUTTON,

	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,
	SPBAR = VK_SPACE,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
};

enum class KeyState {
	none,
	Press,
	Down,
	Up,
	End
};

enum {
	KEY_TYPE_COUNT = static_cast<INT32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<INT32>(KeyState::End)
};
class InputManager {
	DECLARE_SINGLE(InputManager);
public:
	void init(HWND hwnd);
	void Update();
	bool GetButton(keytype key) { return GetState(key) == KeyState::Press; }
	bool GetButtonDwon(keytype key) { return GetState(key) == KeyState::Down; }
	bool GetButtonUP(keytype key) { return GetState(key) == KeyState::Up; }
	POINT GetMousePos() { return _mousePos; }
private:
	KeyState GetState(keytype key) { return _states[static_cast<UINT8>(key)]; }
private:
	HWND _hwnd = 0;
	std::vector <KeyState>_states;
	POINT _mousePos;
};