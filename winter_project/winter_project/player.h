#include "init.h"

class player {
public :
	Vector2 before_pos;
	Vector2 pos;
	Vector2 dir;
	Vector2 size;
	bool is_ground;
	int hp;
	float gravity;
	float velocityY;

	void pc_init(float gravity) {
		is_ground = false;
		pos = zero();
		this->gravity = gravity;
	}
	void move() {
		before_pos = pos;
		if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP)) pos.y -= 1;
		if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT))pos.x -= 1;
		if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN))pos.y += 1;
		if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT))pos.x += 1;
	}
	void update_dir(Vector2 mouse_pos) {
		dir.x = pos.x - mouse_pos.x;
		dir.y = pos.y - mouse_pos.y;
		dir.x = dir.x / lengthpts(pos.x, pos.y, mouse_pos.x, mouse_pos.y);
		dir.y = dir.y / lengthpts(pos.x, pos.y, mouse_pos.x, mouse_pos.y);
	}//void get_hp() { return hp; }
};