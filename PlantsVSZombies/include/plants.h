#pragma once
#define MAX_PLANT_NUMBER 10

class Game;

class Plant{
  protected:
    std::string name;
    int x, y;
    int maxHP;
    int HP;
    bool jumpover;//是否能被撑杆僵尸越过
    bool changepath;//是否能使僵尸改变道路
    bool OnGrassland;//能否种在草地上
    bool OnPlant;//能否种在植物上
  public:
    int get_HP();
    bool get_changepath();
    bool get_OnGrassland();
    bool get_OnPlant();
    bool get_jumpover();
    void hit(int att);
    void printName(int color);
    void printHP();
    virtual void run(Game& _game){}
};

class Peashooter: public Plant{
  private:
    int attack;
    int speed;
    int cnt;
    int bulletspeed;
  public:
    Peashooter(int _x, int _y);
    void run(Game& _game);
};

class Sunflower: public Plant{
  private:
    int attack;
    int speed;
    int cnt;
  public:
    Sunflower(int _x, int _y);
    void run(Game& _game);
};

class Repeater: public Plant{
  private:
    int attack;
    int speed;
    int cnt;
    int bulletspeed;
  public:
    Repeater(int _x, int _y);
    void run(Game& _game);
};

class Snowpea: public Plant{
  private:
    int attack;
    int speed;
    int cnt;
    int bulletspeed;
  public:
    Snowpea(int _x, int _y);
    void run(Game& _game);
};

class Wallnut: public Plant{
  public:
    Wallnut(int _x, int _y);
    void run(Game& _game){};
};

class Tallnut: public Plant{
  public:
    Tallnut(int _x, int _y);
    void run(Game& _game){};
};

class Squash: public Plant{
  private:
    int attack;
  public:
    Squash(int _x, int _y);
    void run(Game& _game);
};

class Cherrybomb: public Plant{
  private:
    int attack;
    int preparetime;
    int cnt;
  public:
    Cherrybomb(int _x, int _y);
    void run(Game& _game);
};

class Gralic: public Plant{
  public:
    Gralic(int _x, int _y);
    void run(Game& _game){};
};

class Pumpkin: public Plant{
  public:
    Pumpkin(int _x, int _y);
    void run(Game& _game){};
};

/*
加入植物：
在common.h中加入enum
在plant.h中修改宏MAX_PLANT_NUMBER
在plant.h声明，在plant.cpp定义
在store.cpp中初始化PlangCard
在map.cpp的addPlant函数中加入choice
在common.h中将新类设置为友元
*/