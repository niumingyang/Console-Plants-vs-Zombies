#include "../include/common.h"

Game::Game(): map(), store(), state(RUNNING), score(0){
    srand(time(0));
    cd = 100;
	cnt = 0;
    scd = 10;
    scnt = 0;
    selected_x = selected_y = 0;
}

void Game::running(){
    char ch;
	if (_kbhit()){
		ch = _getch();
		switch (ch){
			case 'b':case 'B':
				state = CHOOSING;
                selected_x = selected_y = 0;
                map.blocks[selected_x][selected_y].selected = true;
				break;
            case 'r':case 'R':
                state = REMOVING;
                selected_x = selected_y = 0;
                map.blocks[selected_x][selected_y].selected = true;
				break;
			default: break;
		}
	}
}

void Game::choosing(){
    char ch;
    if (_kbhit()){
        ch = _getch();
        if (ch >= 48 && ch <= 57){
            int PlantNumber = (int)ch - 48;
            if (store.pay(PlantNumber, selected_x, selected_y, map)) {
                map.blocks[selected_x][selected_y].selected = false;
                state = RUNNING;
			}
        }
        else switch(ch){
            case 72:// up
                if (selected_x > 0){
                    map.blocks[selected_x][selected_y].selected = false;
                    selected_x--;
                    map.blocks[selected_x][selected_y].selected = true;
                }
                break;
            case 80:// down
                if (selected_x < ALL_ROW-1){
                    map.blocks[selected_x][selected_y].selected = false;
                    selected_x++;
                    map.blocks[selected_x][selected_y].selected = true;
                }
                break;
            case 75:// left
                if (selected_y > 0){
                    map.blocks[selected_x][selected_y].selected = false;
                    selected_y--;
                    map.blocks[selected_x][selected_y].selected = true;
                }
                break;
            case 77:// right
                if (selected_y < ALL_COLUMN-1){
                    map.blocks[selected_x][selected_y].selected = false;
                    selected_y++;
                    map.blocks[selected_x][selected_y].selected = true;
                }
                break;
            case 27:// Esc
                map.blocks[selected_x][selected_y].selected = false;
                state = RUNNING;
                break;
            case '\r':// Enter
                state = BUYING;
			    break;
            default: break;
        }
    }
}

void Game::buying(){
    char ch;
    store.initselect();
    if (_kbhit()){
        ch = _getch();
        if (ch >= 48 && ch <= 57){
            int PlantNumber = (int)ch - 48;
            if (store.pay(PlantNumber, selected_x, selected_y, map)) {
                map.blocks[selected_x][selected_y].selected = false;
                store.endselect();
                state = RUNNING;
			}
        }
        
        else switch(ch){
            case 72:// up
            case 80:// down
            case 75:// left
            case 77:// right
                store.changeselect(ch);
                break;
            case 27:// Esc
                map.blocks[selected_x][selected_y].selected = false;
                store.endselect();
                state = RUNNING;
                break;
            case '\r':// Enter
                if (store.pay(-1, selected_x, selected_y, map)) {
                    map.blocks[selected_x][selected_y].selected = false;
                    store.endselect();
                    state = RUNNING;
			    }
                break;
            default: break;
        }
    }
}

