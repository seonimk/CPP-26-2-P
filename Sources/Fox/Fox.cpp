#include "Fox.h"
#include "../World/World.h"
#include "../Rabbit/Rabbit.h"

Fox::Fox(int x, int y, int energy) : x(x), y(y), energy(energy), alive(true) { }

void Fox::act(World& world) {
    energy--;       // 매 턴 에너지 1 감소

    // 1) 사냥 : 상하좌우에 토끼가 있으면 잡아먹고 그 칸으로 이동 (한 턴에 한 마리만)
    bool ate = false;

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    for (int i = 0; i < 4; i++) {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if (world.inside(tx, ty) && world.cell[ty][tx] != nullptr) {
            world.killRabbit(world.cell[ty][tx]);   // 토끼 죽음 처리 (칸도 비워짐)
            
            world.moveFox(this, tx, ty);            // 빈 칸이 된 그 자리로 이동
            energy += FOX_EAT;
            ate = true;
            break;      // return 대신 break : 번식 · 죽음도 확인해야함
        }
    }

    // 2) 사냥하지 못했으면 빈 칸으로 무작위 이동
    int nx, ny;
    if (world.randomEmptyNeighbor(x, y, nx, ny)) {
        world.moveFox(this, nx, ny);
    }

    // 3) 번식 : 에너지가 충분하고 옆에 빈 칸이 있으면 에너지를 반으로 나눠 새끼들을 낳는다.
    if (energy >= FOX_BIRTH && world.randomEmptyNeighbor(x, y, nx, ny)) {
        energy /= 2;
        world.addFoxAt(nx, ny, energy);
    }

    // 4) 죽음 : 에너지가 0 이하면 죽는다 (delete 는 턴이 끝난 뒤)
    if (energy <= 0) {
        world.killFox(this);
    }
}