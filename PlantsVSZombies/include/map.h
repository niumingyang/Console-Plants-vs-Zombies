#pragma once
#include <vector>
#define ALL_ROW 3
#define ALL_COLUMN 7

class Game;
class Plant;
class Zombie;
class Bullet;

class Block{
  public:
    int x, y;
    Plant* _plant;
    Plant* plantonplant;
    std::vector<Zombie*> zombies;
    std::vector<Bullet*> bullets;
    bool selected;
    Block();
    void set(int _x, int _y);
    void delZombie(Zombie *z);
    void addZombie(Zombie *z);
    void delBullet(Bullet *p);
    void addBullet(Bullet *p);
    bool addPlant(int choice);
    void delPlant();
    void delPlantOnPlant();
    void eatPlant(int att, int whichfirst = 0);
    void restart();
};

class Map{
  public:
    Map();
    Block blocks[ALL_ROW][ALL_COLUMN+1];
    void update(Game& _game);
    void restart();
};