void Game::removing(){
    char ch;
    if (_kbhit()){
        ch = _getch();
        switch(ch){
            case 72:// up
                if (selected_x > 0){
                    map.blocks[selected_x][selected_y].selected = false;
                    selected_x--;
                    map.blocks[selected_x][selected_y].selected = true;
                }
                break;
            case 80:// down
                if (selected_x < ALL_ROW-1){
                    map.blocks[selected_x][selected_y].selected = false;
                    selected_x++;
                    map.blocks[selected_x][selected_y].selected = true;
                }
                break;
            case 75:// left
                if (selected_y > 0){
                    map.blocks[selected_x][selected_y].selected = false;
                    selected_y--;
                    map.blocks[selected_x][selected_y].selected = true;
                }
                break;
            case 77:// right
                if (selected_y < ALL_COLUMN-1){
                    map.blocks[selected_x][selected_y].selected = false;
                    selected_y++;
                    map.blocks[selected_x][selected_y].selected = true;
                }
                break;
            case 27:// Esc
                map.blocks[selected_x][selected_y].selected = false;
                state = RUNNING;
                break;
            case '\r':// Enter
                if (map.blocks[selected_x][selected_y]._plant != nullptr){
                    map.blocks[selected_x][selected_y].delPlant();
                    map.blocks[selected_x][selected_y].selected = false;
                    state = RUNNING;
                }
			    break;
            default: break;
        }
    }
}

void Game::gameover(){
    printscreen();
    cout << _BOLD << _YELLOW << "游戏结束!!!   按下Enter键以重新开始..." << _NONE << endl;
    char ch;
	if (_kbhit()){
		ch = _getch();
		switch (ch){
			case '\r':// Enter
				state = RUNNING;
                score = 0;
                cnt = 0;
                scnt = 0;
                selected_x = selected_y = 0;
                map.restart();
                store.restart();
                for (auto it = bullets.begin(); it != bullets.end(); ){
			        delete (*it);
			        it = bullets.erase(it);
	            }
                for (auto it = zombies.begin(); it != zombies.end(); ){
			        delete (*it);
			        it = zombies.erase(it);
	            }
				break;
			default: break;
		}
	}
}

void Game::GenerateZombies(){
    cnt++;
	if (cnt >= cd) {
        cnt = 0;
        Zombie* newZombie = nullptr;
        int x = rand()%ALL_ROW;
        int y = ALL_COLUMN;
        int type = rand()%MAX_ZOMBIE_NUMBER;
        switch(type){
            case ZOMBIE:       newZombie = new NormalZombie(x, y);       break;
            case CONEHEAD:     newZombie = new ConeheadZombie(x, y);     break;
            case NEWSPAPER:    newZombie = new NewspaperZombie(x, y);    break;
            case POLEVAULTING: newZombie = new PoleVaultingZombie(x, y); break;
            case JACKINTHEBOX: newZombie = new JackInTheBoxZombie(x, y); break;
            case CATAPULT:     newZombie = new CatapultZombie(x, y);     break;
        }
        map.blocks[x][y].addZombie(newZombie);
		zombies.push_back(newZombie);
	}
}

void Game::MoveBullet(){
    for (auto& var : bullets) {
		var->move(map);
	}
	for (auto it = bullets.begin(); it != bullets.end(); ){
		if ((*it)->get_hit()){
			delete (*it);
			it = bullets.erase(it);
		}
		else it++;
	}
}

void Game::AddBullet(Bullet* p){
    bullets.push_back(p);
}

bool Game::UpdateZombie(){
    for (auto& var : zombies)
        if (var->run(map))
            return true;
	return false;
}

void Game::DelZombie(){
	for (auto it = zombies.begin(); it != zombies.end(); ){
		if ((*it)->get_HP() <= 0){
			score += (*it)->get_score();
			map.blocks[(*it)->get_x()][(*it)->get_y()].delZombie(*it);
			delete (*it);
			it = zombies.erase(it);
		}
		else it++;
	}
}

void Game::updatescore(){
    scnt++;
	if (scnt >= scd) {
		scnt = 0;
		score += 10;
	}
}

