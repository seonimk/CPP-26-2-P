#pragma once

class World;    // 전방 선언

class Fox {
public:
    int x, y;       // 위치
    int energy;     // 에너지
    bool alive;     // 살아있는지

    Fox(int x, int y, int energy);
    void act(World& world);     // 한 턴 행동
};