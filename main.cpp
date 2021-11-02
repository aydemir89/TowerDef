#include "rlutil.h"
#include <ctime>
#include "math.h"

class GameObject{
public:
    int x;
    int y;
    char sym;
    bool ex;
};

class Sentinel: public GameObject{
public:
    int hp;
    int price;
    int uPrice;

    Sentinel(int h, int up, int xp, int yp, char s, bool e){
        hp = h;
        x = xp;
        y = yp;
        sym = s;
        ex = e;
        price = 0;
        uPrice = up;
    }

    void upgrade(){
        if(price >= uPrice){
            price -= uPrice;
            hp += 1;
        }
    }

    void draw(){
        rlutil::setColor(1);
        rlutil::locate(x,y); std::cout << sym;
    }
};

class Gun: public GameObject{
public:
    int dir;

    Gun(int xp, int yp, char s, bool e){
        x = xp;
        y = yp;
        dir = 1;
        sym = s;
        ex = e;
    }

    void changeDir(int dirp){
        if(dirp == 1){
            dir--;
        } else if(dirp == 2){
            dir++;
        }

        if(dir==0){
            dir = 4;
        } else if(dir==5){
            dir = 1;
        }
    }

    void draw(){
        int xn, yn;
        if(dir==1){
            xn = x;
            yn = y-1;
        } else if(dir==2){
            xn = x+1;
            y = y;
        } else if(dir==3){
            xn = x;
            yn = y+1;
        } else if(dir==4){
            xn = x-1;
            yn = y;
        }
        rlutil::setColor(3);
        rlutil::locate(xn,yn); std::cout << sym;
    }
};

class Bullet: public GameObject{
public:
    int oldX;
    int oldY;
    int dir;
    int step;

    Bullet(int xp, int yp, int dirp, char s){
        step = 1;
        x = xp;
        y = yp;
        oldX = xp;
        oldY = yp;
        dir = dirp;
        sym = s;
        ex = false;
    }

    void draw(int rng) {
        if(step >= rng){
            ex = false;
            step = 1;
        }
        if(ex){
            if(dir==1){
                y -= 1;
            } else if(dir==2){
                x += 1;
            } else if(dir==3){
                y += 1;
            } else if(dir==4){
                x -= 1;
            }
            step++;
            rlutil::setColor(14);
            rlutil::locate(x,y); std::cout << sym;
        } else {
            x = oldX;
            y = oldY;
        }
    }
};

class Enemy: public GameObject{
public:
    int oldX;
    int oldY;
    int dir;

    Enemy(int xp, int yp, int dirp, char s){
        x = xp;
        y = yp;
        oldX = xp;
        oldY = yp;
        dir = dirp;
        ex = false;
        sym = s;
    }

    void draw(){
        if(ex){
            if(dir == 1){
                y += 1;
            } else if(dir == 2){
                x -= 1;
            } else if(dir == 3){
                y -= 1;
            } else if(dir == 4){
                x += 1;
            }
            rlutil::setColor(4);
            rlutil::locate(x,y); std::cout << sym;
        } else {
            x = oldX;
            y = oldY;
        }
    }
};

void draw(Sentinel *s, Gun *g, Bullet *b1, Bullet *b2, Bullet *b3, Bullet *b4, Enemy *e1, Enemy *e2, Enemy *e3, Enemy *e4){
    rlutil::cls();
    s->draw();
    g->draw();

    if(b1->y == e1->y || b1->y == e1->y+1){
        e1->ex = false;
        b1->ex = false;
        s->price += 10;
    }
    if(b2->x == e2->x || b2->x == e2->x-1){
        e2->ex = false;
        b2->ex = false;
        s->price += 10;
    }
    if(b3->y == e3->y || b3->y == e3->y-1){
        e3->ex = false;
        b3->ex = false;
        s->price += 10;
    }
    if(b4->x == e4->x || b4->x == e4->x+1){
        e4->ex = false;
        b4->ex = false;
        s->price += 10;
    }

    if(s->y == e1->y+1){
        e1->ex = false;
        s->hp--;
    }
    if(s->x == e2->x-1){
        e2->ex = false;
        s->hp--;
    }
    if(s->y == e3->y+1){
        e3->ex = false;
        s->hp--;
    }
    if(s->x == e4->x+1){
        e4->ex = false;
        s->hp--;
    }
    b1->draw(10);
    b2->draw(10);
    b3->draw(10);
    b4->draw(10);
    e1->draw();
    e2->draw();
    e3->draw();
    e4->draw();
    rlutil::setColor(13);
    rlutil::locate(1,30); std::cout << "HP: " << s->hp << " Price: " << s->price << "\n(A) Turn left. (D) Turn right. (W) Fire. (B) Buy HP (100 Coin).";
    rlutil::msleep(250);
}

int main(){
    rlutil::hidecursor();
    srand((unsigned) time(0));
    while(true){
        Sentinel sn(3, 10, 13, 13, '@', true);
        Gun gn(13, 13, 'o', true);
        Bullet b1(13, 13, 1, '.');
        Bullet b2(13, 13, 2, '.');
        Bullet b3(13, 13, 3, '.');
        Bullet b4(13, 13, 4, '.');
        Enemy e1(13, 0, 1, 's');
        Enemy e2(25, 13, 2, 's');
        Enemy e3(13, 25, 3, 's');
        Enemy e4(0, 13, 4, 's');
        rlutil::cls();
        rlutil::setColor(13);
        printf("TowerDefance\n(A) Turn left. (D) Turn right. (W) Fire. (B) Buy HP (100 Coin).\nPress any key to continue...");
        rlutil::anykey();
        while(true){
            if (kbhit()) {
                char k = getch();
                if (k == 'a'){
                    gn.changeDir(1);
                }
                else if (k == 'd'){
                    gn.changeDir(2);
                } else if (k == 'w'){
                    if(gn.dir == 1){
                        b1.ex = true;
                    } else if(gn.dir == 2){
                        b2.ex = true;
                    } else if(gn.dir == 3){
                        b3.ex = true;
                    } else if(gn.dir == 4){
                        b4.ex = true;
                    }
                } else if(k == 'b'){
                    sn.upgrade();
                }
            }
            int result = 1 + (rand() % 15);
            if(result == 1){
                e1.ex = true;
            } else if(result == 2){
                e2.ex = true;
            } else if(result == 3){
                e3.ex = true;
            } else if(result == 4){
                e4.ex = true;
            }
            draw(&sn, &gn, &b1, &b2, &b3, &b4, &e1, &e2, &e3, &e4);
            if(sn.hp <= 0){
                break;
            }
        }
    }
    return 0;
}
