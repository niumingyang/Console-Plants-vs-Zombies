#pragma once
#define MAX_PLANT_NUMBER 10

class Game;

class Plant{
  protected:
    std::string name;
    int x, y;
    int maxHP;
    int HP;
    bool jumpover;//�Ƿ��ܱ��Ÿ˽�ʬԽ��
    bool changepath;//�Ƿ���ʹ��ʬ�ı��·
    bool OnGrassland;//�ܷ����ڲݵ���
    bool OnPlant;//�ܷ�����ֲ����
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
����ֲ�
��common.h�м���enum
��plant.h���޸ĺ�MAX_PLANT_NUMBER
��plant.h��������plant.cpp����
��store.cpp�г�ʼ��PlangCard
��map.cpp��addPlant�����м���choice
��common.h�н���������Ϊ��Ԫ
*/