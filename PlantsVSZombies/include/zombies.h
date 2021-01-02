#pragma once
#define MAX_ZOMBIE_NUMBER 6

class Map;

class Zombie{
  protected:
    std::string name;
    int x, y;
    int maxHP;
    int HP;
    int attack;// damage/100ms
    int speed;// 行进速度
    int cnt;// 行进计时器
    int changepathCD;//切换道路CD
    int changepathcnt;//切换道路计时器
    int score;
    bool eating;//是否在吃植物
    bool slowdown;//是否被减速
  public:
    int get_HP();
    int get_x();
    int get_y();
    int get_score();
    void printName(int color);
    void printHP();
    void change_eat(bool flag);
    void hit(int att, int kind);
    bool move(Map& m);
    virtual bool run(Map& m){return false;};
};

class NormalZombie: public Zombie{
  public:
    NormalZombie(int _x, int _y);
    bool run(Map& m);
};
class ConeheadZombie: public Zombie{
  public:
    ConeheadZombie(int _x, int _y);
    bool run(Map& m);
};

class NewspaperZombie: public Zombie{
  private:
    int criticalpoint;//临界点
    bool flag;
  public:
    NewspaperZombie(int _x, int _y);
    bool run(Map& m);
};

class PoleVaultingZombie: public Zombie{
  private:
    bool flag;//表示是否已经跳过植物
  public:
    PoleVaultingZombie(int _x, int _y);
    bool run(Map& m);
};

class JackInTheBoxZombie: public Zombie{
  private:
    int bombblock;//爆炸的格子
    int bombattack;//爆炸伤害
  public:
    JackInTheBoxZombie(int _x, int _y);
    bool run(Map& m);
};

class CatapultZombie: public Zombie{
  private:
    int ballnum;
    int ballattack;
    int ballspeed;
    int ballcnt;
  public:
    CatapultZombie(int _x, int _y);
    bool run(Map& m);
};

/*
加入僵尸：
在common.h在enum中加入僵尸type
修改zombies.h中的MAX_ZOMBIE_NUMBER
在zombies.h中声明，在zombies.cpp中定义
在common.cpp的GenerateZombies函数中加入
*/