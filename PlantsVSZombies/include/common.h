#pragma once
#include "map.h"
#include "store.h"
#include "plants.h"
#include "bullets.h"
#include "zombies.h"

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <conio.h>

using namespace std;

#define _WHITE "\e[1;37m"
#define _RED "\e[0;31m"
#define _YELLOW "\e[1;33m"
#define _BLUE "\e[0;34m"
#define _NONE "\e[0m"
#define _BOLD "\e[1m"
#define _REVERSE "\e[7m"
#define _UNDERLNE "\e4m"
enum PVZ_STATE { RUNNING, CHOOSING, BUYING, REMOVING, GAMEOVER };
enum PVZ_ZOMBIE { ZOMBIE, CONEHEAD, NEWSPAPER, POLEVAULTING, JACKINTHEBOX, CATAPULT };
enum PVZ_PLANT { PEASHOOTER, SUNFLOWER, REPEATER, SNOWPEA, WALLNUT, TALLNUT, SQUASH, CHERRYBOMB, GRALIC, PUMPKIN };
enum PVZ_COLOR { ANY, WHITE, RED, YELLOW, BLUE };
enum PVZ_HITKIND { NORMALBULLET, SNOWBULLET, ATTACK };

class Game{
  private:
    Map map;
    Store store;
    vector<Bullet*> bullets;
    vector<Zombie*> zombies;
    // generate zombies
    int cd; //������ʬ��ʱ����
    int cnt; //������ʬ�ļ�ʱ��
    int state; //��ǰ��Ϸ״̬
    int score; //��ǰ��Ϸ�÷�
    // add score
    int scd; //�÷����ӵ�ʱ����
    int scnt; //�÷����ӵļ�ʱ��
    int selected_x, selected_y; //��Ǳ�ѡ�еؿ������
    void GenerateZombies();
    void MoveBullet();
    bool UpdateZombie();
    void DelZombie();
    void updatescore();
    void running();
    void choosing();
    void buying();
    void removing();
    void gameover();
    void printscreen();
  public:
    Game();
    void AddBullet(Bullet* p);
    void run();
    friend class Peashooter;
    friend class Sunflower;
    friend class Repeater;
    friend class Snowpea;
    friend class Wallnut;
    friend class Tallnut;
    friend class Squash;
    friend class Cherrybomb;
    friend class Gralic;
    friend class Pumpkin;
};