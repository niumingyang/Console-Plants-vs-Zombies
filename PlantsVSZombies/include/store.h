#pragma once
#include <string>

class Map;

class PlantCard{
  private:
    std::string name;
    int CD;
    int cnt;
    int price;
    friend class Store;
  public:
    void printName();
    void printPlainName();
    void printPrice();
    void printCD();
    void set(std::string _name, int _CD, int _price);
    void cooling();
    bool cooled();
};

class Store{
  private:
    int sun;
    int speed;
    int cnt;
    int selected;
    PlantCard* allplant;
  public:
    Store();
    int get_sun();
    void printInfo();
    void addSun(int add);
    void run();
    bool pay(int choice, int x, int y, Map &map);
    void restart();
    void initselect();
    void endselect();
    void changeselect(char ch);
};