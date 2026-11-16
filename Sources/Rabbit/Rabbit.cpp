#include "Rabbit.h"
#include "../World/World.h"

Rabbit::Rabbit(int x, int y, int energy) : x(x), y(y), energy(energy) { }

void Rabbit::act(World& world) {
    energy--;   // 매 턴 에너지 1 감소

    // 1) 이동 : 비어 있는 이웃 칸이 있으면 그쪽으로
    int nx, ny;
    if (world.randomEmptyNeighbor(x, y, nx, ny)) {
        world.moveRabbit(this, nx, ny);
    }

    // 2) 풀 먹기 : 지금 칸에 풀이 있으면 먹는다
    if (world.grass[y][x]) {
        world.grass[y][x] = false;
        energy += RABBIT_EAT;
    }
}