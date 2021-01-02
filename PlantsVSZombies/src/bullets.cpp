#include "../include/common.h"

Bullet::Bullet(int _speed, int _attack, int _x, int _y, int _kind){
    speed = _speed;
	attack = _attack;
	hit = false;
	cnt = 0;
	x = _x;
	y = _y;
    kind = _kind;
}

bool Bullet::get_hit(){
	return hit;
}

int Bullet::get_x(){
	return x;
}

int Bullet::get_y(){
	return y;
}

void Bullet::move(Map &m){
	cnt++;
	if (m.blocks[x][y].zombies.size() > 0) {
		m.blocks[x][y].zombies[0]->hit(attack, kind);
		hit = true;
        m.blocks[x][y].delBullet(this);
		return;
	}
	if (cnt == speed) {
		cnt = 0;
        m.blocks[x][y].delBullet(this);
		if (y==ALL_COLUMN){
			hit = true;
			return;
		}
		y++;
		if (m.blocks[x][y].zombies.size() > 0) {
			m.blocks[x][y].zombies[0]->hit(attack, kind);
			hit = true;
			return;
		}
        m.blocks[x][y].addBullet(this);
	}
}