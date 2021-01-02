#include "../include/common.h"

void PlantCard::set(string _name, int _CD, int _price){
    name = _name;
    CD = _CD;
    price = _price;
    cnt = 0;
}

void PlantCard::cooling(){
	if (cnt >= CD) return;
	else cnt++;
}

bool PlantCard::cooled(){
    return cnt >= CD;
}

void PlantCard::printName(){
	cout << _YELLOW << name << _NONE;
}

void PlantCard::printPlainName(){
    cout << name;
}

void PlantCard::printPrice(){
	cout << "价格:";
    if (price >= 100) cout << price;
    else cout << ' ' << price;
}

void PlantCard::printCD(){
	cout << "冷却:";
    int _cool = cnt*100/CD;
    if (_cool == 100) cout << _cool << '%';
    else if (_cool >= 10) cout << ' ' << _cool << '%';
    else cout << "  " << _cool << '%';
}

Store::Store(){
    allplant = new PlantCard[MAX_PLANT_NUMBER];
    allplant[0].set("豌豆射手", 75,  100);
    allplant[1].set(" 向日葵 ", 75,  50);
    allplant[2].set("双发射手", 75,  200);
    allplant[3].set("寒冰射手", 75,  175);
    allplant[4].set(" 坚果墙 ", 300, 50);
    allplant[5].set(" 高坚果 ", 300, 125);
    allplant[6].set("  倭瓜  ", 300, 50);
    allplant[7].set("樱桃炸弹", 500, 150);
    allplant[8].set("  大蒜  ", 75,  50);
    allplant[9].set(" 南瓜头 ", 300, 125);
    sun = 200;
    speed = 60;
    cnt = 0;
    selected = -1;
}

void Store::addSun(int add){
    sun += add;
}

int Store::get_sun(){
	return sun;
}

void Store::printInfo(){
	for (int i = 0; i < MAX_PLANT_NUMBER; ++i){
        if (selected == i){
            cout << "    ";
            cout << _REVERSE;
            cout << '*';
            cout << '[' << i << ']';
		    allplant[i].printPlainName();
		    cout << ' ';
		    allplant[i].printPrice();
		    cout << ' ';
		    allplant[i].printCD();
            cout << _NONE;
        }
        else {
            cout << "     ";
            cout << '[' << i << ']';
		    allplant[i].printName();
		    cout << ' ';
		    allplant[i].printPrice();
		    cout << ' ';
		    allplant[i].printCD();
        }
        if (i%2 == 1) cout << '\n';
	}
    if (MAX_PLANT_NUMBER%2) cout << '\n';
}

void Store::run(){
    cnt++;
	if (cnt >= speed) {
		cnt = 0;
		addSun(50);
	}
	for (int i = 0; i < MAX_PLANT_NUMBER; i++) {
		allplant[i].cooling();
	}
}

bool Store::pay(int choice, int x, int y, Map &map){
    if (choice == -1) choice = selected;
	if (sun >= allplant[choice].price && allplant[choice].cooled()) {
		if (map.blocks[x][y].addPlant(choice)) {
			sun -= allplant[choice].price;
			allplant[choice].cnt = 0;
			return true;
		}
	}
	return false;
}

void Store::restart(){
    sun = 200;
    cnt = 0;
    for (int i = 0; i < MAX_PLANT_NUMBER; ++i){
        allplant[i].cnt = 0;
    }
    selected = -1;
}

void Store::initselect(){
    if (selected == -1) selected = 0;
}

void Store::endselect(){
    selected = -1;
}

void Store::changeselect(char ch){
    switch(ch){
        case 72:// up
            selected = (selected+8)%10;
            break;
        case 80:// down
            selected = (selected+2)%10;
            break;
        case 75:// left
            selected = (selected+9)%10;
            break;
        case 77:// right
            selected = (selected+1)%10;
            break;
    }
}