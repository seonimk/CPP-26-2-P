#pragma once

class World;    // 전방 선언 (헤더끼리 서로 include 하지 않기 위해)

class Rabbit {
public:
    int x, y;       // 위치
    int energy;     // 에너지

    Rabbit(int x, int y, int energy);
    void act(World& world);     // 한 턴 행동
};