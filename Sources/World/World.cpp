#include <iostream>
#include <string>
#include <cstdlib>
#include "World.h"
#include "../Rabbit/Rabbit.h"
using namespace std;

// 처음 풀 배치 : 칸마다 GRASS_START 확률로 풀이 있음
// 동물 칸은 비워 둠
World::World() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grass[y][x] = (rand() % 100) < GRASS_START;
            cell[y][x] = nullptr;
        }
    }
}

// new로 만든 토끼들을 모두 delete
World::~World() {
    for (Rabbit* r : rabbits) {
        delete r;
    }
}

// 빈 칸을 무작위로 골라 토끼를 count 마리 배치
void World::addRabbits(int count) {
    int added = 0;
    while (added < count) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        if (cell[y][x] == nullptr) {
            Rabbit* r = new Rabbit(x, y, RABBIT_ENERGY);
            rabbits.push_back(r);   // 목록에도 넣고
            cell[y][x] = r;         // 격자에도 넣는다.
            added++;
        }
    }
}

// (x, y)가 격자 안인지
bool World::inside(int x, int y) {
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

// 상하좌우 중 격자 안이고 비어 있는 칸 하나를 무작위로 골라 (nx, ny)에 담기
bool World::randomEmptyNeighbor(int x, int y, int& nx, int& ny) {
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    vector<int> candidates;

    for (int i = 0; i < 4; i++) {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if (inside(tx, ty) && cell[ty][tx] == nullptr) {    // 범위 검사를 먼저!
            candidates.push_back(i);
        }
    }
    if (candidates.empty()) {
        return false;
    }

    int pick = candidates[rand() % candidates.size()];
    nx = x + dx[pick];
    ny = y + dy[pick];
    return true;
}

// 토끼 이동 : 옛 칸 비우기 -> 좌표 바꾸기 -> 새 칸 채우기 (순서대로 셋 다)
void World::moveRabbit(Rabbit* r, int nx, int ny) {
    cell[r->y][r->x] = nullptr;
    r->x = nx;
    r->y = ny;
    cell[ny][nx] = r;
}

// 풀이 없는 칸에 매 턴 GRASS_REGROW 확률로 풀이 다시 날 확률(%)
void World::regrowGrass() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (!grass[y][x] && (rand() % 100) < GRASS_REGROW) {
                grass[y][x] = true;
            }
        }
    }
}

// 한 턴 진행
// 토끼들이 행동한 뒤 풀이 자란다.
void World::step() {
    for (Rabbit* r : rabbits) {
        r->act(*this);
    }
    regrowGrass();
}

// 화면 전체를 문자열 하나에 모았다가 한 번에 출력
void World::Print(int turn) {
    string screen;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (cell[y][x] != nullptr)
                screen += "🐰";     // 토끼를 풀보다 먼저 확인
            else if (grass[y][x])
                screen += "🌱";
            else
                screen += "  ";     // 이모지가 2칸이라 빈 칸도 2개
        }
        screen += "\n";
    }
    screen += "Turn: " + to_string(turn) + "   🐰 " + to_string(rabbits.size()) + "\n";
    cout << screen;
}