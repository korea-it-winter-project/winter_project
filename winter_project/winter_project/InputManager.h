#pragma once
#include "pch.h"

enum class keytype {
	L_mouse = VK_LBUTTON,
	R_mouse = VK_RBUTTON,

	L_Ctrl = VK_CONTROL,
	BACKSP = VK_BACK,
	ESC = VK_ESCAPE,

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
	void Init(HWND hwnd);
	void Update(RECT _rect);


	bool GetButton(keytype key) { return GetState(key) == KeyState::Press; }
	bool GetButtonDwon(keytype key) { return GetState(key) == KeyState::Down; }
	bool GetButtonUP(keytype key) { return GetState(key) == KeyState::Up; }
	POINT GetMousePos() { return _mousePos; }
	int CheckMousePoint(RECT rect) {
		if ((_mousePos.x - rect.left) * (_mousePos.x - rect.right) <= 0 && (_mousePos.y - rect.top) * (_mousePos.y - rect.bottom) <= 0)
			return 1;
		else return 0;
	}
	RECT GetRect() { return rect; }
private:
	KeyState GetState(keytype key) { return _states[static_cast<UINT8>(key)]; }
private:
	HWND _hwnd = 0;
	std::vector <KeyState>_states;
	POINT _mousePos;
	RECT rect;
};
