#include <iostream>
#include <string>
#include <cstdlib>
#include "World.h"
using namespace std;

// 처음 풀 배치 : 칸마다 GRASS_START 확률로 풀이 있음
World::World() {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            grass[x][y] = (rand() % 100) < GRASS_START;
        }
    }
}

// 풀이 없는 칸에 매 턴 GRASS_REGROW 확률로 풀이 다시 날 확률(%)
void World::regrowGrass() {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (!grass[x][y] && (rand() % 100) < GRASS_REGROW) {
                grass[x][y] = true;
            }
        }
    }
}

// 한 턴 진행
void World::step() {
    regrowGrass();
}

// 화면 전체를 문자열 하나에 모았다가 한 번에 출력
void World::Print(int turn) {
    string screen;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (grass[y][x])
                screen += "🌱";
            else
                screen += "  ";
        }
        screen += "\n";
    }
    screen += "Turn: " + to_string(turn) + "\n";
    cout << screen;
}