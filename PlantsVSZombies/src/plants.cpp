#include "../include/common.h"

int Plant::get_HP(){
	return HP;
}

bool Plant::get_changepath(){
	return changepath;
}

bool Plant::get_OnGrassland(){
    return OnGrassland;
}

bool Plant::get_OnPlant(){
    return OnPlant;
}

bool Plant::get_jumpover(){
    return jumpover;
}

void Plant::hit(int att){
	HP -= att;
}

void Plant::printName(int color){
	cout << "#";
    switch (color){
        case WHITE: cout << _WHITE;  break;
        case RED:   cout << _RED;    break;
        case YELLOW:cout << _YELLOW; break;
        case BLUE:  cout << _BLUE;   break;
    }
	cout << name << _NONE;
}

void Plant::printHP(){
    if (OnGrassland){
        int rat = HP*100/maxHP;
        if (rat==100) cout << "#   100%   ";
        else if (rat>=10) cout << "#    " << rat << "%   ";
        else cout << "#     " << rat << "%   ";
    }
    else if (OnPlant){
        int rat = HP*100/maxHP;
        if (rat==100) cout << "100%";
        else if (rat>=10) cout << " " << rat << "%";
        else cout << "  " << rat << "%";
    }
}

Peashooter::Peashooter(int _x, int _y){
    name = " 豌豆射手 ";
    maxHP = HP = 300;
    x = _x;
	y = _y;
    attack = 20;
    speed = 14;
    cnt = 0;
    bulletspeed = 10;
    jumpover = true;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
}

void Peashooter::run(Game& _game){
	bool ZombiesOnPath = false;
	for (int j = y; j <= ALL_COLUMN; j++) {
		if (_game.map.blocks[x][j].zombies.size() != 0) {
			ZombiesOnPath = true; 
            break;
		}
	}
	if (ZombiesOnPath) {
		cnt++;
		if (cnt >= speed) {
			cnt = 0;
			Bullet *p = new Bullet(bulletspeed, attack, x, y, NORMALBULLET);
			_game.AddBullet(p);
            _game.map.blocks[x][y].addBullet(p);
		}
	}
}

Sunflower::Sunflower(int _x, int _y){
    name = "  向日葵  ";
    maxHP = HP = 300;
    attack = 50;
    x = _x;
	y = _y;
    speed = 200;
    cnt = 0;
    jumpover = true;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
}

void Sunflower::run(Game& _game){
	cnt++;
	if (cnt >= speed) {
		cnt = 0;
		_game.store.addSun(attack);
	}
}

Repeater::Repeater(int _x, int _y){
    name = " 双发射手 ";
    maxHP = HP = 300;
    x = _x;
	y = _y;
    attack = 20;
    speed = 14;
    cnt = 0;
    bulletspeed = 10;
    jumpover = true;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
}

void Repeater::run(Game& _game){
	bool ZombiesOnPath = false;
	for (int j = y; j <= ALL_COLUMN; j++) {
		if (_game.map.blocks[x][j].zombies.size() != 0) {
			ZombiesOnPath = true; 
            break;
		}
	}
	if (ZombiesOnPath) {
		cnt++;
		if (cnt >= speed) {
			cnt = 0;
			Bullet *p = new Bullet(bulletspeed, attack, x, y, NORMALBULLET);
			_game.AddBullet(p);
            _game.map.blocks[x][y].addBullet(p);
            Bullet *q = new Bullet(bulletspeed, attack, x, y, NORMALBULLET);
			_game.AddBullet(q);
            _game.map.blocks[x][y].addBullet(q);
		}
	}
}

Snowpea::Snowpea(int _x, int _y){
    name = " 寒冰射手 ";
    maxHP = HP = 300;
    x = _x;
	y = _y;
    attack = 20;
    speed = 14;
    cnt = 0;
    bulletspeed = 10;
    jumpover = true;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
}

void Snowpea::run(Game& _game){
	bool ZombiesOnPath = false;
	for (int j = y; j <= ALL_COLUMN; j++) {
		if (_game.map.blocks[x][j].zombies.size() != 0) {
			ZombiesOnPath = true; 
            break;
		}
	}
	if (ZombiesOnPath) {
		cnt++;
		if (cnt >= speed) {
			cnt = 0;
			Bullet *p = new Bullet(bulletspeed, attack, x, y, SNOWBULLET);
			_game.AddBullet(p);
            _game.map.blocks[x][y].addBullet(p);
		}
	}
}

Wallnut::Wallnut(int _x, int _y){
    name = "  坚果墙  ";
    maxHP = HP = 4000;
    x = _x;
	y = _y;
    jumpover = true;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
}

Tallnut::Tallnut(int _x, int _y){
    name = "  高坚果  ";
    maxHP = HP = 8000;
    x = _x;
	y = _y;
    jumpover = false;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
}

Squash::Squash(int _x, int _y){
    name = "   倭瓜   ";
    attack = 1800;
    maxHP = HP = 300;
    x = _x;
	y = _y;
    jumpover = true;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
}

void Squash::run(Game& _game){
    vector<Zombie*>& ZbThis = _game.map.blocks[x][y].zombies;
    vector<Zombie*>& ZbNext = _game.map.blocks[x][y+1].zombies;
	if (ZbThis.size() > 0) {
        for (auto it = ZbThis.begin(); it != ZbThis.end(); it++)
            (*it)->hit(attack, ATTACK);
        _game.map.blocks[x][y].delPlant();
	}
    else if (ZbNext.size() > 0) {
        for (auto it = ZbNext.begin(); it != ZbNext.end(); it++)
            (*it)->hit(attack, ATTACK);
        _game.map.blocks[x][y].delPlant();
	}
}

Cherrybomb::Cherrybomb(int _x, int _y){
    name = " 樱桃炸弹 ";
    attack = 1800;
    maxHP = HP = 300;
    x = _x;
	y = _y;
    jumpover = true;
    preparetime = 10;
    cnt = 0;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
}

void Cherrybomb::run(Game& _game){
	bool ZombiesInrange = false;
    for (int i = x-1; i < x+2; ++i)
        for (int j = y-1; j < y+2; ++j)
            if (i >= 0 && i < ALL_ROW && j >=0 && j <= ALL_COLUMN){
                if (_game.map.blocks[i][j].zombies.size() != 0)
                    ZombiesInrange = true;
            }
	if (ZombiesInrange) {
		cnt++;
		if (cnt >= preparetime) {
            for (int i = x-1; i < x+2; ++i)
                for (int j = y-1; j < y+2; ++j)
                    if (i >= 0 && i < ALL_ROW && j >=0 && j <= ALL_COLUMN){
                        vector<Zombie*>& Zb = _game.map.blocks[i][j].zombies;
                        for (auto it = Zb.begin(); it != Zb.end(); it++)
                            (*it)->hit(attack, ATTACK);
                    }
            
            _game.map.blocks[x][y].delPlant();
		}
	}
}

Gralic::Gralic(int _x, int _y){
    name = "   大蒜   ";
    maxHP = HP = 400;
    x = _x;
	y = _y;
    jumpover = true;
    changepath = true;
    OnGrassland = true;
    OnPlant = false;
}

Pumpkin::Pumpkin(int _x, int _y){
    name = "南瓜头";
    maxHP = HP = 4000;
    x = _x;
	y = _y;
    jumpover = true;
    changepath = false;
    OnGrassland = false;
    OnPlant = true;
}