#include "../include/common.h"

int main(){
    ios::sync_with_stdio(false);
    system("mode con cols=94 lines=32");
    system("title 植物大战僵尸(控制台版)");
    Game newgame;
    newgame.run();
}