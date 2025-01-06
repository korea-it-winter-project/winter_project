#include "vector2.h"


class player {
public :
	Vector2 before_pos;
	Vector2 pos;
	Vector2 dir;
	int hp;

	void move() {

		if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP)) pos.y -= 1;
		if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT))pos.x -= 1;
		if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN))pos.y += 1;
		if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT))pos.x += 1;
	}
	//void get_hp() { return hp; }
};