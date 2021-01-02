#include "../include/common.h"

Block::Block(){
    x = y = 0;
	selected = false;
	_plant = nullptr;
    plantonplant = nullptr;
}

void Block::set(int _x, int _y){
	x = _x;
	y = _y;
    selected = false;
	_plant = nullptr;
}

void Block::delZombie(Zombie *z){
	for (auto it = zombies.begin(); it != zombies.end(); ){
		if ((*it)==z){
            it = zombies.erase(it);
            return;
        }
		else it++;
	}
}

void Block::addZombie(Zombie *z){
	zombies.push_back(z);
}

void Block::delBullet(Bullet *p){
    for (auto it = bullets.begin(); it != bullets.end(); ){
		if ((*it)==p){
            it = bullets.erase(it);
            return;
        }
		else it++;
	}
}

void Block::addBullet(Bullet *p){
    bullets.push_back(p);
}

bool Block::addPlant(int choice){
	Plant* newPlant;
	switch(choice){
		case PEASHOOTER: newPlant = new Peashooter(x, y); break;
        case SUNFLOWER:  newPlant = new Sunflower(x, y);  break;
        case REPEATER:   newPlant = new Repeater(x, y);   break;
        case SNOWPEA:    newPlant = new Snowpea(x, y);    break;
        case WALLNUT:    newPlant = new Wallnut(x, y);    break;
        case TALLNUT:    newPlant = new Tallnut(x, y);    break;
        case SQUASH:     newPlant = new Squash(x, y);     break;
        case CHERRYBOMB: newPlant = new Cherrybomb(x, y); break;
        case GRALIC:     newPlant = new Gralic(x, y);     break;
        case PUMPKIN:    newPlant = new Pumpkin(x, y);    break;
	}
    if (_plant == nullptr && newPlant->get_OnGrassland()){
        _plant = newPlant;
        return true;
    }
    else if (_plant != nullptr && plantonplant == nullptr && newPlant->get_OnPlant()){
        plantonplant = newPlant;
        return true;
    }
    else {
        delete newPlant;
	    return false;
    }  
}

void Block::delPlant(){
	delete _plant; 
	_plant = nullptr;
    if (plantonplant != nullptr)
        delPlantOnPlant();
}

void Block::delPlantOnPlant(){
	delete plantonplant; 
	plantonplant = nullptr;
}

void Block::eatPlant(int att, int whichfirst){
    if (whichfirst == 0){
        if (plantonplant != nullptr){
            plantonplant->hit(att);
            if (plantonplant->get_HP() <= 0) {
		    	delPlantOnPlant();
		    }
        }
	    else if (_plant != nullptr) {
		    _plant->hit(att);
		    if (_plant->get_HP() <= 0) {
			    delPlant();
		    }
	    }
    }
    else if (whichfirst == 1){
        if (_plant != nullptr) {
		    _plant->hit(att);
		    if (_plant->get_HP() <= 0) {
			    delPlant();
		    }
	    }
    }
}

void Block::restart(){
    selected = false;
    if (_plant != nullptr)
        delPlant();
    if (plantonplant != nullptr)
        delPlantOnPlant();
    for (auto it = zombies.begin(); it != zombies.end(); ){
        it = zombies.erase(it);
	}
    for (auto it = bullets.begin(); it != bullets.end(); ){
        it = bullets.erase(it);
	}
}

Map::Map(){
	for (int i = 0; i < ALL_ROW; i++) {
		for (int j = 0; j <= ALL_COLUMN; j++) {
			blocks[i][j].set(i, j);
		}
	}
}

void Map::update(Game& _game){
    for (int i = 0; i < ALL_ROW; i++) {
		for (int j = 0; j <= ALL_COLUMN; j++){
            // update zombies
			if (blocks[i][j]._plant != nullptr && blocks[i][j].zombies.size() != 0) {
		        for (auto&var : blocks[i][j].zombies) {
			        var->change_eat(true);
		        }
	        }
	        else if (blocks[i][j]._plant == nullptr && blocks[i][j].zombies.size() != 0) {
		        for (auto&var : blocks[i][j].zombies) {
			        var->change_eat(false);
		        }
	        }
            // update plants
			if (blocks[i][j]._plant != nullptr){
				blocks[i][j]._plant->run(_game);
			}
            if (blocks[i][j].plantonplant != nullptr){
				blocks[i][j].plantonplant->run(_game);
			}
		}
	}
}

void Map::restart(){
    for (int i = 0; i < ALL_ROW; i++)
		for (int j = 0; j <= ALL_COLUMN; j++)
            blocks[i][j].restart();
}