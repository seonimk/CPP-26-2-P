#pragma once
#include "../Config.h"
#include <vector>
using namespace std;

class Rabbit;   // 전방 선언
class Fox;      // 전방 선언 

class World {
public:
    bool grass[HEIGHT][WIDTH];      // 칸마다 풀이 있는지 ([y][x] 순서!)
    
    Rabbit* cell[HEIGHT][WIDTH];    // 칸마다 있는 토끼 (없으면 nullptr)
    vector<Rabbit*> rabbits;        // 살아 있는 토끼 목록

    Fox* foxCell[HEIGHT][WIDTH];    // 칸마다 있는 여우 (없으면 nullptr)
    vector<Fox*> foxes;             // 여우 목록

    World();
    ~World();
    
    void addRabbits(int count);  // 토끼를 count마리 추가
    bool inside(int x, int y);
    bool randomEmptyNeighbor(int x, int y, int& nx, int& ny);
    void moveRabbit(Rabbit* r, int nx, int ny);

    void addRabbitAt(int x, int y, int energy);  // (x, y)에 토끼 한 마리 추가
    void killRabbit(Rabbit* r);                  // 죽음 표시 + 격자에서 비우기
    void removeDead();                           // 죽은 토끼 · 여우 delete
    
    void addFoxes(int count);                    // 여우를 count마리 추가
    void moveFox(Fox* f, int nx, int ny);
    void addFoxAt(int x, int y, int energy);     // (x, y)에 여우 한마리 추가
    void killFox(Fox* f);                        // 여우 죽음 표시 + 격자에서 비우기 

    void regrowGrass();     // 풀이 없는 칸에 매 턴 풀이 다시 날 확률(%)
    void step();
    void Print(int turn);
};