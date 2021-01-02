#pragma once

class Map;

class Bullet{
  protected:
    int x, y;
    int speed;
    int attack;
    int cnt;
    int kind;
    bool hit;
  public:
    Bullet(int _speed, int _attack, int _x, int _y, int _kind);
    bool get_hit();
    int get_x();
    int get_y();
    void move(Map &m);
};