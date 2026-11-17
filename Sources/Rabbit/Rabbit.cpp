#include "Rabbit.h"
#include "../World/World.h"

Rabbit::Rabbit(int x, int y, int energy) : x(x), y(y), energy(energy), alive(true) { }

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

    // 3) 번식 : 에너지가 충분하고 옆에 빈 칸이 있으면 에너지를 반으로 나눠 새끼를 낳는다
    if (energy >= RABBIT_BIRTH && world.randomEmptyNeighbor(x, y, nx, ny)) {
        energy /= 2;
        world.addRabbitAt(nx, ny, energy);
    }

    // 4) 죽음 : 에너지가 0 이하면 죽는다 (delete는 턴이 끝난 뒤 World가 한꺼번에)
    if (energy <= 0) {
        world.killRabbit(this);
    }
}