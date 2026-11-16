#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>    // SetConsoleOutputCP, Sleep
#include "World/World.h"
using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);  // 콘솔 출력 UTF-8로 설정
    srand(time(0));  // 난수 시드 초기화

    World world;
    world.addRabbits(RABBIT_COUNT);  // 토끼 배치

    for (int turn = 1; turn <= 200; turn++) {
        world.step();
        system("cls");  // 화면 지우기
        world.Print(turn);
        Sleep(300);  // 0.3초 대기
    }
    
    return 0;
}