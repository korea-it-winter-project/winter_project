class Npc {
	int hp;
	int speed;
	int dmg;
public:
	
};
void add_Gravity(player* pc) {
	if (pc->is_ground == false) {
		pc->velocityY += pc->gravity;
	}
	else {
		pc->velocityY = 0;
	}
	pc->pos.y += pc->velocityY;
}