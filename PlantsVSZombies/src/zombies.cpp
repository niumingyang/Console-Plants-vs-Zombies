#include "../include/common.h"

void Zombie::change_eat(bool flag){
    eating = flag;
}

int Zombie::get_HP(){
    return HP;
}

int Zombie::get_x(){
    return x;
}

int Zombie::get_y(){
    return y;
}

int Zombie::get_score(){
    return score;
}

void Zombie::printName(int color){
    cout << "#";
    switch (color){
        case ANY: if (slowdown) cout << _BLUE; break;
        case WHITE: cout << _WHITE;  break;
        case RED:   cout << _RED;    break;
        case YELLOW:cout << _YELLOW; break;
        case BLUE:  cout << _BLUE;   break;
    }
	cout << name << _NONE;
}

void Zombie::printHP(){
    int rat = HP*100/maxHP;
    if (rat==100) cout << "#   100%   ";
    else if (rat>=10) cout << "#    " << rat << "%   ";
    else cout << "#     " << rat << "%   ";
}

void Zombie::hit(int att, int kind){
    HP -= att;
    if (kind == SNOWBULLET){
        if (!slowdown){
            slowdown = true;
            speed *= 2;
        }
    }
}

bool Zombie::move(Map& m){
    if (!eating) {
		cnt++;
		if (cnt >= speed) {
            cnt = 0;
			m.blocks[x][y].delZombie(this);
			y--;
			if (y < 0)
				return true;
			m.blocks[x][y].addZombie(this);
		}
	}
	else {
		m.blocks[x][y].eatPlant(attack);
        if (m.blocks[x][y]._plant == nullptr){
            changepathcnt = 0;
            return false;
        }
        if (m.blocks[x][y].plantonplant == nullptr && m.blocks[x][y]._plant->get_changepath()){
            changepathcnt++;
            if (changepathcnt >= changepathCD){
                changepathcnt = 0;
                m.blocks[x][y].delZombie(this);
                if (x == 0) x++;
                else if (x == ALL_ROW-1) x--;
                else {
                    if (rand()%2) x++;
                    else x--;
                }
                m.blocks[x][y].addZombie(this);
            }
        }
	}
    return false;
}

NormalZombie::NormalZombie(int _x, int _y){
    name = " ÆÕÍ¨½©Ê¬ ";
    maxHP = HP = 270;
    x = _x;
    y = _y;
    attack = 10;
    speed = 55;
    cnt = 0;
    eating = false;
    slowdown = false;
    score = 50;
    changepathCD = 5;
    changepathcnt = 0;
}

bool NormalZombie::run(Map& m){
    return move(m);
}

ConeheadZombie::ConeheadZombie(int _x, int _y){
    name = " Â·ÕÏ½©Ê¬ ";
    maxHP = HP = 640;
    x = _x;
    y = _y;
    attack = 10;
    speed = 55;
    cnt = 0;
    eating = false;
    slowdown = false;
    score = 100;
    changepathCD = 5;
    changepathcnt = 0;
}

bool ConeheadZombie::run(Map& m){
    return move(m);
}

NewspaperZombie::NewspaperZombie(int _x, int _y){
    name = " ¶Á±¨½©Ê¬ ";
    maxHP = HP = 420;
    x = _x;
    y = _y;
    attack = 10;
    speed = 55;
    cnt = 0;
    eating = false;
    slowdown = false;
    score = 150;
    changepathCD = 5;
    changepathcnt = 0;
    criticalpoint = 270;
    flag = false;
}

bool NewspaperZombie::run(Map& m){
    if (HP <= criticalpoint && !flag){
        flag = true;
        speed = speed * 18 / 55;
    }
    return move(m);
}

PoleVaultingZombie::PoleVaultingZombie(int _x, int _y){
    name = " ³Å¸Ë½©Ê¬ ";
    maxHP = HP = 500;
    x = _x;
    y = _y;
    attack = 10;
    speed = 25;
    cnt = 0;
    eating = false;
    slowdown = false;
    score = 150;
    changepathCD = 5;
    changepathcnt = 0;
    flag = false;
}

bool PoleVaultingZombie::run(Map& m){
    if (eating && !flag && m.blocks[x][y]._plant->get_jumpover()){
        m.blocks[x][y].delZombie(this);
		y--;
        if (y < 0) return true;
		m.blocks[x][y].addZombie(this);
        flag = true;
        speed = speed * 55 / 25;
    }
    return move(m);
}

JackInTheBoxZombie::JackInTheBoxZombie(int _x, int _y){
    name = " Ð¡³ó½©Ê¬ ";
    maxHP = HP = 500;
    x = _x;
    y = _y;
    attack = 10;
    speed = 22;
    cnt = 0;
    eating = false;
    slowdown = false;
    score = 200;
    changepathCD = 5;
    changepathcnt = 0;
    bombattack = 1800;
    bombblock = (rand()%2 ? rand()%3 : rand()%(ALL_COLUMN-3)+3);
}

bool JackInTheBoxZombie::run(Map& m){
    if (y == bombblock){
        HP = 0;
        for (int i = x-1; i <= x+1; ++i)
            for (int j = y-1; j <= y+1; ++j)
                if (i >= 0 && i < ALL_ROW && j >= 0 && j <= ALL_COLUMN)
                    m.blocks[i][j].eatPlant(bombattack);
    }
    return move(m);
}

CatapultZombie::CatapultZombie(int _x, int _y){
    name = " Í¶Ê¯½©Ê¬ ";
    maxHP = HP = 850;
    x = _x;
    y = _y;
    attack = 100;
    speed = 70;
    cnt = 0;
    eating = false;
    slowdown = false;
    score = 200;
    changepathCD = 5;
    changepathcnt = 0;
    ballnum = 20;
    ballattack = 50;
    ballspeed = 25;
    ballcnt = 0;
}

bool CatapultZombie::run(Map& m){
    if (ballnum > 0){
        int PlantOnPath = -1;
        for (int j = 0; j <= y; j++) {
		    if (m.blocks[x][j]._plant != nullptr) {
			    PlantOnPath = j; 
                break;
		    }
	    }
        if (PlantOnPath == -1){
            ballcnt = 0;
            return move(m);
        }
        else {
            ballcnt++;
            if (ballcnt >= ballspeed){
                ballcnt = 0;
                m.blocks[x][PlantOnPath].eatPlant(ballattack, 1);
                ballnum--;
            }
            return false;
        }
    }
    else return move(m);
}