void Game::printscreen(){
    system("cls");
    for (int i = 0; i < ALL_ROW; ++i){
        for (int j = 0; j <= ALL_COLUMN; ++j)
            cout << "###########";
        cout << "######";
        cout << '\n';
        
        for (int j = 0; j <= ALL_COLUMN; ++j){
            if (map.blocks[i][j].plantonplant != nullptr){
                if (map.blocks[i][j].zombies.size()==0)
                    map.blocks[i][j].plantonplant->printName(WHITE);
                else map.blocks[i][j].plantonplant->printName(RED);
                map.blocks[i][j].plantonplant->printHP();
            }
            else cout << "#          ";
        }
        cout << '\n';

        for (int j = 0; j <= ALL_COLUMN; ++j){
            if (map.blocks[i][j]._plant != nullptr){
                if (map.blocks[i][j].zombies.size()>0 && map.blocks[i][j].plantonplant == nullptr)
                    map.blocks[i][j]._plant->printName(RED);
                else map.blocks[i][j]._plant->printName(WHITE);
            }
            else {
                if (map.blocks[i][j].zombies.size()>0){
                    if (map.blocks[i][j].zombies.size() == 1)
                        map.blocks[i][j].zombies[0]->printName(ANY);
                    else cout << "#   僵尸   ";
                }
                else if (map.blocks[i][j].bullets.size()>0){
                    if (map.blocks[i][j].bullets.size()==1)
                        cout << "#    〇    ";
                    else if (map.blocks[i][j].bullets.size()==2)
                        cout << "#   〇〇   ";
                    else if (map.blocks[i][j].bullets.size()>=3)
                        cout << "#  〇〇〇  ";
                }
                else cout << "#          ";
            }
            
        }
        cout << '\n';

        for (int j = 0; j <= ALL_COLUMN; ++j){
            if (map.blocks[i][j]._plant != nullptr){
                map.blocks[i][j]._plant->printHP();
            }
            else {
                if (map.blocks[i][j].zombies.size()>1){
                    if (map.blocks[i][j].zombies.size()<10)
                        cout << "#   X  " << map.blocks[i][j].zombies.size() << "   ";
                    else cout << "   ....   ";
                }
                else if (map.blocks[i][j].zombies.size()==1)
                    map.blocks[i][j].zombies[0]->printHP();
                else cout << "#          ";
            }
            
        }
        cout << '\n';

        for (int j = 0; j <= ALL_COLUMN; ++j)
            if (map.blocks[i][j].selected) cout << "#    " << _YELLOW << "**" << _NONE << "    ";
            else cout << "#          ";
        cout << '\n'; 
    }
    for (int i = 0; i < 94; ++i)
        cout << '#';
    
    cout << "\n\n\n";

    for (int i = 0; i < 94; ++i)
        cout << '=';
    cout << '\n';

    cout << "[商店]     阳光: " << store.get_sun() <<  "     得分: " << score << '\n';
    
    for (int i = 0; i < 94; ++i)
        cout << '-';
    cout << '\n';

    store.printInfo();

    for (int i = 0; i < 94; ++i)
        cout << '=';
    cout << '\n';

    cout << "购买： b 键选择地块，↑ ↓ ← → 键选择植物， Enter 键购买， Esc 键退出购买模式\n";
    cout << "铲除： r 键开始选择，↑ ↓ ← → 键选择地块， Enter 键铲除， Esc 键退出铲除模式\n";
    
    for (int i = 0; i < 94; ++i)
        cout << '=';
    cout << endl;
}

void Game::run(){
    clock_t last, next;
    last = clock();
    while(true){
        next = clock();
        if ((next-last)*10>=CLOCKS_PER_SEC){
            last = next;
            // update with input
            if (state == RUNNING){
                running();
            }
            else if (state == CHOOSING){
                choosing();
            }
            else if (state == BUYING){
                buying();
            }
            else if (state == REMOVING){
                removing();
            }
            else if (state == GAMEOVER){
                gameover();
                continue;
            }
            // generate zombies
            GenerateZombies();
            // update plant
            map.update(*this);
            DelZombie();
            // update bullets and zombies
            if (UpdateZombie()) {
			    state = GAMEOVER;
		    }
            MoveBullet();
            DelZombie();
            // update store
            store.run();
            // update score
            updatescore();
            // print screen
            printscreen();
        }
    }
}