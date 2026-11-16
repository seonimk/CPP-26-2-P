#pragma once
#include "../Config.h"

class World {
public:
    bool grass[WIDTH][HEIGHT];  // 격자에 풀이 있는지 여부

    World();
    void regrowGrass();  // 풀이 없는 칸에 매 턴 풀이 다시 날 확률(%)
    void step();
    void Print(int turn);
};