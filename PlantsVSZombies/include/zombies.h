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
    int speed;// �н��ٶ�
    int cnt;// �н���ʱ��
    int changepathCD;//�л���·CD
    int changepathcnt;//�л���·��ʱ��
    int score;
    bool eating;//�Ƿ��ڳ�ֲ��
    bool slowdown;//�Ƿ񱻼���
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
    int criticalpoint;//�ٽ��
    bool flag;
  public:
    NewspaperZombie(int _x, int _y);
    bool run(Map& m);
};

class PoleVaultingZombie: public Zombie{
  private:
    bool flag;//��ʾ�Ƿ��Ѿ�����ֲ��
  public:
    PoleVaultingZombie(int _x, int _y);
    bool run(Map& m);
};

class JackInTheBoxZombie: public Zombie{
  private:
    int bombblock;//��ը�ĸ���
    int bombattack;//��ը�˺�
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
���뽩ʬ��
��common.h��enum�м��뽩ʬtype
�޸�zombies.h�е�MAX_ZOMBIE_NUMBER
��zombies.h����������zombies.cpp�ж���
��common.cpp��GenerateZombies�����м���
*/